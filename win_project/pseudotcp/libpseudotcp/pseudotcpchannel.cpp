#include "stdafx.h"
#include "PseudoTcpChannel.h"
#include <pthread.h>
#include <unistd.h>  
using namespace wzy;

CPseudoTcpChannel::CPseudoTcpChannel()
{
	m_pPseudoTcp = NULL;
	m_pSocket = NULL;
	mbTcpClose = true;
	mbCanRead = false;
	mbCanWrite = false;
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

StreamState CPseudoTcpChannel::GetState() const {

	CritScope lock(&cs_);
	if (!m_pPseudoTcp)
		return SS_OPENING;
	switch (m_pPseudoTcp->State()) {
	case PseudoTcp::TCP_LISTEN:
	case PseudoTcp::TCP_SYN_SENT:
	case PseudoTcp::TCP_SYN_RECEIVED:
		return SS_OPENING;
	case PseudoTcp::TCP_ESTABLISHED:
		return SS_OPEN;
	case PseudoTcp::TCP_CLOSED:
	default:
		return SS_CLOSED;
	}
}

bool CPseudoTcpChannel::Start(const char* src_ip, const unsigned short src_port,
			const char* dst_ip, const unsigned short dst_port)
{
	ASSERT(m_pPseudoTcp == NULL);
	ASSERT(m_pSocket == NULL);

	if ((m_pPseudoTcp != NULL) || (m_pSocket != NULL))
	{
		return false;
	}

	m_pPseudoTcp = new PseudoTcp(this, 0);
	m_pSocket = new CSocket;
	m_pSocket->Open(src_ip, src_port, dst_ip, dst_port);
	
	pthread_t thread_;
	int error_code;
	error_code = pthread_create(&thread_, 0, ClockThread, this);	
	error_code = pthread_create(&thread_, 0, ReadThread, this);	
	
	
	unsigned short mtu = 65535;
	m_pPseudoTcp->NotifyMTU(mtu);
	AdjustClock();		
	return true;
}

bool CPseudoTcpChannel::Connect()
{
	ASSERT(m_pPseudoTcp != NULL);
	CritScope lock(&cs_);
	m_pPseudoTcp->Connect();
	AdjustClock();
	return true;
}

StreamResult CPseudoTcpChannel::Read(char* buffer, size_t buffer_len,
									 size_t* read, int* error)
{
	CritScope lock(&cs_);
	if (!m_pPseudoTcp)
		return SR_BLOCK;
	
	stream_readable_ = false;
	int result = m_pPseudoTcp->Recv(static_cast<char*>(buffer), buffer_len);
	/*
	cout << "CPseudoTcpChannel::Read, result=" << result <<endl;
	
	if (result < 0)
	{
		if (m_pPseudoTcp->GetError()==ENOTCONN)
			cout << "CPseudoTcpChannel::Read, m_pPseudoTcp->GetError()=ENOTCONN" <<endl;
		else
			cout << "CPseudoTcpChannel::Read, m_pPseudoTcp->GetError()=EWOULDBLOCK" <<endl;
	}
	*/
	
	if (result > 0) {
		if (read)
			*read = result;
		stream_readable_ = true;		
		return SR_SUCCESS;
	} 
	else if (IsBlockingError(m_pPseudoTcp->GetError())) 
	{
		return SR_BLOCK;
	} 
	else
	{
		if (error)
			*error = m_pPseudoTcp->GetError();
		return SR_ERROR;
	}
	AdjustClock();
	return SR_SUCCESS;
}
StreamResult CPseudoTcpChannel::Write(const char* data, size_t data_len,
									  size_t* written, int* error)
{
	CritScope lock(&cs_);
	if (!m_pPseudoTcp)
		return SR_BLOCK;
	int result = m_pPseudoTcp->Send(static_cast<const char*>(data), data_len);
	if (result > 0) {
		if (written)
			*written = result;
		return SR_SUCCESS;
	} else if (IsBlockingError(m_pPseudoTcp->GetError())) {
		return SR_BLOCK;
	} else {
		if (error)
			*error = m_pPseudoTcp->GetError();
		return SR_ERROR;
	}
	AdjustClock();
	return SR_SUCCESS;
}

void CPseudoTcpChannel::Close()
{
	m_pSocket->Close();
}

int CPseudoTcpChannel::TcpReadPack()
{		
	char memcache[MAX_PACKET_SIZE];
	memset(memcache, 0, MAX_PACKET_SIZE);
	size_t len = 0;
	int nRet = m_pSocket->RecvData(memcache, len);
	if(nRet == 0)
	{
		if (len > 0)
			cout  << "PID=" << getpid() << " Time=" << Time() << " CPseudoTcpChannel::TcpReadPack(), len=" << len << ", " << m_pPseudoTcp->State() << endl;
		
		OnChannelRead(memcache, len);				
		cout << "PID=" << getpid() << " Time=" << Time() << " m_pPseudoTcp->State()="  << m_pPseudoTcp->State() << endl;
		return 0;
	}	
	return -1;
}

void CPseudoTcpChannel::OnChannelRead(const char* data, size_t size) 
{
	CritScope lock(&cs_);
	if (!m_pPseudoTcp) 
	{
		return;
	}
	bool ret=m_pPseudoTcp->NotifyPacket(data, size);
	ASSERT(ret);
	AdjustClock();
}

void CPseudoTcpChannel::AdjustClock(bool clear /* = true */)
{
	//¼ì²âÊ±ÖÓ
	ASSERT(NULL != m_pPseudoTcp);

	long timeout = 0;
	if (m_pPseudoTcp->GetNextClock(PseudoTcp::Now(), timeout)) {
		CritScope lock(&cs_);
		if (m_pPseudoTcp) 
		{
			m_pPseudoTcp->NotifyClock(PseudoTcp::Now());
		}
		return;
	}

	delete m_pPseudoTcp;
	m_pPseudoTcp = NULL;
	ready_to_connect_ = false;

	m_pSocket->Close();
	return;
	
}

void CPseudoTcpChannel::OnTcpOpen(PseudoTcp* ptcp)
{
	mbTcpClose = false;
}

void CPseudoTcpChannel::OnTcpReadable(PseudoTcp* ptcp)
{
	mbCanRead = true;
}

void CPseudoTcpChannel::OnTcpWriteable(PseudoTcp* ptcp)
{
	mbCanWrite = true;
}

void CPseudoTcpChannel::OnTcpClosed(PseudoTcp* ptcp, uint32 nError)
{
	mbTcpClose = true;
}

IPseudoTcpNotify::WriteResult CPseudoTcpChannel::TcpWritePacket(
	PseudoTcp* tcp,const char* buffer,size_t len)
{
	int sent = m_pSocket->SendData(buffer, len);
	if (sent == 0) 
	{
		if (len > 0)
			cout << "PID=" << getpid() << " Time=" << Time() << " CPseudoTcpChannel::TcpWritePacket(), len=" << len << ", " << m_pPseudoTcp->State() << endl;
		return IPseudoTcpNotify::WR_SUCCESS;
	} 
	else if (sent == -2) 
	{
		return IPseudoTcpNotify::WR_TOO_LARGE;
	} 
	else 
	{
		return IPseudoTcpNotify::WR_FAIL;
	}
}

void* CPseudoTcpChannel::ClockThread(void *pv)
{
	CPseudoTcpChannel* pThis = (CPseudoTcpChannel*)pv;
	//cout << "void* CPseudoTcpChannel::ClockThread(void *pv)" <<endl;
	
	int nLastTime(Time());
	while(pThis->m_pPseudoTcp)
	{
		pThis->AdjustClock();		
			
		if (TimeDiff(Time(), nLastTime) > 3000)			
		{
			//cout << "PID= " << getpid() << " Time=" << Time() << ", m_pPseudoTcp->State()=" << pThis->m_pPseudoTcp->State() << endl;
			nLastTime=Time();
		}	
	}
}

void* CPseudoTcpChannel::ReadThread(void *pv)
{
	CPseudoTcpChannel* pThis = (CPseudoTcpChannel*)pv;
	//cout << "void* CPseudoTcpChannel::ReadThread(void *pv)" <<endl;
		
	while(pThis->m_pPseudoTcp)
	{
		pThis->TcpReadPack();				
	}
}