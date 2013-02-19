
#ifndef _DNS_WORKER_H_
#define _DNS_WORKER_H_

#include "sigslot.h"
#include "include.h"
#include "Time.h"
#include "FileStream.h"
#include "DNSConfig.h"
#include "NetSocket.h"
#include "DNSChildWorker.h"

class CDNSWorker
{
public:
	CDNSWorker();
	~CDNSWorker();
	void SetConfig(CDNSConfig *apDnsConfig);
	void Run();
	static void ChildProcess(void *parameter);
private:
	void Dump();
	void TimeOutWork();
private:
	CDNSConfig *m_pDnsConfig;
	uint64 m_i64LastDumpTime;
	uint64 m_i64LastLogTime;
	CNetSocket m_DnsListenFd;
};

#endif//_DNS_WORKER_H_


