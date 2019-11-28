// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "up6Event.h"

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	this->m_btnOpenFile.Attach(this->GetDlgItem(BTN_OPENFILE));
	this->m_edtMsg.Attach(this->GetDlgItem(TB_FILES));

	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::openFile_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CLSID clsid;
	HRESULT hr = ::CLSIDFromProgID(L"Xproer.HttpPartition6.1", &clsid);
	if (!SUCCEEDED(hr))
	{
		MessageBoxW(L"创建组件失败，请先安装或注册组件", L"错误", MB_OK);
		return 0;
	}

	CComPtr < IUnknown > spUnk;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID *)&spUnk);
	CComDispatchDriver up6 = spUnk;
	this->m_up6Ent = std::make_shared<up6Event>();
	this->m_up6Ent->m_entFilesOpen.connect(boost::bind(&CMainDlg::files_opend, this, _1, _2));
	this->m_up6Ent->DispEventAdvise(spUnk);

	CComVariant version;
	up6.GetPropertyByName(L"Version", &version);

	std::wstring js = L"{\"name\":\"open_files\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	hr = up6.Invoke1(
		L"postMessage",
		&v1,			
		&ret);		

	this->m_up6Ent->DispEventUnadvise(spUnk);

	return 0;
}