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
	string time;//剩余时间
	string speed;//速度
	string lenPost;//已传大小
	string percent;//md5进度(已传进度)
	string err;
	bool complete;
	bool deleted;
};