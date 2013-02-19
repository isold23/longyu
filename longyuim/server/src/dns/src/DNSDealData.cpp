#include "DNSDealData.h"

CDNSDealData::CDNSDealData()
{

}
CDNSDealData::~CDNSDealData()
{

}

/************************************************************************/
/*
返回值： 根据返回值不同对数据进行不同处理
0 不做任何处理
1 回复数据给发送者
2 数据广播
*/
/************************************************************************/
uint32 CDNSDealData::DNSDealDcsData(const char *apIn, 
				   const uint32 aiIn, char *apOut, uint32 &aiOut)
{
	return 0;
}

uint32 CDNSDealData::DNSDealCrsData(const char *apIn, 
					  const uint32 aiIn, char *apOut, uint32 &aiOut)
{
	return 0;
}