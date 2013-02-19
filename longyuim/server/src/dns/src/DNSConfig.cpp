

#include "DNSConfig.h"

CDNSConfig::CDNSConfig()
{
	server_ip = 0;
	server_port = 0;
	dcs_ip = 0;
	dcs_port = 0;
}

CDNSConfig::~CDNSConfig()
{

}

bool CDNSConfig::parse_value(const char* key, const char* value)
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

	if (!strcmp(key, "dcs_ip")) 
	{
		dcs_ip = ntohl(inet_addr(value));
		return true;
	}

	if (!strcmp(key, "dcs_port")) 
	{
		dcs_port = (unsigned short)strtol(value, NULL, 0);
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

	if (!strcmp(key, "max_process_size")) 
	{
		max_process_size = (unsigned short)strtol(value, NULL, 0);
		return true;
	}

	if (!strcmp(key, "max_file_size")) 
	{
		max_file_size = (unsigned short)strtol(value, NULL, 0);
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












