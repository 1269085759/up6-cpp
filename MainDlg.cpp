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
	this->m_edtMsg.Attach(this->GetDlgItem(TB_MSG));
	
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
		("send_msg", boost::bind(&CMainDlg::send_msg, this, _1))
		("md5_process", boost::bind(&CMainDlg::file_md5_process, this, _1))
		("md5_complete", boost::bind(&CMainDlg::file_md5_complete, this, _1))
		("md5_error", boost::bind(&CMainDlg::file_md5_error, this, _1))
		("init_file_cmp", boost::bind(&CMainDlg::file_init_file_cmp, this, _1))
		("init_file_err", boost::bind(&CMainDlg::file_init_file_err, this, _1))
		("post_process", boost::bind(&CMainDlg::file_post_process, this, _1))
		("post_error", boost::bind(&CMainDlg::file_post_error, this, _1))
		("post_complete", boost::bind(&CMainDlg::file_post_complete, this, _1))
		("post_stoped", boost::bind(&CMainDlg::file_post_stoped, this, _1))
		("folder_scan_process", boost::bind(&CMainDlg::folder_scan_process, this, _1))
		("folder_scan_complete", boost::bind(&CMainDlg::folder_scan_complete, this, _1))
		("folder_post_process", boost::bind(&CMainDlg::folder_post_process, this, _1))
		("folder_post_error", boost::bind(&CMainDlg::folder_post_error, this, _1))
		("folder_post_complete", boost::bind(&CMainDlg::folder_post_complete, this, _1))
		("folder_post_stoped", boost::bind(&CMainDlg::folder_post_stoped, this, _1))
		;

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
	
	//
	auto dir = Utils::curDir();
	dir.append(L"config.js");

	this->addMsg(L"加截配置文件：" + dir);

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
		this->addMsg(L"解析配置文件失败，请检查配置文件语法");
		auto dw = Utils::from_utf8(data);
		this->addMsg(dw);
	}
}

void CMainDlg::addMsg(const wstring& v)
{
	this->m_edtMsg.AppendText(v.c_str());
	this->m_edtMsg.AppendText(L"\r\n");
}

/*
 Method:    获取上传对象
 FullName:  CMainDlg::getFile
 Access:    public 
 Returns:   std::shared_ptr<FileUploader>
 Qualifier:
 Parameter: string v
*/
std::shared_ptr<FileUploader> CMainDlg::getUper(string id)
{
	std::shared_ptr<FileUploader> u;
	auto ret = this->data.files.find(id);
	if (this->data.files.end() != ret)
	{
		u = ret->second;
	}
	return u;
}

void CMainDlg::send_msg(long v)
{
	auto d = this->data.mc->pop(v);
	auto msg = boost::any_cast<string>(d->getData());
	this->m_edtMsg.AppendText( Utils::from_utf8(msg).c_str() );
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
	up->data.tm = this->data.tm;
	up->data.mc = this->data.mc;
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

	auto fd = std::make_shared<FolderUploader>(this->m_up6.get(), this);
	fd->data.tm = this->data.tm;
	fd->data.mc = this->data.mc;
	fd->data.cfg = this->data.cfg;
	fd->data.fileSvr.id = id;
	fd->data.fileSvr.nameLoc = nameLoc;
	fd->data.fileSvr.pathLoc = pathLoc;
	this->data.files.insert(std::make_pair(id, fd));

	boost::thread td([fd]() {
		fd->scan();
	});
}

void CMainDlg::file_post_process(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	auto lenw = Utils::from_utf8(f->data.fileSvr.lenPost);
	auto spedw = Utils::from_utf8(f->data.fileSvr.speed);
	auto timew = Utils::from_utf8(f->data.fileSvr.time);
	boost::wformat fmt(L"正在上传文件，speed:%1%,postLen:%2%,time:%3% id:%4%");
	fmt % spedw % lenw % timew % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_post_error(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"上传错误，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_post_complete(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"上传完毕，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_post_stoped(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"上传停止，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::folder_scan_process(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	auto perw = Utils::from_utf8(f->data.fileSvr.percent);
	boost::wformat fmt(L"扫描中......%1%，id:%2%");
	fmt % perw % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::folder_scan_complete(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"扫描完毕......，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::folder_post_process(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	auto lenw = Utils::from_utf8(f->data.fileSvr.lenPost);
	auto spedw = Utils::from_utf8(f->data.fileSvr.speed);
	auto timew = Utils::from_utf8(f->data.fileSvr.time);
	boost::wformat fmt(L"目录上传中......，speed:%1%,postLen:%2%,time:%3% id:%4%");
	fmt % spedw % lenw % timew % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::folder_post_error(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"目录上传错误，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::folder_post_complete(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"目录上传完毕，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::folder_post_stoped(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"目录上传停止，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::up6_update_fd_complete(long v)
{

}

void CMainDlg::file_md5_process(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	auto perw = Utils::from_utf8(f->data.fileSvr.percent);
	boost::wformat fmt(L"正在计算文件MD5，进度：%1% id:%2%");
	fmt % perw % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_md5_complete(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto idw = Utils::from_utf8(id);
	auto f = this->getUper(id);
	boost::wformat fmt(L"md5计算完毕,开始初始化文件，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_md5_error(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"md5计算错误，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_init_file_cmp(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto idw = Utils::from_utf8(id);
	boost::wformat fmt(L"文件初始化完毕，开始上传，id:%1%");
	fmt % idw;
	this->addMsg(fmt.str());
}

void CMainDlg::file_init_file_err(long v)
{
	auto d = this->data.mc->pop(v);
	auto id = boost::any_cast<string>(d->getData());
	auto f = this->getUper(id);
	auto idw = Utils::from_utf8(id);
	auto errw = Utils::from_utf8( f->data.fileSvr.err );
	boost::wformat fmt(L"文件初始化错误，id:%1%,err:%2%");
	fmt % idw % errw;
	this->addMsg(fmt.str());
}

void CMainDlg::up6_add_folder_err(long v)
{
	this->addMsg(L"添加目录失败");
}

void CMainDlg::up6_load_complete(long v)
{
	this->addMsg(L"控件初始化完毕");
}