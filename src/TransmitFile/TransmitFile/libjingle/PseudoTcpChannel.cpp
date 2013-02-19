#include "stdafx.h"
#include "PseudoTcpChannel.h"

CPseudoTcpChannel::CPseudoTcpChannel()
{
	m_pPseudoTcp = NULL;
	m_pSocket = NULL;
}
CPseudoTcpChannel::~CPseudoTcpChannel()
{
	if (m_pPseudoTcp != NULL)
	{
		delete m_pPseudoTcp;
		m_pPseudoTcp = NULL;
	}

	if (m_pSocket != NULL)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}
}

bool CPseudoTcpChannel::Start(const std::string& channel_name)
{
	ASSERT(m_pPseudoTcp == NULL);
	ASSERT(m_pSocket == NULL);

	if ((m_pPseudoTcp != NULL) || (m_pSocket != NULL))
	{
		return false;
	}

	m_pPseudoTcp = new PseudoTcp(this, 0);
	m_pSocket = new CSocket;
	return true;
}

bool CPseudoTcpChannel::Connect()
{
	ASSERT(m_pPseudoTcp != NULL);
	
	return true;
}

StreamResult CPseudoTcpChannel::Read(void* buffer, size_t buffer_len,
									 size_t* read, int* error)
{
	return SR_SUCCESS;
}
StreamResult CPseudoTcpChannel::Write(const void* data, size_t data_len,
									  size_t* written, int* error)
{
	return SR_SUCCESS;
}

void CPseudoTcpChannel::Close()
{

}

void CPseudoTcpChannel::AdjustClock(bool clear /* = true */)
{
	//ºÏ≤‚ ±÷”
}

void CPseudoTcpChannel::OnTcpOpen(PseudoTcp* ptcp)
{
	
}
void CPseudoTcpChannel::OnTcpReadable(PseudoTcp* ptcp)
{
}
void CPseudoTcpChannel::OnTcpWriteable(PseudoTcp* ptcp)
{

}
void CPseudoTcpChannel::OnTcpClosed(PseudoTcp* ptcp, uint32 nError)
{

}
IPseudoTcpNotify::WriteResult CPseudoTcpChannel::TcpWritePacket(
	PseudoTcp* tcp,const char* buffer,size_t len)
{
	return WR_SUCCESS;
}

