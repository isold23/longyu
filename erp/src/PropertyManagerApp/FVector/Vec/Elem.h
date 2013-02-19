#pragma once
#include "vectypes.h"
#include "DrawHelper.h" 
#include "../Utils/ArrayAdaptor.h"

#define VW_VER_DESIGNER 1
#define VW_VER_CUSTOMER 2

#if VW_VER_CURRENT == VW_VER_DESIGNER
#define VW_DEF_ALPHA_NORMAL 100
#define VW_DEF_ALPHA_SELECTED 50
#else
#define VW_DEF_ALPHA_SELECTED 40
#define VW_DEF_ALPHA_TICKED 50
#define VW_DEF_ALPHA_HOVER 20
#endif
 

#define VW_DEF_OUTLINE_COLOR RGB(255,0,0)
#define VW_DEF_OUTLINE_WIDHT 1
#define VW_DEF_DASH_STYLE   PS_SOLID 
#define VW_DEF_FILL_COLOR RGB(150,150,255)
#define VM_DEF_POLY_FILLMODE WINDING
 
class CVecWnd;

class CElem
{ 
public:
	enum DrawFlagEnum 
	{
		DrawNormal = 0x01,
		DrawSelected = 0x02,
#if VW_VER_CURRENT == VW_VER_DESIGNER	
#else
		DrawHover = 0x04,
		DrawTick = 0x08,
		DrawHide = 0x10
#endif
	};
	enum HitTestEnum { TopLeft=1, Top, TopRight, Right, BottomRight,Bottom,BottomLeft,Left,Body,HitMax };
	enum ElemTypeEnum{ UnknownElem,Line,FreeLine,Bezier,Region,Arc,Poly,Rectangle,RoundRect,Ellipse,Chord,Pie,Gauge,Multi,Composite };
protected:
	static const REAL HITTEST_DIST;
	static const REAL CIRCLEMARK_RADIUS;
	static const REAL DIAMONDMARK_RADIUS;

protected:
	CElem(CVecWnd *pWnd = NULL);

public:
	virtual ~CElem(void);

	virtual int GetType(void) const = 0;

	virtual int HitTest(CPointF point,BOOL bSelect) = 0;
	virtual HCURSOR GetCursor(int nHitTest) = 0;

	virtual void InitDrag(CPointF point) = 0;
	virtual void InitReDrag(CPointF point);
	virtual void InitDragging(CPointF point) = 0;
	virtual BOOL InitPauseDrag(CPointF point);	// Return TRUE if dragging should be ended
	virtual void InitEndDrag(CPointF point) = 0;

	virtual BOOL OnDragStart(int nHitTest,CPointF point) = 0;	// Return TRUE if this point should be saved as m_ptMarkPos of CVecWnd
	virtual void OnDrag(int nHitTest,CPointF point) = 0;
	virtual BOOL OnDragEnd(int nHitTest,CPointF point) = 0;	// Return TRUE if CVecWnd need to be refreshed

	virtual void OnOption(int nHitTest,CPointF point) {};

	virtual void OnDraw(CDC *pDC,UINT nDrawFlag,CDC *pAuxDC) = 0;
	virtual void GetBoundsRect(CRectF &rect) const = 0;
	virtual void SetBoundsRect(const CRectF &rect) = 0;

 
	virtual CElem* Clone(void) const = 0;

	CVecWnd* GetWnd(void);
	void SetWnd(CVecWnd *pWnd); 
		 
	const CString& GetDesc(void) const;
	void SetDesc(const CString &strDesc);

	DWORD_PTR GetCustomData(void) const;
	void SetCustomData(DWORD_PTR dwCustomData);

 
#if VW_VER_CURRENT == VW_VER_CUSTOMER
	DWORD_PTR GetUserData(void) const;
	void SetUserData(DWORD_PTR dwUserData);

	BOOL IsHidden(void) const;
	void SetHidden(BOOL bHidden);

	BOOL IsTicked(void) const;
	void SetTicked(BOOL bTicked);
#endif

protected:  
	BOOL PtInCircleMark(CPointF ptMark,CPointF ptTest);
	BOOL PtInDiamondMark(CPointF ptMark,CPointF ptTest);

	void DrawDiamondMark(CDC *pDC,CPointF point);
	void DrawCircleMark(CDC *pDC,CPointF point);

	void DrawRect(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom);

	HCURSOR Cursor(int nHitTest);
	void DrawSelectRect(CDC *pDC); 

	int HitTestSelectRect(CPointF point);

	CVecWnd *m_pWnd;
	CString m_strDesc; 
	DWORD_PTR m_dwCustomData;

#if VW_VER_CURRENT == VW_VER_CUSTOMER
	DWORD_PTR m_dwUserData; 
	BYTE m_cDrawFlag;
#endif
};

inline CVecWnd* CElem::GetWnd(void) {
	return m_pWnd;
} 

inline void CElem::SetWnd(CVecWnd *pWnd) {
	m_pWnd = pWnd;
}
 
inline const CString& CElem::GetDesc(void) const {
	return m_strDesc;
}

inline void CElem::SetDesc(const CString &strDesc) {
	m_strDesc = strDesc;
}

inline DWORD_PTR CElem::GetCustomData(void) const {
	return m_dwCustomData;
}

inline void CElem::SetCustomData(DWORD_PTR dwCustomData) {
	m_dwCustomData = dwCustomData;
}




#if VW_VER_CURRENT == VW_VER_CUSTOMER
inline DWORD_PTR CElem::GetUserData(void) const {
	return m_dwUserData;
}

inline void CElem::SetUserData(DWORD_PTR dwUserData) {
	m_dwUserData = dwUserData;
}

inline BOOL CElem::IsTicked(void) const {
	return m_cDrawFlag & DrawTick;
}

inline void CElem::SetTicked(BOOL bTicked) {
	if (bTicked)
		m_cDrawFlag |= DrawTick;
	else
		m_cDrawFlag &= ~DrawTick;
}

inline BOOL CElem::IsHidden(void) const {
	return m_cDrawFlag & DrawHide;
}

inline void CElem::SetHidden(BOOL bHidden) {
	if (bHidden)
		m_cDrawFlag |= DrawHide;
	else
		m_cDrawFlag &= ~DrawHide;	
}
#endif

#define DECLARE_TYPE(x) virtual int GetType(void) const {return x;}

 