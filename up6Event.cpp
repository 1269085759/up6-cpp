#include "stdafx.h"
#include "up6Event.h"


up6Event::up6Event()
{
}


up6Event::~up6Event()
{
}

STDMETHODIMP up6Event::recvMessage(BSTR msg)
{
	auto js = Encoder::to_utf8(msg);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		auto n= root["name"].asString();
		if (n == "open_files") this->open_files(root);
		else if (n == "open_folders") this->open_folders(root);
		else if (n == "paste_files") this->open_files(root);
		else if (n == "post_process") this->post_process(root);
		else if (n == "post_error") this->post_error(root);
		else if (n == "post_complete") this->post_complete(root);
		else if (n == "post_stoped") this->post_stoped(root);
		else if (n == "scan_process") this->scan_process(root);
		else if (n == "scan_complete") this->scan_complete(root);
		else if (n == "update_folder_complete") this->update_folder_complete(root);
		else if (n == "md5_process") this->md5_process(root);
		else if (n == "md5_complete") this->md5_complete(root);
		else if (n == "md5_error") this->md5_error(root);
		else if (n == "add_folder_error") this->add_folder_error(root);
		else if (n == "load_complete") this->load_complete(root);
	}

	return S_OK;
}

void up6Event::open_files(Json::Value& val)
{
	int count = val["files"].size();

	// 遍历文件列表
	for (int i = 0; i < count; ++i)
	{
		auto f = val["files"][i];
		std::string nameLoc = f.get("nameLoc", "").asString();
		std::string pathLoc = f.get("pathLoc", "").asString();
		this->entSelFile(nameLoc, pathLoc);
	}
}

void up6Event::open_folders(Json::Value& val)
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

void up6Event::post_process(Json::Value& val)
{
	std::string id = val["id"].asString();
	std::string lenSvr = val["lenSvr"].asString();
	std::string perSvr = val["perSvr"].asString();
	std::string percent = val["percent"].asString();
	std::string lenPost = val["lenPost"].asString();
	std::string speed = val["speed"].asString();
	std::string time = val["time"].asString();
	this->entPostProcess(val);
}

void up6Event::post_error(Json::Value& val)
{
	std::string id = val["id"].asString();
	std::string errCode = val["value"].asString();
	this->entPostError(val);
}

void up6Event::post_complete(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entPostComplete(val);
}

void up6Event::post_stoped(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entPostStoped(val);
}

void up6Event::scan_process(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entScanProcess(val);
}

void up6Event::scan_complete(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entScanComplete(val);
}

void up6Event::update_folder_complete(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entUpdateFolderComplete(val);
}

void up6Event::md5_process(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entMd5Process(val);
}

void up6Event::md5_complete(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entMd5Complete(val);
}

void up6Event::md5_error(Json::Value& val)
{
	std::string id = val["id"].asString();
	this->entMd5Error(val);
}

void up6Event::add_folder_error(Json::Value& val)
{
	this->entAddFolderErr(val);
}

void up6Event::load_complete(Json::Value& val)
{
	this->entLoadComplete(val);
}
