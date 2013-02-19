#pragma once

#include "Filled.h"

class CRoundRect : public CFilled
{
public:
	enum HITTEST{Ellipse=HitMax};
public:
	CRoundRect(CVecWnd *pWnd = NULL);
	virtual ~CRoundRect(void);

	DECLARE_TYPE(RoundRect);

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

	REAL GetXEllipse(void) const;
	void SetXEllipse(REAL fXEllipse);

	REAL GetYEllipse(void) const;
	void SetYEllipse(REAL fYEllipse);
private:
	void DrawRoundRectXY(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fXEllipse,REAL fYEllipse);
	void DrawRoundRect(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL nWidth,REAL nHeight);

	CPointF GetEllipseMarkPos(void) const;
	
	REAL m_fXEllipse;
	REAL m_fYEllipse;
	CRectF m_rc;
};

inline REAL CRoundRect::GetXEllipse(void) const {
	return m_fXEllipse;
}

inline REAL CRoundRect::GetYEllipse(void) const {
	return m_fYEllipse;
}