
#ifndef _DNS_CONFIG_H_
#define _DNS_CONFIG_H_

#include "include.h"
#include "Configure.h"

class CDNSConfig : public CConfigure
{
public:
	CDNSConfig();
	virtual ~CDNSConfig();

	virtual bool parse_value(const char* key, const char* value);

public:
	//±¾µØ×Ö½ÚÐò
	unsigned int server_ip;
	unsigned short server_port;
	unsigned int dcs_ip;
	unsigned short dcs_port;
	unsigned short max_connect_time;
	unsigned short max_bind_time;
	unsigned short max_process_size;
	unsigned short max_file_size;
	unsigned int log_file_update_time;
	unsigned int dump_info_time;
};

#endif//_DNS_CONFIG_H_


