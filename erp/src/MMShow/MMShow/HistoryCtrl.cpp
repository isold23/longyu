#include "stdafx.h"
#include "HistoryCtrl.h"
#include "XMLDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CHistoryCtrl::CHistoryCtrl(LPCTSTR pcszTagName)
	:m_pcszTagName(pcszTagName)
{
}

CHistoryCtrl::~CHistoryCtrl(void)
{
}


BEGIN_MESSAGE_MAP(CHistoryCtrl,CComboBox)
	ON_CONTROL_REFLECT(CBN_SELENDOK,&CHistoryCtrl::OnSelChange)
END_MESSAGE_MAP()


 
BOOL CHistoryCtrl::Load(CXmlNode &node)
{
	CXmlNode n = node.GetFirstChild(m_pcszTagName);
	if (n.IsNull())
		return FALSE;

	CString strText;
	for (int i=0,cnt=n.ChildCount; i<cnt; ++i)
	{
		CXmlNode nc = n.Child[i];
		if (!n.IsNull())
		{
			strText = n.Value;
			if (!strText.IsEmpty())
				AddString(strText);
		}
	}
	AddString(_T("清空历史记录..."));
	return TRUE;
}

BOOL CHistoryCtrl::Save(CXmlNode &node)
{
	CString strText;
	for (int i=0,cnt=GetCount()-1; i<cnt; ++i)
	{
		GetLBText(i,strText);
		CXmlNode n = node.AppendChild(_T("Elem"));
		n.Value = strText;
	}
	return TRUE;
}

void CHistoryCtrl::OnSelChange(void)
{
	CString str;
	int nIndex = GetCurSel();
	if (nIndex == GetCount()-1)
		ResetContent();
	else if (nIndex >= 0)
		GetParent()->SendMessage(WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),CN_COMMAND),(LPARAM)GetSafeHwnd());
}

void CHistoryCtrl::Add(const CString &strText)
{
	SetWindowText(strText);

	int nIndex = FindString(-1,strText);
	if (nIndex > 0)
		DeleteString(nIndex);
	if (nIndex != 0)
		InsertString(0,strText);
	if (GetCount() == 1)
		AddString(_T("清空历史记录..."));
}

