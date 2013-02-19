#ifndef _NET_SESSION_H_
#define _NET_SESSION_H_

#include "..\..\common\defines.h"
#include "../common/thread.h"
#include "../xml/xml.h"
#include "socket.h"
#include "receiver.h"
using namespace net;

class CNetSession : public CThreadBase
{
public:
	enum {WM_START = WM_USER + 1000, WM_STOP};
	CNetSession(void);
	~CNetSession(void);
	bool StartServer(void);
	bool StopServer(void);

	DWORD WorkItem(LPVOID param);

private:
	void Init();
	bool StartServerListen(void);
	bool StopServerListen(void);
	bool RecvMsg(void);
	bool SendMsg();

private:
	bool m_bListen;
	CReceiver m_hRecv;
	Socket m_sock;
	CNetEvent m_Event;
	CUserInfo m_UserInfo;
	CXmlConfig m_XmlConfig;

};

__inline void CNetSession::Init(void)
{
	m_bListen = false;
}
#endif //_NET_SESSION_H_