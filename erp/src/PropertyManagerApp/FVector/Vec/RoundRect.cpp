#include "stdafx.h"
#include "RoundRect.h"
#include "resource.h"
#include "VecWnd.h"
#include "GraphAlgorithm.h"

CRoundRect::CRoundRect(CVecWnd *pWnd)
	: CFilled(pWnd)
{ 
}

CRoundRect::~CRoundRect(void)
{

}


int CRoundRect::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		if (PtInDiamondMark(GetEllipseMarkPos(),point))
			return Ellipse;

		int nHitTest = CFilled::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;
	}

	if (!EllipseHelper::PtInRoundRect(m_rc,m_fXEllipse,m_fYEllipse,point))
		return -1;

	if (m_bFill)
		return Body;

	CRectF rc(m_rc);
	rc.DeflateRect(HITTEST_DIST,HITTEST_DIST);
	return EllipseHelper::PtInRoundRect(rc,m_fXEllipse,m_fYEllipse,point) ? -1 : Body;
}

HCURSOR CRoundRect::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=Ellipse);
	
	HCURSOR cur = CFilled::Cursor(nHitTest);
	if (cur != NULL)
		return cur;

	static HCURSOR curs[] = {
		AfxGetApp()->LoadStandardCursor(IDC_CROSS)
	};
	return curs[nHitTest-HitMax];
}

void CRoundRect::InitDrag(CPointF point)
{
	m_rc.left = point.x;
	m_rc.top = point.y;
	m_fXEllipse = m_fYEllipse = 0.5;

	CClientDC dc(m_pWnd);

	CPen pen(PS_DOT,1,RGB(0,0,0));
	CElastic elastic(&dc,this);

	DrawRoundRectXY(&dc,m_rc.left,m_rc.top,m_rc.left,m_rc.top,m_fXEllipse,m_fYEllipse);
}

void CRoundRect::InitDragging(CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawRoundRectXY(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_fXEllipse,m_fYEllipse);
	DrawRoundRectXY(&dc,m_rc.left,m_rc.top,point.x,point.y,m_fXEllipse,m_fYEllipse);
}

void CRoundRect::InitEndDrag(CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	m_rc.left += dx;
	m_rc.top += dy;
	m_rc.right = point.x+dx;
	m_rc.bottom = point.y+dy;
}


BOOL CRoundRect::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = FALSE;

	CClientDC dc(m_pWnd);	
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		DrawRoundRectXY(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case Top:
		DrawRoundRectXY(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case TopRight:
		DrawRoundRectXY(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break; 
	case Right:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case BottomRight:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y,m_fXEllipse,m_fYEllipse);
		break;
	case Bottom:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y,m_fXEllipse,m_fYEllipse);
		break;
	case BottomLeft:
		DrawRoundRectXY(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y,m_fXEllipse,m_fYEllipse);
		break;
	case Left:
		DrawRoundRectXY(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case Ellipse:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		bRet = TRUE;
		break;
	case Body:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		bRet = TRUE;
		break;
	default:
		ASSERT(FALSE);
	}
 
	return bRet;
}

void CRoundRect::OnDrag(int nHitTest,CPointF point)
{
	REAL x,y;
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		DrawRoundRectXY(&dc,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case Top:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case TopRight:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break; 
	case Right:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case BottomRight:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y,m_fXEllipse,m_fYEllipse);
		break;
	case Bottom:
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y,m_fXEllipse,m_fYEllipse);
		break;
	case BottomLeft:
		DrawRoundRectXY(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y,m_fXEllipse,m_fYEllipse);
		break;
	case Left:
		DrawRoundRectXY(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		DrawRoundRectXY(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fXEllipse,m_fYEllipse);
		break;
	case Ellipse:
		{
			REAL fWidth = m_rc.Width()*m_fXEllipse;
			REAL fHeight = m_rc.Height()*m_fYEllipse;

			x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x;
			y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y;
			DrawRoundRect(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,fWidth+x*2,fHeight+y*2);

			x = point.x-m_pWnd->GetMarkPos().x;
			y = point.y-m_pWnd->GetMarkPos().y;
			DrawRoundRect(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,fWidth+x*2,fHeight+y*2);
		}
		break;
	case Body: 
		x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x-dx;
		y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y-dy;
		DrawRoundRectXY(&dc,m_rc.left+x,m_rc.top+y,m_rc.right+x,m_rc.bottom+y,m_fXEllipse,m_fYEllipse);

		x = point.x-m_pWnd->GetMarkPos().x-dx;
		y = point.y-m_pWnd->GetMarkPos().y-dy;
		DrawRoundRectXY(&dc,m_rc.left+x,m_rc.top+y,m_rc.right+x,m_rc.bottom+y,m_fXEllipse,m_fYEllipse);
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

BOOL CRoundRect::OnDragEnd(int nHitTest,CPointF point)
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
		m_rc.left = point.x+dx; 
		break;
	case Ellipse:
		m_fXEllipse += (REAL)(point.x-m_pWnd->GetMarkPos().x)*2/(m_rc.Width());
		m_fYEllipse += (REAL)(point.y-m_pWnd->GetMarkPos().y)*2/(m_rc.Height());
		if (m_fXEllipse > 1.0)
			m_fXEllipse = 1.0;
		else if (m_fXEllipse < 0.0)
			m_fXEllipse = 0.0;

		if (m_fYEllipse > 1.0)
			m_fYEllipse = 1.0;
		else if (m_fYEllipse < 0.0)
			m_fYEllipse = 0.0;

		break;
	case Body:
		m_rc.MoveToXY(m_rc.left+point.x-m_pWnd->GetMarkPos().x,
			m_rc.top+point.y-m_pWnd->GetMarkPos().y);
		break;
	default:
		ASSERT(FALSE);
	}
	return TRUE;
}



void CRoundRect::Draw(CDC *pDC)
{ 
	DrawRoundRectXY(pDC,m_rc.left,m_rc.top,m_rc.right,m_rc.bottom,m_fXEllipse,m_fYEllipse);
}

void CRoundRect::DrawSelect(CDC *pDC)
{
	CFilled::DrawSelectRect(pDC);

	CDiamondSelector diamondSelector(pDC);
	DrawDiamondMark(pDC,GetEllipseMarkPos());
}

void CRoundRect::GetBoundsRect(CRectF &rect) const
{
	rect = m_rc;
}

void CRoundRect::SetBoundsRect(const CRectF &rect)
{
	m_rc = rect;
}

CElem *CRoundRect::Clone(void) const 
{
	CRoundRect *pRoundRect = new CRoundRect(*this);
	return pRoundRect;
}
 

void CRoundRect::SetXEllipse(REAL fXEllipse)
{
	m_fXEllipse = fXEllipse;
}

void CRoundRect::SetYEllipse(REAL fYEllipse)
{
	m_fYEllipse = fYEllipse;
}

inline CPointF CRoundRect::GetEllipseMarkPos(void) const
{
	return CPointF(m_rc.left+m_rc.Width()*m_fXEllipse/2.0f,m_rc.top+m_rc.Height()*m_fYEllipse/2.0f);
}

void CRoundRect::DrawRoundRectXY(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fXEllipse,REAL fYEllipse)
{
	if (CRectF(left,top,right,bottom).IsRectEmpty())
		return;

	REAL w = right - left;
	REAL h = bottom - top;

	REAL fWidth = (REAL)(fXEllipse*w);
	REAL fHeight = (REAL)(fYEllipse*h);

	if ((fWidth<0 && w>0) ||(fWidth>0 && w<0))
		fWidth = 0;
	else if (abs(fWidth) > abs(w))
		fWidth = w;

	if ((fHeight<0 && h>0) ||(fHeight>0 && h<0))
		fHeight = 0;
	else if (abs(fHeight) > abs(h))
		fHeight = h;

	if (fWidth==0.0 || fHeight==0.0)
	{
		DrawRect(pDC,left,top,right,bottom);
	}
	else
	{
		exchange_if_less(REAL,right,left);
		exchange_if_less(REAL,bottom,top);
		absx(fWidth);absx(fHeight);

		pDC->RoundRect((int)left,(int)top,(int)right,(int)bottom,(int)fWidth,(int)fHeight);
	}
}

void CRoundRect::DrawRoundRect(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fWidth,REAL fHeight)
{
	REAL w = right - left;
	REAL h = bottom - top;

	if ((fWidth<0 && w>0) ||(fWidth>0 && w<0))
		fWidth = 0;
	else if (abs(fWidth) > abs(w))
		fWidth = w;


	if ((fHeight<0 && h>0) ||(fHeight>0 && h<0))
		fHeight = 0;
	else if (abs(fHeight) > abs(h))
		fHeight = h;

	REAL cx = fWidth/2;
	REAL cy = fHeight/2;

	if (fWidth==0.0 || fHeight==0.0)
	{
		DrawRect(pDC,left,top,right,bottom);
	}
	else
	{
		exchange_if_less(REAL,right,left);
		exchange_if_less(REAL,bottom,top);
		absx(cx);absx(cy);
		absx(fWidth);absx(fHeight);

		pDC->RoundRect((int)left,(int)top,(int)right,(int)bottom,(int)fWidth,(int)fHeight);
	}
}




