
#include "stdafx.h" 
#include "CfgChildDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



 
CCfgChildDlg::CCfgChildDlg(void)
{
}

CCfgChildDlg::CCfgChildDlg(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	:CDialog(lpszTemplateName,pParentWnd)
{
}

CCfgChildDlg::CCfgChildDlg(UINT nIDTemplate, CWnd* pParentWnd)
	:CDialog(nIDTemplate,pParentWnd)
{
}


void CCfgChildDlg::OnOK(void)
{
	((CCfgChildDlg*)GetParent())->OnOK();
}

void CCfgChildDlg::OnCancel(void)
{
	((CCfgChildDlg*)GetParent())->OnCancel();
}

BOOL CCfgChildDlg::SaveCfg(CString &strTip)
{
	return TRUE;
}

BOOL CCfgChildDlg::CancelCfg(CString &strTip)
{
	return TRUE;
}




