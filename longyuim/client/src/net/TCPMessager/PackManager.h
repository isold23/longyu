#pragma once
#include "Interface.h"
#include "AutoBuffer.h"
#include "AutoLock.h"

#define TCPPACK_LEN   64*1024 - 1        //tcp包最大长度
#define MAXBUFFSIZE 65536

#define WM_SOCKET_CLOSE WM_USER + 1000
#define WM_SOCKET_ERROR WM_USER + 1001
#define WM_RECV_PACK	WM_USER + 1002
#define WM_SOCKET_OPEN_RESULT	WM_USER + 1003

typedef struct STRU_PACK_INFO
{
	char* mpBuffer;
	WORD mwBuffLen;
	STRU_PACK_INFO()
	{
		mpBuffer = new char[MAXBUFFSIZE];
		memset(mpBuffer, 0, MAXBUFFSIZE);
		mwBuffLen = MAXBUFFSIZE;
	}
	~STRU_PACK_INFO()
	{
		delete [] mpBuffer;
	}
}*PSTRU_PACK_INFO;

template<class T>
class CPackManager:public IPackManager
{
public:
	CPackManager(int aiBufferMaxLen);
	virtual ~CPackManager();

	virtual void SocketClose();
	virtual void SocketError(int ErrorCode);
	virtual void AddRecvData(const char* apszBuffer, WORD awDataLen);
	virtual int GetSendData(const char* apszBuffer, WORD& awMaxDataLen);

	//----------------------------------------------------
	//将输入的数据打包成TCP通讯包
	//参数：	apInData: 输入的数据
	//		awInDataLen 输入的数据的长度
	//		char * apTcpPack 打包好的TCP数据
	//		WORD& awTcpPackLen 打包好的tcp数据长度
	//返回值：	int  1= 成功；-1=失败
	//解释：				
	//----------------------------------------------------
	//virtual int	Pack(char* apInData, WORD awInDataLen, char* apTcpPack, WORD& awTcpPackLen) = 0;

	///----------------------------------------------------
	//将TCP通讯包解包
	//参数：
	//		char * apTcpBuffer  TCP缓存
	//		WORD& awTcpBuffLen TCP缓存长度
	//		apOutData: 解包后的数据
	//		WORD& awOutDataLen 解包后的数据的长度
	//      WORD&  awtimestamp 时间戳位移数值
	//返回值：	 1= 成功；-1=失败

	//----------------------------------------------------
	//virtual int UnPack(char* apTcpBuffer, WORD& awTcpBuffLen, char* apOutData, WORD& awOutDataLen, WORD& awtimestamp) = 0;

	bool AddSendData(const char* apszBuffer, WORD awDataLen);

	void Init(HWND ahMsgHandle, void* apUserParam){mhMsgHandle = ahMsgHandle; mpUserParam = apUserParam;}

	void* GetUserParam(){return mpUserParam;}
private:
	char* mpRecvBuffer;
	int   miRecvBuffMaxlen;
	int   miRecvBuffLen;
	CAutoBuffer m_SendBuffer;
	CCriticalSection m_SendCS;
	CCriticalSection m_RecvCS;

	void* mpUserParam;
	HWND mhMsgHandle;
};