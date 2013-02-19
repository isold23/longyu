#include "stdafx.h"
#include "Outlined.h"
#include "VecWnd.h"






COutlined::COutlined(CVecWnd *pWnd)
	:CElem(pWnd),
	 m_clrOutline(VW_DEF_OUTLINE_COLOR),
	 m_nDashStyle(VW_DEF_DASH_STYLE),
	 m_nOutlineWidth(VW_DEF_OUTLINE_WIDHT)
{
 
}

COutlined::~COutlined(void)
{

}

void COutlined::SetOutlineColor(COLORREF clr)
{
	if (m_clrOutline != clr)
	{
		m_clrOutline = clr;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

void COutlined::SetOutlineWidth(int nWidth)
{
	if (m_nOutlineWidth != nWidth)
	{
		m_nOutlineWidth = nWidth;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

 

void COutlined::SetDasHStyle(int nDasStyle) 
{
	if (m_nDashStyle != nDasStyle)
	{
		m_nDashStyle = nDasStyle;
		if (m_pWnd != NULL)
			m_pWnd->Redraw();
	}
}

void COutlined::OnDraw(CDC *pDC,UINT nDrawFlag,CDC *pAuxDC)
{
	CPenSelector pen(pDC,m_nDashStyle,m_nOutlineWidth,m_clrOutline); 
	Draw(pDC);

#if VW_VER_CURRENT == VW_VER_CUSTOMER
	if (GetType() == Gauge)
#endif
	if (nDrawFlag & DrawSelected)
		DrawSelect(pDC);
}
