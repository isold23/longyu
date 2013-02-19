/********************************************************************
	created:	2009/09/20
	created:	20:9:2009   9:16
	filename: 	TaskProcessorConfig.cpp
	file path:	\TaskProcessor\src
	file base:	TaskProcessorConfig
	file ext:	cpp
	author:		wangzeyu
	
	purpose:	
*********************************************************************/

#include "TaskProcessorConfig.h"

CTaskProcessorConfig::CTaskProcessorConfig()
{
	tps_port = 0;
	max_processor = 0;
	max_connected = 0;
	connected_time_out = 0;
}

CTaskProcessorConfig::~CTaskProcessorConfig()
{

}

bool CTaskProcessorConfig::parse_value(const char* key, const char* value)
{
	if (!strcmp(key, "tps_port")) 
	{
		tps_port = (uint16)strtol(value, NULL, 0);
		return true;
	}
	if (!strcmp(key, "max_processor_number")) 
	{
		max_processor = (uint32)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "max_Connection_number")) 
	{
		max_connected = (uint32)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "user_time_out")) 
	{
		connected_time_out = (uint64)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "tps_ip")) 
	{
		tps_ip = inet_addr(value);
		return true;
	}
	if (!strcmp(key, "keep_alive")) 
	{
		keep_alive = (bool)strtol(value, NULL, 0);
		return true;
	}
	return true;
}



