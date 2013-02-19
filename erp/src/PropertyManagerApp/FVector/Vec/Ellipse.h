#pragma once
#include "Filled.h"

class CEllipse : public CFilled
{
public:	
	enum HITTEST{};

public:
	CEllipse(CVecWnd *pWnd = NULL);
	virtual ~CEllipse(void);

	DECLARE_TYPE(Ellipse);

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
private:
	void DrawEllipse(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom);

	CRectF m_rc;
};
