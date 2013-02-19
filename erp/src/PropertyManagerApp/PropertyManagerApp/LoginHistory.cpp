#include "StdAfx.h"
#include "LoginHistory.h"
#include "../Utils/XMLDoc.h"



CLoginHistory g_lhistory;

CLoginHistory::CLoginHistory(void)
{
}

CLoginHistory::~CLoginHistory(void)
{
}

BOOL CLoginHistory::Load(void)
{
	CString strLoginFile = AfxGetApp()->GetProfileString(USER_CFG,LOGIN_HISTORY_FILE);

	CXmlDoc doc;
	if (!doc.SetText(strLoginFile))
		return FALSE;

	Record rec;
	CXmlNode root = doc.Root;
	m_strAutoLogin = root.GetStringAttrib(_T("AutoLogin"));
 
	for (int i=0,cnt=root.GetChildCount(); i<cnt; ++i)
	{
		CXmlNode node = root.Child[i];

		rec.User = node.GetStringAttrib(_T("U"));
		rec.Pwd = node.GetStringAttrib(_T("P"));
		rec.SavePwd = node.GetBoolAttrib(_T("S"));

		m_records.Add(rec);
	}

	return TRUE;

}

BOOL CLoginHistory::Save(void)
{
	CXmlDoc doc;
	CXmlNode root = doc.CreateRoot(_T("LoginHistory"));
	root.SetAttrib(_T("AutoLogin"),m_strAutoLogin);

	for (int i=0; i<m_records.GetCount(); ++i)
	{
		Record &rec = m_records[i];
		CXmlNode node = root.AppendChild(_T("I"));
		node.SetAttrib(_T("U"),rec.User);
		node.SetAttrib(_T("P"),rec.Pwd);
		node.SetAttrib(_T("S"),rec.SavePwd);
	}

	return  AfxGetApp()->WriteProfileString(USER_CFG,LOGIN_HISTORY_FILE,doc.GetText());
}

void CLoginHistory::Clear(void)
{
	m_strAutoLogin.Empty();
	m_records.RemoveAll();

	 AfxGetApp()->WriteProfileString(USER_CFG,LOGIN_HISTORY_FILE,_T(""));
}

int CLoginHistory::GetAutoLogin(void) const 
{
	for (int i=0; i<m_records.GetCount(); ++i)
		if (m_records[i].User == m_strAutoLogin)
			return i;
	return -1;
}


void CLoginHistory::Add(const CString &strUser,const CString &strPwd,BOOL bSavePwd,BOOL bAutoLogin)
{
	int i = 0;
	int nRecCount = m_records.GetCount();
	for (; i<nRecCount; ++i)
		if (m_records[i].User == strUser)
			break;
	
	if (i != nRecCount)
		m_records.RemoveAt(i);

	Record rec = { strUser,strPwd,bSavePwd };
	m_records.InsertAt(0,rec);

	if (bAutoLogin)
		m_strAutoLogin = strUser;
}

