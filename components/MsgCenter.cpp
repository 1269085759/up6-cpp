#include "stdafx.h"
#include "MsgCenter.h"

MsgCenter::MsgCenter()
{
}

MsgCenter::~MsgCenter()
{
}

MsgCenter& MsgCenter::get()
{
	return MsgCenterIns::get_mutable_instance();
}

MsgDataPtr MsgCenter::make_msg( boost::any d )
{
	boost::mutex::scoped_lock lock( this->m_items_mt );//使用RAII型的lock_guard
	auto msg = std::make_shared<MsgData>();
	msg->m_id = this->m_idCount++;
	msg->setData(d);
	this->m_items.insert( std::make_pair( msg->m_id , msg ) );
	return msg;
}

MsgDataPtr MsgCenter::pop( long id )
{
	boost::mutex::scoped_lock lock( this->m_items_mt );//使用RAII型的lock_guard
	auto ret = this->m_items.find( id );
	auto data = ret->second;
	this->m_items.erase( id );//
	return data;
}