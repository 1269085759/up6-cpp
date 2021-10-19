#include "stdafx.h"
#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

string Utils::ReadAll(const wstring& path, long& fileLength)
{
	fileLength = 0;
	boost::shared_array<char> buf;

	HANDLE hFile = CreateFileW(path.c_str(),// name of the write
		GENERIC_READ,          // open for writing
		FILE_SHARE_READ,       // do not share
		NULL,                   // default security
		OPEN_EXISTING,          // overwrite existing
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ATLTRACE("打开文件错误\n");
		return "";
	}

	LARGE_INTEGER fileLen; // length of file
	GetFileSizeEx(hFile, &fileLen);
	fileLength = (long)fileLen.QuadPart;
	buf.reset(new char[fileLength + 1]);
	ZeroMemory(buf.get(), fileLength + 1);

	DWORD bytesRead = 0;
	ReadFile(hFile, buf.get(), fileLength, &bytesRead, NULL);
	CloseHandle(hFile);
	string str = buf.get();
	return str;
}

BOOL Utils::WriteAll(const wstring& path, const string& data)
{
	HANDLE hFile = CreateFileW(path.c_str(),// name of the write
		GENERIC_WRITE,          // open for writing
		0,       // do not share
		NULL,                   // default security
		CREATE_ALWAYS,          // overwrite existing
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ATLTRACE("打开文件错误\n");
		return FALSE;
	}

	DWORD bytesWrite = 0;
	BOOL ret = WriteFile(hFile, data.c_str(), data.length(), &bytesWrite, NULL);
	CloseHandle(hFile);
	return ret;
}

string Utils::to_utf8(const wstring& v)
{
	UINT code = CP_UTF8 ;
	int u8Len = ::WideCharToMultiByte(code, NULL, v.c_str(), -1, NULL, 0, NULL, NULL);
	char* szU8 = new char[u8Len + 1];
	ZeroMemory(szU8, u8Len + 1);
	::WideCharToMultiByte(code, NULL, v.c_str(), -1, szU8, u8Len, NULL, NULL);

	string stra = szU8;
	delete[] szU8;
	return stra;
}

wstring Utils::from_utf8(const string& a)
{
	UINT code = CP_UTF8;
	int len = MultiByteToWideChar(code, 0, a.c_str(), -1, NULL, NULL);
	boost::shared_array<wchar_t> data(new wchar_t[len + 1]);
	ZeroMemory(data.get(), len + 1);
	MultiByteToWideChar(code, 0, a.c_str(), -1, data.get(), len);
	wstring w = data.get();
	return w;
}

string Utils::url_decode(const string& src)
{
	std::string dst, dsturl;

	int srclen = src.size();

	for (size_t i = 0; i < srclen; i++)
	{
		if (src[i] == '%')
		{
			if (isxdigit(src[i + 1]) && isxdigit(src[i + 2]))
			{
				char c1 = src[++i];
				char c2 = src[++i];
				c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
				c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
				dst += (unsigned char)(c1 * 16 + c2);
			}
		}
		else
			if (src[i] == '+')
			{
				dst += ' ';
			}
			else
			{
				dst += src[i];
			}
	}

	return dst;
}

/*
 Method:    当前目录
 D:\\Soft\\
 FullName:  Utils::curDir
 Access:    public static 
 Returns:   wstring
 Qualifier:
*/
wstring Utils::curDir()
{
	wchar_t buf[MAX_PATH] = { 0 };
	DWORD ret = ::GetModuleFileNameW(NULL, buf, MAX_PATH);
	if (ret == 0) return FALSE;

	wstring path = buf;
	auto pos = path.find_last_of(L"\\") + 1;
	path = path.erase(pos);
	return path;
}

/*
 Method:    清理注释
 所有 // \r
 FullName:  Utils::clearComment
 Access:    public static 
 Returns:   
 Qualifier:
 Parameter: string & v
*/
void Utils::clearComment(string& v)
{
	list<std::pair<size_t/*begin*/,size_t/*end*/>> tags;

	for (size_t i = 0 ,l=v.length();i<l;++i)
	{
		if (v[i] == '\"')
		{
			//跳过字符串
			while (++i<l)
			{
				if (v[i] == '\"')break;
			}
		}//注释标签开始1
		else if (v[i] == '/')
		{
			size_t pos = i;
			if (++i<l)
			{
				//不是注释字符
				if (v[i]!='/') continue;
			}

			while (++i<l)
			{
				if (v[i]=='\r')
				{
					tags.push_front(std::make_pair(pos, i));
					break;
				}
			}
		}
	}

	for (auto& t : tags)
	{
		v.erase(t.first, t.second - t.first);
	}
}

bool Utils::parse(const string& v, Json::Value& json)
{
	try
	{
		Json::Reader reader;
		return reader.parse(v, json);
	}
	catch (std::exception& e)
	{
	}
	return false;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	string data((const char*)ptr, (size_t)size * nmemb);

	*((stringstream*)stream) << data;

	return size * nmemb;
}

/*
 Method:    http请求
 FullName:  Utils::http_get
 Access:    public static 
 Returns:   bool
 Qualifier:
 Parameter: const string & url
 Parameter: map<string
 Parameter: string> & header
*/
bool Utils::http_get(string url, mapStrPtr hd, string& svr_res)
{
	bool hr = false;
	std::stringstream response;
	CURL *curl = curl_easy_init();
	if (curl) {

		//拼接查询参数
		list<string> qs;
		for (auto& h : *hd)
		{
			qs.push_back( h.first + "=" + h.second);
		}
		url = url + "?" + boost::join(qs, "&");

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		/* Perform the request, res will get the return code */
		CURLcode res = curl_easy_perform(curl);
		int httpstate = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpstate);
		hr = res == CURLE_OK;
		if (hr) hr = 200 == httpstate;
		/* Check for errors */
		if(hr)
		{
			svr_res = response.str();
			svr_res = Utils::url_decode(svr_res);
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return hr;
}
