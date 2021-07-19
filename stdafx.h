// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#include <atlbase.h>
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
using namespace std;
#include <boost/signals2/signal.hpp>
using namespace boost::signals2;

#define BIZ_MESSAGE (WM_USER + 100)

#include "json/json.h"
#include "core-head.h"
#include "Utils.h"
#include "Up6Impl.h"
#include "FileData.h"
#include "components/MsgCenter.h"
#include "components/MsgData.h"
#include "components/ThreadMessage.h"
#include "link-json.h"
#include "link-core.h"
#include "link-crypt.h"