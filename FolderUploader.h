#pragma once

class FolderUploader : public FileUploader
{
public:
	FolderUploader(Up6Impl* up6, CMainDlg* dlg);
	virtual ~FolderUploader();

	//methods
	virtual void post();
	void scan();
	void init_folder();
	void init_error();
	void init_complete();
	void update_info();

	//ent
	virtual void scan_process(Json::Value v);
	virtual void scan_complete(Json::Value v);
	virtual void post_process(Json::Value v);
	virtual void post_complete(Json::Value v);
	virtual void post_error(Json::Value v);
	virtual void post_stoped(Json::Value v);
};