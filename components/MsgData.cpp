#include "stdafx.h"
#include "MsgData.h"

MsgData::MsgData()
{
}

MsgData::~MsgData()
{
}

boost::any MsgData::getData()
{
	return this->m_data;
}

int MsgData::getID()
{
	return this->m_id;
}

void MsgData::setData(boost::any d)
{
	this->m_data = d;
}
