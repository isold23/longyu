#include "stdafx.h"
#include "Elem.h"
#include "VecWnd.h"







CFilled::CFilled(CVecWnd *pWnd)
   :CElem(pWnd),
	m_bOutline(TRUE),
	m_clrOutline(VW_DEF_OUTLINE_COLOR),
	m_nDashStyle(VW_DEF_DASH_STYLE),
	m_nOutlineWidth(VW_DEF_OUTLINE_WIDHT),
	m_bFill(TRUE),
	m_clrFill(VW_DEF_FILL_COLOR)
{
}

CFilled::~CFilled(void)
{
}

void CFilled::SetOutline(BOOL bOutline)
{
	if (m_bOutline != bOutline)
	{
		m_bOutline = bOutline;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

void CFilled::SetOutlineColor(COLORREF clr)
{
	if (m_clrOutline != clr) 
	{
		m_clrOutline = clr;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}


void CFilled::SetOutlineWidth(int nWidth)
{
	if (m_nOutlineWidth != nWidth)
	{
		m_nOutlineWidth = nWidth;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

void CFilled::SetDasHStyle(int nDasStyle) 
{
	if (m_nDashStyle != nDasStyle)
	{
		m_nDashStyle = nDasStyle;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

void CFilled::SetFill(BOOL bFill)
{
	if (m_bFill != bFill)
	{
		m_bFill = bFill;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}
void CFilled::SetFillColor(COLORREF clr)
{
	if (m_clrFill != clr)
	{
		m_clrFill = clr;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

void CFilled::DrawAlpha(CDC *pDC,BYTE alpha,CDC *pAuxDC)
{
	CRectF rc;
	GetBoundsRect(rc);
	int left = (int)rc.left;
	int top = (int)rc.top;
	int width = (int)rc.Width();
	int height = (int)rc.Height();

	pAuxDC->FillSolidRect(0,0,width,height,RGB(0,0,0));
	pAuxDC->SetWindowOrg(left,top);
	Draw(pAuxDC); 
	pAuxDC->SetWindowOrg(0,0);

	BLENDFUNCTION  bf = {0,AC_SRC_OVER,alpha,AC_SRC_ALPHA};
	pDC->AlphaBlend(left,top,width,height,pAuxDC,0,0,width,height,bf);
}

void CFilled::OnDraw(CDC *pDC,UINT nDrawFlag,CDC *pAuxDC)
{ 
	CPenSelector pen;
	CBrushSelector brush;

	if (m_bFill && m_bOutline)
	{
		pen.Attach(pAuxDC,m_nDashStyle,m_nOutlineWidth,m_clrOutline);
		brush.Attach(pAuxDC,m_clrFill);
	}
	else if (m_bFill)
	{
		pen.Attach(pAuxDC);
		brush.Attach(pAuxDC,m_clrFill); 
	}
	else if (m_bOutline)
	{	
		pen.Attach(pAuxDC,m_nDashStyle,m_nOutlineWidth,m_clrOutline);
		brush.Attach(pAuxDC);
	}
 
#if VW_VER_CURRENT == VW_VER_DESIGNER
	if (nDrawFlag & DrawSelected)
	{
		DrawSelect(pDC);
		DrawAlpha(pDC,VW_DEF_ALPHA_SELECTED,pAuxDC);
	}
	else
	{ 
		DrawAlpha(pDC,VW_DEF_ALPHA_NORMAL,pAuxDC);	
	}
#else
	BYTE alpha = 0;
	if (nDrawFlag & DrawSelected)
		alpha = VW_DEF_ALPHA_SELECTED;
	else if (nDrawFlag & DrawHover)
		alpha = VW_DEF_ALPHA_HOVER;
	else if (nDrawFlag & DrawTick)
		alpha = VW_DEF_ALPHA_TICKED;
	if (alpha != 0)
		DrawAlpha(pDC,alpha,pAuxDC);
#endif

 
	 
}
