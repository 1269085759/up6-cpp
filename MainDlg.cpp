// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "Up6Impl.h"
#include "FileUploader.h"

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

	//
	this->data.tm = &ThreadMessage::get();
	this->data.mc = &MsgCenter::get();

	//bind msg
	this->data.tm->m_form = m_hWnd;
	boost::assign::insert(this->data.tm->m_handler)
		("md5_process", boost::bind(&CMainDlg::up6_md5_process, this, _1))
		("md5_complete", boost::bind(&CMainDlg::up6_md5_complete, this, _1))
		("md5_error", boost::bind(&CMainDlg::up6_md5_error, this, _1))
		("post_process", boost::bind(&CMainDlg::up6_post_process, this, _1))
		("post_error", boost::bind(&CMainDlg::up6_post_error, this, _1))
		("post_complete", boost::bind(&CMainDlg::up6_post_complete, this, _1))
		("post_stoped", boost::bind(&CMainDlg::up6_post_stoped, this, _1))
		("scan_process", boost::bind(&CMainDlg::up6_scan_process, this, _1))
		("scan_complete", boost::bind(&CMainDlg::up6_scan_complete, this, _1));

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
	this->m_up6->openFiles();

	return 0;
}

LRESULT CMainDlg::openFolder_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	this->m_up6->openFolders();
	return 0;
}

LRESULT CMainDlg::addFileLoc_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString txt;
	auto win = GetDlgItem(IDC_EDITPATHLOC);
	win.GetWindowTextW(txt);
	this->m_up6->addFileLoc((LPCWSTR)txt);
	return 0;
}

LRESULT CMainDlg::biz_message(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	boost::mutex::scoped_lock lock(this->data.tm->mx_msg);//使用RAII型的lock_guard
	auto& ms = this->data.tm->m_msgs;
	while (!ms.empty())
	{
		auto p = ms.front();
		ms.pop_front();
		this->data.tm->call(p.first, p.second);
	}

	return TRUE;
}

void CMainDlg::up6_component_init()
{
	this->m_up6 = std::make_shared<Up6Impl>(this);
	this->m_up6->entSelFile.connect(boost::bind(&CMainDlg::up6_sel_files, this, _1));
	this->m_up6->entSelFolder.connect(boost::bind(&CMainDlg::up6_sel_folder, this, _1));
	/*this->m_up6->entPostProcess.connect(boost::bind(&CMainDlg::up6_post_process, this, _1));
	this->m_up6->entPostError.connect(boost::bind(&CMainDlg::up6_post_error, this, _1));
	this->m_up6->entPostComplete.connect(boost::bind(&CMainDlg::up6_post_complete, this, _1));
	this->m_up6->entPostStoped.connect(boost::bind(&CMainDlg::up6_post_stoped, this, _1));
	this->m_up6->entScanProcess.connect(boost::bind(&CMainDlg::up6_scan_process, this, _1));
	this->m_up6->entScanComplete.connect(boost::bind(&CMainDlg::up6_scan_complete, this, _1));
	this->m_up6->entUpdateFolderComplete.connect(boost::bind(&CMainDlg::up6_update_fd_complete, this, _1));
	this->m_up6->entMd5Process.connect(boost::bind(&CMainDlg::up6_md5_process, this, _1));
	this->m_up6->entMd5Complete.connect(boost::bind(&CMainDlg::up6_md5_complete, this, _1));
	this->m_up6->entMd5Error.connect(boost::bind(&CMainDlg::up6_md5_error, this, _1));
	this->m_up6->entLoadComplete.connect(boost::bind(&CMainDlg::up6_load_complete, this, _1));*/
	
	//
	auto dir = Utils::curDir();
	dir.append(L"config.js");

	long len = 0;
	auto data = Utils::ReadAll(dir, len);
	Json::Reader jr;
	Utils::clearComment(data);
	if (jr.parse(data.c_str(), this->data.cfg))
	{
		this->m_up6->init(this->data.cfg);
	}
	else
	{
		this->addMsg(L"初始化失败");
	}
}

void CMainDlg::addMsg(const wstring& v)
{
	this->m_edtMsg.AppendText(v.c_str());
	this->m_edtMsg.AppendText(L"\r\n");
}

void CMainDlg::up6_sel_files(Json::Value& v)
{
	auto id = v.get("id", "").asString();
	auto nameLoc = v.get("nameLoc", "").asString();
	auto pathLoc = v.get("pathLoc", "").asString();
	auto sizeLoc = v.get("sizeLoc", "").asString();
	auto lenLoc = std::atoll( v.get("lenLoc", "0").asString().c_str());

	this->m_edtMsg.AppendText(L"文件名称：");
	this->m_edtMsg.AppendText( Utils::from_utf8(nameLoc).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
	this->m_edtMsg.AppendText(L"文件路径：");
	this->m_edtMsg.AppendText(Utils::from_utf8(pathLoc).c_str());
	this->m_edtMsg.AppendText(L"\r\n");

	auto up = std::make_shared<FileUploader>(this->m_up6.get(), this);
	up->data.cfg = this->data.cfg;
	up->data.fileSvr.id = id;
	up->data.fileSvr.nameLoc = nameLoc;
	up->data.fileSvr.pathLoc = pathLoc;
	up->data.fileSvr.sizeLoc = sizeLoc;
	up->data.fileSvr.lenLoc = lenLoc;
	this->data.files.insert(std::make_pair(id, up));

	boost::thread td([up]() {
		up->check_file();
	});
}

void CMainDlg::up6_sel_folder(Json::Value& v)
{
	std::string id = v.get("id", "").asString();
	std::string nameLoc = v.get("nameLoc", "").asString();
	std::string pathLoc = v.get("pathLoc", "").asString();

	this->m_edtMsg.AppendText(L"目录名称：");
	this->m_edtMsg.AppendText(Utils::from_utf8(nameLoc).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
	this->m_edtMsg.AppendText(L"目录路径：");
	this->m_edtMsg.AppendText(Utils::from_utf8(pathLoc).c_str());
	this->m_edtMsg.AppendText(L"\r\n");
}

void CMainDlg::up6_post_process(long v)
{

}

void CMainDlg::up6_post_error(long v)
{

}

void CMainDlg::up6_post_complete(long v)
{

}

void CMainDlg::up6_post_stoped(long v)
{

}

void CMainDlg::up6_scan_process(long v)
{

}

void CMainDlg::up6_scan_complete(long v)
{
	this->addMsg(L"目录扫描完毕");
}

void CMainDlg::up6_update_fd_complete(long v)
{

}

void CMainDlg::up6_md5_process(long v)
{
	auto d = this->data.mc->pop(v);
	auto jv = boost::any_cast<Json::Value>(d->m_data);
	auto id = jv.get("id", "").asString();
	auto f = this->data.files.find(id);
	if (f != this->data.files.end())
	{
		f->second->md5_process(jv);
	}
}

void CMainDlg::up6_md5_complete(long v)
{
	auto d = this->data.mc->pop(v);
	auto jv = boost::any_cast<Json::Value>(d->m_data);
	auto id = jv.get("id", "").asString();
	auto f = this->data.files.find(id);
	if (f != this->data.files.end())
	{
		f->second->md5_complete(jv);
	}
}

void CMainDlg::up6_md5_error(long v)
{
	this->addMsg(L"md5错误");
}

void CMainDlg::up6_add_folder_err(long v)
{
	this->addMsg(L"添加目录失败");
}

void CMainDlg::up6_load_complete(long v)
{
	this->addMsg(L"控件初始化完毕");
}