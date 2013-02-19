
#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#include "include.h"
using std::string;

#define ASCIILINESZ         (1024)
#define INI_INVALID_KEY     ((char*)-1)

typedef enum _line_status_ 
{
	LINE_UNPROCESSED,
	LINE_ERROR,
	LINE_EMPTY,
	LINE_COMMENT,
	LINE_SECTION,
	LINE_VALUE
} line_status;

class CConfigure
{
public:
	CConfigure();
	virtual ~CConfigure();

	void set_conf_file_name(const char* apFileName);
	const string get_conf_file_name(void){ return _file_name; }
	bool load();

protected:
	line_status iniparser_line(
		char * input_line,
		char * section,
		char * key,
		char * value);
	char * strstrip(char * s);
	char * strlwc(const char * s);
	virtual bool parse_value(const char* key, const char* value) = 0;
protected:
	string _file_name;
};


#endif //_CONFIGURE_H_













