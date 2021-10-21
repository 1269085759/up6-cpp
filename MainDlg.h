// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
class Up6Impl;
class FileUploader;

class CMainDlg : public CDialogImpl<CMainDlg>
{
	typedef struct _datadef
	{
		map<string, std::shared_ptr<FileUploader>> files;
		Json::Value cfg;//≈‰÷√
		ThreadMessage* tm;
		MsgCenter* mc;
	}DataDef;
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(BTN_OPENFILE, openFile_click)
		COMMAND_ID_HANDLER(BTN_OPENFOLDER, openFolder_click)
		COMMAND_ID_HANDLER(BTN_ADDLOC, addFileLoc_click)
		MESSAGE_HANDLER(BIZ_MESSAGE, biz_message)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT openFile_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT openFolder_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT addFileLoc_click(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT biz_message(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void up6_component_init();
	void addMsg(const wstring& v);
	std::shared_ptr<FileUploader> getUper(string id);

	//event
	void send_msg(long v);
	void up6_sel_files(Json::Value& v);
	void up6_sel_folder(Json::Value& v);

	//file event
	void file_post_process(long v);
	void file_post_error(long v);
	void file_post_complete(long v);
	void file_post_stoped(long v);
	void file_md5_process(long v);
	void file_md5_complete(long v);
	void file_md5_error(long v);
	void file_init_file_cmp(long v);
	void file_init_file_err(long v);
	
	//folder event
	void folder_scan_process(long v);
	void folder_scan_complete(long v);
	void folder_post_process(long v);
	void folder_post_error(long v);
	void folder_post_complete(long v);
	void folder_post_stoped(long v);

	void up6_update_fd_complete(long v);
	void up6_add_folder_err(long v);
	void up6_load_complete(long v);

private:
	CButton m_btnOpenFile;
	CRichEditCtrl m_edtMsg;
	std::shared_ptr<Up6Impl> m_up6;
	DataDef data;
};
