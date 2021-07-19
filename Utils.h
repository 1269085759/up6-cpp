#pragma once

/*
   常用工具类
*/
class Utils
{
public:
	Utils();
	~Utils();

	static boost::shared_array<char> ReadAll(const wstring& path, long& fileLength);
	static string to_utf8(const wstring& v) { return ""; }
	static wstring from_utf8(const string& a);
	static wstring curDir(){}
};