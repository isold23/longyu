#pragma once

#include <cmath>
 
class CTextColorSelector
{
public:
	CTextColorSelector(CDC *pDC,COLORREF clr) {
		m_pDC = pDC;
		m_clrOld = pDC->SetTextColor(clr);
	}

	~CTextColorSelector(void) {
		m_pDC->SetTextColor(m_clrOld);
	}

private:
	CDC *m_pDC;
	COLORREF m_clrOld;
};

class CPenSelector
{
public:
	CPenSelector(void)
		: m_pDC(NULL)
	{
	}

	CPenSelector(CDC *pDC)	
	{
		Attach(pDC);
	}

	CPenSelector(CDC *pDC,int nPenStyle, int nWidth, COLORREF clr)
	{
		Attach(pDC,nPenStyle,nWidth,clr);
	}	

	CDC* GetDC(void)
	{
		return m_pDC;
	}

	void Attach(CDC *pDC)
	{
		m_pDC = pDC; 
		m_pOldPen = (CPen*)pDC->SelectStockObject(NULL_PEN);
		m_pen.Detach();
	}

	void Attach(CDC *pDC,int nPenStyle, int nWidth, COLORREF clr)
	{
		m_pDC = pDC;
		m_pen.CreatePen(nPenStyle,nWidth,clr);
		m_pOldPen = pDC->SelectObject(&m_pen); 
	}	

	
	~CPenSelector(void)
	{ 
		if (m_pDC != NULL)
			m_pDC->SelectObject(m_pOldPen);
	}

private:
	CDC *m_pDC;
	CPen m_pen;
	CPen *m_pOldPen;
};

class CBrushSelector
{
public:
	CBrushSelector(void)		
		: m_pDC(NULL)
	{
	}

	CBrushSelector(CDC *pDC)
	{
		Attach(pDC);
	}

	CBrushSelector(CDC *pDC,COLORREF clr)
	{
		Attach(pDC,clr);
	}

	CBrushSelector(CDC *pDC,int nIndex,COLORREF clr)	
	{
		Attach(pDC,nIndex,clr);
	}


	CDC* GetDC(void)
	{
		return m_pDC;
	}

	void Attach(CDC *pDC)
	{
		m_pDC = pDC;
		m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		m_brush.Detach();
	}

	void Attach(CDC *pDC,COLORREF clr)	
	{
		m_pDC = pDC;
		m_brush.CreateSolidBrush(clr);
		m_pOldBrush = pDC->SelectObject(&m_brush); 
	}

	void Attach(CDC *pDC,int nIndex,COLORREF clr)	
	{
		m_pDC = pDC;
		m_brush.CreateHatchBrush(nIndex,clr);
		m_pOldBrush = pDC->SelectObject(&m_brush); 
	}

	~CBrushSelector(void)
	{ 
		if (m_pDC != NULL)
			m_pDC->SelectObject(m_pOldBrush);
	}

private:
	CDC *m_pDC;
	CBrush m_brush;
	CBrush *m_pOldBrush;
};
 
#if 0
class CXFormSelector
{
public:
	CXFormSelector(CDC *pDC,REAL fAngle,const CRectF &rc)
		:m_pDC(pDC)
	{
		if (pDC->GetGraphicsMode() != GM_ADVANCED)
			pDC->SetGraphicsMode(GM_ADVANCED);

		m_ptCenter = rc.CenterPoint();

		XFORM xForm;
		xForm.eM11 = cosf(fAngle); 
		xForm.eM12 = sinf(fAngle); 
		xForm.eM21 = -xForm.eM12; 
		xForm.eM22 = xForm.eM11; 
		xForm.eDx  =  m_ptCenter.x; 
		xForm.eDy  =  m_ptCenter.y; 

		m_pDC->GetWorldTransform(&m_oldXForm);
		m_pDC->SetWorldTransform(&xForm);
	}

	~CXFormSelector(void)
	{
		if (m_pDC != NULL)
			m_pDC->SetWorldTransform(&m_oldXForm);
	}

	CPointF Offset(void) const
	{
		return m_ptCenter;
	}

private:
	CDC *m_pDC;
	XFORM m_oldXForm;
	CPointF m_ptCenter;
};
#endif

class CDrawModeSelector
{
public:
	CDrawModeSelector(void)
		:m_pDC(NULL)
	{
	}

	CDrawModeSelector(CDC *pDC,int nDrawMode)
	{
		Attach(pDC,nDrawMode);
	}

	void Attach(CDC *pDC,int nDrawMode)
	{
		m_pDC = pDC;
		m_nOldDrawMode = pDC->SetROP2(nDrawMode);
	}

	~CDrawModeSelector(void)
	{	
		if (m_pDC != NULL)
			m_pDC->SetROP2(m_nOldDrawMode);
	}

private:
	CDC *m_pDC;
	int m_nOldDrawMode;
};

class CElastic
{
public:
	template<typename ElemType>
	CElastic(CDC *pDC,ElemType *pElem)
		:m_modeSelector(pDC,R2_NOTXORPEN)
	{
		m_pen.Attach(pDC,PS_SOLID,pElem->GetOutlineWidth(),RGB(0,0,0));
	}

private:
	CPenSelector m_pen;
	CDrawModeSelector m_modeSelector;
};

class CNonBrushPenSelector
{
public:
	CNonBrushPenSelector(CDC *pDC,int nPenStyle, int nWidth, COLORREF clr)
		:m_pen(pDC,nPenStyle,nWidth,clr)
	{
		m_brush.Attach(pDC);
	}

private:
	CPenSelector m_pen;
	CBrushSelector m_brush;
};


class CNonPenBrushSelector
{
public:
	CNonPenBrushSelector(CDC *pDC,COLORREF clr)
		:m_brush(pDC,clr)
	{
		m_pen.Attach(pDC);
	}

private:
	CPenSelector m_pen;
	CBrushSelector m_brush;
};

class CDiamondSelector
{
public:
	CDiamondSelector(CDC *pDC)
		:m_brush(pDC,RGB(255,255,0)),
		 m_pen(pDC,PS_SOLID,1,RGB(0,0,0))
	{
	}

private:
	CPenSelector m_pen;
	CBrushSelector m_brush;
};
 
class CCircleSelector
{
public:
	CCircleSelector(CDC *pDC)
		:m_brush(pDC,RGB(0,255,0)),
		 m_pen(pDC,PS_SOLID,1,RGB(0,0,0))
	{
	}

private:
	CPenSelector m_pen;
	CBrushSelector m_brush;
};
 

class CTickCounter
{
public:
	CTickCounter(const CString &strTag)
	{
		m_dwStart = ::GetTickCount();
		m_strTag = strTag;
	}

	CTickCounter(LPCTSTR pcszFileName,int nLine)
	{
		m_dwStart = ::GetTickCount(); 
		m_strTag.Format(_T("File:[%s] Line:[%d]"),pcszFileName,nLine);
	}
	
	CTickCounter(int nTag,LPCTSTR pcszFileName,int nLine)
	{
		m_dwStart = ::GetTickCount(); 
		m_strTag.Format(_T("%d : File:[%s] Line:[%d]"),nTag,pcszFileName,nLine);
	}

	~CTickCounter(void)
	{
		DWORD dwNow = ::GetTickCount();
		TRACE(_T("tag:[%s] start tick[%d]    end tick[%d]   elapsed[%d]\n"),m_strTag,m_dwStart,dwNow,dwNow-m_dwStart);
	}

private:
	DWORD m_dwStart;
	CString m_strTag;
};

class CClientRect : public CRect
{
public:
	CClientRect(CWnd *pWnd)
	{
		pWnd->GetClientRect(this);
	}
	CClientRect(CWnd &wnd)
	{
		wnd.GetClientRect(this);
	}
	CClientRect(HWND hWnd)
	{
		::GetClientRect(hWnd,this);
	}

};

class CWindowRect : public CRect
{
public:
	CWindowRect(CWnd *pWnd)
	{
		pWnd->GetWindowRect(this);
	}
	CWindowRect(CWnd &wnd)
	{
		wnd.GetWindowRect(this);
	}
	CWindowRect(HWND hWnd)
	{
		::GetWindowRect(hWnd,this);
	}


};

class CCurorPos : public CPoint
{
public:
	CCurorPos(void)
	{
		GetCursorPos(this);
	}
	CCurorPos(CWnd *pWnd)
	{
		GetCursorPos(this);
		pWnd->ScreenToClient(this);
	}
};
 
class CxMemDC : public CDC
{
public:
	CxMemDC(CDC &dc,CWnd *pWnd,BOOL bCopyIt)
		:m_dc(dc)
	{
		pWnd->GetClientRect(m_rc);
		Init(bCopyIt);
	}

	CxMemDC(CDC &dc,const CRect &rc,BOOL bCopyIt)
		:m_dc(dc), m_rc(rc) 
	{
		Init(bCopyIt);
	}

	~CxMemDC(void)
	{
		if (m_bCopyIt)
			m_dc.BitBlt(0,0,m_rc.right,m_rc.bottom,this,0,0,SRCCOPY);
	}

	void Fill(COLORREF clr)
	{
		FillSolidRect(m_rc,clr);
	}

	const CRect& Rect(void) const 
	{
		return m_rc;
	}
private:
	void Init(BOOL bCopyIt)
	{
		m_bCopyIt = bCopyIt;
		CreateCompatibleDC(&m_dc);
		m_dcBmp.CreateCompatibleBitmap(&m_dc,m_rc.right,m_rc.bottom);
		SelectObject(&m_dcBmp);
		SelectObject(m_dc.GetCurrentFont());  
		SetBkMode(m_dc.GetBkColor()); 
		SetTextColor(m_dc.GetTextColor());
		SetPolyFillMode(m_dc.GetPolyFillMode());
		if (bCopyIt)
			FillSolidRect(m_rc,m_dc.GetBkColor());
	}

	CRect m_rc;
	CBitmap m_dcBmp;
	CDC &m_dc;
	BOOL m_bCopyIt;
};

class CTinyString : public CString
{
public:
	CTinyString(UINT nResId) {
		LoadString(nResId);
	}

	CTinyString(LPCTSTR pcszFmt,...) {
		va_list argList;
		va_start( argList, pcszFmt );
		FormatV( pcszFmt, argList );
		va_end( argList );
	} 
};

class CNumericString : public CTinyString
{
public:
	CNumericString(char val) : CTinyString(_T("%d"),val) {}
	CNumericString(BYTE val) : CTinyString(_T("%u"),val) {}
	CNumericString(short val) : CTinyString(_T("%d"),val) {}
	CNumericString(USHORT val) : CTinyString(_T("%u"),val) {}
	CNumericString(int val) : CTinyString(_T("%d"),val) {}
	CNumericString(UINT val) : CTinyString(_T("%u"),val) {}
	CNumericString(LONGLONG val) : CTinyString(_T("%lld"),val) {}
	CNumericString(ULONGLONG val) : CTinyString(_T("%llu"),val) {}
	CNumericString(float val) : CTinyString(_T("%f"),(double)val) {}
	CNumericString(double val) : CTinyString(_T("%f"),val) {} 
};

inline BOOL RealEqual(float l,float r)
{
	const float MIN_INC = 0.001f;
	return fabs(l-r) <=0.001f;
}


#define FUNC2(x,y) x##y
#define FUNC1(x,y) FUNC2(x,y)
#define FUNC(x) FUNC1(x,__COUNTER__)
#define X_DECLARE(type,var) type FUNC(xxx)(var)

#ifdef _DEBUG
#define TcIt(x) CTickCounter x(_T(#x)) 
#define TcCode() CTickCounter FUNC(Tc_xx)(_T(__FILE__),__LINE__)
#else
#define TcIt(x)
#define TcCode()
#endif
 
