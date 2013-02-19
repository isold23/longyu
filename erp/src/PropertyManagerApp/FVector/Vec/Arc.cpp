#include "stdafx.h"
#include "Arc.h"
#include "resource.h"
#include "VecWnd.h"
#include "GraphAlgorithm.h"


CArc::CArc(CVecWnd *pWnd)
	: COutlined(pWnd)
{

}

CArc::~CArc(void)
{

}


int CArc::HitTest(CPointF point,BOOL bSelect)
{
	CPointF ptStart = GetStartPoint();
	CPointF ptEnd = GetEndPoint();

	if (bSelect)
	{
		if (PtInDiamondMark(ptStart,point))
			return Start;
		
		if (PtInDiamondMark(ptEnd,point))
			return End; 

		int nHitTest = COutlined::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;
	}

	CRectF rc(m_rc);
	rc.InflateRect(HITTEST_DIST,HITTEST_DIST);
	if (!EllipseHelper::PtInPie(rc,m_fStartAngel,m_fEndAngel,point))
		return -1;

	rc.DeflateRect(HITTEST_DIST*2,HITTEST_DIST*2);
	return EllipseHelper::PtInPie(rc,m_fStartAngel,m_fEndAngel,point) ? -1 : Body;
}

HCURSOR CArc::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=End); 

	HCURSOR cur = COutlined::Cursor(nHitTest);
	if (cur != NULL)
		return cur;

	static HCURSOR curs[] = {
		AfxGetApp()->LoadStandardCursor(IDC_CROSS),
		AfxGetApp()->LoadStandardCursor(IDC_CROSS)
	};
	return curs[nHitTest-HitMax]; 
}


void CArc::InitDrag(CPointF point)
{
	m_rc.left = point.x;
	m_rc.top = point.y;

	const REAL DEF_Start_ANGLE = 0.0;
	const REAL DEF_End_ANGLE = M_PI/2;

	m_fStartAngel = DEF_Start_ANGLE;
	m_fEndAngel = DEF_End_ANGLE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawArcSEA(&dc,m_rc.left,m_rc.top,m_rc.left,m_rc.top,m_fStartAngel,m_fEndAngel);
}

void CArc::InitDragging(CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawArcSEA(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
	DrawArcSEA(&dc,m_rc.left,m_rc.top,point.x,point.y,m_fStartAngel,m_fEndAngel);
}

void CArc::InitEndDrag(CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	m_rc.left += dx;
	m_rc.top += dy;
	m_rc.right = point.x+dx;
	m_rc.bottom = point.y+dy;
}

BOOL CArc::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = TRUE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{	
	case TopLeft:
		DrawArcSEA(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Top:
		DrawArcSEA(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case TopRight:
		DrawArcSEA(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break; 
	case Right:
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case BottomRight:
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Bottom:
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case BottomLeft:
		DrawArcSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Left:
		DrawArcSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Start:
	case End:
	case Body:
		{
			CPointF ptStart = GetStartPoint();
			CPointF ptEnd = GetEndPoint();
			dc.Arc((int)(m_rc.left-dx),(int)(m_rc.top-dy),(int)(m_rc.right-dx),(int)(m_rc.bottom-dy),(int)(ptStart.x-dx),(int)(ptStart.y-dy),(int)(ptEnd.x-dx),(int)(ptEnd.y-dy));
		}
		break;
	}

	return bRet;
}

void CArc::OnDrag(int nHitTest,CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	REAL x = m_pWnd->GetCapturePos().x - m_pWnd->GetMarkPos().x - dx;
	REAL y = m_pWnd->GetCapturePos().y - m_pWnd->GetMarkPos().y - dy;
	REAL x1 = point.x-m_pWnd->GetMarkPos().x - x -dx;
	REAL y1 = point.y-m_pWnd->GetMarkPos().y - y - dy;

	switch (nHitTest)
	{ 
	case TopLeft:
		DrawArcSEA(&dc,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Top:
		DrawArcSEA(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case TopRight:
		DrawArcSEA(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break; 
	case Right:
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case BottomRight:
		DrawArcSEA(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,m_rc.left,m_rc.top,point.x,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Bottom:
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case BottomLeft:
		DrawArcSEA(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Left:
		DrawArcSEA(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawArcSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Start:
		{
			CPointF pt = GetStartPoint();
			pt.Offset(x,y);
			DrawArcEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,pt.x,pt.y,m_fEndAngel);
			pt.Offset(x1,y1);
			DrawArcEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,pt.x,pt.y,m_fEndAngel);
		}
		break;
	case End: 
		{
			CPointF pt(GetEndPoint());
			pt.Offset(x,y);
			DrawArcSA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,pt.x,pt.y);
			pt.Offset(x1,y1);
			DrawArcSA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,pt.x,pt.y);	
		}	
		break;
	case Body:
		{
			CRectF rc(m_rc);
			rc.OffsetRect(x,y);
			DrawArcSEA(&dc,rc.left,rc.top,rc.right,rc.bottom,m_fStartAngel,m_fEndAngel);
			rc.OffsetRect(x1,y1);		
			DrawArcSEA(&dc,rc.left,rc.top,rc.right,rc.bottom,m_fStartAngel,m_fEndAngel);
		}
	
		break;
	default:
		ASSERT(FALSE);
		break;
	} 

}

BOOL CArc::OnDragEnd(int nHitTest,CPointF point)
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
	case Start:
		m_fStartAngel = EllipseHelper::Angel(m_rc,point + CPointF(dx,dy));
		break;
	case End:
		m_fEndAngel = EllipseHelper::Angel(m_rc,point + CPointF(dx,dy));
		break;
	case Body:
		m_rc.OffsetRect(point.x-m_pWnd->GetMarkPos().x,point.y-m_pWnd->GetMarkPos().y);
		break;
	default:
		ASSERT(FALSE);
	}
	return TRUE;
}

void CArc::Draw(CDC *pDC)
{ 
	DrawArcSEA(pDC,m_rc.left,m_rc.top,m_rc.right,m_rc.bottom,m_fStartAngel,m_fEndAngel);
}

void CArc::DrawSelect(CDC *pDC)
{
	COutlined::DrawSelectRect(pDC);

	CDiamondSelector diamondSelector(pDC);
	DrawDiamondMark(pDC,GetStartPoint());
	DrawDiamondMark(pDC,GetEndPoint()); 
}

void CArc::GetBoundsRect(CRectF &rect) const
{
	rect = m_rc;
}

void CArc::SetBoundsRect(const CRectF &rect)
{
	m_rc = rect;	
}

CElem* CArc::Clone(void) const 
{
	CArc *pArc = new CArc(*this);
	return pArc;
}

void CArc::SetStartAngel(REAL fAngel)
{
	m_fStartAngel = fAngel;
}

void CArc::SetEndAngel(REAL fAngel)
{
	m_fEndAngel = fAngel;
}
 
CPointF CArc::GetStartPoint(void) const
{
	CPointF pt;
	EllipseHelper::Angel(m_rc,m_fStartAngel,pt.x,pt.y);
	return pt;
}

CPointF CArc::GetEndPoint(void) const
{
	CPointF pt;
	EllipseHelper::Angel(m_rc,m_fEndAngel,pt.x,pt.y);
	return pt;
}
void CArc::DrawArcSEA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fStartAngel,REAL fEndAngel)
{
	CRectF rc(left,top,right,bottom);
	if (rc.IsRectEmpty())
		return;

	CPointF ptStart;
	EllipseHelper::Angel(rc,fStartAngel,ptStart.x,ptStart.y);

	CPointF ptEnd;
	EllipseHelper::Angel(rc,fEndAngel,ptEnd.x,ptEnd.y);

	pDC->Arc((int)rc.left,(int)rc.top,(int)rc.right,(int)rc.bottom,(int)ptStart.x,(int)ptStart.y,(int)ptEnd.x,(int)ptEnd.y);

} 

void CArc::DrawArcEA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL xStart,REAL yStart,REAL fEndAngel)
{
	CRectF rc(left,top,right,bottom);
	if (rc.IsRectEmpty())
		return;

	CPointF ptStart(xStart,yStart);

	CPointF ptEnd;
	EllipseHelper::Angel(rc,fEndAngel,ptEnd.x,ptEnd.y);

	pDC->Arc((int)rc.left,(int)rc.top,(int)rc.right,(int)rc.bottom,(int)ptStart.x,(int)ptStart.y,(int)ptEnd.x,(int)ptEnd.y);
} 

void CArc::DrawArcSA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fStartAngel,REAL xEnd,REAL yEnd)
{
	CRectF rc(left,top,right,bottom);
	if (rc.IsRectEmpty())
		return;

	CPointF ptStart;
	EllipseHelper::Angel(rc,fStartAngel,ptStart.x,ptStart.y);

	CPointF ptEnd(xEnd,yEnd);

	pDC->Arc((int)rc.left,(int)rc.top,(int)rc.right,(int)rc.bottom,(int)ptStart.x,(int)ptStart.y,(int)ptEnd.x,(int)ptEnd.y);
}

