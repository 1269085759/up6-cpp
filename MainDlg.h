// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
class Up6Impl;

class CMainDlg : public CDialogImpl<CMainDlg>
{
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

	void up6_component_init();
	//event
	void up6_sel_files(std::string fileName,std::string filePath);
	void up6_sel_folder(Json::Value& v);
	void up6_post_process(Json::Value& v);
	void up6_post_error(Json::Value& v);
	void up6_post_complete(Json::Value& v);
	void up6_post_stoped(Json::Value& v);
	void up6_scan_process(Json::Value& v);
	void up6_scan_complete(Json::Value& v);
	void up6_update_fd_complete(Json::Value& v);
	void up6_md5_process(Json::Value& v);
	void up6_md5_complete(Json::Value& v);
	void up6_md5_error(Json::Value& v);
	void up6_add_folder_err(Json::Value& v);
	void up6_load_complete(Json::Value& v);

private:
	CButton m_btnOpenFile;
	CEdit m_edtMsg;
	std::shared_ptr<Up6Impl> m_up6;
};
