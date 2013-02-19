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

#include "pseudotcp.h"
#include "socket.h"
using namespace ns_pseudo_tcp;

enum StreamResult { SR_ERROR, SR_SUCCESS, SR_BLOCK, SR_EOS };

class CPseudoTcpChannel:public IPseudoTcpNotify
{
public:
	CPseudoTcpChannel();
	virtual ~CPseudoTcpChannel();

	bool Start(const std::string& channel_name);

	bool Connect();

	StreamResult Read(void* buffer, size_t buffer_len,
		size_t* read, int* error);
	StreamResult Write(const void* data, size_t data_len,
		size_t* written, int* error);

	void Close();

	void AdjustClock(bool clear = true);

	virtual void OnTcpOpen(PseudoTcp* ptcp);
	virtual void OnTcpReadable(PseudoTcp* ptcp);
	virtual void OnTcpWriteable(PseudoTcp* ptcp);
	virtual void OnTcpClosed(PseudoTcp* ptcp, uint32 nError);
	virtual IPseudoTcpNotify::WriteResult TcpWritePacket(
		PseudoTcp* tcp,const char* buffer,size_t len);

private:
	PseudoTcp *m_pPseudoTcp;
	CSocket   *m_pSocket;
};
#endif //_PseudoTcpChannel_H_