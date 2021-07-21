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

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	string data((const char*)ptr, (size_t)size * nmemb);

	*((stringstream*)stream) << data;

	return size * nmemb;
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
	boost::thread td([this]() {
		std::stringstream response;
		CURL *curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, this->data.cfg.get("UrlCreate", "").asString().c_str());
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			curl_slist *header = NULL;
			string md5 = "md5:" + this->data.fileSvr.md5;
			string id = "id:" + this->data.fileSvr.id;
			string uid = "uid:" + std::to_string(this->data.fileSvr.uid);
			string lenLoc = "lenLoc:" + std::to_string(this->data.fileSvr.lenLoc);
			string sizeLoc = "sizeLoc:" + this->data.fileSvr.sizeLoc;
			string pathLoc = "pathLoc:" + this->data.fileSvr.pathLoc;
			header = curl_slist_append(header, md5.c_str());
			header = curl_slist_append(header, id.c_str());
			header = curl_slist_append(header, uid.c_str());
			header = curl_slist_append(header, lenLoc.c_str());
			header = curl_slist_append(header, sizeLoc.c_str());
			header = curl_slist_append(header, pathLoc.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

			/* Perform the request, res will get the return code */
			CURLcode res = curl_easy_perform(curl);
			int httpstate = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpstate);
			/* Check for errors */
			if (res != CURLE_OK|| 200 != httpstate)
			{
				this->init_file_error();
			}
			else
			{
				auto res = response.str();
				res = Utils::url_decode(res);
				Json::Value json;
				if (Utils::parse(res, json))
				{
					this->data.fileSvr.pathSvr = json.get("pathSvr", "").asString();
					this->post_file();
				}
			}

			/* always cleanup */
			curl_slist_free_all(header);//
			curl_easy_cleanup(curl);
		}
	});
}

void FileUploader::init_file_complete()
{
	this->data.dlg->addMsg(L"文件初始化成功");
}

void FileUploader::init_file_error()
{
	this->data.dlg->addMsg(L"文件初始化失败");
}

void FileUploader::post_file()
{
	Json::Value v;
	v["name"] = "check_file";
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
