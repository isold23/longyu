/********************************************************************
	created:	2009/09/21
	created:	21:9:2009   10:19
	filename: 	\TaskProcessor\src\TaskProcessor.h
	file path:	\TaskProcessor\src
	file base:	TaskProcessor
	file ext:	h
	author:		isold
	
	purpose:	
*********************************************************************/
#ifndef _TASK_PROCESSOR_H_
#define _TASK_PROCESSOR_H_

#include "include.h"
#include "sigslot.h"
#include "NetAddress.h"
#include "NetEpoll.h"
#include "NetSocket.h"
#include "TaskProcessorConfig.h"
#include "ITaskProcess.h"

class CTaskProcessor : public sigslot::has_slots<>
{
public:
	CTaskProcessor();
	~CTaskProcessor();

	void SetConfigInfo(CTaskProcessorConfig *apConfig);
	void SetDealDataPtr(ITaskProcess *apTaskProcessPtr);
	int Run();
	void DealData(CNetSocket* fd, char *buffer, int length);
	static void ChildProcess(void *parameter);

private:
	void ChildProcessFun();
private:
	CTaskProcessorConfig *m_pConfig;
	ITaskProcess *m_pTaskProcess;
	CNetSocket m_Listener;
};

#endif//_TASK_PROCESSOR_H_


