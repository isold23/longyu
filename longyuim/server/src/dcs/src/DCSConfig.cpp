

#include "DCSConfig.h"

CDCSConfig::CDCSConfig()
{
	server_ip = 0;
	server_port = 0;
}

CDCSConfig::~CDCSConfig()
{

}

bool CDCSConfig::parse_value(const char* key, const char* value)
{
	if (!strcmp(key, "server_ip")) 
	{
		server_ip = ntohl(inet_addr(value));
		return true;
	}

	if (!strcmp(key, "server_port")) 
	{
		server_port = (unsigned short)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "max_connect_time")) 
	{
		max_connect_time = (unsigned short)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "max_bind_time")) 
	{
		max_bind_time = (unsigned short)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "log_file_update_time")) 
	{
		log_file_update_time = (unsigned int)strtol(value, NULL, 0);
		return true;
	}
	
	if (!strcmp(key, "dump_info_time")) 
	{
		dump_info_time = (unsigned int)strtol(value, NULL, 0);
		return true;
	}

	return true;
}












