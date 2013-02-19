#pragma once

#include "Elem.h"

class COutlined : public CElem
{ 
public: 
	COutlined(CVecWnd *pWnd = NULL);
	virtual ~COutlined(void);
 
	COLORREF GetOutlineColor(void) const;
	void SetOutlineColor(COLORREF clr);

	int GetOutlineWidth(void) const;
	void SetOutlineWidth(int nWidth);

	int GetDashStyle(void) const;
	void SetDasHStyle(int nDasStyle);

	virtual void OnDraw(CDC *pDC,UINT nDrawFlag,CDC *pAuxDC);

protected:
	virtual void Draw(CDC *pDC) = 0;
	virtual	void DrawSelect(CDC *pDC) = 0;

	COLORREF m_clrOutline; 
	int m_nOutlineWidth;
	int m_nDashStyle;	 
};


inline COLORREF COutlined::GetOutlineColor(void) const {
	return m_clrOutline;
}
 

inline int COutlined::GetOutlineWidth(void) const {
	return m_nOutlineWidth;
}

inline int COutlined::GetDashStyle(void) const {
	return m_nDashStyle;
}

