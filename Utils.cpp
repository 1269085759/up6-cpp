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
