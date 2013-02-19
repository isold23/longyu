// ImportShortMsgFun.cpp: implementation of the ImportShortMsgFun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImportShortMsgFun.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImportShortMsgFun::ImportShortMsgFun()
{
    m_hShortMsgDLL = NULL;
	
    m_pfOpenCom = NULL;
    m_pfCloseCom = NULL;
    m_pfATCommand = NULL;
    m_pfSendMsg = NULL;
    m_pfDeleteMsg = NULL;
    m_pfReadMsg = NULL;
    m_pfGetSmsc = NULL;
    m_pfSMSInit = NULL;
    m_pfSetSmsc = NULL;
    m_pfReadAllMsg = NULL;
    m_pfSetSendModle = NULL;
	m_pfGetSmCapacity = NULL;
}

ImportShortMsgFun::~ImportShortMsgFun()
{

}

BOOL ImportShortMsgFun::InitShortMsg(TCHAR* pszError)
{
    //¶¯Ì¬µ÷ÓÃ
    m_hShortMsgDLL = ::LoadLibrary(_T("DaxShortMsg.dll"));
    if (!m_hShortMsgDLL)
    {
        _tcscpy(pszError, _T("LoadLibrary fail."));
        return FALSE;
    }
    else
    {
        m_pfOpenCom = (IOpenCom)::GetProcAddress(m_hShortMsgDLL,"OpenCom");
        if (!m_pfOpenCom)
        {
            _tcscpy(pszError, _T("GetProcAddress OpenCom fail."));
            return FALSE;
        }

        m_pfCloseCom = (ICloseCom)::GetProcAddress(m_hShortMsgDLL,"CloseCom");
        if (!m_pfCloseCom)
        {
            _tcscpy(pszError, _T("GetProcAddress CloseCom fail."));
            return FALSE;
        }

        m_pfATCommand = (IATCommand)::GetProcAddress(m_hShortMsgDLL,"ATCommand");
        if (!m_pfATCommand)
        {
            _tcscpy(pszError, _T("GetProcAddress ATCommand fail."));
            return FALSE;
        }

        m_pfSendMsg = (ISendMsg)::GetProcAddress(m_hShortMsgDLL,"SendMsg");
        if (!m_pfSendMsg)
        {
            _tcscpy(pszError, _T("GetProcAddress SendMsg fail."));
            return FALSE;
        }

        m_pfDeleteMsg = (IDeleteMsg)::GetProcAddress(m_hShortMsgDLL,"DeleteMsg");
        if (!m_pfDeleteMsg)
        {
            _tcscpy(pszError, _T("GetProcAddress DeleteMsg fail."));
            return FALSE;
        }

        m_pfReadMsg = (IReadMsg)::GetProcAddress(m_hShortMsgDLL,"ReadMsg");
        if (!m_pfReadMsg)
        {
            _tcscpy(pszError, _T("GetProcAddress ReadMsg fail."));
            return FALSE;
        }

        m_pfGetSmsc = (IGetSmsc)::GetProcAddress(m_hShortMsgDLL,"GetSmsc");
        if (!m_pfGetSmsc)
        {
            _tcscpy(pszError, _T("GetProcAddress GetSmsc fail."));
            return FALSE;
        }

        m_pfSMSInit = (ISMSInit)::GetProcAddress(m_hShortMsgDLL,"SMSInit");
        if (!m_pfSMSInit)
        {
            _tcscpy(pszError, _T("GetProcAddress SMSInit fail."));
            return FALSE;
        }

        m_pfSetSmsc = (ISetSmsc)::GetProcAddress(m_hShortMsgDLL,"SetSmsc");
        if (!m_pfSetSmsc)
        {
            _tcscpy(pszError, _T("GetProcAddress SetSmsc fail."));
            return FALSE;
        }

        m_pfReadAllMsg = (IReadAllMsg)::GetProcAddress(m_hShortMsgDLL,"ReadAllMsg");
        if (!m_pfReadAllMsg)
        {
            _tcscpy(pszError, _T("GetProcAddress ReadAllMsg fail."));
            return FALSE;
        }

        m_pfSetSendModle = (ISetSendModle)::GetProcAddress(m_hShortMsgDLL,"SetSendModle");
        if (!m_pfSetSendModle)
        {
            _tcscpy(pszError, _T("GetProcAddress SetSendModle fail."));
            return FALSE;
        }

		
        m_pfGetSmCapacity = (IGetSmCapacity)::GetProcAddress(m_hShortMsgDLL,"GetSmCapacity");
        if (!m_pfGetSmCapacity)
        {
            _tcscpy(pszError, _T("GetProcAddress GetSmCapacity fail."));
            return FALSE;
        }
    }

    return TRUE;
}

void ImportShortMsgFun::UnInitShortMsg()
{
    if (!m_hShortMsgDLL)
        return;

    m_pfOpenCom = NULL;
    m_pfCloseCom = NULL;
    m_pfATCommand = NULL;
    m_pfSendMsg = NULL;
    m_pfDeleteMsg = NULL;
    m_pfReadMsg = NULL;
    m_pfGetSmsc = NULL;
    m_pfSMSInit = NULL;
    m_pfSetSmsc = NULL;
    m_pfReadAllMsg = NULL;
    m_pfSetSendModle = NULL;
	m_pfGetSmCapacity = NULL;


    ::FreeLibrary(m_hShortMsgDLL);
    m_hShortMsgDLL = NULL;
}

int ImportShortMsgFun::OpenCom(int port, int baud_rate)
{
    if (!m_pfOpenCom) return FALSE;
    return m_pfOpenCom(port, baud_rate);
}

void ImportShortMsgFun::CloseCom()
{
    if (!m_pfCloseCom) return;
    m_pfCloseCom();
}

int ImportShortMsgFun::ATCommand(char* ATCmd,char* result)
{
    if (!m_pfATCommand) return FALSE;
    return m_pfATCommand(ATCmd, result);
}

int ImportShortMsgFun::SendMsg(char* PhoneID,char* SmsContent)
{
    if (!m_pfSendMsg) return FALSE;
    return m_pfSendMsg(PhoneID, SmsContent);
}

int ImportShortMsgFun::DeleteMsg(int index)
{
    if (!m_pfDeleteMsg) return FALSE;
    return m_pfDeleteMsg(index);
}

int ImportShortMsgFun::ReadMsg(int index,char* PhoneID,char* SmsContent,char* Date)
{
    if (!m_pfReadMsg) return FALSE;
    return m_pfReadMsg(index, PhoneID, SmsContent, Date);
}

int ImportShortMsgFun::GetSmsc(char* smsc)
{
    if (!m_pfGetSmsc) return FALSE;
    return m_pfGetSmsc(smsc);
}

int ImportShortMsgFun::SMSInit()
{
    if (!m_pfSMSInit) return FALSE;
    return m_pfSMSInit();
}

int ImportShortMsgFun::SetSmsc(char* smsc)
{
    if (!m_pfSetSmsc) return FALSE;
    return m_pfSetSmsc(smsc);
}

int ImportShortMsgFun::ReadAllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index)
{
    if (!m_pfReadAllMsg) return FALSE;
    return m_pfReadAllMsg(type, PhoneID, SmsContent, Date, Index);
}

int ImportShortMsgFun::SetSendModle(int modle)
{
    if (!m_pfSetSendModle) return FALSE;
    return m_pfSetSendModle(modle);
}

int ImportShortMsgFun::GetSmCapacity(char* smCapacity)
{
    if (!m_pfGetSmCapacity) return FALSE;
    return m_pfGetSmCapacity(smCapacity);
}

