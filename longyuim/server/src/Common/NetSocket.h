
#ifndef _NET_SOCKET_H_
#define _NET_SOCKET_H_

#include "include.h"
#include "CriticalSection.h"
#include "NetPack.h"
#include "list.h"

#define DEF_LOCAL_ADDR "127.0.0.1"
#define DEF_SOCKET_CATCH_LEN (10*1024)

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

enum NET_STAT
{
	TCP_ERROR = ERROR,
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
	~CNetSocket();

	//本地字节序
	bool CreateSocket(const char* ip, const short port);
	bool CreateSocket(void);

	bool Close(int flag = 2);

	bool Listen();
	//本地字节序
	bool ConnectServer(const char* ip, const short port);

	//ACCEPT ip 和 port均为本地字节序
	int Accept(int &ip, short &port);

	bool SetNoBlock();

	int SendData(const char* buffer, const int length);

	int SendData();

	bool RecvData(char* buffer, int &length);

	bool RecvData();

	const int GetSocket(){ return miSocket; }

	void Dump();
	void TimeOutWork();

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
	int miSocket;
	bool mbListenSocket;
	bool mbClientSocket;
	bool mbCanSend;
	SEND_STAT moSendStat;
private:
	char mszResendBuffer[DEF_BUFFER_LEN+1];
	CCriticalSection moSendSection;
	CCriticalSection moRecvSection;
	int miResendLength;
	_List<STRU_NET_DATA_INFO> moSendList;
	_List<STRU_NET_DATA_INFO> moRecvList;
	char mszRecvCache[DEF_BUFFER_LEN*2+1];
	int miRecvCacheLength;
};
#endif //_NET_SOCKET_H_

















