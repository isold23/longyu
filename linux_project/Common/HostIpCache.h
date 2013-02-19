#ifndef _HOST_IP_CACHE_H_
#define _HOST_IP_CACHE_H_
#include <string>
#include <map>
#include "CriticalSection.h"

class CHostIpCache{
public:
	CHostIpCache(void);
	~CHostIpCache(void);
	void SetHostIp(const string& astrHost,const string& astrIp);
	bool DelHostIp(const string& astrHost);
	bool GetHostIp(const string& astrHost,string& astrIp);
private:
	map<string,string> mmapHostIps;
	CCriticalSection moMutex;
};
#endif //_HOST_IP_CACHE_H_
