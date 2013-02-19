#ifndef _DNS_CHILD_WORKER_H_
#define _DNS_CHILD_WORKER_H_

#include "include.h"
#include "Time.h"
#include "FileStream.h"
#include "DNSInclude.h"
#include "DNSConfig.h"
#include "NetEpoll.h"
#include "DNSDealData.h"
#include "ThreadGroup.h"
#include <map>

//存活时间为120秒
#define KEEP_LIVE_TIME_OUT	120
//超时时间5分钟
#define CRS_DNS_TIMEOUT		300

typedef struct stru_DNS_NODE_INFO
{
	int fd;
	uint32 m_i32NodeId;
	uint64 m_i32GroupId;
	uint64 m_iTimeStamp;
}STRU_DNS_NODE_INFO ,*PSTRU_DNS_NODE_INFO;

class CDNSChildWorker : public sigslot::has_slots<>
{
public:
	CDNSChildWorker();
	~CDNSChildWorker();

	void SetDnsListenFd(CNetSocket *apDnsListenFd);
	void SetConfig(CDNSConfig *apDnsConfig);
	void Run();

	static unsigned int CheckNetEvent(STRU_THREAD_CONTEXT& apContext);
	static unsigned int DealSendEvent(STRU_THREAD_CONTEXT& apContext);
	static unsigned int DealRecvEvent(STRU_THREAD_CONTEXT& apContext);

private:
	bool InitDnsServer();
	bool InitDcsNode();
	void Dump();
	void TimeOutWork();
	void OnDealErrorFd(int fd);
	void DealNetData(int fd, char *buffer, int length);
	void DealCrsData(int fd, char *buffer, int length);
	void DealDcsData(char *buffer, int length);
	void DealDcsDataComplete(int rtn_op, int fd, CBasePack* pack);
	void DealCrsDataComplete(int rtn_op, int fd, CBasePack* pack);
	void KeepLive();
	void Login();
	void Logout();
public:
	CDNSConfig *m_pDnsConfig;
	CNetEpoll m_DnsServer;
	CNetSocket *m_pDnsListenFd;
	CNetEpoll m_DcsNode;
	CNetSocket m_DcsNodeFd;
	CDNSDealData m_DNSDealData;
	uint32 m_iMaxFd;
	uint64 m_i64LastDumpTime;
	uint64 m_i64LastKeepLive;
	uint64 m_i64LastLogTime;
	uint64 m_i64LastCheckTimeOut;
	CThreadGroup m_ThreadManager;
private:
	std::map<uint32,PSTRU_DNS_NODE_INFO> mHallList;
	int SetAlive(uint32 hallId ,PSTRU_DNS_NODE_INFO phall = NULL);
	int GetFDByHallId(uint32 hallid);
	int CheckTimeOut();
	int RemoveHall(uint32 hallid);
	CCriticalSection mSection;
	int SendByChatRootType(uint32 type,const char *buffer, const uint32 length);
};

#endif //_DNS_CHILD_WORKER_H_
