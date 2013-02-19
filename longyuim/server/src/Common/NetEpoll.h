
#ifndef _NET_EPOLL_H_
#define _NET_EPOLL_H_

#include <sys/epoll.h>

#include "include.h"
#include "CriticalSection.h"
#include "NetSocket.h"
#include "sigslot.h"


typedef std::map<int, CNetSocket*> NET_SOCKET_LIST;
typedef std::map<int, CNetSocket*>::iterator NET_SOCKET_LIST_ITER;

#define DEF_EPOLL_SIZE 10240
#define DEF_EPOLL_TIMEOUT 0

class CNetEpoll
{
public:
	CNetEpoll();
	~CNetEpoll();

	bool Init(unsigned int aiMaxSocketSize = DEF_EPOLL_SIZE);
	bool Destroy();

	void SetMaxFdNumber(unsigned int aiMaxFdNumber){ miMaxFdNumber = aiMaxFdNumber; }

	int AddEpollEvent(int iSocket, unsigned int ulEvent);
	int ModifyEpollEvent(int iSocket, unsigned int ulEvent);
	int DelEpollEvent(int iSocket);

	int CheckEpollEvent(int time_out=0);
	int ProcessEpollEvent(int aiEventSize);

	bool SendData(int fd, const char* buffer, const int length);
	bool SendData();
	bool SendAllData(const char* buffer, const int length);
	bool RecvData();

	bool Addfd(CNetSocket* apNetSocket);
	bool Delfd(CNetSocket* apNetSocket);
	bool Addfd(int fd);
	bool Delfd(int fd);
	bool Findfd(int fd);

	unsigned int GetConnectedSize();
	bool CloseConnect();

	void Dump();
	void TimeOutWork();

	bool WaitSendEvent();
	bool WaitRecvEvent();

private:
	bool Delfd(NET_SOCKET_LIST_ITER iter);

public:
		sigslot::signal3<int, char*, int> RecvFrom;
		sigslot::signal1<int> OnErrorNotice;
		bool mbHasListenFd;
		bool mbKeepAlive;
private:
	NET_SOCKET_LIST moNetSocketList;
	CCriticalSection moFdSection;
	int miEpfd;
	struct epoll_event mstruEvent[DEF_EPOLL_SIZE];
	CEvent mSendEvent;
	CEvent mRecvEvent;
	unsigned int miMaxFdNumber;
};

#endif //_NET_EPOLL_H_






