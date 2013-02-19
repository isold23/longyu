#ifndef _DNS_DEAL_DATA_H_
#define _DNS_DEAL_DATA_H_

#include "sigslot.h"
#include "BasePack.h"
#include "include.h"

class CDNSDealData
{
public:
	CDNSDealData();
	~CDNSDealData();
	/************************************************************************/
	/*
	返回值： 根据返回值不同对数据进行不同处理
	0 不做任何处理
	1 回复数据给发送者
	2 数据广播
	*/
	/************************************************************************/
	uint32 DNSDealDcsData(const char *apIn, 
		const uint32 aiIn, char *apOut, uint32 &aiOut);

	uint32 DNSDealCrsData(const char *apIn, 
		const uint32 aiIn, char *apOut, uint32 &aiOut);

public:
	sigslot::signal3<int, int, CBasePack*> DealDcsDataComplete;
	sigslot::signal3<int, int, CBasePack*> DealCrsDataComplete;
};
#endif //_DNS_DEAL_DATA_H_












