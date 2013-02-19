#pragma once
#include <Unknwn.h>

interface IPackManager
{
	virtual void SocketClose() = 0;
	virtual void SocketError(int ErrorCode) = 0;
	virtual void AddRecvData(const char* apszBuffer, WORD awDataLen) = 0;
	virtual int GetSendData(const char* apszBuffer, WORD& awDataLen) = 0;
};

interface ITCPMessager:public IUnknown
{
	virtual bool __stdcall Open()=0;
	virtual void __stdcall Close()=0;
	virtual bool __stdcall IsClosed()=0;
	virtual GUID __stdcall getGUID()=0;

	virtual int  __stdcall Init()=0;
	virtual void __stdcall adviseSystemInterface(LPVOID * apVoid)=0;

	virtual void __stdcall setNetInfo(int netType,const char* proxyIP, int proxyPort,const char* proxyUser,const char* proxyPwd)=0;
	virtual bool __stdcall OpenTCPSession(GUID &aFunGuid,long &alHallID,const char* astrServerAddr,WORD awServerPort)=0;
	virtual void __stdcall CloseTCPSession(GUID &aFunGuid,long &alHallID)=0;
	virtual int	 __stdcall SendTCPData(GUID &aFunGuid,long &alHallID,char *apData,WORD awDataLen)=0;
	virtual void __stdcall SendTCPLivePack()=0;
} ;

class CSendPack;
//System supply interface for Message
interface ISystemMSG
{
	enum ENUM_PACKSOURCE  {PackbyDirect,PackbyServerTrans,PackbyServerStore};
	virtual void __stdcall messagerOpened()=0;
	virtual void __stdcall messagerClosed()=0;
	/*
	网络错误报告
	aiError = MESSAGER_CANNOT_OPEN  表示Messager无法打开.
	= NET_DISCONNECT 网络已断
	*/
	virtual void __stdcall  netError(const int aiError)=0;

	virtual int __stdcall solvePack(const GUID &guid,const std::string &userID,const std::string &nickName,const int &photoNum, char * apPackData, WORD awPackDataLen,ENUM_PACKSOURCE aByType) =0;

	/*
	//功能：处理发包错误,当消息中心发包出现错误时，调用此函数. 此包是发向userID的包,模块GUID为guid, 包内容为packData,错误类型由error指定
	//使用：可以在此函数中，提示用户或进行其它操作
	//参数：
	error     =SENDPACK_TIMEOUT 发包超时无回应
	=HASNOT_ADDR  地址缓冲找不用户地址
	=NET_DISCONNECT 网络已断

	*/
	virtual void __stdcall solveError(const GUID &guid,const int &error,const  std::string  &userID,char * apPackData, WORD awPackDataLen ,const std::string &astrNickName,__int64 &aiPicNum)=0;
	virtual void __stdcall solveError(const GUID &guid,const int &error,const  __int64 mi64UserID,char * apPackData, WORD awPackDataLen ,const std::string &astrNickName,__int64 &aiPicNum)=0;
	virtual	void __stdcall  sendPackSuccess(GUID guid,unsigned char abyErr,std::string astrUserDesID,  char * apPackData, WORD awPackDataLen )=0;
	virtual BYTE __stdcall GetSysStatus() = 0;
	virtual void __stdcall SendServerTransPack(CSendPack * apoPack,
		WORD awDestACSSiteID=0,
		BYTE abyDestNetType=0,
		std::string astrDestAddr="",
		WORD awDestPort=0)= 0;
	virtual void __stdcall GetOtherUserStatus(__int64 ai64UserID)=0;

	//tcp mesager
	virtual void __stdcall OnOpenTCPSession(const GUID &aFunGuid,const long &alHallID)=0;//连接成功
	virtual void __stdcall OnCloseTCPSession(const GUID &aFunGuid,const long &alHallID)=0;//关闭成功
	virtual void __stdcall OnErrTCPSession(const BYTE &abyErrType,const GUID &aFunGuid,const long &alHallID)=0;//和该大厅连接关闭
	virtual void __stdcall SolveTCPPackage(const GUID &aFunGuid,const long &alHallID,char * apPackData, WORD awPackDataLen)=0;//收包
	virtual int	 __stdcall OnInterCheckPack(char *apBuffer ,long alLen,__int64 ai64UserID,unsigned long alSourceIpAddr,WORD awSourcePort,WORD awLoginAcsID)=0;    
	virtual HWND __stdcall GetSystemHandle()=0;

};