#pragma once

/*
   �ļ�����
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
	bool f_fdTask;//�Ƿ���Ŀ¼
	bool f_fdChild;//�Ƿ����ļ�
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
	string time;//ʣ��ʱ��
	string speed;//�ٶ�
	string lenPost;//�Ѵ���С
	string percent;//md5����(�Ѵ�����)
	string err;
	bool complete;
	bool deleted;
};