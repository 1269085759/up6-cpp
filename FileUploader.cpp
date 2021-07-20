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
	this->data.dlg->addMsg(L"开始初始化文件");
}

void FileUploader::init_file_error()
{

}

void FileUploader::post_file()
{

}

void FileUploader::md5_process(Json::Value v)
{
	this->data.dlg->addMsg(L"md5计算中...");
}

void FileUploader::md5_complete(Json::Value v)
{
	this->data.fileSvr.md5 = v.get("md5","").asString();
	this->data.dlg->addMsg(L"md5计算完毕");
	boost::format fmt("md5:%1%");
	fmt % this->data.fileSvr.md5;
	this->data.dlg->addMsg(Utils::from_utf8(fmt.str()));

	this->init_file();
}

void FileUploader::md5_error(Json::Value v)
{

}

void FileUploader::post_process(Json::Value v)
{

}

void FileUploader::post_complete(Json::Value v)
{

}

void FileUploader::post_error(Json::Value v)
{

}

void FileUploader::scan_process(Json::Value v)
{

}

void FileUploader::scan_complete(Json::Value v)
{

}
