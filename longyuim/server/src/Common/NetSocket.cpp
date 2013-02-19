
#include "NetSocket.h"

CNetSocket::CNetSocket()
{
	miSocket = -1;
	memset(mszResendBuffer, 0, DEF_BUFFER_LEN+1);
	miResendLength = 0;
	memset(mszRecvCache, 0, DEF_BUFFER_LEN*2+1);
	miRecvCacheLength = 0;
	mbCanSend = true;
	moNetStat = COMMON_TCP_CLOSED;
	mbListenSocket = false;
	moSendStat = SEND_NULL;
	mbClientSocket = false;
}


CNetSocket::~CNetSocket()
{
	Close();
}

bool CNetSocket::CreateSocket(void)
{
	miSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (miSocket < 0)
	{
		TRACE(1, "CNetSocket::CreateSocket socket() 失败。errno = "<<errno);
		return false;
	}
	return true;
}

bool CNetSocket::CreateSocket(const char* ip, const short port)
{
	miSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (miSocket < 0)
	{
		TRACE(1, "CNetSocket::CreateSocket socket() 失败。errno = "<<errno);
		return false;
	}

	//int iReuseAddr = 1;
	//setsockopt(miSocket, SOL_SOCKET, SO_REUSEADDR, (void*)(&(iReuseAddr))
	//	, sizeof(iReuseAddr));

	struct sockaddr_in stAddr;
	stAddr.sin_family = AF_INET;

	if (ip)
	{
		stAddr.sin_addr.s_addr = inet_addr(ip);
	}
	else
	{
		stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	stAddr.sin_port = htons(port);

	socklen_t loinlen = sizeof(sockaddr_in);

	if (bind(miSocket, (struct sockaddr *)&stAddr, loinlen) < 0)
	{
		TRACE(1, "CNetSocket::CreateSocket bind() 失败。port = "<<port<<
			" ip = "<<ip<<" errno = "<<errno);
		close(miSocket);
		return false;
	}

	return true;
}

bool CNetSocket::Close(int flag /* = 2 */)
{
	//清除发送缓冲区
	memset(mszResendBuffer, 0, DEF_BUFFER_LEN+1);
	miResendLength = 0;
	//清除发送队列
	CAutoLock send_lock(moSendSection);
	STRU_NET_DATA_INFO loNetDataInfo;
	while(moSendList.PopFront(loNetDataInfo))
	{
		delete loNetDataInfo.buffer;
		loNetDataInfo.buffer = NULL;
		loNetDataInfo.length = 0;
	}

	if(moSendList.IsEmpty())
	{
		TRACE(1, "CNetSocket::Close 发送列表已清空。");
	}
	else
	{
		TRACE(1, "CNetSocket::Close 发送列表未清空。");
	}
	//清除接收缓冲区
	memset(mszRecvCache, 0,  DEF_BUFFER_LEN*2+1);
	miRecvCacheLength = 0;
	//清除接收队列
	CAutoLock recv_lock(moRecvSection);
	while(moRecvList.PopFront(loNetDataInfo))
	{
		delete loNetDataInfo.buffer;
		loNetDataInfo.buffer = NULL;
		loNetDataInfo.length = 0;
	}

	if(moRecvList.IsEmpty())
	{
		TRACE(1, "CNetSocket::Close 接收列表已清空。");
	}
	else
	{
		TRACE(1, "CNetSocket::Close 接收列表未清空。");
	}

	shutdown(miSocket, flag);
	close(miSocket);
	moNetStat = COMMON_TCP_CLOSED;
	return true;
}

bool CNetSocket::Listen()
{
	if (listen(miSocket, 1024) < 0)
	{
		TRACE(1, "CNetSocket::Listen 失败。errno = "<<errno);
		return false;
	}
	moNetStat = COMMON_TCP_LISTEN;
	return true;
}
bool CNetSocket::ConnectServer(const char* ip, const short port)
{
	//设置socket连接超时时间
	struct sockaddr_in stAddr;
	stAddr.sin_family = AF_INET;

	if (ip)
	{
		stAddr.sin_addr.s_addr = inet_addr(ip);
	}
	else
	{
		stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	stAddr.sin_port = htons(port);

	socklen_t loinlen = sizeof(sockaddr_in);
	if (connect(miSocket,  (const struct sockaddr*)&stAddr, loinlen) < 0)
	{
		if (errno != EINPROGRESS)
		{
			TRACE(1, "CNetSocket::ConnectServer 失败。 errno = "<<errno<<
				" ip = "<<ip<<" port = "<<port);
			// 出现其他连接错误，则关闭连接
			return false;
		}
		// 非阻塞模式操作未完成
	}
	moNetStat = COMMON_TCP_CONNECTED;
	return true;
}

int CNetSocket::Accept(int &ip, short &port)
{
	sockaddr_in loSockAddr;
	int nRet = 0;
	socklen_t loinlen = sizeof(sockaddr_in);
	nRet = accept(miSocket, (struct sockaddr*)&loSockAddr, &loinlen);
	if(-1 == nRet)
	{
		//TRACE(1, "CNetSocket::Accept 失败。errno = "<<errno);
		return 0;
	}
	ip = ntohl(loSockAddr.sin_addr.s_addr);
	port = ntohs(loSockAddr.sin_port);
	return nRet;
}
bool CNetSocket::SetNoBlock()
{
	int iFlags = 1; // nonblock reusaddr

	ioctl(miSocket, FIONBIO, &iFlags);

	iFlags = fcntl(miSocket, F_GETFL, 0);
	fcntl(miSocket, F_SETFL, iFlags | O_NONBLOCK | O_NDELAY);

	int iBufLen = DEF_SOCKET_CATCH_LEN;
	//设置TCP的接收缓冲
	if(setsockopt(miSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iBufLen, sizeof(iBufLen)) == -1)
	{
		TRACE(1, "CNetSocket::SetNoBlock 设置接收缓冲区失败。");
		return false;
	}

	//设置TCP的发送缓冲
	if(setsockopt(miSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufLen, sizeof(iBufLen)) == -1)
	{
		TRACE(1, "CNetSocket::SetNoBlock 设置发送缓冲区失败。");
		return false;
	}

	//设置存活
	SetTcpSockKeepAlive(1, 90, 30, 3);

	return true;
}

int CNetSocket::SetTcpSockKeepAlive(int nKeepAlive, int nKeepIdle, int nKeepInterval, int nKeepCnt)
{
    if (setsockopt(miSocket, SOL_SOCKET, SO_KEEPALIVE, (void*)&nKeepAlive, sizeof(nKeepAlive)))
    {
        return -1;
    }

    if (nKeepAlive)
    {
        if (nKeepIdle > 0)
        {
            if (setsockopt(miSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&nKeepIdle, sizeof(nKeepIdle)))
            {
                return -2;
            }
        }

        if (nKeepInterval > 0)
        {
            if (setsockopt(miSocket, SOL_TCP, TCP_KEEPINTVL, (void*)&nKeepInterval, sizeof(nKeepInterval)))
            {
                return -3;
            }
        }

        if (nKeepCnt > 0)
        {
            if (setsockopt(miSocket, SOL_TCP, TCP_KEEPCNT, (void*)&nKeepCnt, sizeof(nKeepCnt)))
            {
                return -4;
            }
        }
    }

    return 0;
}


int CNetSocket::SendData(const char* buffer, const int length)
{
	CAutoLock lock(moSendSection);
	char lszSendBuffer[DEF_BUFFER_LEN];
	memset(lszSendBuffer, 0, DEF_BUFFER_LEN);
	int liSendLen = DEF_BUFFER_LEN;
	CNetPackHead loNetPackHead;
	loNetPackHead.miLength = length;
	liSendLen = loNetPackHead.Pack(lszSendBuffer, liSendLen);
	ASSERT(liSendLen == sizeof(CNetPackHead));
	memcpy(lszSendBuffer+liSendLen, buffer, length);
	liSendLen += length;

	STRU_NET_DATA_INFO struNetDataInfo;
	struNetDataInfo.buffer =  new char[liSendLen];
	memset(struNetDataInfo.buffer, 0, liSendLen);
	memcpy(struNetDataInfo.buffer, lszSendBuffer, liSendLen);
	struNetDataInfo.length = liSendLen;

	moSendList.PushBack(struNetDataInfo);
	return 1;
}

int CNetSocket::SendCacheData()
{
	if(miResendLength != 0)
	{
		int nRet = 0;
		nRet = _SendData(mszResendBuffer, miResendLength);
		if(nRet == 0)
		{
			mbCanSend = false;
			return 1;
		}
		if(nRet < 0)
		{
			return -1;
		}
		if((nRet < miResendLength) && (nRet > 0))
		{
			miResendLength -= nRet;
			ASSERT(miResendLength > 0);
			memmove(mszResendBuffer, mszResendBuffer+nRet, miResendLength+1);
			mbCanSend = false;
			return 1;
		}
	}

	miResendLength = 0;
	memset(mszResendBuffer, 0, DEF_BUFFER_LEN+1);
	return 0;
}

int CNetSocket::SendData()
{
	CAutoLock lock(moSendSection);

	if(miResendLength == 0 && moSendList.IsEmpty())
	{
		return 2;
	}

	if(!mbCanSend)
	{
		return 1;
	}

	int nSendCacheRtn = SendCacheData();
	if(nSendCacheRtn != 0)
	{
		return nSendCacheRtn;
	}

	STRU_NET_DATA_INFO loNetDataInfo;
	//如果将所有数据发送完毕就用while
	while(moSendList.TryPop(loNetDataInfo))
	{
		if(miResendLength + loNetDataInfo.length <= DEF_BUFFER_LEN)
		{
			STRU_NET_DATA_INFO info;
			moSendList.PopFront(info);
			
			ASSERT(info.length == loNetDataInfo.length);
			ASSERT(info.buffer == loNetDataInfo.buffer);

			memcpy(mszResendBuffer+miResendLength, loNetDataInfo.buffer, loNetDataInfo.length);
			miResendLength += loNetDataInfo.length;

			delete [] loNetDataInfo.buffer;
			loNetDataInfo.buffer = NULL;
			loNetDataInfo.length = 0;
		}
		else
		{
			int liReSendCache = SendCacheData();
			if(liReSendCache != 0)
			{
				return liReSendCache;
			}
		}
	}

	int iRtn = SendCacheData();
	if(iRtn != 0)
	{
		return iRtn;
	}
	return 0;
}

int CNetSocket::_SendData(const char* buffer, const int length)
{
	int nRet = send(miSocket, buffer, length, MSG_NOSIGNAL);
	if(nRet > 0)
	{
		if(nRet == length)
			moSendStat = SENDED;
		return nRet;
	}
	else if(nRet < 0)
	{
		if ((errno == EAGAIN) || (errno == EWOULDBLOCK) || (EINTR == errno))
		{
			//TRACE(1, "CNetSocket::_SendData errno = "<<errno);
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else if(nRet == 0)
	{
		return -1;
	}
	return 0;
}
bool CNetSocket::RecvData(char* buffer, int &length)
{
	CAutoLock lock(moRecvSection);
	ASSERT(buffer != NULL);
	if(moRecvList.IsEmpty())
		return false;

	STRU_NET_DATA_INFO loDataInfo;
	moRecvList.PopFront(loDataInfo);
	memcpy(buffer, loDataInfo.buffer, loDataInfo.length);
	length = loDataInfo.length;
	delete [] loDataInfo.buffer;
	loDataInfo.buffer = NULL;
	return true;
}

bool CNetSocket::RecvData()
{
	CAutoLock lock(moRecvSection);
	char lszBuffer[DEF_BUFFER_LEN];
	int liLength = DEF_BUFFER_LEN;
	while(moNetStat != COMMON_TCP_CLOSED)
	{
		memset(lszBuffer, 0, DEF_BUFFER_LEN);
		liLength = DEF_BUFFER_LEN;
		int nRet = recv(miSocket, lszBuffer, liLength, MSG_NOSIGNAL);
		if(nRet > 0)
		{
			ASSERT((miRecvCacheLength+nRet) <= (DEF_BUFFER_LEN*2));
			memcpy(mszRecvCache+miRecvCacheLength, lszBuffer, nRet);
			miRecvCacheLength += nRet;

			while (miRecvCacheLength > NET_PACK_HEAD_SIZE)
			{
				CNetPackHead loNetPackHead;
				int liHeadSize = NET_PACK_HEAD_SIZE;
				bool nReturn = loNetPackHead.Unpack(mszRecvCache, liHeadSize);
				if(nReturn)
				{
					nReturn = loNetPackHead.CheckHead();
					if(!nReturn)
					{
						TRACE(1, "CNetSocket::RecvData Head Error.fd = "<<miSocket);
						return false;
					}
				}
				else
				{
					TRACE(1, "CNetSocket::RecvData解包失败.fd = "<<miSocket);
					return false;
				}

				if(nReturn)
				{
					if(miRecvCacheLength < (NET_PACK_HEAD_SIZE + loNetPackHead.miLength))
					{
						break;
					}

					if(loNetPackHead.miLength <= DEF_BUFFER_LEN)
					{
						STRU_NET_DATA_INFO loNetDataInfo;
						char *lpBuffer = new char[loNetPackHead.miLength+1];
						memset(lpBuffer, 0, loNetPackHead.miLength+1);
						memcpy(lpBuffer, mszRecvCache+NET_PACK_HEAD_SIZE, loNetPackHead.miLength);
						loNetDataInfo.length = loNetPackHead.miLength;
						loNetDataInfo.buffer = lpBuffer;
						moRecvList.PushBack(loNetDataInfo);
					}
					else
					{
						TRACE(1, "CNetSocket::RecvData 数据有问题。length = "<<loNetPackHead.miLength);
					}

					int liGetLen = NET_PACK_HEAD_SIZE+loNetPackHead.miLength;
					miRecvCacheLength -= liGetLen;
					ASSERT(miRecvCacheLength >= 0);
					if(miRecvCacheLength > 0)
					{
						memmove(mszRecvCache, mszRecvCache+liGetLen, miRecvCacheLength+1);
					}
					else
					{
						memset(mszRecvCache, 0, DEF_BUFFER_LEN*2+1);
					}
				}
			}

			if(nRet >= DEF_BUFFER_LEN)
			{
				continue;
			}
			else
			{
				return true;
			}
		}
		else if (nRet == 0 )
		{
			TRACE(1,"CNetSocket::RecvData recv errno : "<<errno<<" fd = "<<miSocket);
			return false;
		}
		else if((nRet < 0) && (errno != ECONNRESET))
		{
			return true;
		}
	}
	return false;
}

void CNetSocket::Dump()
{

}

void CNetSocket::TimeOutWork()
{

}


















