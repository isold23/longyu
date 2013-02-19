#ifndef _DCS_WORKER_H_
#define _DCS_WORKER_H_

#include "sigslot.h"
#include "include.h"
#include "Time.h"
#include "FileStream.h"
#include "DCSConfig.h"
#include "NetEpoll.h"
#include "DCSDealData.h"
#include "ThreadGroup.h"

class CDCSWorker : public sigslot::has_slots<>
{
public:
	CDCSWorker();
	 ~CDCSWorker();

	 void SetConfig(CDCSConfig *apDcsConfig);
	 void Run();

	 static unsigned int CheckNetEvent(STRU_THREAD_CONTEXT& apContext);
	 static unsigned int DealSendEvent(STRU_THREAD_CONTEXT& apContext);
	 static unsigned int DealRecvEvent(STRU_THREAD_CONTEXT& apContext);

private:
	bool Init();
	void Dump();
	void TimeOutWork();
	void DealDnsData(int fd, char *buffer, int length);
	void DispatchData(const char *buffer, const uint32 length);
	void DealDataComplete(int rtn_op, int fd, CBasePack* pack);
	void OnDealErrorFd(int fd);
private:
	CDCSConfig *m_pDcsConfig;
	uint64 m_i64LastDumpTime;
	uint64 m_i64LastLogTime;
	CNetEpoll m_DcsServer;
	CNetSocket m_DcsListenFd;
	CDCSDealData m_DCSDealData;
	CThreadGroup m_ThreadManager;
};

#endif//_DCS_WORKER_H_


