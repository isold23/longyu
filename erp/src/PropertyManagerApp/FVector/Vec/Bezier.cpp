#include "stdafx.h"
#include "Bezier.h"
#include "resource.h"
#include "VecWnd.h"
#include "PathHelper.h"
#include "GraphAlgorithm.h"

CBezier::CBezier(CVecWnd *pWnd)
	: COutlined(pWnd)
{

}

CBezier::~CBezier(void)
{
	
}


int CBezier::HitTest(CPointF point,BOOL bSelect)
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

	CPoints pts;
	GetPoints(pts);
	CPathHelper helper(m_pWnd);
	helper->PolyBezier(pts.GetData(),(int)pts.GetCount());	
	return (helper.Near(point,HITTEST_DIST) ? Body:-1); 
}

HCURSOR CBezier::GetCursor(int nHitTest)
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

void CBezier::InitDrag(CPointF point)
{
	m_pts.Add(point);
}

void CBezier::InitReDrag(CPointF point)
{
}

void CBezier::InitDragging(CPointF point)
{
	CPointF ptStart = m_pts[m_pts.GetCount()-1] ;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	dc.MoveTo((int)ptStart.x,(int)ptStart.y);
	dc.LineTo((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
	dc.MoveTo((int)ptStart.x,(int)ptStart.y);
	dc.LineTo((int)point.x,(int)point.y);
}

BOOL CBezier::InitPauseDrag(CPointF point)
{
	m_pts.Add(point);
	return FALSE;
}

void CBezier::InitEndDrag(CPointF point)
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
}

 
BOOL CBezier::OnDragStart(int nHitTest,CPointF point)
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

void CBezier::OnDrag(int nHitTest,CPointF point)
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

BOOL CBezier::OnDragEnd(int nHitTest,CPointF point)
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
	return TRUE;
}

void CBezier::Draw(CDC *pDC)
{
	CPoints pts;
	GetPoints(pts);
	pDC->PolyBezier(pts.GetData(),(int)pts.GetCount()); 
}

void CBezier::DrawSelect(CDC *pDC)
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
 
void CBezier::GetBoundsRect(CRectF &rect) const
{
	rect = m_rcBounds;
}

void CBezier::SetBoundsRect(const CRectF &rect)
{
	if (m_rcBounds != rect)
	{
		PointHelper::RecalcPoints(m_rcBounds,rect,m_pts,m_pts);
		m_rcBounds = rect;
	}
}

CElem *CBezier::Clone(void) const 
{
	CBezier *pBesier = new CBezier(*this);
	return pBesier;
}

void CBezier::SetPoints(const CFPoints &pts)
{
	m_pts.Copy(pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}


void CBezier::GetPoints(CPoints &pts) const
{
	PointHelper::ConvertPoints(m_pts,pts);
}

void CBezier::SetPoints(const CPoints &pts)
{
	PointHelper::ConvertPoints(pts,m_pts);
	PointHelper::CalcPointsBoundsRect(m_pts,m_rcBounds);
}
