#pragma once

/*
   常用工具类
*/
class Utils
{
public:
	Utils();
	~Utils();

	static string ReadAll(const wstring& path, long& fileLength);
	static BOOL WriteAll(const wstring& path, const string& data);
	static string to_utf8(const wstring& v);
	static wstring from_utf8(const string& a);
	static wstring curDir();
	static void clearComment(string& v);
};