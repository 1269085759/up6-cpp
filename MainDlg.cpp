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

	this->up6_component_init();

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
	this->up6_component_release();
	// TODO: Add validation code 
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	this->up6_component_release();
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::openFile_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	/*CLSID clsid;
	HRESULT hr = ::CLSIDFromProgID(L"Xproer.HttpPartition6.1", &clsid);
	if (!SUCCEEDED(hr))
	{
		MessageBoxW(L"创建组件失败，请先安装或注册组件", L"错误", MB_OK);
		return 0;
	}

	CComPtr < IUnknown > spUnk;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID *)&spUnk);
	CComDispatchDriver up6 = spUnk;
	this->up6Cmp = spUnk;
	this->m_up6Ent = std::make_shared<up6Event>();
	this->m_up6Ent->entSelFile.connect(boost::bind(&CMainDlg::up6_sel_files, this, _1, _2));
	this->m_up6Ent->DispEventAdvise(spUnk);*/

	CComVariant version;
	this->up6Cmp.GetPropertyByName(L"Version", &version);

	std::wstring js = L"{\"name\":\"open_files\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,			
		&ret);

	return 0;
}

LRESULT CMainDlg::openFolder_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	std::wstring js = L"{\"name\":\"open_folders\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
	return 0;
}

void CMainDlg::up6_component_init()
{
	CLSID clsid;
	HRESULT hr = ::CLSIDFromProgID(L"Xproer.HttpPartition6.1", &clsid);
	if (!SUCCEEDED(hr))
	{
		MessageBoxW(L"创建组件失败，请先安装或注册组件", L"错误", MB_OK);
		return;
	}

	//CComPtr < IUnknown > spUnk;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID *)&this->spUp6);
	//CComDispatchDriver up6 = spUnk;
	this->up6Cmp = this->spUp6;
	this->m_up6Ent = std::make_shared<up6Event>();
	this->m_up6Ent->entSelFile.connect(boost::bind(&CMainDlg::up6_sel_files, this, _1, _2));
	this->m_up6Ent->entSelFolder.connect(boost::bind(&CMainDlg::up6_sel_folder, this, _1));
	this->m_up6Ent->entPostProcess.connect(boost::bind(&CMainDlg::up6_post_process, this, _1));
	this->m_up6Ent->entPostError.connect(boost::bind(&CMainDlg::up6_post_error, this, _1));
	this->m_up6Ent->entPostComplete.connect(boost::bind(&CMainDlg::up6_post_complete, this, _1));
	this->m_up6Ent->entPostStoped.connect(boost::bind(&CMainDlg::up6_post_stoped, this, _1));
	this->m_up6Ent->entScanProcess.connect(boost::bind(&CMainDlg::up6_scan_process, this, _1));
	this->m_up6Ent->entScanComplete.connect(boost::bind(&CMainDlg::up6_scan_complete, this, _1));
	this->m_up6Ent->entUpdateFolderComplete.connect(boost::bind(&CMainDlg::up6_update_fd_complete, this, _1));
	this->m_up6Ent->entMd5Process.connect(boost::bind(&CMainDlg::up6_md5_process, this, _1));
	this->m_up6Ent->entMd5Complete.connect(boost::bind(&CMainDlg::up6_md5_complete, this, _1));
	this->m_up6Ent->entMd5Error.connect(boost::bind(&CMainDlg::up6_md5_error, this, _1));
	this->m_up6Ent->entLoadComplete.connect(boost::bind(&CMainDlg::up6_load_complete, this, _1));
	this->m_up6Ent->DispEventAdvise(this->spUp6);
}

void CMainDlg::up6_component_release()
{
	this->m_up6Ent->DispEventUnadvise(spUp6);
}

void CMainDlg::up6_sel_files(std::string fileName, std::string filePath)
{
	this->m_edtMsg.AppendText(L"文件名称：");
	this->m_edtMsg.AppendText(Encoder::from_utf8(fileName).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
	this->m_edtMsg.AppendText(L"文件路径：");
	this->m_edtMsg.AppendText(Encoder::from_utf8(filePath).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
}

void CMainDlg::up6_sel_folder(Json::Value& v)
{
	std::string id = v.get("id", "").asString();
	std::string nameLoc = v.get("nameLoc", "").asString();
	std::string pathLoc = v.get("pathLoc", "").asString();

	this->m_edtMsg.AppendText(L"目录名称：");
	this->m_edtMsg.AppendText(Encoder::from_utf8(nameLoc).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
	this->m_edtMsg.AppendText(L"目录路径：");
	this->m_edtMsg.AppendText(Encoder::from_utf8(pathLoc).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
}

void CMainDlg::up6_post_process(Json::Value& v)
{

}

void CMainDlg::up6_post_error(Json::Value& v)
{

}

void CMainDlg::up6_post_complete(Json::Value& v)
{

}

void CMainDlg::up6_post_stoped(Json::Value& v)
{

}

void CMainDlg::up6_scan_process(Json::Value& v)
{

}

void CMainDlg::up6_scan_complete(Json::Value& v)
{

}

void CMainDlg::up6_update_fd_complete(Json::Value& v)
{

}

void CMainDlg::up6_md5_process(Json::Value& v)
{

}

void CMainDlg::up6_md5_complete(Json::Value& v)
{

}

void CMainDlg::up6_md5_error(Json::Value& v)
{

}

void CMainDlg::up6_add_folder_err(Json::Value& v)
{

}

void CMainDlg::up6_load_complete(Json::Value& v)
{

}
