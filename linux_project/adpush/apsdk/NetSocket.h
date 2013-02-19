/********************************************************************
	created:	2011/03/08
	created:	8:3:2011   10:01
	file base:	NetSocket
	file ext:	h
	author:		王立卫
	
	purpose:	TCP协议SOCKET接口类
*********************************************************************/
#ifndef _NET_SOCKET_H_
#define _NET_SOCKET_H_

#include "base/include.h"
#include "base/pack/NetPack.h"
#include "base/list.h"

#define DEF_LOCAL_ADDR "127.0.0.1"
#define DEF_SOCKET_CATCH_LEN (10*1024)
#define RECV_CATCH_LEN (DEF_SOCKET_CATCH_LEN+DEF_BUFFER_LEN+1)
#define SEND_CATCH_LEN (DEF_SOCKET_CATCH_LEN+1)

#if defined(__linux__) || defined(__APPLE__)

#define SOCKET int

#endif

#ifdef _WIN32

typedef int socklen_t;

class CWinNet
{
public:
	CWinNet()
	{
		WSADATA wsd;
		WSAStartup(MAKEWORD(2,2),&wsd);
	}
	~CWinNet()
	{
		WSACleanup();
	}
	static CWinNet* Instance()
	{
		if( PWinNetInstance == 0 )
		{
			PWinNetInstance = new (CWinNet);
		}
		return PWinNetInstance; 
	}

	static CWinNet* PWinNetInstance;

};

#endif

class STRU_NET_DATA_INFO
{
public:
	STRU_NET_DATA_INFO()
	{
		buffer = NULL;
		length = 0;
	}	

	~STRU_NET_DATA_INFO(){}

	STRU_NET_DATA_INFO(const STRU_NET_DATA_INFO &info)
	{
		if(this != &info)
		{
			buffer = info.buffer;
			length = info.length;
		}
	}
	STRU_NET_DATA_INFO& operator = (const STRU_NET_DATA_INFO &info)
	{
		if(this != &info)
		{
			buffer = info.buffer;
			length = info.length;
		}
		return *this;
	}
public:
	char* buffer;
	int length;
};

//网络状态
enum NET_STAT
{
	//错误
	TCP_ERROR = ERROR,
	//监听
	COMMON_TCP_LISTEN, 
	COMMON_TCP_SYN_SENT,
	COMMON_TCP_SYN_RECEIVED, 
	COMMON_TCP_ESTABLISHED, 
	COMMON_TCP_CONNECTING,
	COMMON_TCP_CONNECTED,
	COMMON_TCP_CLOSED
};

enum SEND_STAT
{
	SEND_NULL = ERROR,
	SENDINT,
	SENDED
};

class CNetSocket
{
public:
	CNetSocket();
	CNetSocket(CNetPack *pack)
	{
		assert(pack != NULL);
		m_pNetPack = pack;
	}
	~CNetSocket();

	inline void SetNetPack(CNetPack *pack)
	{
		assert(pack != NULL);
		m_pNetPack = pack;
	}

	//创建socket，并绑定到指定端口
	//参数数据为本地字节序
	bool CreateSocket(const char* ip, const short port);
	//创建socket，不需要绑定
	bool CreateSocket(void);

	//关闭套接字，并清除相关资源
	bool Close(int flag = 2);
	//只是关闭套接字并不清除资源
	void CloseWR(int flag = 2);

	void CloseSocket(SOCKET socket)
	{
#if defined(__linux__) || defined(__APPLE__)
		close(socket);
#endif

#ifdef _WIN32
		closesocket(socket);
#endif
	}

	//启动监听
	bool Listen();
	//本地字节序
	bool ConnectServer(const char* ip, const short port);

	//ACCEPT ip 和 port均为本地字节序
	int Accept(unsigned int &ip, uint16_t &port);

	bool SetNoBlock();

	int SendData(const char* buffer, const int length);

	int SendData();

	bool RecvData(char* buffer, int &length);

	bool RecvData();

	const SOCKET GetSocket(){ return miSocket; }

private:
	int _SendData(const char* buffer, const int length);
	int SendCacheData(void);
	//nKeepAlive-是否开启存活
	//nKeepIdle-多长时间无数据收发, 则探测
	//nKeepInterval-探测发包时间间隔
	//nKeepCnt-探测尝试次数
	int SetTcpSockKeepAlive(int nKeepAlive,int nKeepIdle,
		int nKeepInterval, int nKeepCnt);

public:
	NET_STAT moNetStat;
	SOCKET miSocket;
	bool mbListenSocket;
	bool mbClientSocket;
	bool mbCanSend;
	SEND_STAT moSendStat;
	char mszResendBuffer[SEND_CATCH_LEN];
	CCriticalSection moSendSection;
	CCriticalSection moRecvSection;
	int miResendLength;
	_List<STRU_NET_DATA_INFO> moSendList;
	_List<STRU_NET_DATA_INFO> moRecvList;
	char mszRecvCache[RECV_CATCH_LEN];
	int miRecvCacheLength;
	CNetPack*  m_pNetPack;
};
#endif //_NET_SOCKET_H_

















