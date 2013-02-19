#include "HostIpCache.h"

CHostIpCache::CHostIpCache(void){
}

CHostIpCache::~CHostIpCache(void){
}

void CHostIpCache::SetHostIp(const string& astrHost,const string& astrIp){
	CAutoLock loLock(moMutex);
	mmapHostIps[astrHost] = astrIp;
}
bool CHostIpCache::DelHostIp(const string& astrHost){
	CAutoLock loLock(moMutex);
	map<string,string>::iterator lPos = mmapHostIps.find(astrHost);
	if(mmapHostIps.end() != lPos){
		mmapHostIps.erase(lPos);
		return true;
	}
	return false;
}

bool CHostIpCache::GetHostIp(const string& astrHost,string& astrIp){
	CAutoLock loLock(moMutex);
	map<string,string>::iterator lPos = mmapHostIps.find(astrHost);
	if(mmapHostIps.end() != lPos){
		astrIp = lPos->second;
		return true;
	}
	return false;
}


