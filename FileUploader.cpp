#include "stdafx.h"
#include "FileUploader.h"
#include "resource.h"
#include "MainDlg.h"

FileUploader::FileUploader(Up6Impl* up6, CMainDlg* dlg)
{
	this->data.up6 = up6;
	this->data.dlg = dlg;
}

FileUploader::~FileUploader()
{
}

void FileUploader::check_file()
{
	Json::Value v;
	v["name"] = "check_file";
	v["id"] = this->data.fileSvr.id;
	v["pathLoc"] = this->data.fileSvr.pathLoc;
	this->data.up6->postMessage(v);
}

/*
 Method:    文件初始化
 FullName:  FileUploader::init_file
 Access:    public 
 Returns:   void
 Qualifier:
*/
void FileUploader::init_file()
{
	//this->data.dlg->addMsg(L"开始初始化文件");
	auto ptr=std::make_shared<map<string,string>>();
	map<string, string> header = {
		{"md5",this->data.fileSvr.md5},
		{"id",this->data.fileSvr.id},
		{"uid", std::to_string( this->data.fileSvr.uid) },
		{"lenLoc",std::to_string( this->data.fileSvr.lenLoc) },
		{"sizeLoc",this->data.fileSvr.sizeLoc},
		{"pathLoc",this->data.fileSvr.pathLoc},
	};

	for (auto& h : header)
	{
		(*ptr).insert( std::make_pair(h.first, h.second));
	}
	
	boost::thread td([this,ptr]() {
		string response;
		if (Utils::http_get(this->data.cfg.get("UrlCreate", "").asString(), ptr, response))
		{
			//res = callback(json)
			auto pos = response.find("{");
			if (pos != string::npos) pos = response.find("{", pos+1);
			auto end = response.rfind("}");
			if (end != string::npos) end = response.rfind("}", end-1);

			response = response.substr(pos,end-pos+1);

			Json::Value json;
			auto res = Utils::parse(response, json);
			this->data.fileSvr.pathSvr = json["pathSvr"].asString();
			this->data.fileSvr.lenSvr = json["lenSvr"].asInt64();
			this->init_file_complete();
		}
		else
		{
			this->data.fileSvr.err = response;
			this->init_file_error();
		}
	});
}

void FileUploader::init_file_complete()
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("init_file_cmp", d->getID() );
	//开始上传
	this->post_file();
}

void FileUploader::init_file_error()
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("init_file_err", d->getID() );
}

void FileUploader::post_file()
{
	Json::Value v;
	v["name"] = "post_file";
	v["id"] = this->data.fileSvr.id;
	Json::Value fields;
	fields["uid"] = this->data.fileSvr.uid;
	v["fields"] = fields;
	v["pathLoc"] = this->data.fileSvr.pathLoc;
	v["pathSvr"] = this->data.fileSvr.pathSvr;
	v["lenSvr"] = std::to_string( this->data.fileSvr.lenSvr );
	this->data.up6->postMessage(v);
}

void FileUploader::md5_process(Json::Value v)
{
	this->data.fileSvr.percent = v["percent"].asString();
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("md5_process", d->getID());
}

void FileUploader::md5_complete(Json::Value v)
{
	this->data.fileSvr.md5 = v.get("md5","").asString();
	//this->data.dlg->addMsg(L"md5计算完毕");
	/*boost::format fmt("md5:%1%");
	fmt % this->data.fileSvr.md5;
	this->data.dlg->addMsg(Utils::from_utf8(fmt.str()));*/


	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("md5_complete", d->getID());

	this->init_file();
}

void FileUploader::md5_error(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("md5_error", d->getID());
}

/*
 Method:    post_process
 FullName:  FileUploader::post_process
 Access:    public 
 Returns:   void
 Qualifier:
 Parameter: Json::Value v
*/
void FileUploader::post_process(Json::Value v)
{
	this->data.fileSvr.lenSvr = v["lenSvr"].asInt64();
	this->data.fileSvr.perSvr = v["perSvr"].asString();//已传百分比
	this->data.fileSvr.percent = v["percent"].asString();//已发送百分比
	this->data.fileSvr.lenPost = v["lenPost"].asString();//已发送大小
	this->data.fileSvr.speed = v["speed"].asString();//速度
	this->data.fileSvr.time = v["time"].asString();	//剩余时间

	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("post_process", d->getID());
}

void FileUploader::post_complete(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("post_complete", d->getID());
}

void FileUploader::post_error(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("post_error", d->getID());
}

void FileUploader::post_stoped(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("post_stoped", d->getID());
}

void FileUploader::scan_process(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("scan_process", d->getID());
}

void FileUploader::scan_complete(Json::Value v)
{
	auto d = this->data.mc->make_msg(this->data.fileSvr.id);
	this->data.tm->post("scan_complete", d->getID());
}