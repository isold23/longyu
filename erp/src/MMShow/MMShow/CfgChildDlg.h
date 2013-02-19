#pragma once


class CCfgChildDlg : public CDialog
{
public:
	CCfgChildDlg(void);
	CCfgChildDlg(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	CCfgChildDlg(UINT nIDTemplate, CWnd* pParentWnd = NULL);

	virtual BOOL SaveCfg(CString &strTip);
	virtual BOOL CancelCfg(CString &strTip);

private:
	virtual void OnOK(void);
	virtual void OnCancel(void);
};


