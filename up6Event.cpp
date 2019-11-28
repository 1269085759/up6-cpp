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
		int count = root["files"].size();

		// 遍历文件列表
		for (int i = 0; i < count; ++i)
		{
			auto f = root["files"][i];
			std::string nameLoc = f.get("nameLoc", "").asString();
			std::string pathLoc = f.get("pathLoc", "").asString();
			this->m_entFilesOpen(nameLoc, pathLoc);
		}
	}

	return S_OK;
}
