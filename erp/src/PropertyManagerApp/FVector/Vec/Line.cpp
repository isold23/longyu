#include "StdAfx.h"
#include "Line.h"
#include "resource.h"
#include "GraphAlgorithm.h" 
#include "VecWnd.h"



CLine::CLine(CVecWnd *pWnd)
	:COutlined(pWnd)
{
}

CLine::~CLine(void)
{
}




int CLine::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		if (PtInCircleMark(m_ptStart,point))
			return Start;
		else if (PtInCircleMark(m_ptEnd,point))
			return End;
	}

	if (LineHelper::GetDistFromPointToShortLine(m_ptStart,m_ptEnd,point) <= HITTEST_DIST)
		return Body;
	else
		return -1;
}

HCURSOR CLine::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=Start && nHitTest<=Body);
	static HCURSOR curs[] = {
		AfxGetApp()->LoadCursor(IDC_CURBLTR),
		AfxGetApp()->LoadCursor(IDC_CURTLBR),
		AfxGetApp()->LoadCursor(IDC_CURM)
	};
	return curs[nHitTest-HitMax];
}


void CLine::InitDrag(CPointF point)
{
	m_ptStart = point;
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	dc.MoveTo((int)m_ptStart.x,(int)m_ptStart.y);
	dc.LineTo((int)m_ptStart.x,(int)m_ptStart.y);

}

void CLine::InitDragging(CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	dc.MoveTo((int)m_ptStart.x,(int)m_ptStart.y);
	dc.LineTo((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
	dc.MoveTo((int)m_ptStart.x,(int)m_ptStart.y);
	dc.LineTo((int)point.x,(int)point.y);
}

void CLine::InitEndDrag(CPointF point)
{
 	m_ptStart += m_pWnd->GetStartPos();
	m_ptEnd = point + m_pWnd->GetStartPos();
}


BOOL CLine::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = FALSE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case Start:
		dc.MoveTo((int)point.x,(int)point.y);
		dc.LineTo((int)(m_ptEnd.x-dx),(int)(m_ptEnd.y-dy));
		break;
	case End:
		dc.MoveTo((int)(m_ptStart.x-dx),(int)(m_ptStart.y-dy));
		dc.LineTo((int)point.x,(int)point.y);
		break;
	case Body:
		dc.MoveTo((int)(m_ptStart.x-dx),(int)(m_ptStart.y-dy));
		dc.LineTo((int)(m_ptEnd.x-dx),(int)(m_ptEnd.y-dy));
		bRet = TRUE;
		break;
	}
 
	return bRet;
}

void CLine::OnDrag(int nHitTest,CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);


	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{
	case Start: 
		dc.MoveTo((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
		dc.LineTo((int)(m_ptEnd.x-dx),(int)(m_ptEnd.y-dy));
		dc.MoveTo((int)point.x,(int)point.y);
		dc.LineTo((int)(m_ptEnd.x-dx),(int)(m_ptEnd.y-dy));
		break;
	case End:
		dc.MoveTo((int)(m_ptStart.x-dx),(int)(m_ptStart.y-dy));
		dc.LineTo((int)m_pWnd->GetCapturePos().x,(int)m_pWnd->GetCapturePos().y);
		dc.MoveTo((int)(m_ptStart.x-dx),(int)(m_ptStart.y-dy));
		dc.LineTo((int)point.x,(int)point.y);
		break;
	case Body:
		{
			REAL x = m_pWnd->GetCapturePos().x-m_pWnd->GetMarkPos().x-dx;
			REAL y = m_pWnd->GetCapturePos().y-m_pWnd->GetMarkPos().y-dy;
			dc.MoveTo((int)(m_ptStart.x+x),(int)(m_ptStart.y+y));
			dc.LineTo((int)(m_ptEnd.x+x),(int)(m_ptEnd.y+y));

			x = point.x-m_pWnd->GetMarkPos().x-dx;
			y = point.y-m_pWnd->GetMarkPos().y-dy;
			dc.MoveTo((int)(m_ptStart.x+x),(int)(m_ptStart.y+y));
			dc.LineTo((int)(m_ptEnd.x+x),(int)(m_ptEnd.y+y));
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	} 

}

BOOL CLine::OnDragEnd(int nHitTest,CPointF point)
{
	switch (nHitTest)
	{
	case Start: 
		m_ptStart = point + m_pWnd->GetStartPos();
		break;
	case End:
		m_ptEnd = point + m_pWnd->GetStartPos();
		break;
	case Body:
		{
			REAL x = point.x-m_pWnd->GetMarkPos().x;
			REAL y = point.y-m_pWnd->GetMarkPos().y;
			m_ptStart.Offset(x,y);
			m_ptEnd.Offset(x,y);
		}
		break;
	default:
		ASSERT(FALSE);
	}
	return TRUE;
}

void CLine::Draw(CDC *pDC)
{
	pDC->MoveTo((int)m_ptStart.x,(int)m_ptStart.y);
	pDC->LineTo((int)m_ptEnd.x,(int)m_ptEnd.y); 
}

void CLine::DrawSelect(CDC *pDC)
{
	CCircleSelector circleSelector(pDC);
	DrawCircleMark(pDC,m_ptStart);
	DrawCircleMark(pDC,m_ptEnd);
}

void CLine::GetBoundsRect(CRectF &rect) const
{
	rect.SetRect(m_ptStart,m_ptEnd);
	rect.NormalizeRect();
}

void CLine::SetBoundsRect(const CRectF &rect)
{
	m_ptStart = rect.TopLeft();
	m_ptEnd = rect.BottomRight();
}

CElem* CLine::Clone(void) const 
{
	CLine *pLine = new CLine(*this);
	return pLine;
}

void CLine::SetStartPoint(CPointF point)
{
	m_ptStart = point;
}

void CLine::SetEndPoint(CPointF point)
{
	m_ptEnd = point;
}