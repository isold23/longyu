#include "StdAfx.h"
#include "Options.h"

COptions g_ops;

COptions::COptions(void)
	:m_bModified(FALSE)
{
}

COptions::~COptions(void)
{
}

BOOL COptions::Load(void)
{
	m_strDBAddr = AfxGetApp()->GetProfileString(USER_CFG,DB_ADDR_KEY,DB_ADDR_DEF);
	return TRUE;
}

BOOL COptions::Save(void)
{
	if (m_bModified)
	{
		m_bModified = FALSE;
	
		AfxGetApp()->WriteProfileString(USER_CFG,DB_ADDR_KEY,m_strDBAddr);
	}
	return TRUE;
}


CString COptions::GetDBConnString(LPCTSTR pcszDBAddr) const 
{
	CString str;
	str.Format(DB_STR_FMT,pcszDBAddr);
	return str;
}