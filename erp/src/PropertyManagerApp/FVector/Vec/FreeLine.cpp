#include "stdafx.h"
#include "FreeLine.h"
#include "resource.h"
#include "VecWnd.h"
#include "GraphAlgorithm.h"



CFreeLine::CFreeLine(CVecWnd *pWnd)
	: COutlined(pWnd)
{
	m_rcBounds.SetRectEmpty();
}

CFreeLine::~CFreeLine(void)
{

}

int CFreeLine::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		int nHitTest = COutlined::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;
	}

	CPoints pts;
	GetPoints(pts);

	CClientDC dc(m_pWnd);

	for (int i=0,j=(int)m_pts.GetCount()-1; i<j; ++i)
	{
		if (LineHelper::GetDistFromPointToShortLine(m_pts[i],m_pts[i+1],point) < HITTEST_DIST)
			return Body;
	}
	return -1;
}

HCURSOR CFreeLine::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<= Body);
	return COutlined::Cursor(nHitTest);
}

void CFreeLine::InitDrag(CPointF point)
{ 
//	point += m_pWnd->GetStartPos();
	m_pts.Add(point);
}

void CFreeLine::InitReDrag(CPointF point)
{
}

void CFreeLine::InitDragging(CPointF point)
{
	m_pts.Add(point);

	CClientDC dc(m_pWnd);

	CPoints pts;
	GetPoints(pts);

	dc.Polyline(pts.GetData(),(int)pts.GetCount());
}

void CFreeLine::InitEndDrag(CPointF point)
{ 
	int i = 1;
	while (i<m_pts.GetCount() && m_pts.GetCount()>=2)
	{
		if (LineHelper::LEN(m_pts[i],m_pts[i-1]) <= HITTEST_DIST)
			m_pts.RemoveAt(i);
		else
			++i;
	}

	PointHelper::OffsetPoints(m_pts,m_pWnd->GetStartPos().x,m_pWnd->GetStartPos().y);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}

BOOL CFreeLine::InitPauseDrag(CPointF point)
{
	m_pts.Add(point);
	return FALSE;
}


BOOL CFreeLine::OnDragStart(int nHitTest,CPointF point)
{
	CRectF rc;
	GetBoundsRect(rc);
	rc.OffsetRect(-m_pWnd->GetStartPos().x,-m_pWnd->GetStartPos().y);

	BOOL bRet = FALSE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	CPoints pts;

	switch (nHitTest)
	{
	case TopLeft:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(point.x,point.y,rc.right,rc.bottom),m_pts,pts);
		break;
	case Top:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,point.y,rc.right,rc.bottom),m_pts,pts);
		break;
	case TopRight:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,point.y,point.x,rc.bottom),m_pts,pts);
		break; 
	case Right:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,point.x,rc.bottom),m_pts,pts);
		break;
	case BottomRight:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,point.x,point.y),m_pts,pts);
		break;
	case Bottom:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,rc.right,point.y),m_pts,pts);
		break;
	case BottomLeft:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(point.x,rc.top,rc.right,point.y),m_pts,pts);
		break;
	case Left:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(point.x,rc.top,rc.right,rc.bottom),m_pts,pts);
		break;
	case Body: 
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,rc.right,rc.bottom),m_pts,pts);
		bRet = TRUE;
		break;
	default:
		ASSERT(FALSE);
	} 

	dc.Polyline(pts.GetData(),(int)pts.GetCount());

	return bRet;
}

void CFreeLine::OnDrag(int nHitTest,CPointF point)
{
	CRectF rc;
	GetBoundsRect(rc);
	rc.OffsetRect(-m_pWnd->GetStartPos().x,-m_pWnd->GetStartPos().y);

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);
 
	CPoints pts1,pts2;

	switch (nHitTest)
	{
	case TopLeft:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,rc.right,rc.bottom),m_pts,pts1);
		PointHelper::RecalcPoints(m_rcBounds,CRectF(point.x,point.y,rc.right,rc.bottom),m_pts,pts2);
		break;
	case Top:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,m_pWnd->GetCapturePos().y,rc.right,rc.bottom),m_pts,pts1);
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,point.y,rc.right,rc.bottom),m_pts,pts2);
		break;
	case TopRight:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,rc.bottom),m_pts,pts1);
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,point.y,point.x,rc.bottom),m_pts,pts2);
		break; 
	case Right:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,m_pWnd->GetCapturePos().x,rc.bottom),m_pts,pts1);
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,point.x,rc.bottom),m_pts,pts2);
		break;
	case BottomRight:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y),m_pts,pts1); 
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,point.x,point.y),m_pts,pts2); 
		break;
	case Bottom:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,rc.right,m_pWnd->GetCapturePos().y),m_pts,pts1);
		PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left,rc.top,rc.right,point.y),m_pts,pts2);
		break;
	case BottomLeft:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(m_pWnd->GetCapturePos().x,rc.top,rc.right,m_pWnd->GetCapturePos().y),m_pts,pts1);
		PointHelper::RecalcPoints(m_rcBounds,CRectF(point.x,rc.top,rc.right,point.y),m_pts,pts2); 
		break;
	case Left:
		PointHelper::RecalcPoints(m_rcBounds,CRectF(m_pWnd->GetCapturePos().x,rc.top,rc.right,rc.bottom),m_pts,pts1); 
		PointHelper::RecalcPoints(m_rcBounds,CRectF(point.x,rc.top,rc.right,rc.bottom),m_pts,pts2); 
		break;
	case Body: 
		{
			REAL x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x;
			REAL y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y;

			PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left+x,rc.top+y,rc.right+x,rc.bottom+y),m_pts,pts1);

			x = point.x-m_pWnd->GetMarkPos().x;
			y = point.y-m_pWnd->GetMarkPos().y;
			PointHelper::RecalcPoints(m_rcBounds,CRectF(rc.left+x,rc.top+y,rc.right+x,rc.bottom+y),m_pts,pts2);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	dc.Polyline(pts1.GetData(),(int)pts1.GetCount()); 
	dc.Polyline(pts2.GetData(),(int)pts2.GetCount()); 

}

BOOL CFreeLine::OnDragEnd(int nHitTest,CPointF point)
{
	CRectF rc;
	GetBoundsRect(rc);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case TopLeft:
		rc.left = point.x + dx;
		rc.top = point.y + dy;
		break;
	case Top:
		rc.top = point.y + dy;
		break;
	case TopRight:
		rc.right = point.x + dx;
		rc.top = point.y + dy;
		break; 
	case Right:
		rc.right = point.x + dx;
		break;
	case BottomRight:
		rc.right = point.x + dx;
		rc.bottom = point.y + dy;
		break;
	case Bottom:
		rc.bottom = point.y + dy;
		break;
	case BottomLeft:
		rc.left = point.x + dx;
		rc.bottom = point.y + dy;
		break;
	case Left:
		rc.left = point.x + dx;
		break;
	case Body:
		rc.MoveToXY(rc.left+point.x-m_pWnd->GetMarkPos().x,
			rc.top+point.y-m_pWnd->GetMarkPos().y);
		break;
	default:
		ASSERT(FALSE);
	}

	SetBoundsRect(rc);
	return TRUE;
}



void CFreeLine::Draw(CDC *pDC)
{
	CPoints pts;
	GetPoints(pts);

	pDC->Polyline(pts.GetData(),(int)pts.GetCount());
}

void CFreeLine::DrawSelect(CDC *pDC)
{
	DrawSelectRect(pDC);
}

void CFreeLine::GetBoundsRect(CRectF &rect) const
{
	rect = m_rcBounds;
}

void CFreeLine::SetBoundsRect(const CRectF &rect)
{
	if (m_rcBounds != rect)
	{
		PointHelper::RecalcPoints(m_rcBounds,rect,m_pts,m_pts);
		m_rcBounds = rect;
	}
}

CElem *CFreeLine::Clone(void) const 
{
	CFreeLine *pFreeLine = new CFreeLine(*this);
	return pFreeLine;
}

void CFreeLine::SetPoints(const CFPoints &pts)
{
	m_pts.Copy(pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}


void CFreeLine::GetPoints(CPoints &pts) const
{
	PointHelper::ConvertPoints(m_pts,pts);
}

void CFreeLine::SetPoints(const CPoints &pts)
{
	PointHelper::ConvertPoints(pts,m_pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}
