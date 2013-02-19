#include "stdafx.h"
#include "Gauge.h"
#include "resource.h"
#include "VecWnd.h"
#include "GraphAlgorithm.h"


CGauge::CGauge(CVecWnd *pWnd)
	: COutlined(pWnd)
{
	m_nOutlineWidth = 2;
	m_rcBounds.SetRectEmpty();
}

CGauge::~CGauge(void)
{

}

int CGauge::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		int nHitTest = COutlined::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;

		for (int i=0; i<m_pts.GetCount(); ++i)
			if (PtInDiamondMark(point,m_pts[i]))
				return HtIndex + (int)i;
	}

	for (int i=0,j=m_pts.GetCount()-1; i<j; ++i)
		if (LineHelper::GetDistFromPointToShortLine(m_pts[i],m_pts[i+1],point) < HITTEST_DIST)
			return Body;
	return -1;
}

HCURSOR CGauge::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=HitMax+m_pts.GetCount());
	HCURSOR cur = COutlined::Cursor(nHitTest);
	if (cur != NULL)
		return cur;
	static HCURSOR curs[] = {
		AfxGetApp()->LoadStandardCursor(IDC_CROSS)
	};
	return curs[0];
}

void CGauge::InitDrag(CPointF point)
{ 
	m_pts.Add(point);
}

void CGauge::InitReDrag(CPointF point)
{
}

void CGauge::InitDragging(CPointF point)
{
	CPointF ptStart = m_pts[m_pts.GetCount()-1] ;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	dc.MoveTo((int)ptStart.x,(int)ptStart.y);
	dc.LineTo((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
	dc.MoveTo((int)ptStart.x,(int)ptStart.y);
	dc.LineTo((int)point.x,(int)point.y);
}

BOOL CGauge::InitPauseDrag(CPointF point)
{ 
	m_pts.Add(point);
	return FALSE;
}
 
void CGauge::InitEndDrag(CPointF point)
{ 
	int i = 1;
	while (i<m_pts.GetCount() && m_pts.GetCount()>2)
	{
		if (LineHelper::LEN(m_pts[i],m_pts[i-1]) <= HITTEST_DIST)
			m_pts.RemoveAt(i);
		else
			++i;
	}
	PointHelper::OffsetPoints(m_pts,m_pWnd->GetStartPos().x,m_pWnd->GetStartPos().y);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
	FormatDesc();
}
 

BOOL CGauge::OnDragStart(int nHitTest,CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	CRectF rc;
	GetBoundsRect(rc);
	rc.OffsetRect(-dx,-dy);

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
		GetPoints(pts);
		PointHelper::OffsetPoints(pts,-dx,-dy);
		pts[nHitTest-HtIndex] = CPoint((int)point.x,(int)point.y);
		break;
	} 

	dc.Polyline(pts.GetData(),(int)pts.GetCount());

	return bRet;
}

void CGauge::OnDrag(int nHitTest,CPointF point)
{
	CRectF rc;
	GetBoundsRect(rc);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;
	rc.OffsetRect(-dx,-dy);

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
		{
			GetPoints(pts1);
			PointHelper::OffsetPoints(pts1,-dx,-dy);
			pts1[nHitTest-HtIndex] = CPoint((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);	
			pts2.Copy(pts1);
			pts2[nHitTest-HtIndex] = CPoint((int)point.x,(int)point.y);
		}
		break;
	}

	dc.Polyline(pts1.GetData(),(int)pts1.GetCount()); 
	dc.Polyline(pts2.GetData(),(int)pts2.GetCount()); 
}

BOOL CGauge::OnDragEnd(int nHitTest,CPointF point)
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
		m_pts[nHitTest-HtIndex] = point + m_pWnd->GetStartPos();
		PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
		FormatDesc();
		return TRUE;
	}

	SetBoundsRect(rc);
	
	FormatDesc();
	return TRUE;
}



void CGauge::Draw(CDC *pDC)
{
	CPoints pts;
	GetPoints(pts);

	pDC->Polyline(pts.GetData(),(int)pts.GetCount());

	CRect rc;
	pDC->DrawText(m_strDesc,rc,DT_CALCRECT);
	CPointF ptf(m_rcBounds.CenterPoint());
	CPoint pt((int)ptf.x,(int)ptf.y);
	rc.OffsetRect(pt-rc.CenterPoint());
	pDC->DrawText(m_strDesc,rc,DT_TOP);
}

void CGauge::DrawSelect(CDC *pDC)
{
	DrawSelectRect(pDC);

	CDiamondSelector diamondSelector(pDC);
	for (int i=0; i<m_pts.GetCount(); ++i)
		DrawCircleMark(pDC,m_pts[i]);
}

void CGauge::GetBoundsRect(CRectF &rect) const
{
	rect = m_rcBounds;
}

void CGauge::SetBoundsRect(const CRectF &rect)
{
	if (m_rcBounds != rect)
	{
		PointHelper::RecalcPoints(m_rcBounds,rect,m_pts,m_pts);
		m_rcBounds = rect;
	}
}

CElem *CGauge::Clone(void) const 
{
	CGauge *pPoly = new CGauge(*this);
	return pPoly;
}

void CGauge::SetPoints(const CFPoints &pts)
{
	m_pts.Copy(pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}


void CGauge::GetPoints(CPoints &pts) const
{
	PointHelper::ConvertPoints(m_pts,pts);
}

void CGauge::SetPoints(const CPoints &pts)
{
	PointHelper::ConvertPoints(pts,m_pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}

void CGauge::FormatDesc(void)
{
	REAL fTotal = 0.0f;
	int nLast = m_pts.GetCount() - 1;
	for (int i=nLast; i>=1; --i)
		fTotal += LineHelper::LEN(m_pts[i],m_pts[i-1]);

	m_strDesc.Format(_T("起始点{%d,%d}  终止点{%d,%d}  直接距离{%d}  路径长度{%d}"),
		(int)m_pts[0].x,(int)m_pts[0].y,(int)m_pts[nLast].x,(int)m_pts[nLast].y,
		(int)LineHelper::LEN(m_pts[0],m_pts[nLast]),(int)fTotal);
}
