/********************************************************************
	created:	2009/09/20
	created:	20:9:2009   9:10
	filename: 	TaskProcessorConfig.h
	file path:	\TaskProcessor\src
	file base:	TaskProcessorConfig
	file ext:	h
	author:		wangzeyu
	
	purpose:	
*********************************************************************/
#ifndef _TASK_PROCESSOR_CONFIG_H_
#define _TASK_PROCESSOR_CONFIG_H_

#include "include.h"
#include "Configure.h"

class CTaskProcessorConfig : public CConfigure
{
public:
	CTaskProcessorConfig();
	virtual ~CTaskProcessorConfig();
	virtual bool parse_value(const char* key, const char* value);
public:
	uint32 tps_ip;
	uint16 tps_port;
	uint32 max_processor;
	uint32 max_connected;
	uint64 connected_time_out;
	bool keep_alive;
};

#endif//_TASK_PROCESSOR_CONFIG_H_

