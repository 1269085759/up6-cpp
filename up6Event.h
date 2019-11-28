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

	boost::signals2::signal<void(string fn, string ps)> m_entFilesOpen;
};