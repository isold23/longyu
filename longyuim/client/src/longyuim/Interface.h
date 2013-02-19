#pragma once
#include <Unknwn.h>

interface IPackManager
{
	virtual void SocketClose() = 0;
	virtual void SocketError(int ErrorCode) = 0;
	virtual void AddRecvData(const char* apszBuffer, WORD awDataLen) = 0;
	virtual int GetSendData(const char* apszBuffer, WORD& awDataLen) = 0;
};