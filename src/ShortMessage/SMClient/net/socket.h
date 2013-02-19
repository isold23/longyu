#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "..\..\common\defines.h"

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <thread.h>
#endif

namespace net
{

static const int BUFLEN = 10 * 1024;
/////////////////////////////////////////////////////
class CWinInit
{
public:
	CWinInit(void);
	~CWinInit(void);
private:

};

/////////////////////////////////////////////////////

class CSocketAddr : public sockaddr_in
{
public:
	CSocketAddr(void);
	CSocketAddr(string ip, short port);
	CSocketAddr(int ip, short port);
	~CSocketAddr(void);

	string ip2str(void);
	int ip2h(void);//转换为本地字节序的IP
	short port2h(void);//转换为本地字节序的PORT

	CSocketAddr& operator= (CSocketAddr &addr);
	bool operator ==(CSocketAddr &addr);
private:
	void Init(void);
private:

};

__inline void CSocketAddr::Init(void)
{
	sin_family = AF_INET;
}

__inline CSocketAddr& CSocketAddr::operator = (CSocketAddr &addr)
{
	if (this == &addr)return *this;
	sin_addr = addr.sin_addr;
	sin_family = addr.sin_family;
	sin_port = addr.sin_port;
	memcpy(sin_zero, addr.sin_zero, 8*sizeof(char));
	return *this;
}

__inline bool CSocketAddr::operator ==(net::CSocketAddr &addr)
{
	if (this == &addr)
		return true;
	else
		return false;
}
///////////////////////////////////////////////////////
class CNetEvent;
///////////////////////////////////////////////////////
class Socket
{
public:
	friend class CNetEvent;
	Socket(void);
	Socket(SOCKET &sock);
	~Socket(void);

	bool Create(CSocketAddr &addr);
	bool Bind(void);
	bool Connect(void);
	Socket Accept(void);
	int SendMsg(const char *buffer, const int length);
	int RecvMsg(char *buffer, int length, CSocketAddr *addr);
	bool Listen(int backlog = SOMAXCONN);
	void Close(void);
	void Setopt(void);
	operator SOCKET (void);
	operator bool(void);
	Socket& operator = (SOCKET &sock);
	bool operator == (Socket &sock);

private:
	void Init(void);
private:
	bool m_bConnect;
	SOCKET m_sock;
	CSocketAddr m_SocketAddr;
};

__inline void Socket::Init(void)
{
	m_sock = INVALID_SOCKET;
	m_bConnect = false;
}

__inline Socket::operator SOCKET(void)
{
	return m_sock;
}

__inline Socket::operator bool(void)
{
	return (INVALID_SOCKET != m_sock);
}
/////////////////////////////////////////////////////
class CNetEvent
{
public:
	enum{ ACCEPT = 1, CONNECT, READ, WRITE, CLOSE, CONNECT_ERROR};
	CNetEvent(void);
	CNetEvent(Socket *sock);
	~CNetEvent(void);
	int BindSocket(void);
	int DoEvent(void);
	CNetEvent& operator = (Socket &sock);

	void DelSockeInfo(net::Socket &sock);
	void AddSocketInfo(net::Socket &sock);
private:
	void Init(void);
private:
	Socket m_sock[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT m_event[WSA_MAXIMUM_WAIT_EVENTS];
	int m_nEventTotal;
};

__inline void CNetEvent::Init(void)
{
	//m_pSock = NULL;
	//m_event = NULL;
	m_nEventTotal = 0;
}
/////////////////////////////////////////////////////
};//end of namespace net
#endif //_SOCKET_H_