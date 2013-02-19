#pragma once

#include <cmath>

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
	CElastic(CDC *pDC,COutlined *pElem)
		:m_modeSelector(pDC,R2_NOTXORPEN)
	{
		m_pen.Attach(pDC,pElem->GetDashStyle(),pElem->GetOutlineWidth(),pElem->GetOutlineColor());
	}
	
	CElastic(CDC *pDC,CFilled *pElem)
		:m_modeSelector(pDC,R2_NOTXORPEN)
	{
		m_pen.Attach(pDC,pElem->GetDashStyle(),pElem->GetOutlineWidth(),pElem->GetOutlineColor());
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
	CTickCounter(LPCTSTR pcszTag)
	{
		m_dwStart = ::GetTickCount();
		m_pcszTag = pcszTag;
	}
  
	~CTickCounter(void)
	{
		DWORD dwNow = ::GetTickCount();
		TRACE(_T("tag:[%s] start tick[%d]    end tick[%d]   elapsed[%d]\n"),m_pcszTag,m_dwStart,dwNow,dwNow-m_dwStart);
	}
private:
	DWORD m_dwStart;
	LPCTSTR m_pcszTag;
};


 