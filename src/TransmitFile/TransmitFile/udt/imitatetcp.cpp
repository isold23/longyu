#include "stdafx.h"
#include "imitatetcp.h"

using namespace imitate_tcp;

/************************************************************************/
/** 模拟TCP
*
*/
/************************************************************************/
CImitateTcp::CImitateTcp()
{
	Init();
}

CImitateTcp::~CImitateTcp()
{
	Init();
}

void CImitateTcp::FastTimer()
{

}

void CImitateTcp::SlowTimer()
{


}

void CImitateTcp::CancelTimer()
{

}

void CImitateTcp::Timer(int timer)
{
	switch(timer)
	{

	case TIMER_CON:
		{
			break;
		}
	case TIMER_RETRANS:
		{
			break;
		}
	case TIMER_PERSIST:
		{
			break;
		}
	case TIMER_KEEP:
		{
			break;
		}
	case TIMER_FIN_WAIT2:
		{
			break;
		}
	case TIMER_WAIT:
		{
			break;
		}
	default:
		{
			PrintLog(_LOG_LEVEL_DEBUG, "%s:%d 未知的时钟类型", __FILE__, __LINE__);
			break;
		}
	}
}

void CImitateTcp::SetPersist(void)
{

}

void CImitateTcp::XmitTimer()
{

}
/************************************************************************/
/*                                                                      */
/************************************************************************/