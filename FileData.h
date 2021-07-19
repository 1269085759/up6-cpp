#pragma once

/*
   文件数据
*/
class FileData
{
public:
	FileData();
	~FileData();

public:
	string id;
	string pid;
	string pidRoot;//
	bool f_fdTask;//是否是目录
	bool f_fdChild;//是否子文件
	int uid;
	string nameLoc;
	string nameSvr;
	string pathLoc;
	string pathSvr;
	string pathRel;
	string md5;
	__int64 lenLoc;
	__int64 lenSvr;
	string sizeLoc;
	string perSvr;
	bool complete;
	bool deleted;
};