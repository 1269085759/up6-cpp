#include "stdafx.h"
#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

boost::shared_array<char> Utils::ReadAll(const wstring& path, long& fileLength)
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
		return buf;
	}

	LARGE_INTEGER fileLen; // length of file
	GetFileSizeEx(hFile, &fileLen);
	fileLength = (long)fileLen.QuadPart;
	buf.reset(new char[fileLength + 1]);
	ZeroMemory(buf.get(), fileLength + 1);

	DWORD bytesRead = 0;
	ReadFile(hFile, buf.get(), fileLength, &bytesRead, NULL);
	CloseHandle(hFile);
	return buf;
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