#include "stdafx.h"
#include "FolderUploader.h"

FolderUploader::FolderUploader(Up6Impl* up6, CMainDlg* dlg):FileUploader(up6,dlg)
{
}

FolderUploader::~FolderUploader()
{
}

void FolderUploader::post()
{
	Json::Value v;
	v["name"] = "post_folder";
	v["id"] = this->data.fileSvr.id;
	v["pathLoc"] = this->data.fileSvr.pathLoc;
	Json::Value fields;
	fields["uid"] = this->data.fileSvr.uid;
	v["fields"] = fields;
	this->data.up6->postMessage(v);
}

void FolderUploader::scan()
{
	Json::Value v;
	v["name"] = "scan_folder";
	v["id"] = this->data.fileSvr.id;
	this->data.up6->postMessage(v);
}

void FolderUploader::init_folder()
{
	auto time = boost::posix_time::microsec_clock::universal_time();//微秒精度
	boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
	boost::posix_time::time_duration time_from_epoch =
	boost::posix_time::second_clock::universal_time() - epoch;
	
	auto ptr = std::make_shared<map<string, string>>();
	map<string, string> header = {
		{"id",this->data.fileSvr.id},
		{"uid", std::to_string(this->data.fileSvr.uid) },
		{"lenLoc",std::to_string(this->data.fileSvr.lenLoc) },
		{"sizeLoc",Utils::url_encode(this->data.fileSvr.sizeLoc) },
		{"pathLoc",Utils::url_encode(this->data.fileSvr.pathLoc) },
		{"time", std::to_string( time_from_epoch.total_seconds() ) }
	};

	for (auto& h : header)
	{
		(*ptr).insert(std::make_pair(h.first, h.second));
	}

	boost::thread td([this, ptr]() {
		string response;
		if (Utils::http_get(this->data.cfg.get("UrlFdCreate", "").asString(), ptr, response))
		{
			//res = callback(json)
			auto pos = response.find("{");
			if (pos != string::npos) pos = response.find("{", pos + 1);
			auto end = response.rfind("}");
			if (end != string::npos) end = response.rfind("}", end - 1);

			response = response.substr(pos, end - pos + 1);

			Json::Value json;
			auto res = Utils::parse(response, json);
			this->data.fileSvr.pathSvr = json["pathSvr"].asString();
			this->data.fileSvr.lenSvr = json["lenSvr"].asInt64();
			this->init_complete();
		}
		else
		{
			this->data.fileSvr.err = response;
			this->init_error();
		}
	});
}

void FolderUploader::init_error()
{

}

void FolderUploader::init_complete()
{
	this->update_info();
}

/*
 Method:    更新目录信息,更新路径
 FullName:  FolderUploader::update_info
 Access:    public 
 Returns:   void
 Qualifier:
*/
void FolderUploader::update_info()
{
	Json::Value v;
	v["name"] = "update_folder";
	v["id"] = this->data.fileSvr.id;
	v["pathSvr"] = this->data.fileSvr.pathSvr;
	this->data.up6->postMessage(v);

	//开始上传
	this->post();
}

void FolderUploader::scan_process(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("folder_scan_process", d->getID());
}

void FolderUploader::scan_complete(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("folder_scan_complete", d->getID());

	this->init_folder();
}

void FolderUploader::post_process(Json::Value v)
{
	this->data.fileSvr.lenSvr = v["lenSvr"].asInt64();
	this->data.fileSvr.perSvr = v["perSvr"].asString();//已传百分比
	this->data.fileSvr.percent = v["percent"].asString();//已发送百分比
	this->data.fileSvr.lenPost = v["lenPost"].asString();//已发送大小
	this->data.fileSvr.speed = v["speed"].asString();//速度
	this->data.fileSvr.time = v["time"].asString();	//剩余时间

	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("folder_post_process", d->getID());
}

void FolderUploader::post_complete(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("folder_post_complete", d->getID());
}

void FolderUploader::post_error(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("folder_post_error", d->getID());
}

void FolderUploader::post_stoped(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("folder_post_stoped", d->getID());
}
