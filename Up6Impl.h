#pragma once
#pragma warning (disable : 4146)
#import "HttpUploaderApp.tlb" named_guids, raw_interfaces_only
//#import "Xproer.HttpPartition6.1" no_namespace, raw_interfaces_only

//#include "HttpUploaderApp_p.c"
#include "HttpUploaderApp_i.h"
//#include "HttpUploaderApp_i.c"
class ThreadMessage;
class CMainDlg;

/*
   使用：
   Up6Impl* up6 = new Up6Impl();
   //绑定事件
   up6->entSelFile.connect(boost::bind(&CMainDlg::up6_sel_files, this, _1, _2));
   //调用接口
   up6->openFiles();
*/
class Up6Impl : public IDispEventImpl<0,Up6Impl,&DIID__IHttpPartitionEvents,&LIBID_HttpUploaderAppLib,1,0>
{
	typedef struct _datadef
	{
		ThreadMessage* tm;
		CMainDlg* dlg;
	}DataDef;
public:
	Up6Impl(CMainDlg* dlg);
	~Up6Impl();

	STDMETHOD(recvMessage)(BSTR msg);

	BEGIN_SINK_MAP(Up6Impl)
		SINK_ENTRY_EX(0, DIID__IHttpPartitionEvents, 1, recvMessage)
	END_SINK_MAP()

	boost::signals2::signal<void(Json::Value&)> entSelFile;
	boost::signals2::signal<void(Json::Value&)> entSelFolder;
	boost::signals2::signal<void(Json::Value&)> entUpdateFolderComplete;
	boost::signals2::signal<void(Json::Value&)> entAddFolderErr;

public:
	//api
	void init(Json::Value& cfg);
	void getVersion();
	void openFiles();
	void openFolders();
	void pasteFiles();
	void addFileLoc(const wstring& pathLoc);
	void postMessage(const string& v);
	void postMessage(const Json::Value& v);

private:
	//event
	void ent_open_files(Json::Value& val);
	void ent_open_folders(Json::Value& val);
	void ent_post_process(Json::Value val);
	void ent_post_error(Json::Value val);
	void ent_post_complete(Json::Value val);
	void ent_post_stoped(Json::Value val);
	void ent_scan_process(Json::Value val);
	void ent_scan_complete(Json::Value val);
	void ent_update_folder_complete(Json::Value val);
	void ent_md5_process(Json::Value val);
	void ent_md5_complete(Json::Value val);
	void ent_md5_error(Json::Value val);
	void ent_add_folder_error(Json::Value val);
	void ent_load_complete(Json::Value val);

private:
	CComPtr<IUnknown> up6Ptr;
	CComDispatchDriver up6Cmp;//
	bool m_inited;//初始化
	DataDef data;
};