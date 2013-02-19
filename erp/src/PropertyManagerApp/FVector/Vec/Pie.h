#pragma once

#include "Filled.h" 

class CPie : public CFilled
{
public:
	enum HITTEST{TopLeft=1, Top, TopRight, Right, BottomRight,
		Bottom,BottomLeft,Left,Body,Start,End};
public:
	CPie(CVecWnd *pWnd = NULL);
	virtual ~CPie(void);

	DECLARE_TYPE(Pie);

	virtual int HitTest(CPointF point,BOOL bSelect);
	virtual HCURSOR GetCursor(int nHitTest);

	virtual void InitDrag(CPointF point);
	virtual void InitDragging(CPointF point); 
	virtual void InitEndDrag(CPointF point);

	virtual BOOL OnDragStart(int nHitTest,CPointF point);
	virtual void OnDrag(int nHitTest,CPointF point);
	virtual BOOL OnDragEnd(int nHitTest,CPointF point);
	
	virtual void Draw(CDC *pDC);
	virtual void DrawSelect(CDC *pDC);

	virtual void GetBoundsRect(CRectF &rect) const;
	virtual void SetBoundsRect(const CRectF &rect);

	virtual CElem* Clone(void) const;


	REAL GetStartAngel(void) const;
	void SetStartAngel(REAL fAngel);

	REAL GetEndAngel(void) const;
	void SetEndAngel(REAL fAngel);

	CPointF GetStartPoint(void) const;
	CPointF GetEndPoint(void) const;
private: 
	void DrawPieSEA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fStartAngel,REAL fEndAngel);
	void DrawPieEA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL xStart,REAL yStart,REAL fEndAngel);
	void DrawPieSA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fStartAngel,REAL xEnd,REAL yEnd);

	CRectF m_rc;
	REAL m_fStartAngel; 
	REAL m_fEndAngel;
};


inline REAL CPie::GetStartAngel(void) const {
	return m_fStartAngel;
}

inline REAL CPie::GetEndAngel(void) const {
	return m_fEndAngel;
}

