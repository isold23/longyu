/********************************************************************
	created:	2009/09/21
	created:	21:9:2009   11:11
	filename: 	\TaskProcessor\src\TaskProcess.h
	file path:	\TaskProcessor\src
	file base:	TaskProcess
	file ext:	h
	author:		isold
	
	purpose:	
*********************************************************************/

#ifndef _TASK_PROCESS_H_
#define _TASK_PROCESS_H_

#include "include.h"
#include "CriticalSection.h"
#include "NetPack.h"
#include "ITaskProcess.h"

class CTaskProcess : public ITaskProcess
{
public:
	CTaskProcess();
	virtual ~CTaskProcess();
	virtual void TaskProcessFun(const char *buffer, const int length, char *rtn, int &rtn_len);
private:

};

#endif//_TASK_PROCESS_H_



