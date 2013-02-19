#pragma once

#include "PackManager.h"

class CUCPackManager: public CPackManager<CUCPackManager>
{
public:
	CUCPackManager(int aiBufferMaxLen = TCPPACK_LEN);

	virtual ~CUCPackManager(){}

	//----------------------------------------------------
	//将输入的数据打包成TCP通讯包
	//参数：	apInData: 输入的数据
	//		awInDataLen 输入的数据的长度
	//		char * apTcpPack 打包好的TCP数据
	//		WORD& awTcpPackLen 打包好的tcp数据长度
	//返回值：	int  1= 成功；-1=失败
	//解释：				
	//----------------------------------------------------
	virtual int	Pack(char* apInData, WORD awInDataLen, char* apTcpPack, WORD& awTcpPackLen);

	//----------------------------------------------------
	//将TCP通讯包解包
	//参数：
	//		char * apTcpBuffer  TCP缓存
	//		WORD& awTcpBuffLen TCP缓存长度
	//		apOutData: 解包后的数据
	//		WORD& awOutDataLen 解包后的数据的长度
	//      WORD&  awtimestamp 时间戳位移数值
	//返回值：	 1= 成功；-1=失败

	//----------------------------------------------------
	virtual int UnPack(char* apTcpBuffer, WORD& awTcpBuffLen, char* apOutData, WORD& awOutDataLen, WORD& awtimestamp);
private:

	//----------------------------------------------------
	// 从TCP缓存中分解出TCP包(分析出tcp包后，
	//      需要将分析出的包从缓存区中移出，并相应修改缓存区数据的长度)
	//参数：
	//		char * apTcpBuffer  TCP缓存
	//		WORD& awTcpBuffLen TCP缓存长度
	//		char * apTcpPack  分析出的tcp数据包
	//		WORD& awTcpPackLen 分析出的tcp数据包的长度
	//返回值：	int  1= 分析出有tcp数据包；
	//		    	-1=没有分析出tcp数据包
	//----------------------------------------------------
	int	AnalyseTcpStoreBuffer(char* apTcpBuffer, WORD& awTcpBuffLen, char* apTcpPack, WORD& awTcpPackLen);
private:
	WORD mwTimestamp;
};