#include "stdafx.h"
#include "Region.h"
#include "resource.h"
#include "VecWnd.h"
#include "PathHelper.h"
#include "GraphAlgorithm.h"

CRegion::CRegion(CVecWnd *pWnd)
	: CFilled(pWnd)
{
	m_rgn = new CRgn();
}

CRegion::~CRegion(void)
{
	delete m_rgn;	
}


int CRegion::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		for (int i=0; ; ++i)
		{
			if (PtInCircleMark(m_pts[i],point))
				return (int)i + HtIndex;
			if (++i == m_pts.GetCount())
				break;
			if (PtInDiamondMark(m_pts[i],point))
				return (int)i + HtIndex;
			if (PtInDiamondMark(m_pts[++i],point))
				return (int)i + HtIndex;
		}
	}

	return m_rgn->PtInRegion(CPoint((int)point.x,(int)point.y)) ? Body:-1;
}

HCURSOR CRegion::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=0 && nHitTest<=m_pts.GetCount());

	static HCURSOR curs[] = {
		AfxGetApp()->LoadCursor(IDC_CURM),
		AfxGetApp()->LoadCursor(IDC_CURBLTR),
		AfxGetApp()->LoadCursor(IDC_CURTLBR),
		AfxGetApp()->LoadStandardCursor(IDC_CROSS)
	};

	int nLast = m_pts.GetCount()+HtIndex-1;
	if (nHitTest == Body)
		return curs[0];
	if ((nHitTest-HtIndex)%3 == 0)
		return curs[1];
	return curs[3];
}

void CRegion::InitDrag(CPointF point)
{
	m_pts.Add(point);
}

void CRegion::InitReDrag(CPointF point)
{
}

void CRegion::InitDragging(CPointF point)
{
	CPointF ptStart = m_pts[m_pts.GetCount()-1] ;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	dc.MoveTo((int)ptStart.x,(int)ptStart.y);
	dc.LineTo((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
	dc.MoveTo((int)ptStart.x,(int)ptStart.y);
	dc.LineTo((int)point.x,(int)point.y);
}

BOOL CRegion::InitPauseDrag(CPointF point)
{
	m_pts.Add(point);
	return FALSE;
}

void CRegion::InitEndDrag(CPointF point)
{ 
	int i = 1;
	while (i<m_pts.GetCount() && m_pts.GetCount()>2)
	{
		if (LineHelper::LEN(m_pts[i],m_pts[i-1]) <= HITTEST_DIST)
			m_pts.RemoveAt(i);
		else
			++i;
	}

	for (i=0; i<m_pts.GetCount()-1; ++i)
	{
		CPointF sz = m_pts[i+1]-m_pts[i];
		sz.x /= 3.0f; sz.y /= 3.0f;
		
		m_pts.InsertAt(i+1,CPointF(m_pts[i]+sz)); ++i;
		m_pts.InsertAt(i+1,CPointF(m_pts[i]+sz)); ++i;
	}
	
	PointHelper::OffsetPoints(m_pts,m_pWnd->GetStartPos().x,m_pWnd->GetStartPos().y);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
	CalcRegion();
}

 
BOOL CRegion::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = FALSE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	CPoints pts;
	GetPoints(pts);
	PointHelper::OffsetPoints(pts,-dx,-dy);
	if (nHitTest != Body)
		pts[nHitTest-HtIndex] = CPoint((int)point.x,(int)point.y);
	else
		bRet = TRUE;

	dc.PolyBezier(pts.GetData(),(int)pts.GetCount());

	return bRet;
}

void CRegion::OnDrag(int nHitTest,CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	CPoints pts;
	GetPoints(pts);
	if (nHitTest != Body)
	{
		PointHelper::OffsetPoints(pts,-dx,-dy);
		pts[nHitTest-HtIndex] = CPoint((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
		dc.PolyBezier(pts.GetData(),(int)pts.GetCount());
		pts[nHitTest-HtIndex] = CPoint((int)point.x,(int)point.y);
		dc.PolyBezier(pts.GetData(),(int)pts.GetCount());
	}
	else
	{

		REAL x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x-dx;
		REAL y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y-dy;
		PointHelper::OffsetPoints(pts,x,y);
		dc.PolyBezier(pts.GetData(),(int)pts.GetCount());
		x = point.x-m_pWnd->GetMarkPos().x-dx-x;
		y = point.y-m_pWnd->GetMarkPos().y-dy-y;
		PointHelper::OffsetPoints(pts,x,y);
		dc.PolyBezier(pts.GetData(),(int)pts.GetCount());
	}
}

BOOL CRegion::OnDragEnd(int nHitTest,CPointF point)
{
	if (nHitTest != Body)
	{
		m_pts[nHitTest-HtIndex] = point + m_pWnd->GetStartPos();
	}
	else
	{
		REAL x = point.x-m_pWnd->GetMarkPos().x;
		REAL y = point.y-m_pWnd->GetMarkPos().y;

		PointHelper::OffsetPoints(m_pts,x,y);
	}

	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
	CalcRegion();
	return TRUE;
}

void CRegion::Draw(CDC *pDC)
{
	if (m_bOutline)
	{
		CPoints pts;
		GetPoints(pts);
		pDC->PolyBezier(pts.GetData(),(int)pts.GetCount()); 
	}

	if (m_bFill || !m_bOutline)
		pDC->FillRgn(m_rgn,pDC->GetCurrentBrush());
}

void CRegion::DrawSelect(CDC *pDC)
{
	int i = 0;
	CCircleSelector circleSelector(pDC);
	for (i=0; i<m_pts.GetCount(); i+=3)
		DrawCircleMark(pDC,m_pts[i]);

	CDiamondSelector diamondSelector(pDC);	
	for (int i=1; i<m_pts.GetCount(); i+=2)
	{
		DrawDiamondMark(pDC,m_pts[i++]);
		DrawDiamondMark(pDC,m_pts[i]);
	}
 }
 
void CRegion::GetBoundsRect(CRectF &rect) const
{
	rect = m_rcBounds;
}

void CRegion::SetBoundsRect(const CRectF &rect)
{
	if (m_rcBounds != rect)
	{
		PointHelper::RecalcPoints(m_rcBounds,rect,m_pts,m_pts);
		m_rcBounds = rect;
		CalcRegion();
	}
}

void CRegion::CalcRegion(void)
{
	CPoints pts;
	GetPoints(pts);
	CPathHelper ph(m_pWnd);
	ph->PolyBezier(pts.GetData(),(int)pts.GetCount());
	ph.Region(*m_rgn);

}

CElem *CRegion::Clone(void) const 
{
	CRegion *pRegion = new CRegion(*this);
	pRegion->m_rgn = new CRgn();
	pRegion->CalcRegion();
	return pRegion;
}
 
void CRegion::SetPoints(const CFPoints &pts)
{
	m_pts.Copy(pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
	CalcRegion();
}


void CRegion::GetPoints(CPoints &pts) const
{
	PointHelper::ConvertPoints(m_pts,pts);
}

void CRegion::SetPoints(const CPoints &pts)
{
	PointHelper::ConvertPoints(pts,m_pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
	CalcRegion();
}
