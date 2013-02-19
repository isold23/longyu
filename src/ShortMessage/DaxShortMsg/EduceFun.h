/************************************************************************************
*
*公    司： Beijing DaxStudio dagital Corp,
*文件描述： Dax ShortMsg Foundation Libiary
*时    间： 2005/11/22
*
**************************************************************************************/

#if !defined (AFX_ENCRYPT_H_INCLUDE_)
#define AFX_ENCRYPT_H_INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DLL_EXPORT extern "C"
/*
function:
此函数用于计算MD5散列值。

  Parameters:
  
	lpInBuffer
	指向输入字符串的缓冲区指针。
	
	  lpOutBuffer
	  指向输出MD5散列值缓冲区的指针。
	  (输出长度最长为16)
	  
		Return values:
		此函数固定输出32位长度。
		如果函数调用成功，则返回值为TRUE；如果函数调用失败，返回值为FALSE。
*/
DLL_EXPORT int WINAPI OpenCom(int port, int baud_rate);

DLL_EXPORT void WINAPI CloseCom();

DLL_EXPORT int WINAPI ATCommand(char* ATCmd,char* result);

DLL_EXPORT int WINAPI GetSmCapacity(char* smCapacity);

DLL_EXPORT int WINAPI GetSmsc(char* smsc);

DLL_EXPORT int WINAPI SetSmsc(char* smsc);

DLL_EXPORT int WINAPI SendMsg(char* PhoneID,char* SmsContent);

DLL_EXPORT int WINAPI DeleteMsg(int index);

DLL_EXPORT int WINAPI ReadMsg(int index,char* PhoneID,char* SmsContent,char* Date);

DLL_EXPORT int WINAPI ReadAllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index);

DLL_EXPORT int WINAPI SMSInit();

DLL_EXPORT int WINAPI SetSendModle(int modle);

#endif AFX_ENCRYPT_H_INCLUDE_