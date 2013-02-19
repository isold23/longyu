#include "stdafx.h"
#include "PackManager.h"

template<class T>
CPackManager<T>::CPackManager(int aiBufferMaxLen)
{
	miRecvBuffLen = 0;
	miRecvBuffMaxlen = aiBufferMaxLen;
	mpRecvBuffer = new char[miRecvBuffMaxlen];
	memset(mpRecvBuffer, 0, miRecvBuffMaxlen);
	mhMsgHandle = NULL;
	mpUserParam = NULL;
}

template<class T>
CPackManager<T>::~CPackManager()
{
	delete mpRecvBuffer;
}

template<class T>
void CPackManager<T>::SocketClose()
{
	PostMessage(mhMsgHandle, WM_SOCKET_CLOSE, NULL, (LPARAM)mpUserParam);
}

template<class T>
void CPackManager<T>::SocketError(int ErrorCode)
{
	PostMessage(mhMsgHandle, WM_SOCKET_ERROR, ErrorCode, (LPARAM)mpUserParam);
}

template<class T>
void CPackManager<T>::AddRecvData(const char* apszBuffer, WORD awDataLen)
{
	if(apszBuffer == NULL || awDataLen == 0)
	{
		return;			//缓存区内没有数据
	}

	if((miRecvBuffLen + awDataLen) > miRecvBuffMaxlen)
	{	
		ZeroMemory(mpRecvBuffer, miRecvBuffMaxlen);
		miRecvBuffLen = 0;
		return;  //缓存区存不下
	}

	CAutoLock lock(m_RecvCS);
	memcpy(mpRecvBuffer + miRecvBuffLen, apszBuffer, awDataLen);
	miRecvBuffLen = miRecvBuffLen + awDataLen;
	T* pT = static_cast<T*>(this);
	while (true)
	{
		PSTRU_PACK_INFO pPack = new STRU_PACK_INFO();

		WORD awtimestamp;

		if(pT->UnPack(mpRecvBuffer, ((WORD&)miRecvBuffLen), pPack->mpBuffer, pPack->mwBuffLen, awtimestamp) == 1 && mhMsgHandle != NULL)
		{
			PostMessage(mhMsgHandle, WM_RECV_PACK, (WPARAM)pPack, (LPARAM)mpUserParam);
		}	
		else
		{
			printf("UnPack Failed, left bufferlen:%d\r\n", miRecvBuffLen);
			delete pPack;
			break;
		}
	}	
}

template<class T>
int CPackManager<T>::GetSendData(const char* apszBuffer, WORD& awMaxDataLen)
{
	CAutoLock lock(m_SendCS);
	if(m_SendBuffer.GetLength() != 0)
	{
		int liLen = awMaxDataLen;
		void* pBuffer = (void*)m_SendBuffer.AllocateFullBuffer(liLen);	
		memcpy((void*)apszBuffer, pBuffer, liLen);
		delete pBuffer;
		awMaxDataLen = liLen;
		return liLen;
	}	
	awMaxDataLen = 0;
	return 0;
}

template<class T>
bool CPackManager<T>::AddSendData(const char* apszBuffer, WORD awDataLen)
{
	CAutoLock lock(m_SendCS);

	T* pT = static_cast<T*>(this);
	char pBuffer[65536]={0};
	WORD lwLen = 65536;
	if(pT->Pack(const_cast<char*>(apszBuffer), awDataLen, pBuffer, lwLen) == 1)
	{
		m_SendBuffer.Append((BYTE*)pBuffer, lwLen);
		return true;
	}
	return false;
}