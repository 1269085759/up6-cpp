#include "stdafx.h"
#include "FileUploader.h"

FileUploader::FileUploader(Up6Impl* up6)
{
	this->data.up6 = up6;
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

void FileUploader::init_file()
{

}

void FileUploader::init_file_error()
{

}

void FileUploader::post_file()
{

}

void FileUploader::md5_process(Json::Value v)
{

}

void FileUploader::md5_complete(Json::Value v)
{

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
