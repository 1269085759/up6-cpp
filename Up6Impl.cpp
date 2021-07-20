#include "stdafx.h"
#include "Up6Impl.h"
#include "resource.h"
#include "MainDlg.h"

Up6Impl::Up6Impl(CMainDlg* dlg)
{
	this->m_inited = false;
	this->data.tm = &ThreadMessage::get();
	this->data.dlg = dlg;
}

Up6Impl::~Up6Impl()
{
	this->DispEventUnadvise(this->up6Ptr);
}

STDMETHODIMP Up6Impl::recvMessage(BSTR msg)
{
	auto js = Utils::to_utf8(msg);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		auto n = root["name"].asString();
		if (n == "open_files") this->ent_open_files(root);
		else if (n == "open_folders") this->ent_open_folders(root);
		else if (n == "paste_files") this->ent_open_files(root);
		else if (n == "post_process") this->ent_post_process(root);
		else if (n == "post_error") this->ent_post_error(root);
		else if (n == "post_complete") this->ent_post_complete(root);
		else if (n == "post_stoped") this->ent_post_stoped(root);
		else if (n == "scan_process") this->ent_scan_process(root);
		else if (n == "scan_complete") this->ent_scan_complete(root);
		else if (n == "update_folder_complete") this->ent_update_folder_complete(root);
		else if (n == "md5_process") this->ent_md5_process(root);
		else if (n == "md5_complete") this->ent_md5_complete(root);
		else if (n == "md5_error") this->ent_md5_error(root);
		else if (n == "add_folder_error") this->ent_add_folder_error(root);
		else if (n == "load_complete") this->ent_load_complete(root);
	}

	return S_OK;
}

void Up6Impl::init(Json::Value& cfg)
{
	CLSID clsid;
	HRESULT hr = ::CLSIDFromProgID(L"Xproer.HttpPartition6.1", &clsid);
	if (!SUCCEEDED(hr))
	{
		MessageBoxW(nullptr,L"创建组件失败，请先安装或注册组件", L"错误", MB_OK);
		return;
	}

	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID *)&this->up6Ptr);
	if (SUCCEEDED(hr))
	{
		this->m_inited = true;
		up6Cmp = up6Ptr;
		this->DispEventAdvise(up6Ptr);//挂事件
	}

	Json::Value o;
	o["name"] = "init";
	o["config"] = cfg;
	Json::FastWriter writer;
	auto str = writer.write(o);
	auto json = Utils::from_utf8(str);

	CComVariant v1(json.c_str());
	CComVariant ret;
	hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
}

void Up6Impl::getVersion()
{
	CComVariant version;
	this->up6Cmp.GetPropertyByName(L"Version", &version);
}

void Up6Impl::openFiles()
{
	if (!this->m_inited) return;

	std::wstring js = L"{\"name\":\"open_files\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
}

void Up6Impl::openFolders()
{
	if (!this->m_inited) return;

	std::wstring js = L"{\"name\":\"open_folders\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
}

void Up6Impl::pasteFiles()
{
	if (!this->m_inited) return;

	std::wstring js = L"{\"name\":\"paste_files\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
}

void Up6Impl::addFileLoc(const wstring& pathLoc)
{
	if (!this->m_inited) return;

	std::wstring js = L"{\"name\":\"add_file\",\"pathLoc\":\"" + pathLoc + L"\"}";
	CComVariant v1(js.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
}

void Up6Impl::postMessage(const string& v)
{
	wstring w = Utils::from_utf8(v);
	CComVariant v1(w.c_str());
	CComVariant ret;
	HRESULT hr = this->up6Cmp.Invoke1(
		L"postMessage",
		&v1,
		&ret);
}

void Up6Impl::postMessage(const Json::Value& v)
{
	Json::FastWriter writer;
	auto str = writer.write(v);
	this->postMessage(str);
}

void Up6Impl::ent_open_files(Json::Value& val)
{
	int count = val["files"].size();

	// 遍历文件列表
	for (int i = 0; i < count; ++i)
	{
		auto f = val["files"][i];
		std::string nameLoc = f.get("nameLoc", "").asString();
		std::string pathLoc = f.get("pathLoc", "").asString();
		this->entSelFile(f);
	}
}

void Up6Impl::ent_open_folders(Json::Value& val)
{
	int count = val["folders"].size();

	// 遍历文件列表
	for (int i = 0; i < count; ++i)
	{
		auto f = val["folders"][i];
		std::string id = f.get("id", "").asString();
		std::string nameLoc = f.get("nameLoc", "").asString();
		std::string pathLoc = f.get("pathLoc", "").asString();
		this->entSelFolder(f);
	}
}

void Up6Impl::ent_post_process(Json::Value val)
{
	std::string id = val["id"].asString();
	std::string lenSvr = val["lenSvr"].asString();
	std::string perSvr = val["perSvr"].asString();
	std::string percent = val["percent"].asString();
	std::string lenPost = val["lenPost"].asString();
	std::string speed = val["speed"].asString();
	std::string time = val["time"].asString();
	//this->entPostProcess(val);
	this->data.tm->postAuto("post_process", val);
}

void Up6Impl::ent_post_error(Json::Value val)
{
	std::string id = val["id"].asString();
	std::string errCode = val["value"].asString();
	//this->entPostError(val);
	this->data.tm->postAuto("post_error", val);
}

void Up6Impl::ent_post_complete(Json::Value val)
{
	std::string id = val["id"].asString();
	//this->entPostComplete(val);
	this->data.tm->postAuto("post_complete", val);

}

void Up6Impl::ent_post_stoped(Json::Value val)
{
	std::string id = val["id"].asString();
	//this->entPostStoped(val);
	this->data.tm->postAuto("post_stoped", val);
}

void Up6Impl::ent_scan_process(Json::Value val)
{
	std::string id = val["id"].asString();
	//this->entScanProcess(val);
	this->data.tm->postAuto("scan_process", val);
}

void Up6Impl::ent_scan_complete(Json::Value val)
{
	std::string id = val["id"].asString();
	//this->entScanComplete(val);
	this->data.tm->postAuto("scan_complete", val);
}

void Up6Impl::ent_update_folder_complete(Json::Value val)
{
	std::string id = val["id"].asString();
	this->entUpdateFolderComplete(val);
}

void Up6Impl::ent_md5_process(Json::Value val)
{
	this->data.tm->postAuto("md5_process", val);
}

void Up6Impl::ent_md5_complete(Json::Value val)
{
	auto id = val.get("id","").asString();
	this->data.tm->postAuto("md5_complete", val);
}

void Up6Impl::ent_md5_error(Json::Value val)
{
	/*std::string id = val["id"].asString();
	this->entMd5Error(val);*/
	this->data.tm->postAuto("md5_error", val);
}

void Up6Impl::ent_add_folder_error(Json::Value val)
{
	this->entAddFolderErr(val);
}

void Up6Impl::ent_load_complete(Json::Value val)
{
	this->data.dlg->addMsg(L"控件加载成功");
}
