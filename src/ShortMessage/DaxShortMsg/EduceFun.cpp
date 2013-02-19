#include "StdAfx.h"
#include "EduceFun.h"
#include "Sms.h"

CSms mySms;

DLL_EXPORT int WINAPI OpenCom(int port, int baud_rate)
{
	return mySms.Open_Com(port, baud_rate);
}

DLL_EXPORT void WINAPI CloseCom()
{
	mySms.Close_Com();
}

DLL_EXPORT int WINAPI WINAPI ATCommand(char* ATCmd,char* result)
{
	return mySms.Send_ATCmd(ATCmd,result);
}

DLL_EXPORT int WINAPI GetSmCapacity(char* smCapacity)
{
	return mySms.Get_SmCapacity(smCapacity);
}

DLL_EXPORT int WINAPI GetSmsc(char* smsc){
	return mySms.Get_Smsc(smsc);
}

DLL_EXPORT int WINAPI SetSmsc(char* smsc)
{
	return mySms.Set_Smsc(smsc);
}

DLL_EXPORT int WINAPI SendMsg(char* PhoneID,char* SmsContent)
{
	return mySms.Send_Msg(PhoneID,SmsContent);
}

DLL_EXPORT int WINAPI DeleteMsg(int index)
{
	return mySms.Delete_Msg(index);
}

DLL_EXPORT int WINAPI ReadMsg(int index,char* PhoneID,char* SmsContent,char* Date)
{
	return mySms.Read_Msg(index,PhoneID,SmsContent,Date);
}

DLL_EXPORT int WINAPI ReadAllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index)
{
	return mySms.Read_AllMsg(type,PhoneID,SmsContent,Date,Index);
}

DLL_EXPORT int WINAPI SMSInit()
{
	return mySms.SMS_Init();
}

DLL_EXPORT int WINAPI SetSendModle(int modle)
{
	return mySms.Set_SendModle(modle);
}