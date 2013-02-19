#include "stdafx.h"
#include "net.h"
using namespace wlw;

////////////////////////////////////////////////////////////////////////////////////
CMemoryUnit::CMemoryUnit()
{

}

CMemoryUnit::~CMemoryUnit()
{

}

int CMemoryUnit::AddBuffer(const char *buf, const size_t length)
{
	assert(length + m_nUnitSize < 1024 * 10);
	memcpy(m_pUnitPos + m_nUnitSize, buf, length);
	m_nUnitSize += length;
	return (int)m_nUnitSize;
}

int CMemoryUnit::RemoveBuffer(const size_t length)
{
	assert(m_nUnitSize >= length);
	memset(m_pUnitPos, 0, length);
	memmove(m_pUnitPos, m_pUnitPos + length, m_nUnitSize - length);
	m_nUnitSize -= length;
	return m_nUnitSize;
}

////////////////////////////////////////////////////////////////////////////////////
CMemoryPool::CMemoryPool(size_t poolsize/* = 1024 * 1024 * 11*/, size_t unitsize/* = 1024 * 10*/)
{
	m_nPoolSize = poolsize;
	m_nUnitSize = unitsize;
}

CMemoryPool::~CMemoryPool()
{

}

void CMemoryPool::Init()
{
	size_t nUnitNumbers = calUnitNumbers();
	CMemoryUnit *pMemUnit = new CMemoryUnit[nUnitNumbers];
	for (size_t i = 0; i < nUnitNumbers; i++)
	{
		m_vecMemUnitList.push_back(&pMemUnit[i]);
	}
	pMemUnit = NULL;

	m_pEntryPos = new char[m_nPoolSize];
	memset(m_pEntryPos, 0, m_nPoolSize);
	vector<CMemoryUnit*>::iterator iter = m_vecMemUnitList.begin();
	for (int i = 0;iter != m_vecMemUnitList.end();iter++, i++)
	{
		CMemoryUnit* pMemUnit = static_cast<CMemoryUnit*>(*iter);
		pMemUnit->m_pUnitPos = m_pEntryPos + i * m_nUnitSize;
		pMemUnit->m_nUnitSize = 0;
	}
}

void CMemoryPool::Free()
{
	vector<CMemoryUnit*>::iterator iter = m_vecMemUnitList.begin();
	CMemoryUnit *pMemUnit = static_cast<CMemoryUnit*>(*iter);
	delete [] pMemUnit;
	pMemUnit = NULL;
	m_vecMemUnitList.clear();
	delete [] m_pEntryPos;
	m_pEntryPos = NULL;
}

size_t CMemoryPool::calUnitNumbers()
{
	size_t size = 0;
	size = m_nPoolSize / m_nUnitSize;
	if (m_nPoolSize % m_nUnitSize)
	{
		size++;
	}
	return size;
}
////////////////////////////////////////////////////////////////////////////////////
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

CSocketAddr::CSocketAddr(const CSocketAddr &addr)
{
	*this = addr;
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
////////////////////////////////////////////////////////////////////////////////////
CPingBase::CPingBase()
{

}
CPingBase::CPingBase(CSocketAddr &addr)
{

}

CPingBase::~CPingBase()
{

}

void CPingBase::ping()
{

}
////////////////////////////////////////////////////////////////////////////////////
CProxyInfo::CProxyInfo()
{

}
CProxyInfo::~CProxyInfo()
{

}

////////////////////////////////////////////////////////////////////////////////////
CUdpSocket::CUdpSocket()
{

}
CUdpSocket::CUdpSocket(const size_t ip, const short port)
:m_addr(ip, port)
{
	m_sock = INVALID_SOCKET;
}

CUdpSocket::CUdpSocket(const CSocketAddr &addr)
:m_addr(addr)
{
	m_sock = INVALID_SOCKET;
}

CUdpSocket::~CUdpSocket()
{
	if (m_sock != INVALID_SOCKET)
	{
		Close();
	}
}

int CUdpSocket::Bind()
{
	int nRet = ::bind(m_sock,  (sockaddr*)&m_addr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "bind socket error code = %d", GetLastError());
		return 1;
	}
	return 0;
}

int CUdpSocket::Sendto(const char *buffer, const int length, const CSocketAddr &addr)
{
	size_t nSendedSize = 0;
	nSendedSize = sendto(m_sock, buffer, length, 0, (sockaddr*)&addr, sizeof(sockaddr));
	if (nSendedSize == SOCKET_ERROR)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "send buffer error code = %d", GetLastError());
	}
	return nSendedSize;
}

int CUdpSocket::Recvfrom(char *buffer, int &length, CSocketAddr &addr)
{
	int nRecvedSize = 0;
	int nAddrLen = sizeof(sockaddr);
	nRecvedSize = recvfrom(m_sock, buffer, length, 0, (sockaddr*)&addr, &nAddrLen);
	return nRecvedSize;
}

void CUdpSocket::Close()
{
	assert(m_sock != INVALID_SOCKET);
	shutdown(m_sock, SD_BOTH);
	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
}

inline bool CUdpSocket::SetBlock()
{
	assert(m_sock != INVALID_SOCKET);
	u_long unMode = 0;
	if(SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &unMode))
		return false;
	return true;
}

inline bool CUdpSocket::SetNoblock()
{
	assert(m_sock != INVALID_SOCKET);
	u_long unMode = 1;
	if(SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &unMode))
		return false;
	return true;
}

inline bool CUdpSocket::SetSendTimeOut(const size_t time /*= 10*/)
{
	assert(m_sock != INVALID_SOCKET);
	return true;
}
inline bool CUdpSocket::SetRecvTimeOut(const size_t time /*= 10*/)
{
	assert(m_sock != INVALID_SOCKET);
	return true;
}
inline bool CUdpSocket::SetSendBufferSize(const size_t bufsize /*= 1024 * 10*/)
{
	assert(m_sock != INVALID_SOCKET);
	return true;
}
inline bool CUdpSocket::SetRecvBufferSize(const size_t bufsize /*= 1024 * 10*/)
{
	assert(m_sock != INVALID_SOCKET);
	return true;
}

bool CUdpSocket::Create()
{
	assert(m_sock != INVALID_SOCKET);
	m_sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sock == INVALID_SOCKET)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "创建SOCKET失败，ErrorCode = %d", WSAGetLastError());
		return false;
	}
	//设置SOCKET为非阻塞
	SetNoblock();
	return true;
}
////////////////////////////////////////////////////////////////////////////////////
CUdpSocketManager::CUdpSocketManager()
{

}
CUdpSocketManager::~CUdpSocketManager()
{

}
CUdpSocket* CUdpSocketManager::Create()
{
	CUdpSocket* psock = new CUdpSocket;
	return psock;
}

bool CUdpSocketManager::Destroy()
{
	return true;
}

bool CUdpSocketManager::ClearnAll()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////
CTcpSocket::CTcpSocket()
{
	m_sock = INVALID_SOCKET;
	m_nIp = 0;
	m_sPort = 0;
	m_bConnected = false;
}

CTcpSocket::CTcpSocket(const CTcpSocket &ts)
{
	if (this != &ts)
	{
		m_sock = INVALID_SOCKET;
		m_nIp = ts.m_nIp;
		m_sPort = ts.m_sPort;
		m_bConnected = ts.m_bConnected;
		Create();
	}
}

CTcpSocket::CTcpSocket(const size_t ip, const short port)
{
	m_sock = INVALID_SOCKET;
	m_nIp = ip;
	m_sPort = port;
	m_bConnected = false;
	Create();
}

CTcpSocket::~CTcpSocket()
{
	if (m_sock != INVALID_SOCKET)
	{
		Close();
	}
	m_nIp = 0;
	m_sPort = 0;
	m_bConnected = false;
}

bool CTcpSocket::Create()
{
	assert(m_sock == INVALID_SOCKET);
	m_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "创建SOCKET失败，ErrorCode = %d", WSAGetLastError());
		return false;
	}
	//设置SOCKET为非阻塞
	SetNoblock();
	return true;
}

bool CTcpSocket::Connect()
{
	assert(m_sock != INVALID_SOCKET);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(m_nIp);
	addr.sin_port = htons(m_sPort);

	//PrintLog(_LOG_LEVEL_DEBUG, "连接服务器， ip = %s, port = %d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	int nRet = ::connect(m_sock, (sockaddr*)&addr, sizeof(sockaddr_in));
	if (nRet == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "正在连接服务器，SOCKET = %d", m_sock);
			return true;
		}
		else
		{
			PrintLog(_LOG_LEVEL_DEBUG, "连接服务器失败： ErrorCode = %d", WSAGetLastError());
			return false;
		}
	}
	return true;
}

size_t CTcpSocket::Send(const char *buffer, const size_t length)
{
	assert(m_sock != INVALID_SOCKET);

	m_bConnected = true;
	size_t nSendedLen = 0;
	int nRet = ::send(m_sock, buffer, length, 0);
	nSendedLen = nRet;
	if (nRet == SOCKET_ERROR)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "发送数据失败： ErrorCode = %d", WSAGetLastError());
	}
	else if(nRet < length)
	{
		//有数据未发送完
		while(nSendedLen < length)
		{
			assert(m_sock != INVALID_SOCKET);
			nRet = ::send(m_sock, buffer + nSendedLen, length - nSendedLen, 0);
			if (nRet == SOCKET_ERROR)
			{
				//发送剩余数据时失败
				nSendedLen = nRet;
				PrintLog(_LOG_LEVEL_DEBUG, "发送数据失败： ErrorCode = %d", WSAGetLastError());
				break;
			}
			nSendedLen += nRet;
		}
	}
	PrintLog(_LOG_LEVEL_DEBUG, "发送数据大小： %d, SOCKET = %d", nSendedLen, m_sock);
	m_bConnected = true;
	return nSendedLen;
}

int CTcpSocket::Recv(char *buffer, size_t length)
{
	assert(m_sock != INVALID_SOCKET);
	if (!m_bConnected)return 0;

	int nRecvedLen = 0;
	int nRet = ::recv(m_sock, buffer, length, 0);
	if (nRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			nRet = 0;
		}
		else
		{
			PrintLog(_LOG_LEVEL_DEBUG, "接收数据失败， ErrorCode = %d,  SOCKET = %d", WSAGetLastError(), m_sock);
		}
	}
	else
	{
		if (nRet != 0)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "接收数据大小： %d--%d, SOCKET = %d", length, nRet, m_sock);
		}
	}
	nRecvedLen = nRet;
	return nRecvedLen;
}

void CTcpSocket::Close()
{
	assert(m_sock != INVALID_SOCKET);
	shutdown(m_sock, SD_BOTH);
	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
}

inline bool CTcpSocket::SetBlock()
{
	u_long unMode = 0;
	if(SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &unMode))
		return false;
	return true;
}

inline bool CTcpSocket::SetNoblock()
{
	u_long unMode = 1;
	if(SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &unMode))
		return false;
	return true;
}

inline bool CTcpSocket::SetSendTimeOut(size_t time /*= 10*/)
{
	return true;
}

inline bool CTcpSocket::SetRecvTimeOut(size_t time /*= 10*/)
{
	return true;
}

inline bool CTcpSocket::SetRecvBufferSize(size_t bufsize/* = 1024*10 */)
{
	return true;
}

inline bool CTcpSocket::SetSendBufferSize(size_t bufsize/* = 1024*10 */)
{
	return true;
}

CTcpSocket& CTcpSocket::operator = (const CTcpSocket &ts)
{
	if (this != &ts)
	{
		m_nIp = ts.m_nIp;
		m_sPort = ts.m_sPort;
		m_bConnected = ts.m_bConnected;
		Create();
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////
CTcpSocketManager::CTcpSocketManager()
{

}
CTcpSocketManager::~CTcpSocketManager()
{

}
CTcpSocket* CTcpSocketManager::Create()
{
	CTcpSocket* psock = new CTcpSocket;
	return psock;
}

bool CTcpSocketManager::Destroy()
{
	return true;
}

bool CTcpSocketManager::ClearnAll()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////
CNetEvent::CNetEvent()
{
	m_wsaEvent = WSA_INVALID_EVENT;
	m_wsaEvent = ::WSACreateEvent();
	if (m_wsaEvent == WSA_INVALID_EVENT)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "创建网络事件失败： ErrorCode = %d", WSAGetLastError());
	}
}

CNetEvent::~CNetEvent()
{
	if (m_wsaEvent != WSA_INVALID_EVENT)
	{
		::WSACloseEvent(m_wsaEvent);
		m_wsaEvent = WSA_INVALID_EVENT;
	}
}
////////////////////////////////////////////////////////////////////////////////////
CNetSelect::CNetSelect()
{
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	FD_ZERO(&m_fdRead);
	FD_ZERO(&m_fdWrite);
	FD_ZERO(&m_fdExcept);
}

CNetSelect::~CNetSelect()
{
	FD_ZERO(&m_fdRead);
	FD_ZERO(&m_fdWrite);
	FD_ZERO(&m_fdExcept);
}

void CNetSelect::SetZero()
{
	FD_ZERO(&m_fdRead);
	FD_ZERO(&m_fdWrite);
	FD_ZERO(&m_fdExcept);
}

int CNetSelect::SocketReadSelect(CUdpSocket *sock)
{
	assert(sock != NULL);
	int nRet = 0;
	nRet = FD_ISSET(sock->m_sock, &m_fdRead);
	return nRet;
}

int CNetSelect::SocketWriteSelect(CUdpSocket *sock)
{
	assert(sock != NULL);
	int nRet = 0;
	nRet = FD_ISSET(sock->m_sock, &m_fdWrite);
	return nRet;
}

int CNetSelect::SocketExceptSelect(CUdpSocket *sock)
{
	assert(sock != NULL);
	int nRet = 0;
	nRet = FD_ISSET(sock->m_sock, &m_fdExcept);
	//PrintLog(_LOG_LEVEL_DEBUG, "Get except return = %d, SOCKET = %d", nRet, sock->m_sock);
	return nRet;
}

void CNetSelect::SocketSet(wlw::CUdpSocket *sock)
{
	assert(sock != NULL);
	FD_SET(sock->m_sock, &m_fdRead);
	FD_SET(sock->m_sock, &m_fdWrite);
	FD_SET(sock->m_sock, &m_fdExcept);
}

int CNetSelect::NetSelectFun(unsigned int sock)
{
	int nRet = 0;
	nRet = select(sock, &m_fdRead, &m_fdWrite, &m_fdExcept, &tv);
	return nRet;
}
////////////////////////////////////////////////////////////////////////////////////
CIcmp::CIcmp()
{

}

CIcmp::CIcmp(CSocketAddr &addr)
:m_AddrTo(addr),m_RawSock(NULL)
{
	m_nTimeout = 1000;
	m_nSegNo = 0;
}

CIcmp::~CIcmp()
{

}

bool CIcmp::Init()
{
	m_RawSock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL, 0,WSA_FLAG_OVERLAPPED);
	if(m_RawSock == INVALID_SOCKET) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "WSASocket Error code = %d", WSAGetLastError());
		return false;
	}
	m_nReturn = setsockopt(m_RawSock,SOL_SOCKET,SO_RCVTIMEO,(char*)&m_nTimeout,sizeof(m_nTimeout));
	if(m_nReturn == SOCKET_ERROR) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "set socket recv opt error code = %d", WSAGetLastError());
		return false;
	}

	m_nReturn = setsockopt(m_RawSock,SOL_SOCKET,SO_SNDTIMEO,(char*)&m_nTimeout,sizeof(m_nTimeout));
	if(m_nReturn == SOCKET_ERROR) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "set socket send opt  error code = %d", WSAGetLastError());
		return false;
	} 
	return true;
}

void CIcmp::FillData(const uint8* buffer, uint32 length)
{
	PICMPHDR icmp_hdr; 
	uint8 *datapart; 
	icmp_hdr = (PICMPHDR)buffer;
	icmp_hdr->i_type = ICMP_ECHO; 
	icmp_hdr->i_code = 0; 
	icmp_hdr->i_id = (uint16)GetCurrentProcessId(); 
	icmp_hdr->i_cksum = 0; 
	icmp_hdr->i_seq = 0; 
	datapart = const_cast<uint8*>(buffer + sizeof(ICMPHDR)); 
	memset(datapart,'E', length - sizeof(ICMPHDR)); 
}

uint16 CIcmp::CheckSum(uint16 *buffer, uint32 length)
{
	uint32 cksum = 0; 
	while(length > 1)
	{ 
		cksum += *buffer++;
		length -= sizeof(uint16); 
	} 
	if(length)
	{ 
		cksum += *(uint8*)buffer; 
	} 
	cksum = (cksum >> 16) + (cksum & 0xffff); 
	cksum += (cksum >> 16); 
	return (uint16)(~cksum); 

}

uint32 CIcmp::DecodeIcmp(uint8 *buffer, uint32 length, CSocketAddr &addrFrom)
{
	PIPHDR iphdr = NULL;
	PICMPHDR icmphdr = NULL;
	uint16 iphdrlen = 0;

	iphdr = (PIPHDR)buffer;
	iphdrlen = (iphdr->h_len) * 4;

	if (length < iphdrlen + ICMP_MIN) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "Too small buffer from %s", addrFrom.ip2str());
	return 1;
	}

	icmphdr = (PICMPHDR)(buffer + iphdrlen);
	if (icmphdr->i_type != ICMP_ECHOREPLY) 
	{
		PrintLog(_LOG_LEVEL_DEBUG, "non-echo type %d recvd", icmphdr->i_type);
		return 1;
	}
	if (icmphdr->i_id != (uint16)GetCurrentProcessId())
	{
		PrintLog(_LOG_LEVEL_DEBUG, "The answer is not yours");
		return 1;
	}
	PrintLog(_LOG_LEVEL_DEBUG, "%d bytes from %s:", length, addrFrom.ip2str().c_str());
	PrintLog(_LOG_LEVEL_DEBUG, " icmp_seq = %d. ",icmphdr->i_seq);
	PrintLog(_LOG_LEVEL_DEBUG, " time: %d ms ",GetTickCount()- icmphdr->timestamp);
	return 0;

}

bool CIcmp::ping()
{
	uint32 nReturn = false;
	uint32 nTestReturn = 0;
	bool bInit = Init();
	uint8 *icmpData = new uint8[ICMP_MAX_PACKET];
	uint32 icmpDataLen = DEF_PACKET_SIZE;
	uint8 *recvData = new uint8[ICMP_MAX_PACKET];
	uint32 recvDataLen = 0;
	memset(icmpData, 0, ICMP_MAX_PACKET * sizeof(uint8));
	memset(recvData, 0, ICMP_MAX_PACKET * sizeof(uint8));

	icmpDataLen += sizeof(ICMPHDR);
	FillData(icmpData, icmpDataLen);

	for(int i = 0; i < 4; i++)
	{
		int bwrote;
		((PICMPHDR)icmpData)->i_cksum = 0;
		((PICMPHDR)icmpData)->timestamp = GetTickCount();

		((PICMPHDR)icmpData)->i_seq = m_nSegNo++;
		((PICMPHDR)icmpData)->i_cksum = CheckSum((USHORT*)icmpData,icmpDataLen); 

		nReturn = sendto(m_RawSock, (const char*)icmpData,icmpDataLen,0,(struct sockaddr*)&m_AddrTo,sizeof(sockaddr));
		if (nReturn == SOCKET_ERROR)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "Send icmp error code = %d", WSAGetLastError());
			if (WSAGetLastError() == WSAETIMEDOUT)
			{
				continue;
			}
		}

		if (nReturn < icmpDataLen)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "Send icmp error less than need.");	
		}

		int addrlen = sizeof(sockaddr);
		int recvlen = ICMP_MAX_PACKET;
		nReturn = ::recvfrom(m_RawSock, (char*)recvData, recvlen, 0, (struct sockaddr*)&m_AddrFrom,&addrlen);
		if (nReturn == SOCKET_ERROR)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "Send icmp error code = %d", WSAGetLastError());
			if (WSAGetLastError() == WSAETIMEDOUT) 
			{
				continue;
			}
		}
		int nSuccess = DecodeIcmp(recvData, recvlen, m_AddrFrom);
		if (nSuccess == 0)
		{
			nTestReturn++;
		}
		Sleep(1000);
	}
	delete icmpData;
	delete recvData;
	icmpData = NULL;
	recvData = NULL;
	if (nTestReturn > 0)
		return true;
	return false;
}
////////////////////////////////////////////////////////////////////////////////////