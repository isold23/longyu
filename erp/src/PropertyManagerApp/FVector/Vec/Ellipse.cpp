#include "stdafx.h"
#include "Ellipse.h"
#include "resource.h"
#include "GraphAlgorithm.h"
#include "VecWnd.h"


CEllipse::CEllipse(CVecWnd *pWnd)
	:CFilled(pWnd)
{

}

CEllipse::~CEllipse(void)
{

}

int CEllipse::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		int nHitTest = CFilled::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;
	}

	if (EllipseHelper::PtInEllipse(m_rc,point))
	{
		if (m_bFill)
			return Body;

		CRectF rc(m_rc);
		rc.DeflateRect(HITTEST_DIST,HITTEST_DIST);
		return EllipseHelper::PtInEllipse(rc,point) ? -1:Body;
	}

	return -1;
}

HCURSOR CEllipse::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=Body);
	return CFilled::Cursor(nHitTest);
}



void CEllipse::InitDrag(CPointF point)
{
	m_rc.left = point.x;
	m_rc.top = point.y;
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawEllipse(&dc,m_rc.left,m_rc.top,m_rc.left,m_rc.top);
}

void CEllipse::InitDragging(CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawEllipse(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y);
	DrawEllipse(&dc,m_rc.left,m_rc.top,point.x,point.y);
}

void CEllipse::InitEndDrag(CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	m_rc.left += dx;
	m_rc.top += dy;
	m_rc.right = point.x + dx;
	m_rc.bottom = point.y + dy;
}



BOOL CEllipse::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = FALSE;
	
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);


	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		DrawEllipse(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case Top:
		DrawEllipse(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case TopRight:
		DrawEllipse(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy);
		break; 
	case Right:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy);
		break;
	case BottomRight:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y);
		break;
	case Bottom:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case BottomLeft:
		DrawEllipse(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case Left:
		DrawEllipse(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy); 
		break;
	case Body:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy);
		bRet = TRUE;
		break;
	default:
		ASSERT(FALSE);
	}

	return bRet;
}

void CEllipse::OnDrag(int nHitTest,CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		DrawEllipse(&dc,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy);
		DrawEllipse(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case Top:
		DrawEllipse(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy);
		DrawEllipse(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case TopRight:
		DrawEllipse(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,m_rc.bottom-dy);
		DrawEllipse(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy);
		break; 
	case Right:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_rc.bottom-dy);
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy);
		break;
	case BottomRight:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y);
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y);
		break;
	case Bottom:
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y);
		DrawEllipse(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case BottomLeft:
		DrawEllipse(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y);
		DrawEllipse(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y);
		break;
	case Left:
		DrawEllipse(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy);
		DrawEllipse(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy);
		break;
	case Body: 
		{
			REAL x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x - dx;
			REAL y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y - dy;
			DrawEllipse(&dc,m_rc.left+x,m_rc.top+y,m_rc.right+x,m_rc.bottom+y);

			x = point.x-m_pWnd->GetMarkPos().x - dx;
			y = point.y-m_pWnd->GetMarkPos().y - dy;
			DrawEllipse(&dc,m_rc.left+x,m_rc.top+y,m_rc.right+x,m_rc.bottom+y);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

BOOL CEllipse::OnDragEnd(int nHitTest,CPointF point)
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



void CEllipse::Draw(CDC *pDC)
{ 
	DrawEllipse(pDC,m_rc.left,m_rc.top,m_rc.right,m_rc.bottom);
}

void CEllipse::DrawSelect(CDC *pDC)
{
	CFilled::DrawSelectRect(pDC);
}


void CEllipse::GetBoundsRect(CRectF &rect) const
{
	rect = m_rc;
}

void CEllipse::SetBoundsRect(const CRectF &rect)
{
	m_rc = rect;
}

CElem *CEllipse::Clone(void) const 
{
	CEllipse *pEllipse = new CEllipse(*this);
	return pEllipse;
}

void CEllipse::DrawEllipse(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom)
{
	pDC->Ellipse((int)left,(int)top,(int)right,(int)bottom);
}
