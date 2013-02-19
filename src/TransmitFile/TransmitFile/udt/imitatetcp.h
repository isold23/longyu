#ifndef _IMITATE_TCP_H_
#define _IMITATE_TCP_H_

//    0                   1                   2                   3   
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  0 |                      Conversation Number                      |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  4 |                        Sequence Number                        |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  8 |                     Acknowledgment Number                     |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//    |               |   |U|A|P|R|S|F|                               |
// 12 |    Control    |   |R|C|S|S|Y|I|            Window             |
//    |               |   |G|K|H|T|N|N|                               |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 16 |                       Timestamp sending                       |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 20 |                      Timestamp receiving                      |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 24 |                             data                              |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#include "..\..\..\..\include\defines.h"
#include "..\..\..\..\include\common\common.h"
#include "..\..\..\..\include\net\net.h"

namespace imitate_tcp
{
	//窗口最大值
	static const uint32 MAX_WIN_SIZE = 65535;
	//发送数据缓冲大小
	static const uint32 SEND_BUF_SIZE = 1024 * 60;
	//接收数据缓冲大小
	static const uint32 RECV_BUF_SIZE = 1024 * 90;
	//ACK重复次数的门限值,触发快速重传
	static const uint32 REXMTTHRESH = 3;
	//默认MSS值
	static const uint32 DEFAULT_MSS = 512;
	//windows max shift
	static const uint32 TCP_MAX_WINSHIFT = 14;

	/**********超时重传时间间隔(RTO: retransmission timeout)**********/
	//超时重传算法的选择 
	//1.其他 2.RTO为固定值 3. MIL-STD-1778(TCPIP详解-24章) 4. Van Jacobson的算法
	static const uint32 RTO_ALGORITHM = 4;
	//最小重传超时时限秒(1S)
	static const uint32 MIN_RTO = 1; 
	//最大重传超时时限(64S)
	static const uint32 MAX_RTO = 64;
	//默认重传超时时限(3S)
	static const uint32 DEF_ROT = 3;
	/**********超时重传时间间隔(RTO: retransmission timeout)**********/


	/**********保活时间间隔**********/
	//两次探测时间间隔(75S)
	static const uint32 KEEP_INIT = 75;
	//第一次探测前的空闲时间(2小时)
	static const uint32 KEEP_IDLE = 2 * 60 * 60;
	//默认两次探测时间间隔(75S)
	static const uint32 KEEP_INTVL = 75;
	//探测之后，放弃之前的时间(10M)
	static const uint32 KEEP_PCNT = 10 * 60;
	/**********保活时间间隔**********/

	/************************************************************************/
	//持续定时器最小值(5S)
	static const uint32 PEERS_MIN = 5;
	//持续定时器最大值(60S)
	static const uint32 PEERS_MAX = 60;
	//等待某个ACK的最大重传次数
	static const uint32 MAX_RXTSHIFT = 12;
	//对端无响应时,最大保活测试次数
	static const uint32 KEEP_COUNT = 8;
	//用于SO_LINGER插口选项的最大时间(120S)
	static const uint32 LINGER_TIME = 120;
	/************************************************************************/

	//连接状态
	enum IT_STATE 
	{ 
		IT_CLOSE = 0, 
		IT_LISTEN = 1, 
		IT_SYN_SENT = 2, 
		IT_SYN_RECEIVED = 3, 
		IT_ESTABLISHED = 4, 
		IT_CLOSE_WAIT = 5, 
		IT_FIN_WAIT_1 = 6, 
		IT_CLOSING = 7, 
		IT_LAST_ACK = 8, 
		IT_FIN_WAIT_2 = 9, 
		IT_TIME_WAIT = 10
	};

	enum IT_TH_FLAGS 
	{ 
		TH_FIN = 0x01, //确认序号有效 
		TH_SYN = 0x02, //发送方字节流结束
		TH_RST = 0x04, //接收方应该立即将数据提交给应用程序
		TH_PUSH = 0x08,//连接复位
		TH_ACK = 0x10, //序号同步(建立连接)
		TH_URG = 0x20, //紧急数据偏移量有效
	};

	enum IT_TF_FLAGS
	{
		TF_ACKNOW = 0x0001,//立即发送ACK
		TF_DELACK = 0x0002,//延迟发送ACK
		TF_NODELAY = 0x0004,//立即发送用户数据,不等待形成最大报文段(禁止Nagle算法)
		TF_NOOPT = 0x0008,//不使用TCP选项
		TF_SENTFIN = 0x0010,//FIN已发送
		TF_REQ_SCALE = 0x0020, //已经/将要在SYN报文中请求窗口变化选项
		TF_RCVD_SCALE = 0x0040,//对端在SYN报文中发送窗口变化时置位
		TF_REQ_TSTMP = 0x0080,//已经/将要在SYN报文中请求时间戳选项
		TF_RCVD_TSTMP = 0x0100,//对端在SYN报问中发送时间戳选项时置位
		TF_SACK_PERMIT = 0x0200, //other side said I could SACK
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
	typedef struct
	{
		uint32 m_nConNum;
		uint32 m_nSeqNum;
		uint32 m_nAckNum;
		uint8  m_nControl;
		uint8  m_nFlag;  
		uint16 m_nWinSize;
		uint32 m_nTimeSend;
		uint32 m_nTimeRecv;
	}IT_HEADER,*PIT_HEADER;
#pragma pack()

	static const uint32 HEADER_SIZE = sizeof(IT_HEADER);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	class CImitateTcp
	{
	public:
		CImitateTcp(void);
		virtual ~CImitateTcp(void);

		const uint32 Now(void) const { return wlw::CTimeBase::GetTime(); }
		const uint32 GetError(void) const { return m_Error; }

		void TimerRangSet(uint32 tv, uint32 value, uint32 min, uint32 max);
		/**关闭所有定时器*/
		void CancelTimer();
		/**每隔200MS调用一次, 用于操作延迟ACK定时器*/
		void FastTimer();
		/**每隔500MS调用一次, 用于操作其他6个定时器: 
		* 1. 连接建立定时器--
		* 2. 重传定时器      --  在TCP实现中这两个是一个标志 KEEP
		* 3. 持续定时器      --  在TCP实现中这两个是一个标志 KEEP
		* 4. 保活定时器------
		* 5. FIN_WAIT_2定时器--在TCP实现中这两个是一个标志
		* 6. 2MSL定时器--------在TCP实现中这两个是一个标志
		*/
		void SlowTimer();
		/************************************************************************/
		/**
		*  当计数器减为0时调用
		*/
		/************************************************************************/
		void Timer(int timer);
		/************************************************************************/
		/** 持续定时器函数
		*   在持续定时器超时后将调用这个函数.这个函数用到了TCP的重传超时算法.
		*/
		/************************************************************************/
		void SetPersist(void);
		/************************************************************************/
		/** 在得到一个RTT测量值,更新已平滑估计器(srtt)和平均偏差(rttvar)时调用 
		*/
		/************************************************************************/
		void XmitTimer();
	private:
		void Init(void);
	private:
		IT_HEADER m_itHeader;
		//网络状态
		IT_STATE m_itState;
		//错误信息
		uint32 m_Error;
		int8 m_SendBuf[SEND_BUF_SIZE];
		int8 m_RecvBuf[RECV_BUF_SIZE];
		//发送序号
		uint32 m_nSeq;
		//当前时间
		uint32 m_nNow;
		//数据发送端地址
		wlw::CSocketAddr m_AddrFrom;
		//数据接收端地址
		wlw::CSocketAddr m_AddrTo;
		//发送数据包总数
		uint32 m_nSendTotal;
		//接收数据包总数
		uint32 m_nRecvTotal;
		//重传数据包总数
		uint32 m_nRetransmitTotal;
		/*****************************发送序号***8**************************/
		//发送窗口大小
		uint32 m_nSendWnd;
		//最早的未确认的序号
		uint32 m_nSendUna;
		//下一个发送序号
		uint32 m_nSendNxt;
		//最大发送序号
		uint32 m_nSendMax;
		/*****************************发送序号*****************************/
		/*****************************接收序号****5*************************/
		//接收窗口大小
		uint32 m_nRecvWnd;
		//下一个接收序号
		uint32 m_nRecvNxt;
		//通告序号最大值加1
		uint32 m_nRecvAdv;
		/*****************************接收序号*****************************/
		/*****************************时钟****7*************************/
		//发送SYN报文后,连接建立时候启动，
		//如果没有在75S内收到回复,连接将终止
		uint32 m_nTimerCon;
#define TIMER_CON 0
		//重传定时器,动态计算
		uint32 m_nTimerRetransmission;
#define TIMER_RETRANS 1
		//收到必需确认但无需马上确认的数据包后,等待200MS后发送确认,
		//如果在这200MS内有在这一连接上发送的数据,确认就跟在数据
		//后边一起发送("捎带确认")
		uint32 m_nTimerDelayAck;
#define TIMER_DELAYACK 2
		//持续定时器(作用未明白)
		uint32 m_nTimerPersist;
#define TIMER_PERSIST 3
		//保活定时器,如果连接连续空闲超过2个小时就发送探测数据包,
		//强制对端响应.如果收到响应,连接正常.如果未收到响应就持续
		//若干次(次数未定),一直没有响应就认为对端崩溃.
		uint32 m_nTimerKeepLive;
#define TIMER_KEEP 4
		//当连接从FIN_WAIT_1状态变迁到FIN_WAIT_2状态并且不能再接收任何数据
		//时(意味着应用进程调用了close,而非shutdown,没有利用TCP的半关闭功能),
		//FIN_WAIT_2定时器启动,设为10分钟.定时器超时后,重新设为75S,第二次超时后
		//连接被关闭.加入这个定时器的原因是避免对端一直发送FIN,某个连接会永远
		//滞留在FIN_WAIT_2状态
		uint32 m_nTimerFinWait2;
#define TIMER_FIN_WAIT2 5
		//TIMN_WAIT定时器,一般也称为2MSL定时器.2MSL指两倍的MSL.当连接转移到
		//TIME_WAIT状态,既连接主动关闭时,定时器启动.连接进入TIME_WAIT状态时,
		//定时器设定为1分钟,超时后,TCP控制块和Internet PCB被删除,端口可重新使用.
		uint32 m_nTimerWait;
#define TIMER_WAIT 6
		/*****************************时钟*****************************/

#define TIMER_COUNT 7
		short m_nTimersp[TIMER_COUNT];

		IT_TF_FLAGS m_nTFlag;
		//Round-Trip Time: 往返时间
		uint32 m_nRTT;
		//重发时间
		uint32 m_nRTO;

		/**超时重传用到的变量****************************************************/
		//已平滑的RTT估计器 : m_nSrtt * 8
		uint32 m_nSrtt;
		//已平滑的RTT平均偏差估计器: m_nRttvar * 4
		uint32 m_nRttvar;
		//当前重传时限:RTO
		uint32 m_nRxtcur;
		//重传时限最小值
		uint32 m_nRttmin;
		//tcp_backoff[数组索引(指数退避)]
		uint32 m_nRxtshift;
		//相乘: *8
#define RTT_SCALE 8
		//移位: <<3
#define RTT_SHIFT 3
		//相乘: *4
#define RTTVAR_SCALE 4
		//移位: <<2
#define RTTVAR_SHIFT 2
		/************************************************************************/
	};
	inline void CImitateTcp::Init(void)
	{
		memset(&m_itHeader, 0, sizeof(IT_HEADER));
		m_Error = 0;
		memset(m_SendBuf, 0, SEND_BUF_SIZE);
		memset(m_RecvBuf, 0, RECV_BUF_SIZE);
		m_nSeq = 0;
		m_itState = IT_LISTEN;
		m_nNow = Now();

		m_nSendWnd = MAX_WIN_SIZE << TCP_MAX_WINSHIFT;
	}

	inline void CImitateTcp::TimerRangSet(uint32 tv, uint32 value, uint32 min, uint32 max)
	{
		tv = value;
		if (tv < min) tv = min;
		else if(tv > max) tv = max;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
}//end of namespace imitate_tcp
#endif //_IMITATE_TCP_H_
