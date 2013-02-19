#ifndef _XML_H_
#define _XML_H_

#include "..\..\common\defines.h"
#include "MarkupSTL.h"

/////////////////////////////////////////////////////
class CXmlConfig
{
public:
	CXmlConfig(void);
	~CXmlConfig(void);

	void GetServerInfo(string &ip, short &port);
	void GetUpLen(int &len);
	void GetUserInfo(string &name, string &password);

private:

};
//////////////////////////////////////////////////////

#endif //_XML_H_