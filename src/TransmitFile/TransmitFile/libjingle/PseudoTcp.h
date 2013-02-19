/********************************************************************
	created:	2008/08/29
	created:	29:8:2008   16:30
	filename: 	pseudotcp.h
	file base:	pseudotcp
	file ext:	h
	author:		王立伟
	
	purpose:	模拟TCP实现
*********************************************************************/

#ifndef __PSEUDOTCP_H__
#define __PSEUDOTCP_H__

#include <list>
#include <cassert>

namespace ns_pseudo_tcp
{

//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEINPROGRESS
#define EALREADY WSAEALREADY
#define ENOTSOCK WSAENOTSOCK
#define EDESTADDRREQ WSAEDESTADDRREQ
#define EMSGSIZE WSAEMSGSIZE
#define EPROTOTYPE WSAEPROTOTYPE
#define ENOPROTOOPT WSAENOPROTOOPT
#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
#define EOPNOTSUPP WSAEOPNOTSUPP
#define EPFNOSUPPORT WSAEPFNOSUPPORT
#define EAFNOSUPPORT WSAEAFNOSUPPORT
#define EADDRINUSE WSAEADDRINUSE
#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
#define ENETDOWN WSAENETDOWN
#define ENETUNREACH WSAENETUNREACH
#define ENETRESET WSAENETRESET
#define ECONNABORTED WSAECONNABORTED
#define ECONNRESET WSAECONNRESET
#define ENOBUFS WSAENOBUFS
#define EISCONN WSAEISCONN
#define ENOTCONN WSAENOTCONN
#define ESHUTDOWN WSAESHUTDOWN
#define ETOOMANYREFS WSAETOOMANYREFS
#define ETIMEDOUT WSAETIMEDOUT
#define ECONNREFUSED WSAECONNREFUSED
#define ELOOP WSAELOOP
#undef ENAMETOOLONG // remove errno.h's definition
#define ENAMETOOLONG WSAENAMETOOLONG
#define EHOSTDOWN WSAEHOSTDOWN
#define EHOSTUNREACH WSAEHOSTUNREACH
#undef ENOTEMPTY // remove errno.h's definition
#define ENOTEMPTY WSAENOTEMPTY
#define EPROCLIM WSAEPROCLIM
#define EUSERS WSAEUSERS
#define EDQUOT WSAEDQUOT
#define ESTALE WSAESTALE
#define EREMOTE WSAEREMOTE
#undef EACCES
#define SOCKET_EACCES WSAEACCES
#endif // WIN32

//////////////////////////////////////////////////////////////////////////////////////////////
//type define
//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef COMPILER_MSVC
typedef __int64 int64;
#else
typedef long long int64;
#endif /* COMPILER_MSVC */
typedef long int32;
typedef short int16;
typedef char int8;

#ifdef COMPILER_MSVC
typedef unsigned __int64 uint64;
typedef __int64 int64;
#else
typedef unsigned long long uint64;
typedef long long int64;
#endif /* COMPILER_MSVC */
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#ifdef WIN32
typedef int socklen_t;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
#define ASSERT(a) assert(a)
//////////////////////////////////////////////////////////////////////////////////////////////
//error code
//////////////////////////////////////////////////////////////////////////////////////////////

#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41


#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80

#define EDEADLOCK       EDEADLK

//////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline T _min(T a, T b) { return (a > b) ? b : a; }
template<class T> inline T _max(T a, T b) { return (a < b) ? b : a; }
//////////////////////////////////////////////////////////////////////////////////////////////
//net function
//////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32")
#else
#include <arpa/inet.h>
#endif

inline uint16 HostToNetwork16(uint16 n)
{
	return htons(n);
}


inline uint32 HostToNetwork32(uint32 n) 
{
	return htonl(n);
}

inline uint16 NetworkToHost16(uint16 n) 
{
	return ntohs(n);
}

inline uint32 NetworkToHost32(uint32 n) 
{
	return ntohl(n);
}
//////////////////////////////////////////////////////////////////////////////////////////////
//time function
//////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
inline uint32 Time() 
{
	return GetTickCount();
}
#else
#include <sys/time.h>
inline uint32 Time() 
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
#endif

inline uint32 StartTime() 
{
	// Close to program execution time
	static const uint32 g_start = Time();
	return g_start;
}

// Make sure someone calls it so that it gets initialized
static uint32 ignore = StartTime();

inline bool TimeIsBetween(uint32 later, uint32 middle, uint32 earlier) 
{
	if (earlier <= later) 
	{
		return ((earlier <= middle) && (middle <= later));
	} 
	else 
	{
		return !((later < middle) && (middle < earlier));
	}
}

inline int32 TimeDiff(uint32 later, uint32 earlier) 
{
	uint32 LAST = 0xFFFFFFFF;
	uint32 HALF = 0x80000000;
	if (TimeIsBetween(earlier + HALF, later, earlier)) 
	{
		if (earlier <= later) 
		{
			return static_cast<long>(later - earlier);
		} 
		else 
		{
			return static_cast<long>(later + (LAST - earlier) + 1);
		}
	}
	else 
	{
		if (later <= earlier) 
		{
			return -static_cast<long>(earlier - later);
		} 
		else 
		{
			return -static_cast<long>(earlier + (LAST - later) + 1);
		}
	}
}

inline uint32 ElapsedTime() 
{
	return TimeDiff(Time(), StartTime());
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPseudoTcpNotify
//////////////////////////////////////////////////////////////////////////////////////////////
class PseudoTcp;

class IPseudoTcpNotify 
{
public:
	// Notification of tcp events
	virtual void OnTcpOpen(PseudoTcp * tcp) = 0;
	virtual void OnTcpReadable(PseudoTcp * tcp) = 0;
	virtual void OnTcpWriteable(PseudoTcp * tcp) = 0;
	virtual void OnTcpClosed(PseudoTcp * tcp, uint32 nError) = 0;

	// Write the packet onto the network
	enum WriteResult { WR_SUCCESS, WR_TOO_LARGE, WR_FAIL };
	virtual WriteResult TcpWritePacket(PseudoTcp * tcp, const char * buffer, size_t len) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// PseudoTcp
//////////////////////////////////////////////////////////////////////////////////////////////

class PseudoTcp {
public:
	static uint32 Now();

	PseudoTcp(IPseudoTcpNotify * notify, uint32 conv);
	virtual ~PseudoTcp();

	int Connect();
	int Recv(char * buffer, size_t len);
	int Send(const char * buffer, size_t len);
	void Close(bool force);
	int GetError();

	enum TcpState { TCP_LISTEN, TCP_SYN_SENT, TCP_SYN_RECEIVED, TCP_ESTABLISHED, TCP_CLOSED };
	TcpState State() const { return m_state; }

	// Call this when the PMTU changes.
	void NotifyMTU(uint16 mtu);

	// Call this based on timeout value returned from GetNextClock.
	// It's ok to call this too frequently.
	void NotifyClock(uint32 now);

	// Call this whenever a packet arrives.
	// Returns true if the packet was processed successfully.
	bool NotifyPacket(const char * buffer, size_t len);

	// Call this to determine the next time NotifyClock should be called.
	// Returns false if the socket is ready to be destroyed.
	bool GetNextClock(uint32 now, long& timeout);

protected:
	enum SendFlags { sfNone, sfDelayedAck, sfImmediateAck };
	enum 
	{
		// Note: can't go as high as 1024 * 64, because of uint16 precision
		kRcvBufSize = 1024 * 60,
		// Note: send buffer should be larger to make sure we can always fill the
		// receiver window
		kSndBufSize = 1024 * 90
	}; 

	struct Segment 
	{
		uint32 conv, seq, ack;
		uint8 flags;
		uint16 wnd;
		const char * data;
		uint32 len;
		uint32 tsval, tsecr;
	};

	struct SSegment {
		uint32 seq, len;
		//uint32 tstamp;
		uint8 xmit;
		bool bCtrl;

		SSegment(uint32 s, uint32 l, bool c) : seq(s), len(l), /*tstamp(0),*/ xmit(0), bCtrl(c) { }
	};
	typedef std::list<SSegment> SList;

	struct RSegment {
		uint32 seq, len;
	};

	uint32 queue(const char * data, uint32 len, bool bCtrl);

	IPseudoTcpNotify::WriteResult packet(uint32 seq, uint8 flags, const char * data, uint32 len);
	bool parse(const uint8 * buffer, uint32 size);

	void attemptSend(SendFlags sflags = sfNone);

	void closedown(uint32 err = 0);

	bool clock_check(uint32 now, long& nTimeout);

	bool process(Segment& seg);
	bool transmit(const SList::iterator& seg, uint32 now);

	void adjustMTU();

private:
	IPseudoTcpNotify * m_notify;
	enum Shutdown { SD_NONE, SD_GRACEFUL, SD_FORCEFUL } m_shutdown;
	int m_error;

	// TCB data
	TcpState m_state;
	uint32 m_conv;
	bool m_bReadEnable, m_bWriteEnable, m_bOutgoing;
	uint32 m_lasttraffic;

	// Incoming data
	typedef std::list<RSegment> RList;
	RList m_rlist;
	char m_rbuf[kRcvBufSize];
	uint32 m_rcv_nxt, m_rcv_wnd, m_rlen, m_lastrecv;

	// Outgoing data
	SList m_slist;
	char m_sbuf[kSndBufSize];
	uint32 m_snd_nxt, m_snd_wnd, m_slen, m_lastsend, m_snd_una;
	// Maximum segment size, estimated protocol level, largest segment sent
	uint32 m_mss, m_msslevel, m_largest, m_mtu_advise;
	// Retransmit timer
	uint32 m_rto_base;

	// Timestamp tracking
	uint32 m_ts_recent, m_ts_lastack;

	// Round-trip calculation
	uint32 m_rx_rttvar, m_rx_srtt, m_rx_rto;

	// Congestion avoidance, Fast retransmit/recovery, Delayed ACKs
	uint32 m_ssthresh, m_cwnd;
	uint8 m_dup_acks;
	uint32 m_recover;
	uint32 m_t_ack;
};

//////////////////////////////////////////////////////////////////////////////////////////////
}//ns_pseudo_tcp

#endif // __PSEUDOTCP_H__





