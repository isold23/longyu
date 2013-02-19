#pragma once
#include "Filled.h"

class CRectangle : public CFilled
{
public:
	enum HITTEST{TopLeft=1, Top, TopRight, Right, BottomRight,
			Bottom,BottomLeft,Left,Body};
public:
	CRectangle(CVecWnd *pWnd = NULL);
	virtual ~CRectangle(void);
	
	DECLARE_TYPE(Rectangle);

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

	const CString& GetText(void) const;
	void SetText(const CString &strText);

	COLORREF GetTextColor(void) const;
	void SetTextColor(COLORREF clrText);

private:
	void DrawText(CDC *pDC);
	
	CRectF m_rc;

	CString m_strText;
	COLORREF m_clrText;
};

inline const CString& CRectangle::GetText(void) const {
	return m_strText;
}

inline void CRectangle::SetText(const CString &strText) {
	m_strText = strText;
}

inline COLORREF CRectangle::GetTextColor(void) const {
	return m_clrText;
}

inline void CRectangle::SetTextColor(COLORREF clrText) {
	m_clrText = clrText;
}