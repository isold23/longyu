

#ifndef _DCS_CONFIG_H_
#define _DCS_CONFIG_H_

#include "include.h"
#include "Configure.h"

class CDCSConfig : public CConfigure
{
public:
	CDCSConfig();
	virtual ~CDCSConfig();

	virtual bool parse_value(const char* key, const char* value);

public:
	//±¾µØ×Ö½ÚÐò
	unsigned int server_ip;
	unsigned short server_port;
	unsigned short max_connect_time;
	unsigned short max_bind_time;
	unsigned int log_file_update_time;
	unsigned int dump_info_time;
};

#endif//_DCS_CONFIG_H_


