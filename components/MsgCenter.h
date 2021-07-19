#pragma once
class MsgData;
typedef std::shared_ptr<MsgData> MsgDataPtr;

class MsgCenter
{
public:
	MsgCenter();
	~MsgCenter();

	static MsgCenter& get();
	MsgDataPtr make_msg( boost::any d );
	MsgDataPtr pop( long id );

public:
	boost::atomic_long m_idCount;///计数器
	boost::unordered_map<long , MsgDataPtr> m_items;
	boost::mutex m_items_mt;
};
typedef singleton_default<MsgCenter> MsgCenterIns;