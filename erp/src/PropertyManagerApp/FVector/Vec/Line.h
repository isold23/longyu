#pragma once
#include "Outlined.h"

class CLine : public COutlined
{
public:
	enum HITTEST{Start=HitMax,End,Body};

public:
	CLine(CVecWnd *pWnd = NULL);
	virtual ~CLine(void);

	DECLARE_TYPE(Line);

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

	CPointF GetStartPoint(void) const;
	void SetStartPoint(CPointF point);

	CPointF GetEndPoint(void) const;
	void SetEndPoint(CPointF point);

private:
	CPointF m_ptStart;
	CPointF m_ptEnd;
};



inline CPointF CLine::GetStartPoint(void) const {
	return m_ptStart;
}

inline CPointF CLine::GetEndPoint(void) const {
	return m_ptEnd;
}
