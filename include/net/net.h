#ifndef _NET_H_
#define _NET_H_

#include <string>
#include <vector>
#include <cassert>
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")

#include "..\common\common.h"
using namespace wlw;

namespace wlw
{
	////////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************************
	在一个大的联系缓存中给每个用户分配一小的缓存使用.
	:)不能使用别人的内存奥
	**********************************************************************************/
	class CMemoryUnit
	{
	public:
		CMemoryUnit();
		~CMemoryUnit();

		int AddBuffer(const char* buf, const size_t length);
		int RemoveBuffer(const size_t length);

	public:
		char *m_pUnitPos;
		size_t m_nUnitSize;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CMemoryPool
	{
	public:
		CMemoryPool(size_t poolsize = 1024 * 1024 * 5, size_t unitsize = 1024 * 10);
		~CMemoryPool();

		void Init();
		void Free();

	private:
		size_t calUnitNumbers();
	public:
		char *m_pEntryPos;
		vector<CMemoryUnit*> m_vecMemUnitList;
	private:
		size_t m_nPoolSize;
		size_t m_nUnitSize;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CWinInit
	{
	public:
		CWinInit()
		{
			WSADATA wsaData;
			::WSAStartup(2, &wsaData);
		}
		~CWinInit()
		{
			::WSACleanup();
		}
	};
	////////////////////////////////////////////////////////////////////////////////////
	/************************************************************************/
	/** 字节序转换函数 
	*/
	/************************************************************************/

	static const uint32 n2hl(uint32 value)
	{
		return ntohl(value);
	}

	static const uint32 h2nl(uint32 value)
	{
		return htonl(value);
	}

	static const uint16 n2hs(uint16 value)
	{
		return ntohs(value);
	}

	static const uint16 h2ns(uint16 value)
	{
		return htons(value);
	}

	/************************************************************************/
	/** 地址 
	*/
	/************************************************************************/
	class CSocketAddr : public sockaddr_in
	{
	public:
		CSocketAddr(void);
		CSocketAddr(string ip, short port);
		CSocketAddr(int ip, short port);
		CSocketAddr(const CSocketAddr &addr);
		~CSocketAddr(void);

		string ip2str(void);
		int ip2h(void);//转换为本地字节序的IP
		short port2h(void);//转换为本地字节序的PORT

		CSocketAddr& operator= (const CSocketAddr &addr);
	private:
		void Init(void);
	private:

	};

	inline void CSocketAddr::Init(void)
	{
		sin_family = AF_INET;
	}

	inline CSocketAddr& CSocketAddr::operator = (const CSocketAddr &addr)
	{
		if (this == &addr)return *this;
		sin_addr = addr.sin_addr;
		sin_family = addr.sin_family;
		sin_port = addr.sin_port;
		memcpy(sin_zero, addr.sin_zero, 8*sizeof(char));
		return *this;
	}
	////////////////////////////////////////////////////////////////////////////////////
	class CPingBase
	{
	public:
		CPingBase(void);
		CPingBase(CSocketAddr &addr);
		~CPingBase(void);
		const uint32 GetPingResult(void) const { return m_nPingResult; }
	private:
		void ping(void);
	private:

		uint32 m_nPingResult;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CProxyInfo
	{
	public:
		enum PROXY_TYPE { PROXY_NO = 0, PROXY_HTTP10, PROXY_HTTP11, PROXY_SOCKET4, PROXY_SOCKET5 };
		CProxyInfo(void);
		~CProxyInfo(void);

	private:
		std::string m_strUser;
		std::string m_strPassword;
		uint32 m_nIp;
		uint16 m_nPort;
		PROXY_TYPE m_nType;
	};

	////////////////////////////////////////////////////////////////////////////////////
	/**
	* 原始套接字
	*/
	class CRowSocket
	{
	public:
		CRowSocket();
		~CRowSocket();

	private:
		SOCKET m_sock;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CUdpSocket
	{
	public:
		CUdpSocket(void);
		CUdpSocket(const size_t ip, const short port);
		CUdpSocket(const CSocketAddr &addr);
		~CUdpSocket();

		int Bind();
		int Sendto(const char *buffer, const int length, const CSocketAddr &addr);
		int Recvfrom(char *buffer, int &lenght, CSocketAddr &addr);

		void Close();
		bool SetBlock();
		bool SetNoblock();
		bool SetSendTimeOut(const size_t time = 10);
		bool SetRecvTimeOut(const size_t time = 10);
		bool SetSendBufferSize(const size_t bufsize = 1024 * 10);
		bool SetRecvBufferSize(const size_t bufsize = 1024 * 10);

	private:
		bool Create();
	public:
		SOCKET m_sock;
		CSocketAddr m_addr;
	};
	////////////////////////////////////////////////////////////////////////////////////

	typedef vector<CUdpSocket*> UdpSocketList;
	typedef vector<CUdpSocket*>::iterator UdpSocketIter;

	class  CUdpSocketManager
	{
	public:
		CUdpSocketManager();
		~CUdpSocketManager();

		CUdpSocket* Create();
		bool Destroy();
		bool ClearnAll();

	private:
		UdpSocketList m_UdpSockets;
	};

	////////////////////////////////////////////////////////////////////////////////////
	class CTcpSocket
	{
	public:
		CTcpSocket();
		CTcpSocket(const CTcpSocket &ts);
		CTcpSocket(const size_t ip, const short port);
		~CTcpSocket();

		bool Connect();
		size_t Send(const char *buffer, const size_t length);
		int Recv(char *buffer, size_t length);
		void Close();
		bool SetBlock();
		bool SetNoblock();
		bool SetSendTimeOut(size_t time = 10);
		bool SetRecvTimeOut(size_t time = 10);
		bool SetSendBufferSize(size_t bufsize = 1024 * 10);
		bool SetRecvBufferSize(size_t bufsize = 1024 * 10);


		CTcpSocket& operator = (const CTcpSocket &ts);

	private:
		bool Create();
	public:
		SOCKET m_sock;
		size_t m_nIp;
		short m_sPort;
		bool m_bConnected;
	};
	////////////////////////////////////////////////////////////////////////////////////

	typedef vector<CTcpSocket*> TcpSocketList;
	typedef vector<CTcpSocket*>::iterator TcpSocketIter;

	class  CTcpSocketManager
	{
	public:
		CTcpSocketManager();
		~CTcpSocketManager();

		CTcpSocket* Create();
		bool Destroy();
		bool ClearnAll();

	private:
		TcpSocketList m_TcpSockets;
	};

	////////////////////////////////////////////////////////////////////////////////////
	class CNetEvent
	{
	public:
		CNetEvent(void);
		~CNetEvent(void);

	public:
		WSAEVENT m_wsaEvent;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CNetSelect
	{
	public:
		CNetSelect(void);
		~CNetSelect(void);

		void SocketSet(CUdpSocket *sock);
		int NetSelectFun(unsigned int sock);
		int SocketReadSelect(CUdpSocket *sock);
		int SocketWriteSelect(CUdpSocket *sock);
		int SocketExceptSelect(CUdpSocket *sock);
		void SetZero();

	public:
		fd_set m_fdRead;
		fd_set m_fdWrite;
		fd_set m_fdExcept; 
		struct timeval tv;
	};
	////////////////////////////////////////////////////////////////////////////////////
	/**
	* 实现PING功能，检测网络是否可达
	* 1. 直接使用WIN的icmp.dll模块实现
	* 2. 写ICMP协议来实现
	* 这里使用第二种方法实现
	*/
	class CIcmp
	{
	public:

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
		//ICMP 包的最小长度,恰好ICMP包头的长度
#define ICMP_MIN 8
#define STATUS_FAILED 0xFFFF
#define DEF_PACKET_SIZE    32
		 //发送数据报的个数
#define DEF_PACKET_NUMBER  4   
#define ICMP_MAX_PACKET 1024

#pragma pack(1)
		typedef struct iphrd
		{
			uint32 h_len:4; // length of the header
			uint32 version:4; // Version of IP
			uint8 tos; // Type of service
			uint16 total_len; // total length of the packet
			uint16 ident; // unique identifier
			uint16 frag_and_flags; // flags
			uint8 ttl;
			uint8 proto; // protocol (TCP, UDP etc)
			uint16 checksum; // IP checksum
			uint32 sourceIP;
			uint32 destIP; 
		}IPHDR, *PIPHDR;

		typedef struct icmphrd
		{
			uint8 i_type;
			uint8 i_code; /* type sub code */
			uint16 i_cksum;
			uint16 i_id;
			uint16 i_seq;
			/* This is not the std header, but we reserve space for time */
			uint32 timestamp; 
		}ICMPHDR, *PICMPHDR;
#pragma pack()

		CIcmp(void);
		CIcmp(CSocketAddr &addr);
		~CIcmp(void);

		bool ping(void);
	private:
		bool Init(void);
		void FillData(const uint8 *buffer, uint32 length);
		uint16 CheckSum(uint16 *buffer, uint32 length);
		uint32 DecodeIcmp(uint8 *buffer, uint32 length, CSocketAddr &addrFrom);

	private:
		CSocketAddr m_AddrTo;
		CSocketAddr m_AddrFrom;
		SOCKET m_RawSock;
		uint32 m_nReturn;
		uint32 m_nTimeout;
		uint32 m_nSegNo;
	};
	////////////////////////////////////////////////////////////////////////////////////
};

#endif //_NET_H_