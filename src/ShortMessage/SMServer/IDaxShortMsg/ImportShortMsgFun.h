// ImportShortMsgFun.h: interface for the ImportShortMsgFun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTSHORTMSGFUN_H__4A151594_F145_4D3C_A425_0120EDB9E7C1__INCLUDED_)
#define AFX_IMPORTSHORTMSGFUN_H__4A151594_F145_4D3C_A425_0120EDB9E7C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ImportShortMsgFun  
{
public:
	ImportShortMsgFun();
	virtual ~ImportShortMsgFun();
public:
    BOOL	InitShortMsg(TCHAR* pszError);
    void	UnInitShortMsg();
	
    typedef int  (WINAPI *IOpenCom)(int port, int baud_rate);
    typedef void (WINAPI *ICloseCom)();
    typedef int  (WINAPI *IATCommand)(char* ATCmd,char* result);
    typedef int  (WINAPI *ISendMsg)(char* PhoneID,char* SmsContent);
    typedef int  (WINAPI *IDeleteMsg)(int index);
    typedef int  (WINAPI *IReadMsg)(int index,char* PhoneID,char* SmsContent,char* Date);
    typedef int  (WINAPI *IGetSmsc)(char* smsc);
    typedef int  (WINAPI *ISMSInit)();
    typedef int  (WINAPI *ISetSmsc)(char* smsc);
    typedef int  (WINAPI *IReadAllMsg)(int type,char* PhoneID,char* SmsContent,char* Date,char* Index);
    typedef int  (WINAPI *ISetSendModle)(int modle);
	typedef int  (WINAPI *IGetSmCapacity)(char* smCapacity);
    
    int  OpenCom(int port, int baud_rate);
    void CloseCom();
    int  ATCommand(char* ATCmd, char* result);
    int  SendMsg(char* PhoneID,char* SmsContent);
    int  DeleteMsg(int index);
    int  ReadMsg(int index,char* PhoneID,char* SmsContent,char* Date);
    int  GetSmsc(char* smsc);
    int  SMSInit();
    int  SetSmsc(char* smsc);
    int  ReadAllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index);
    int  SetSendModle(int modle);
	int  GetSmCapacity(char* smCapacity);
	
private:
    HINSTANCE           m_hShortMsgDLL;
	
    IOpenCom            m_pfOpenCom;
    ICloseCom           m_pfCloseCom;
    IATCommand          m_pfATCommand;
    ISendMsg            m_pfSendMsg;
    IDeleteMsg          m_pfDeleteMsg;
    IReadMsg            m_pfReadMsg;
    IGetSmsc            m_pfGetSmsc;
    ISMSInit            m_pfSMSInit;
    ISetSmsc            m_pfSetSmsc;
    IReadAllMsg         m_pfReadAllMsg;
    ISetSendModle       m_pfSetSendModle;
	IGetSmCapacity      m_pfGetSmCapacity;
};

#endif // !defined(AFX_IMPORTSHORTMSGFUN_H__4A151594_F145_4D3C_A425_0120EDB9E7C1__INCLUDED_)
