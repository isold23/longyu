#include "StdAfx.h"
#include "____sql_sp_call_impl.h"

#define TRACE_COM_ERROR(ex) TRACE(_T("Sp::Open exception Error:[0x%X] Description:[%s] ErrorMessage:[%s]\n"),ex.Error(),ex.Description().GetBSTR(),ex.ErrorMessage());

_com_error ____sql_sp_call_error(0);

void ____sql_sp_call_clear_err(void)
{
	____sql_sp_call_error = _com_error(0);
}

void ____sql_sp_call_set_err(_com_error &e)
{
	____sql_sp_call_error = e;
}

const _com_error& sperr(void)
{
	return ____sql_sp_call_error;
}


Sp g_sp;

Sp::Sp(void)
{
}

Sp::~Sp(void)
{
	Close(FALSE);
}

BOOL Sp::Open(LPCTSTR lpcszConn,int nTimeout,BOOL bAsync)
{
	try
	{
		m_conn.CreateInstance("ADODB.Connection");
		if (nTimeout > 0)
			m_conn->ConnectionTimeout = nTimeout;
		HRESULT hr = m_conn->Open(lpcszConn,L"",L"",bAsync ? adAsyncConnect : adConnectUnspecified);
		if  (SUCCEEDED(hr))
		{
			return TRUE;
		}
		else
		{
			TRACE(_T("Sp::Open exception Hr:0x%X\n"),hr);
			m_conn = NULL;
			return FALSE;
		}
	}
	catch (_com_error &ex)
	{
		m_conn = NULL;
		TRACE_COM_ERROR(ex);

		return FALSE;
	}
}
 


void Sp::Close(BOOL bCancel)
{
	try 
	{ 
		if (bCancel)
			m_conn->Cancel();
	 
		m_conn = NULL; 
	}
	catch (_com_error &ex)
	{
		TRACE_COM_ERROR(ex);
	}
}

BOOL Sp::IsConnected(void)
{
	try 
	{ 
		return (m_conn->State == adStateOpen);
	}
	catch (_com_error &ex)
	{
		TRACE_COM_ERROR(ex);
		return FALSE;
	}
	
}