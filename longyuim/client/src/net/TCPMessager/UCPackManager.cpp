#include "stdafx.h"
#include "UCPackManager.h"
#include "PackManager.cpp"
#include <time.h>
#include "LMEnDecrypt.H"


extern LMEnDecrypt goEnDecrypt;

const char macPackHeader[] = "\01\02\03\0";
const char macPackTail[] = "\04\05\06\0";

#define LM_ENCRYPT

#define TCP_PACK_VERSION 1
#define TCP_PACK_STRUCT_LEN 13


CUCPackManager::CUCPackManager(int aiBufferMaxLen)
		:CPackManager(aiBufferMaxLen)
{
	srand((unsigned)time(NULL));
	mwTimestamp = rand();           
}

int	CUCPackManager::Pack(char* apInData, WORD awInDataLen, char* apTcpPack, WORD& awTcpPackLen)
{
	BYTE lpBuffer[TCPPACK_LEN];

	memset(lpBuffer, 0,TCPPACK_LEN);
	awTcpPackLen = 0;

#ifdef LM_ENCRYPT	
	//加密
	//改变成8的倍数
	WORD lwDecryptLen = 8-(awInDataLen+2)%8;
	int liTempDecryptLen=lwDecryptLen+	awInDataLen+2;
	//加密过长
	if (liTempDecryptLen>TCPPACK_LEN)
		return -1; 
	lwDecryptLen=liTempDecryptLen;

	char *lpcEncrypt = new char[lwDecryptLen];
	ZeroMemory(lpcEncrypt, lwDecryptLen);

	if (goEnDecrypt.LmEncrypt(apInData, awInDataLen, lpcEncrypt, lwDecryptLen) == -1)
	{//加密失败
		if (lpcEncrypt != NULL)
		{
			delete[] lpcEncrypt;
			lpcEncrypt = NULL;
		}
		return -2;
	}
#else	
	if (awInDataLen > TCPPACK_LEN)
		return -1;
	WORD lwDecryptLen = awInDataLen;
	char *lpcEncrypt = new char[lwDecryptLen];
	ZeroMemory(lpcEncrypt, lwDecryptLen);
	memcpy(lpcEncrypt,apInData,awInDataLen);
#endif

	mwTimestamp++;

	BYTE lbyVersion =TCP_PACK_VERSION; 
	//包头
	memcpy(lpBuffer, (BYTE *)macPackHeader, 3);

	//包长
	memcpy(lpBuffer + 3, (BYTE *)&lwDecryptLen, 2);

	//版本
	memcpy(lpBuffer + 5, (BYTE *)&lbyVersion, 1);

	//时间戳
	memcpy(lpBuffer + 6, (BYTE *)&mwTimestamp, 2);

	//数据
	memcpy(lpBuffer + 8, (BYTE *)lpcEncrypt, lwDecryptLen);
	awTcpPackLen = 8 + lwDecryptLen;

	//包尾
	memcpy(lpBuffer + awTcpPackLen, (BYTE *)macPackTail, 3);
	awTcpPackLen +=3;
	//包长
	memcpy(lpBuffer + awTcpPackLen, (BYTE *)&lwDecryptLen, 2);
	awTcpPackLen  += 2;

	memcpy(apTcpPack, lpBuffer, awTcpPackLen);
	if (lpcEncrypt != NULL)
	{
		delete[] lpcEncrypt;
		lpcEncrypt = NULL;
	}
	return 1;
}

int CUCPackManager::UnPack(char* apTcpBuffer, WORD& awTcpBuffLen, char* apOutData, WORD& awOutDataLen, WORD& awtimestamp)
{
	BYTE    lpBuffer[TCPPACK_LEN];
	WORD   lwPacklenHeader=0;
	WORD   lwPacklenTail  =0;
	char   tempbuffer[4];
	WORD   lwTcpPackLen=0;
	lwTcpPackLen = TCPPACK_LEN;

	if(AnalyseTcpStoreBuffer(apTcpBuffer, awTcpBuffLen, (char*)lpBuffer, lwTcpPackLen) != 1)
		return   -1;

	//TCP通讯包解包长度不够
	if(lwTcpPackLen < TCP_PACK_STRUCT_LEN)
		return -2; 

	//判断包头
	memset(tempbuffer,0, 4);
	memcpy(tempbuffer,lpBuffer,3);
	if(memcmp(tempbuffer,macPackHeader,3)!=0)
	{ //头不对
		return -3; 
	}

	memcpy(&lwPacklenHeader, lpBuffer + 3,2);
	if (lwPacklenHeader > TCPPACK_LEN)
	{
		return -4; //不足以容纳包内容
	}

	BYTE lbyVersion=0;
	//得到版本
	memcpy(&lbyVersion, lpBuffer+5,1);
	//得到时间戳
	memcpy(&awtimestamp, lpBuffer+6,2);

	//拷贝内容
	memcpy(apOutData, lpBuffer + 8, lwPacklenHeader);

	//判断包尾
	memset(tempbuffer, 0, 4);
	memcpy(tempbuffer, lpBuffer + 8 + lwPacklenHeader, 3);
	if(memcmp(tempbuffer, macPackTail, 3)!=0)
	{ 
		return -5; //尾不对
	}

	//判断包前后长度
	memcpy(&lwPacklenTail, lpBuffer + 11 + lwPacklenHeader, 2);
	if (lwPacklenTail != lwPacklenHeader)
	{
		return -6; //前后长度不一致
	}
#ifdef LM_ENCRYPT
	WORD lwDataLen=0;
	char *lpDecrypt = new char[lwPacklenHeader];
	memcpy(lpDecrypt,apOutData,lwPacklenHeader);
	if (goEnDecrypt.LmDecrypt(lpDecrypt, lwPacklenHeader, apOutData, awOutDataLen) == -1)
	{//解密失败
		if (lpDecrypt)
		{
			delete []lpDecrypt;
			lpDecrypt = NULL;
		}
		return -7;
	}
	if (lpDecrypt)
	{
		delete []lpDecrypt;
		lpDecrypt = NULL;
	}
#else
	awOutDataLen = lwPacklenHeader;
#endif
	return 1;
}

int	CUCPackManager::AnalyseTcpStoreBuffer(char* apTcpBuffer, WORD& awTcpBuffLen, char* apTcpPack, WORD& awTcpPackLen)
{
	int liPacklenHeader = 0;
	int liPacklenTail  = 0;
	int	liResult = -1;

	for(int i=0;i < (awTcpBuffLen - 2 ); i++)
	{ 
		if(memcmp(macPackHeader,apTcpBuffer + i,3)==0)
		{
			memcpy(&liPacklenHeader, apTcpBuffer + i + 3, 2);
			if (liPacklenHeader > (awTcpBuffLen - i - TCP_PACK_STRUCT_LEN))
			{
				break;		//包长比缓充区剩下的还大
			}

			if ((liPacklenHeader > awTcpPackLen))
			{
				continue;		//内容长度超过一个包最大的长度
			}

			if(liPacklenHeader > (awTcpBuffLen - i - TCP_PACK_STRUCT_LEN)
				|| (liPacklenHeader == 0)) 
			{
				liResult = 0;	//有包没到全
				break;
			}

			if(memcmp(macPackTail, apTcpBuffer + i+ (TCP_PACK_STRUCT_LEN - 5) + liPacklenHeader, 3) != 0)
			{
				break;		//包尾未到
			}

			memcpy(&liPacklenTail,apTcpBuffer + i + (TCP_PACK_STRUCT_LEN - 2) + liPacklenHeader, 2);

			if(liPacklenHeader != liPacklenTail)
			{
				break;		//后一个包长度未到
			}

			//得到TCP包的内容及长度
			memcpy(apTcpPack, apTcpBuffer + i,liPacklenHeader + TCP_PACK_STRUCT_LEN);
			awTcpPackLen = liPacklenHeader + TCP_PACK_STRUCT_LEN;

			//移动缓存中数据，并初始化使用过的数据
			memmove(apTcpBuffer, apTcpBuffer + awTcpPackLen + i, awTcpBuffLen - awTcpPackLen-i);
			memset(apTcpBuffer + awTcpBuffLen- awTcpPackLen-i, 0, awTcpPackLen + i);
			awTcpBuffLen = awTcpBuffLen - awTcpPackLen - i;
			liResult = 1;
			break;
		}
		else
		{
			if(i== awTcpBuffLen - 3)
			{
				memset(apTcpBuffer, 0, awTcpBuffLen);
				awTcpBuffLen = 0;
				liResult = -1;
				break;
			}
		}
	}
	return liResult;
}