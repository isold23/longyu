/********************************************************************
	created:	2008/08/29
	created:	29:8:2008   16:37
	filename: 	PseudoTcpChannel.h
	file base:	PseudoTcpChannel
	file ext:	h
	author:		王立伟
	
	purpose:	TCP实现接口类
*********************************************************************/
#ifndef _PseudoTcpChannel_H_
#define _PseudoTcpChannel_H_

#include "PseudoTcp.h"					

#include "socket.h"
#include "../common/common.h"

using wzy::IPseudoTcpNotify;
using wzy::CSocket;

namespace wzy
{

enum StreamState { SS_CLOSED, SS_OPENING, SS_OPEN };
enum StreamResult { SR_ERROR, SR_SUCCESS, SR_BLOCK, SR_EOS };

inline bool IsBlockingError(int e) {
	return (e == EWOULDBLOCK) || (e == EAGAIN) || (e == EINPROGRESS);
}

class CPseudoTcpChannel:public IPseudoTcpNotify
{
public:
	CPseudoTcpChannel();
	virtual ~CPseudoTcpChannel();

	bool Start(const char* ip, const unsigned short port,
		const char* dst_ip, const unsigned short dst_port);

	bool Connect();

	int TcpReadPack();
	void OnChannelRead(const char* data, size_t size);

	StreamResult Read(char* buffer, size_t buffer_len,
		size_t* read, int* error);
	StreamResult Write(const char* data, size_t data_len,
		size_t* written, int* error);

	 StreamState GetState() const;

	void Close();

	void AdjustClock(bool clear = true);

	virtual void OnTcpOpen(PseudoTcp* ptcp);
	virtual void OnTcpReadable(PseudoTcp* ptcp);
	virtual void OnTcpWriteable(PseudoTcp* ptcp);
	virtual void OnTcpClosed(PseudoTcp* ptcp, uint32 nError);
	virtual IPseudoTcpNotify::WriteResult TcpWritePacket(
		PseudoTcp* tcp,const char* buffer,size_t len);

	static void *ClockThread(void *pv);
	static void *ReadThread(void *pv);

public:
	PseudoTcp *m_pPseudoTcp;
	CSocket   *m_pSocket;
	mutable CriticalSection cs_;
	bool stream_readable_;
	bool ready_to_connect_;
	bool mbCanRead;
	bool mbCanWrite;
	bool mbTcpClose;
};
}
#endif //_PseudoTcpChannel_H_