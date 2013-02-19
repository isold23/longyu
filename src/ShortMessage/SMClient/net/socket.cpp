#include "stdafx.h"
#include "socket.h"
using namespace net;

////////////////////////////////////
CWinInit::CWinInit(void)
{
	WSAData wsaData;
	WORD wVersionRequest = MAKEWORD(2, 2);
	WSAStartup(wVersionRequest, &wsaData); 
}
CWinInit::~CWinInit(void)
{
	WSACleanup();
}
////////////////////////////////////
CSocketAddr::CSocketAddr(void)
{
	Init();
}

//字符串形式的IP和本地字节序的PORT
CSocketAddr::CSocketAddr(string ip, short port)
{
	Init();
	sin_port = htons(port);
	sin_addr.S_un.S_addr = inet_addr(ip.c_str());
}

//本地字节序的IP和PORT
CSocketAddr::CSocketAddr(int ip, short port)
{
	Init();
	sin_port = htons(port);
	sin_addr.S_un.S_addr = htonl(ip);
}

CSocketAddr::~CSocketAddr(void)
{
	Init();
}

string CSocketAddr::ip2str(void)
{
	return inet_ntoa(sin_addr);
}

int CSocketAddr::ip2h(void)
{
	return ntohl(sin_addr.S_un.S_addr);
}

short CSocketAddr::port2h(void)
{
	return ntohs(sin_port);
}

////////////////////////////////////
Socket::Socket(void)
{
	Init();
}

Socket::Socket(SOCKET &sock)
{
	m_sock = sock;
	//
	m_bConnect = true;
}

Socket::~Socket(void)
{
	Init();
}

bool Socket::Listen(int backlog)
{
	if ((bool)(*this))
	{
		int error = listen(m_sock, backlog);
		if (error == SOCKET_ERROR)
			throw "listen failed";
	}
	return true;
}

bool Socket::Create(net::CSocketAddr &addr)
{
	m_SocketAddr = addr;
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == m_sock)
		throw "create socket error";
	return true;
}

bool Socket::Bind(void)
{
	if ((bool)*this)throw "bad socket";
	int nRet = bind(m_sock, (sockaddr*)(&m_SocketAddr), sizeof(m_SocketAddr));
	if (nRet == SOCKET_ERROR)
		throw "bind socket error";
	return true;
}

bool Socket::Connect(void)
{
	if ((bool)*this) throw "bad socket";
	int nRet = connect(m_sock, (sockaddr*)(&m_SocketAddr), sizeof(m_SocketAddr));
	if (nRet == SOCKET_ERROR)
	{
		if (GetLastError() != WSAEWOULDBLOCK)
			throw "connect socket error";
	}
	return true;
}

Socket Socket::Accept(void)
{
	if ((bool)*this) throw "bad socket";
	CSocketAddr addr;
	int len = sizeof(CSocketAddr);
	SOCKET sock = accept(m_sock, (sockaddr*)(&addr), &len);
	if (sock == INVALID_SOCKET)
		throw "accept error";
	Socket lsock = sock;
	return lsock;
}

void Socket::Setopt(void)
{
	if ((bool)*this) throw "bad sock";
	int iMode = 1;
	ioctlsocket(m_sock, FIONBIO, (u_long FAR*) &iMode);

	int nOptVal = BUFLEN;
	int nOptLen = sizeof(int);
	int nRet = setsockopt(m_sock, SOL_SOCKET, SO_SNDBUF, 
		(char*)&nOptVal, nOptLen);
	if (nRet == SOCKET_ERROR)
		throw "set opt error";
	
	nRet = setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, 
		(char*)&nOptVal, nOptLen);
	if (nRet == SOCKET_ERROR)
		throw "set opt error";
}

void Socket::Close(void)
{
	if ((bool)*this)
		closesocket(m_sock);
}

Socket& Socket::operator =(SOCKET &sock)
{
	if (this->m_sock != sock)
	{
		m_sock = sock;
		//
		m_bConnect = true;
	}
	return *this;
}

bool Socket::operator ==(Socket &sock)
{
	if (m_sock == sock.m_sock 
		&& m_bConnect == sock.m_bConnect 
		&& m_SocketAddr == sock.m_SocketAddr)
		return true;
	else
		 return false;
}


int Socket::SendMsg(const char *buffer, const int length)
{
	if ((bool)*this) throw "bad sock";
	int nRet = ::send(m_sock, buffer, length, 0);
	if (nRet == SOCKET_ERROR)
		throw "Send message error";
	return nRet;
}

int Socket::RecvMsg(char *buffer, int length, net::CSocketAddr *addr)
{
		if ((bool)*this) throw "bad sock";
		int nRet = ::recv(m_sock, buffer, length, 0);
		if (nRet == SOCKET_ERROR)
			throw "Receive message error";
		return nRet;
}
//////////////////////////////////////
//CNetEvent::CNetEvent(void)
//{
//	WSAEVENT event = WSACreateEvent();
//	if (NULL == event)
//	{
//		int error = WSAGetLastError();
//		throw "Create event error";
//	}
//	m_event[m_nEventTotal - 1] = event;
//}
CNetEvent::CNetEvent(net::Socket *sock)
{
	assert(NULL != sock);
	m_sock[m_nEventTotal] = *sock;
	WSAEVENT event = WSACreateEvent();
	if (NULL == event)
	{
		int error = WSAGetLastError();
		throw "Create event error";
	}
	m_event[m_nEventTotal] = event;
	m_nEventTotal++;
	BindSocket();
}

CNetEvent::CNetEvent()
{

}

CNetEvent::~CNetEvent(void)
{
	if (0 != m_nEventTotal)
	{
		for (int i = 0; i < m_nEventTotal; i++)
		{
			BOOL bRet = WSACloseEvent(m_event[i]);
			if (!bRet)
			{
				int error = WSAGetLastError();
				throw "Close event error";
			}
		}
	}
	Init();
}

CNetEvent& CNetEvent::operator =(Socket &sock)
{
	assert((bool)sock);
	m_sock[m_nEventTotal] = sock;
	WSAEVENT event = WSACreateEvent();
	if (NULL == event)
	{
		int error = WSAGetLastError();
		throw "Create event error";
	}
	m_event[m_nEventTotal] = event;
	m_nEventTotal++;
	BindSocket();
	return *this;
}

int CNetEvent::BindSocket(void)
{
	assert(m_nEventTotal > 0);
	int nRet = WSAEventSelect((SOCKET)(m_sock[m_nEventTotal - 1]), m_event[m_nEventTotal - 1],
		FD_READ | FD_WRITE | FD_CONNECT | FD_ACCEPT | FD_CLOSE);
	if (nRet == SOCKET_ERROR)
		throw "set event error";
	return 0;
}

void CNetEvent::AddSocketInfo(net::Socket &sock)
{
	if ((bool)(sock))return;
	m_sock[m_nEventTotal - 1] = sock;
	WSAEVENT event = WSACreateEvent();
	if (NULL == event)
	{
		int error = WSAGetLastError();
		throw "Create event error";
	}
	m_event[m_nEventTotal] = event;
	m_nEventTotal++;
	BindSocket();
}

void CNetEvent::DelSockeInfo(net::Socket &sock)
{
	assert(m_nEventTotal);
	for (int i = 0; i < m_nEventTotal; i++)
	{
		if (m_sock[i] == sock)
		{
			BOOL bRet = WSACloseEvent(m_event[i]);
			if (!bRet)
			{
				int error = WSAGetLastError();
				throw "Close event error";
			}
			break;
		}
	}
}

//分析网络事件
int CNetEvent::DoEvent()
{
	WSANETWORKEVENTS NetworkEvents;
	DWORD dwEvent = 0;
	dwEvent = WSAWaitForMultipleEvents(m_nEventTotal, m_event, FALSE, WSA_INFINITE, FALSE);
	if (WSA_WAIT_FAILED == dwEvent)
		throw "wait for multiple events error";
	int nRet = WSAEnumNetworkEvents((SOCKET)m_sock[dwEvent - WSA_WAIT_EVENT_0], 
		m_event[dwEvent - WSA_WAIT_EVENT_0], &NetworkEvents); 
	if (nRet == SOCKET_ERROR)
	{
		throw "enum network events error";
	}

	if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
	{
		if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
		{
			return ACCEPT;
		}
	}
	else if (NetworkEvents.lNetworkEvents & FD_CONNECT)
	{
		if (NetworkEvents.iErrorCode[FD_CONNECT_BIT] != 0)
		{
			m_sock[dwEvent - WSA_WAIT_EVENT_0].m_bConnect = true;
			return CONNECT;
		}
		else
		{
			return CONNECT_ERROR;
		}
	}
	else if (NetworkEvents.lNetworkEvents & FD_READ)
	{
		if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
		{
			return READ;
		}
	}
	else if (NetworkEvents.lNetworkEvents & FD_WRITE)
	{
		if (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
		{
			return WRITE;
		}
	}
	else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
	{
		if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
		{
			return CLOSE;
		}
	}
	return 0;
}
//////////////////////////////////////