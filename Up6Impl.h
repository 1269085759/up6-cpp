#pragma once
#pragma warning (disable : 4146)
#import "F:\xproeratl\up6\code\x86\atl\obj\Debug\HttpUploaderApp.tlb" named_guids, raw_interfaces_only
//#import "Xproer.HttpPartition6.1" no_namespace, raw_interfaces_only

//#include "HttpUploaderApp_p.c"
#include "HttpUploaderApp_i.h"
//#include "HttpUploaderApp_i.c"

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
public:
	Up6Impl();
	~Up6Impl();

	STDMETHOD(recvMessage)(BSTR msg);

	BEGIN_SINK_MAP(Up6Impl)
		SINK_ENTRY_EX(0, DIID__IHttpPartitionEvents, 1, recvMessage)
	END_SINK_MAP()

	boost::signals2::signal<void(string, string)> entSelFile;
	boost::signals2::signal<void(Json::Value&)> entSelFolder;
	boost::signals2::signal<void(Json::Value&)> entPostProcess;
	boost::signals2::signal<void(Json::Value&)> entPostError;
	boost::signals2::signal<void(Json::Value&)> entPostComplete;
	boost::signals2::signal<void(Json::Value&)> entPostStoped;
	boost::signals2::signal<void(Json::Value&)> entScanProcess;
	boost::signals2::signal<void(Json::Value&)> entScanComplete;
	boost::signals2::signal<void(Json::Value&)> entUpdateFolderComplete;
	boost::signals2::signal<void(Json::Value&)> entMd5Process;
	boost::signals2::signal<void(Json::Value&)> entMd5Complete;
	boost::signals2::signal<void(Json::Value&)> entMd5Error;
	boost::signals2::signal<void(Json::Value&)> entAddFolderErr;
	boost::signals2::signal<void(Json::Value&)> entLoadComplete;

public:
	//api
	void init(const wstring& cfgFile);
	void getVersion();
	void openFiles();
	void openFolders();
	void pasteFiles();
	void addFileLoc(const wstring& pathLoc);

private:
	//event
	void ent_open_files(Json::Value& val);
	void ent_open_folders(Json::Value& val);
	void ent_post_process(Json::Value& val);
	void ent_post_error(Json::Value& val);
	void ent_post_complete(Json::Value& val);
	void ent_post_stoped(Json::Value& val);
	void ent_scan_process(Json::Value& val);
	void ent_scan_complete(Json::Value& val);
	void ent_update_folder_complete(Json::Value& val);
	void ent_md5_process(Json::Value& val);
	void ent_md5_complete(Json::Value& val);
	void ent_md5_error(Json::Value& val);
	void ent_add_folder_error(Json::Value& val);
	void ent_load_complete(Json::Value& val);

private:
	CComPtr<IUnknown> up6Ptr;
	CComDispatchDriver up6Cmp;//
	bool m_inited;//初始化
};