#pragma once

#include "Elem.h"

class CMulti : public CElem
{
public:
	enum HITTEST{TopLeft=1, Top, TopRight, Right, BottomRight,
		Bottom,BottomLeft,Left,Body};
public:
	CMulti(CVecWnd *pWnd = NULL);
	virtual ~CMulti(void);

	DECLARE_TYPE(Multi);

	virtual int HitTest(CPointF point,BOOL bSelect);
	virtual HCURSOR GetCursor(int nHitTest);

	virtual void InitDrag(CPointF point);
	virtual void InitDragging(CPointF point); 
	virtual void InitEndDrag(CPointF point);

	virtual BOOL OnDragStart(int nHitTest,CPointF point);
	virtual void OnDrag(int nHitTest,CPointF point);
	virtual BOOL OnDragEnd(int nHitTest,CPointF point);

	virtual void Draw(CDC *pDC,UINT nDrawFlag);
	virtual void GetBoundsRect(CRectF &rect) const;
	virtual void SetBoundsRect(const CRectF &rect);

	virtual CElem* Clone(void) const;

	const CElems& GetElems(void) const; 

	int IndexOf(CElem *pElem);
	void AddElem(CElem *pElem);
	CElem* RemoveElem(int nIndex);
	void RemoveElem(CElem *pElem);

protected:
	CElems m_elems;
};


inline const CElems& CMulti::GetElems(void) const {
	return m_elems;
}