#pragma once
#include "ElemInc.h"
#include "GdiPlusHelper.h"
 

#define VWN_SELCHANGE 1
#define VWN_HOVERCHANGE 2

class CVecWnd : public CWnd
{
	DECLARE_MESSAGE_MAP()

public:
	static LPCTSTR VECWND_CLASSNAME;
public:
	CVecWnd(void);
	virtual ~CVecWnd(void);

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	void Redraw(void);

	const CPointF& GetCapturePos(void) const;
	const CPointF& GetMarkPos(void) const;
	const CPointF& GetStartPos(void) const;

	CElem* CloneSelectedElem(void);

	CElem* GetSelectedElem(void); 
	void SetSelectedElem(CElem *pElem);
	void EnsureVisible(CElem *pElem);
	
	CElem* GetHoverElem(void);

	UINT GetElemCount(void) const;
	CElem* GetElemByIndex(UINT nIndex);
	const CElem* GetElemByIndex(UINT nIndex) const;
	void RemoveAt(UINT nIndex);

	int GetOPType(void) const;
	void SetOPType(int nOPType);

	void RemoveSelected(void);
	void SetSelectTopmost(void);
	void SetSelectDownmost(void);

	COLORREF GetBkColor(void) const;
	void SetBkColor(COLORREF clr);

	BOOL SetBkgndImage(const CString &path);
	const CString& GetBkgndImage(void) const;

	CSizeF GetScale(void) const;
	void SetScale(CSizeF scale);

	void Zoom(REAL fXScale,REAL fYScale);
	void GetElemsBoudsRect(CRectF &rc);
	
	BOOL Load(LPCTSTR pcszFileName);
	BOOL Save(LPCTSTR pcszFileName);

	const CString& GetDesc(void) const;
	void SetDesc(const CString &strDesc);

	DWORD_PTR GetCustomData(void) const;
	void SetCustomData(DWORD_PTR dwCustomData);

	DWORD_PTR GetUserData(void) const;
	void SetUserData(DWORD_PTR dwUserData);

	BOOL PauseDraw(BOOL bPause);

#if VW_VER_CURRENT == VW_VER_CUSTOMER
	BOOL IsTicked(void) const;
	void SetTicked(BOOL bTicked);
#endif

private:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode(void);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); 
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); 
	
	BOOL ResetStartPos(CPointF ptStart);

	void ResetMemember(void);
	void OnHover(CPointF point,BOOL bRedraw);

	void RemoveAllElem(void);
	CElem* GetPrototype(int nOPType);
	CElem* HitTest(CPointF point,int &nHitTest);
	void NotifyChange(UINT uNotifyCode,void *pObject);

	void DrawBkgndImage(CDC *pDC);
	

	BOOL m_bLButtonDown;
	CPointF m_ptCapture;
	CPointF m_ptMark;
	CPointF m_ptStart;
	int m_nDragHitTest;

	int m_nOPType;
	CElem *m_pSelElem; 
	CElem *m_pHoverElem; 

	COLORREF m_clrBk;
	Gdiplus::Bitmap *m_pImgBkgnd;
	CString m_strBkgndImagePath;

	CSizeF m_scale;

	CString m_strDesc;
	DWORD_PTR m_dwCustomData;
	DWORD_PTR m_dwUserData;

	BOOL m_bDrawPaused;
	CElems m_elems; 

#if VW_VER_CURRENT == VW_VER_CUSTOMER
	BOOL m_bTicked;
#endif  
};

inline const CString& CVecWnd::GetBkgndImage(void) const {
	return m_strBkgndImagePath;
}

inline const CPointF& CVecWnd::GetCapturePos(void) const {
	return m_ptCapture;
}

inline const CPointF& CVecWnd::GetMarkPos(void) const {
	return m_ptMark;
}


inline const CPointF& CVecWnd::GetStartPos(void) const {
	return m_ptStart;
}

inline CElem* CVecWnd::GetSelectedElem(void) {
	return m_pSelElem;
}

inline CElem* CVecWnd::GetHoverElem(void) {
	return m_pHoverElem;
}

inline int CVecWnd::GetOPType(void) const {
	return m_nOPType;
}
inline COLORREF CVecWnd::GetBkColor(void) const {
	return m_clrBk;
}

inline void CVecWnd::Redraw(void) {
	if (!m_bDrawPaused && m_hWnd!=NULL)
		RedrawWindow();
}

inline CSizeF CVecWnd::GetScale(void) const {
	return m_scale;
}

inline void CVecWnd::SetScale(CSizeF scale) {
	if (m_scale != scale) {
		Zoom(scale.cx/m_scale.cx,scale.cy/m_scale.cy);
	}
}

inline const CString& CVecWnd::GetDesc(void) const {
	return m_strDesc;
}

inline void CVecWnd::SetDesc(const CString &strDesc) {
	m_strDesc = strDesc;
}
inline DWORD_PTR CVecWnd::GetCustomData(void) const {
	return m_dwCustomData;
}

inline void CVecWnd::SetCustomData(DWORD_PTR dwCustomData) {
	m_dwCustomData = dwCustomData;
}


inline DWORD_PTR CVecWnd::GetUserData(void) const {
	return m_dwUserData;
}

inline void CVecWnd::SetUserData(DWORD_PTR dwUserData) {
	m_dwUserData = dwUserData;
}

inline UINT CVecWnd::GetElemCount(void) const {
	return (UINT)m_elems.GetCount();
}

inline CElem* CVecWnd::GetElemByIndex(UINT nIndex) {
	return m_elems[nIndex];
} 

inline const CElem* CVecWnd::GetElemByIndex(UINT nIndex) const {
	return m_elems[nIndex];
}

inline BOOL CVecWnd::PauseDraw(BOOL bPause) {
	BOOL bOrg = m_bDrawPaused;
	m_bDrawPaused = bPause;
	return bOrg;
}
 
#if VW_VER_CURRENT == VW_VER_CUSTOMER
inline BOOL CVecWnd::IsTicked(void) const {
	return m_bTicked;
}

inline void CVecWnd::SetTicked(BOOL bTicked) {
	//if (m_bTicked != bTicked) {
		m_bTicked = bTicked;
		Redraw();
	//}
}
#endif