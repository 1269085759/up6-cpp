#pragma once
#pragma warning (disable : 4146)
#import "F:\xproeratl\up6\code\x86\atl\obj\Debug\HttpUploaderApp.tlb" named_guids, raw_interfaces_only
//#import "Xproer.HttpPartition6.1" no_namespace, raw_interfaces_only

//#include "HttpUploaderApp_p.c"
#include "HttpUploaderApp_i.h"
//#include "HttpUploaderApp_i.c"

class up6Event : public IDispEventImpl<0,up6Event,&DIID__IHttpPartitionEvents,&LIBID_HttpUploaderAppLib,1,0>
{
public:
	up6Event();
	~up6Event();

	STDMETHOD(recvMessage)(BSTR msg);

	BEGIN_SINK_MAP(up6Event)
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

private:
	void open_files(Json::Value& val);
	void open_folders(Json::Value& val);
	void post_process(Json::Value& val);
	void post_error(Json::Value& val);
	void post_complete(Json::Value& val);
	void post_stoped(Json::Value& val);
	void scan_process(Json::Value& val);
	void scan_complete(Json::Value& val);
	void update_folder_complete(Json::Value& val);
	void md5_process(Json::Value& val);
	void md5_complete(Json::Value& val);
	void md5_error(Json::Value& val);
	void add_folder_error(Json::Value& val);
	void load_complete(Json::Value& val);
};