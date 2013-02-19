#pragma once

class CGaugedWnd;
 
class CGaugeWnd : public CWnd
{
	DECLARE_MESSAGE_MAP()

	enum HtResult{Non,Left=1,Top=2,Right=4,Bottom=8,TopLeft=Top|Left,TopRight=Top|Right,
		BottomRight=Bottom|Right,BottomLeft=Bottom|Left,Body=Left|Top|Right|Bottom};

public:
	CGaugeWnd(void);
	virtual ~CGaugeWnd(void);

	BOOL Create(CWnd *pHostWnd,BOOL bTransparent,CWnd *pVisibleWnd=NULL);
	void Show(BOOL bShow=TRUE);	
	CWnd* GetHost(void) const;

	BOOL IsManualVisible(void) const;
	void ShowManual(BOOL bShow);

	void SetBorder(COLORREF clr);
 
	const CRect& GetWndRect(void) const;

	CRect& CalcViewRect(CRect &rcRefOut);

	void RecalcWindowRect(void);

	DWORD GetSampleTick(void) const;
private:
	afx_msg void OnPaint(void);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

	int HitTest(CPoint point);
	void OnDrag(CPoint point);

	void ResetWindowRect(const CRect &rc,BOOL bFromOuter=FALSE);
	void ValidateRgn(int cx,int cy);


	COLORREF m_clrBorder;
	int m_nBorderWidth;
	BOOL m_bTransparent;

	int m_nHitTest;
	CPoint m_ptCapture;

	POINTF m_ptTopLeft;
	POINTF m_ptBottomRight;
	CRect m_rcWindow;
	CWnd *m_pVisibleWnd;
	CWnd *m_pHostWnd;

	DWORD m_dwSampleTick;

	BOOL m_bShowManual;
};

inline CWnd* CGaugeWnd::GetHost(void) const {
	return m_pHostWnd;
}


inline BOOL CGaugeWnd::IsManualVisible(void) const {
	return m_bShowManual;
}

inline const CRect& CGaugeWnd::GetWndRect(void) const {
	return m_rcWindow;
}

inline CRect& CGaugeWnd::CalcViewRect(CRect &rcRefOut) {
	CSize size = rcRefOut.Size();
	rcRefOut.left = size.cx*m_ptTopLeft.x;
	rcRefOut.top = size.cy*m_ptTopLeft.y;
	rcRefOut.right = size.cx*m_ptBottomRight.x;
	rcRefOut.bottom = size.cy*m_ptBottomRight.y;
	return rcRefOut;
}


inline DWORD CGaugeWnd::GetSampleTick(void) const {
	return m_dwSampleTick;
}
