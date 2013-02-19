#ifndef _NET_SESSION_H_
#define _NET_SESSION_H_
#include "..\..\common\defines.h"
#include "../common/thread.h"
#include "../xml/xml.h"
#include "socket.h"
using namespace net;

#include "receiver.h"
#include "../protocol/protocol.h"
using namespace cds;
using namespace protocol;

class CNetSession : public CThreadBase
{
public:
	enum {WM_CONNECT = WM_USER + 1000, WM_DISCONNECT, WM_SEND, WM_RECONNECT};
	explicit CNetSession(void);
	~CNetSession(void);
	
	void SetRecvHandle(CReceiver &recv);
	bool SendMsgBuffer(const CSendMsg &msg);
	bool Connect(void);
	bool Disconnect(void);
	virtual DWORD WorkItem(LPVOID param);
private:
	bool DoReceive(void);
	bool SendMsgBuffer(const char *buf, const int len);
	bool Connect(string ip, short port);
	bool Disconnect(bool IsReconnect);
	void Init(void);
private:
	bool m_bConnect;
	CReceiver m_hRecv;
	Socket m_sock;
	CNetEvent m_Event;
	CUserInfo m_UserInfo;
	CXmlConfig m_XmlConfig;
};

__inline void CNetSession::Init(void)
{
	m_bConnect = false;
}

#endif //_NET_SESSION_H_