#pragma once

class CReportPageDlg : public CXTPResizeDialog
{
	DECLARE_MESSAGE_MAP()

public:
	CReportPageDlg(void);
	CReportPageDlg(const UINT nID, CWnd* pParent = 0, const UINT nFlags = 0); 
	CReportPageDlg(LPCTSTR lpszTemplateName, CWnd* pParent = 0, const UINT nFlags = 0);
	~CReportPageDlg(void);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

};
