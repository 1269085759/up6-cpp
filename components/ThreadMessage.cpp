#include "StdAfx.h"
#include "ThreadMessage.h"

ThreadMessage::ThreadMessage()
{
	this->m_form = nullptr;
	this->m_mc = &MsgCenterIns::instance();
}

ThreadMessage::~ThreadMessage()
{
}

ThreadMessage& ThreadMessage::get()
{
	return ThreadMsg::instance();
}

void ThreadMessage::post( const string& n , long v )
{
	boost::mutex::scoped_lock lock( this->mx_msg );//使用RAII型的lock_guard
	this->m_msgs.push_back( std::make_pair(n,v) );
	BOOST_ASSERT( this->m_form );
	//通知UI取数据
	PostMessageA( this->m_form , BIZ_MESSAGE , 0 , 0 );
}

void ThreadMessage::postAuto(const string& name, boost::any data)
{
	auto d = this->m_mc->make_msg(data);
	this->post(name, d->getID());
}

void ThreadMessage::call( string n , long v )
{
	auto range = this->m_handler.equal_range( n );
	for ( auto i = range.first; i != range.second; ++i )
	{
		i->second( v );
	}
}