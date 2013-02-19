#pragma once
#include "Elem.h"




class CFilled  : public CElem
{ 

public:
	CFilled(CVecWnd *pWnd = NULL);
	virtual ~CFilled(void);

	BOOL IsOutline(void) const;
	void SetOutline(BOOL bOutline);
	
	COLORREF GetOutlineColor(void) const;
	void SetOutlineColor(COLORREF clr);

	int GetOutlineWidth(void) const;
	void SetOutlineWidth(int nWidth);
	
	int GetDashStyle(void) const;
	void SetDasHStyle(int nDasStyle);

	BOOL IsFill(void) const;
	void SetFill(BOOL bFill);
	COLORREF GetFillColor(void) const;
	void SetFillColor(COLORREF clr);

	virtual void OnDraw(CDC *pDC,UINT nDrawFlag,CDC *pAuxDC);

protected:
	virtual void Draw(CDC *pDC) = 0;
	virtual	void DrawSelect(CDC *pDC) = 0;
	
	void DrawAlpha(CDC *pDC,BYTE alpha,CDC *pAuxDC);
 
	BOOL m_bOutline;
	COLORREF m_clrOutline; 
	int m_nOutlineWidth;
	int m_nDashStyle;	 

	BOOL m_bFill;
	COLORREF m_clrFill;  
};


inline BOOL CFilled::IsOutline(void) const {
	return m_bOutline;
}

inline COLORREF CFilled::GetOutlineColor(void) const {
	return m_clrOutline;
}

inline int CFilled::GetOutlineWidth(void) const {
	return m_nOutlineWidth;
}

inline int CFilled::GetDashStyle(void) const {
	return m_nDashStyle;
}

inline BOOL CFilled::IsFill(void) const {
	return m_bFill;
}

inline COLORREF CFilled::GetFillColor(void) const {
	return m_clrFill;
}