#ifndef _UPNP_H_
#define _UPNP_H_

#include <strstream>
using namespace std;

#include "upnpnat.h"

class CUpnpNat
{
public:
	CUpnpNat(void);
	~CUpnpNat(void);
private:
	int AddPortMapping(void);
	int DelPortMapping(void);
private:
	const short m_sPort;
};

#endif //_UPNP_H_