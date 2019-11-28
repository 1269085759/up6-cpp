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
	if (reader.parse(js, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��
	{
		int count = root["files"].size();

		// �����ļ��б�
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
