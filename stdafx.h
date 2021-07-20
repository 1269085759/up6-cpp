// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#include <atlbase.h>
#include <atlstr.h>
#include <atltypes.h>
#include <atlapp.h>

extern CAppModule _Module;
#include <atlcom.h>
#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <string>
#include <memory>
#include <map>
using namespace std;

#include <boost/serialization/singleton.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/assign.hpp>
#include <boost/function.hpp>
#include <boost/any.hpp>
#include <boost/unordered_map.hpp>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/shared_array.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>
using namespace boost::assign;
using namespace boost::signals2;

#define BIZ_MESSAGE (WM_USER + 100)

#include "json/json.h"
#include "Utils.h"
#include "Up6Impl.h"
#include "FileData.h"
#include "components/MsgCenter.h"
#include "components/MsgData.h"
#include "components/ThreadMessage.h"
#include "link-json.h"
#include "link-core.h"
#include "link-crypt.h"