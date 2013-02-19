#ifndef _NET_SELECT_H_
#define _NET_SELECT_H_

#include "base/include.h"
#include "NetSocket.h"

#define DEF_FD_SIZE 2

typedef void (*ptrOnNotify)(void* param, uint32_t fd);
typedef void (*ptrOnRecvDataNotify)(void* param, uint32_t fd, char *buffer, uint32_t length);

class CNetSelect
{
public:
	CNetSelect();
	CNetSelect(CNetPack *pack)
	{
		assert(pack != NULL);
		m_pNetPack = pack;
	}
	~CNetSelect();

	inline void SetPack(CNetPack *pack)
	{
		assert(pack != NULL);
		m_pNetPack = pack;
	}

	bool Init(unsigned int aiMaxSocketSize = DEF_FD_SIZE);
	bool Destroy();
	int CheckEvent(int time_out=0);
	int ProcessEvent(int aiEventSize);
	bool SendData(int fd, const char* buffer, const int length);
	bool Addfd(CNetSocket* apNetSocket);
	bool Delfd(CNetSocket* apNetSocket);
	void SetCallBackFun(ptrOnNotify pError, ptrOnNotify pConnect, ptrOnRecvDataNotify pRecvData, void* param);
private:
	bool Setfd(int fd);
	//flag: true add false delete
	//void ModifyReadEvent(bool flag);
public:
		
	uint32_t m_currentFdNum;
private:
	fd_set m_stReadSet;
	fd_set m_stWriteSet;
	fd_set m_stExceptSet;
	CNetSocket* m_pSocket[DEF_FD_SIZE];
	uint32_t m_maxFd;
	ptrOnNotify  ptr_error_notify;
	ptrOnNotify  ptr_connect_notify;
	ptrOnRecvDataNotify ptr_data_notify;
	void* m_pUserParam;
	CNetPack* m_pNetPack;
};


#endif //_NET_SELECT_H_
