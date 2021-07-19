#pragma once

class MsgData
{
public:
	MsgData();
	~MsgData();

	boost::any getData();
	int getID();
	void setData(boost::any d);

public:
	long m_id;
	boost::any  m_data;
};
typedef std::shared_ptr<MsgData> MsgDataPtr;