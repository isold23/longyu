#include "stdafx.h"
#include "Rectangle.h"
#include "resource.h"
#include "GraphAlgorithm.h" 
#include "VecWnd.h"


CRectangle::CRectangle(CVecWnd *pWnd)
	:CFilled(pWnd),
	 m_clrText(0)
{

}

CRectangle::~CRectangle(void)
{

}


int CRectangle::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		int nHitTest = CFilled::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;
	}

	CRectF rc(m_rc);
	rc.NormalizeRect();
	if (!rc.PtInRect(point))
		return -1;
	
	if (m_bFill)
		return Body;

	rc.DeflateRect(HITTEST_DIST,HITTEST_DIST);
	return rc.PtInRect(point) ? -1 : Body;
}

HCURSOR CRectangle::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=Body);

	return CFilled::Cursor(nHitTest);
}

void CRectangle::InitDrag(CPointF point)
{
	m_rc.left = point.x;
	m_rc.top = point.y;
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawRect(&dc,m_rc.left,m_rc.top,m_rc.left,m_rc.top);

}

void CRectangle::InitDragging(CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);
	
	DrawRect(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y);
	DrawRect(&dc,m_rc.left,m_rc.top,point.x,point.y);
}
 
void CRectangle::InitEndDrag(CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	m_rc.left += dx;
	m_rc.top += dy;
	m_rc.right = point.x + dx;
	m_rc.bottom = point.y + dy;
}

BOOL CRectangle::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = FALSE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;


	switch (nHitTest)
	{
	case TopLeft:
		DrawRect(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case Top:
		DrawRect(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case TopRight:
		DrawRect(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy);
		break; 
	case Right:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy);
		break;
	case BottomRight:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y);
		break;
	case Bottom:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case BottomLeft:
		DrawRect(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case Left:
		DrawRect(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy); 
		break;
	case Body:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy);
		bRet = TRUE;
		break;
	default:
		ASSERT(FALSE);
	}
 
	return bRet;
}

void CRectangle::OnDrag(int nHitTest,CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		DrawRect(&dc,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy);
		DrawRect(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case Top:
		DrawRect(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy);
		DrawRect(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case TopRight:
		DrawRect(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,m_rc.bottom-dy);
		DrawRect(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy);
		break; 
	case Right:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_rc.bottom-dy);
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy);
		break;
	case BottomRight:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y);
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y);
		break;
	case Bottom:
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y);
		DrawRect(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case BottomLeft:
		DrawRect(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y);
		DrawRect(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case Left:
		DrawRect(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy);
		DrawRect(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case Body: 
		{
			REAL x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x - dx;
			REAL y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y - dy;
			DrawRect(&dc,m_rc.left+x,m_rc.top+y,m_rc.right+x,m_rc.bottom+y);

			x = point.x-m_pWnd->GetMarkPos().x - dx;
			y = point.y-m_pWnd->GetMarkPos().y - dy;
			DrawRect(&dc,m_rc.left+x,m_rc.top+y,m_rc.right+x,m_rc.bottom+y);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

BOOL CRectangle::OnDragEnd(int nHitTest,CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		m_rc.left = point.x + dx;
		m_rc.top = point.y + dy;
		break;
	case Top:
		m_rc.top = point.y + dy;
		break;
	case TopRight:
		m_rc.right = point.x + dx;
		m_rc.top = point.y + dy;
		break; 
	case Right:
		m_rc.right = point.x + dx;
		break;
	case BottomRight:
		m_rc.right = point.x + dx;
		m_rc.bottom = point.y + dy;
		break;
	case Bottom:
		m_rc.bottom = point.y + dy;
		break;
	case BottomLeft:
		m_rc.left = point.x + dx;
		m_rc.bottom = point.y + dy;
		break;
	case Left:
		m_rc.left = point.x + dx;
		break;
	case Body:
		m_rc.OffsetRect(point.x-m_pWnd->GetMarkPos().x,point.y-m_pWnd->GetMarkPos().y);
		break;
	default:
		ASSERT(FALSE);
	}
	return TRUE;
}
 
void CRectangle::Draw(CDC *pDC)
{
	DrawRect(pDC,m_rc.left,m_rc.top,m_rc.right,m_rc.bottom);
	DrawText(pDC);
}

void CRectangle::DrawSelect(CDC *pDC)
{
	DrawSelectRect(pDC);
	DrawText(pDC);

}
void CRectangle::GetBoundsRect(CRectF &rect) const
{
	rect = m_rc;
}

void CRectangle::SetBoundsRect(const CRectF &rect)
{
	m_rc = rect;
}

CElem *CRectangle::Clone(void) const 
{
	CRectangle *pRect = new CRectangle(*this);
	return pRect;
}

void CRectangle::DrawText(CDC *pDC)
{
	if (!m_strText.IsEmpty()) 
	{
		CRect rect((int)m_rc.left,(int)m_rc.top,(int)m_rc.right,(int)m_rc.bottom); 
		pDC->DrawText(m_strText,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}
}
