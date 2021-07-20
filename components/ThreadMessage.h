#pragma once

class MsgCenter;
class ThreadMessage
{
public:
	ThreadMessage();
	~ThreadMessage();

	static ThreadMessage& get();

	void init(const map<string,boost::function<void(long)>>& es);
	/*
	 Method:    post 
	 Access:    public 
	 Returns:   void
	 Parameter: n 消息名称
	 Parameter: v 消息数据ID
	*/
	void post( const string& n ,long v);
	void postAuto(const string& name,boost::any data);
	void call( string n , long v );

public:
	HWND m_form;//UI窗口句柄
	//网络消息队列,消息名称，消息数据ID
	typedef std::pair<string , long> msg_data;
	std::list<msg_data > m_msgs;
	boost::mutex mx_msg;
	//结构：事件名称，事件处理
	boost::unordered_multimap<string , boost::function<void(long)>> m_handler;
	MsgCenter* m_mc;
};
typedef boost::serialization::singleton<ThreadMessage> ThreadMsg;