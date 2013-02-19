/********************************************************************
	created:	2009/09/21
	created:	21:9:2009   10:21
	filename: 	\TaskProcessor\src\ITaskProcess.h
	file path:	\TaskProcessor\src
	file base:	ITaskProcess
	file ext:	h
	author:		isold
	
	purpose:	
*********************************************************************/
#ifndef _I_TASK_PROCESS_H_
#define _I_TASK_PROCESS_H_

class ITaskProcess
{
public:
	virtual ~ITaskProcess(){}
	virtual void TaskProcessFun(const char *buffer, const int length, char *rtn, int &rtn_len) = 0;
};
#endif//_I_TASK_PROCESS_H_


