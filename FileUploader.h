#pragma once

class CMainDlg;
/*
   文件上传对象
*/
class FileUploader
{
	typedef struct _datadef
	{
		FileData fileSvr;
		Up6Impl* up6;
		CMainDlg* dlg;
		ThreadMessage* tm;
		MsgCenter* mc;
		Json::Value cfg;
	}DataDef;
public:
	FileUploader(Up6Impl* up6,CMainDlg* dlg);
	~FileUploader();

	//methods
	void check_file();
	void init_file();
	void init_file_complete();
	void init_file_error();
	virtual void post();

	//ent
	void md5_process(Json::Value v);
	void md5_complete(Json::Value v);
	void md5_error(Json::Value v);
	virtual void scan_process(Json::Value v){}
	virtual void scan_complete(Json::Value v){}
	virtual void post_process(Json::Value v);
	virtual void post_complete(Json::Value v);
	virtual void post_error(Json::Value v);
	virtual void post_stoped(Json::Value v);

public:
	DataDef data;
};