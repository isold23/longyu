#pragma once

class CSimpleToolTip : public CWnd
{
	DECLARE_MESSAGE_MAP()
public:
	CSimpleToolTip(void);
	~CSimpleToolTip(void);

	BOOL Create(void);
	void ShowTip(CWnd *pRefWnd,const CString &strTip);
	void UpdateTip(CWnd *pRefWnd,const CString &strTip);
	void CancelTip(CWnd *pRefWnd);

private:
	afx_msg void OnPaint(void);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message);
	
	void Show(BOOL bShow);

	
	CWnd *m_pRefWnd;
	CString m_strTip;

	int m_status;
};
 