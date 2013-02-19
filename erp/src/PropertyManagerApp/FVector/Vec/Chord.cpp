#include "stdafx.h"
#include "Chord.h"
#include "resource.h"
#include "VecWnd.h" 
#include "GraphAlgorithm.h"

CChord::CChord(CVecWnd *pWnd)
	: CFilled(pWnd)
{

}

CChord::~CChord(void)
{

}


int CChord::HitTest(CPointF point,BOOL bSelect)
{
	CPointF ptStart = GetStartPoint();
	CPointF ptEnd = GetEndPoint();

	if (bSelect)
	{
		if (PtInDiamondMark(ptStart,point))
			return Start;

		if (PtInDiamondMark(ptEnd,point))
			return End; 

		int nHitTest = CFilled::HitTestSelectRect(point);
		if (nHitTest != -1)
			return nHitTest;
	}

	if (!EllipseHelper::PtInChord(m_rc,m_fStartAngel,m_fEndAngel,point))
		return -1;
	if (m_bFill)
		return Body;

	CRectF rc(m_rc);
	rc.DeflateRect(HITTEST_DIST,HITTEST_DIST);
	if (!EllipseHelper::PtInChord(rc,m_fStartAngel,m_fEndAngel,point))
		return Body;

	if (LineHelper::GetDistFromPointToShortLine(ptEnd,ptStart,point) <= HITTEST_DIST)
		return Body;

	return -1;

}

HCURSOR CChord::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=End); 

	HCURSOR cur = CFilled::Cursor(nHitTest);
	if (cur != NULL)
		return cur;

	static HCURSOR curs[] = {
		AfxGetApp()->LoadStandardCursor(IDC_CROSS),
		AfxGetApp()->LoadStandardCursor(IDC_CROSS)
	};
	return curs[nHitTest-HitMax]; 
}


void CChord::InitDrag(CPointF point)
{
	m_rc.left = point.x;
	m_rc.top = point.y;

	const REAL DEF_Start_ANGLE = 0.0;
	const REAL DEF_End_ANGLE = M_PI/2;

	m_fStartAngel = DEF_Start_ANGLE;
	m_fEndAngel = DEF_End_ANGLE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawChordSEA(&dc,m_rc.left,m_rc.top,m_rc.left,m_rc.top,m_fStartAngel,m_fEndAngel);
}

void CChord::InitDragging(CPointF point)
{
	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	DrawChordSEA(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
	DrawChordSEA(&dc,m_rc.left,m_rc.top,point.x,point.y,m_fStartAngel,m_fEndAngel);
}

void CChord::InitEndDrag(CPointF point)
{
	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	m_rc.left += dx;
	m_rc.top += dy;
	m_rc.right = point.x+dx;
	m_rc.bottom = point.y+dy;
}

BOOL CChord::OnDragStart(int nHitTest,CPointF point)
{
	BOOL bRet = TRUE;

	CClientDC dc(m_pWnd);
	CElastic elastic(&dc,this);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{	
	case TopLeft:
		DrawChordSEA(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Top:
		DrawChordSEA(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case TopRight:
		DrawChordSEA(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break; 
	case Right:
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case BottomRight:
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,point.x,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Bottom:
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case BottomLeft:
		DrawChordSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Left:
		DrawChordSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Start:
	case End:
	case Body:
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	}

	return bRet;
}

void CChord::OnDrag(int nHitTest,CPointF point)
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
		DrawChordSEA(&dc,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,point.x,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Top:
		DrawChordSEA(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,m_rc.left-dx,point.y,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case TopRight:
		DrawChordSEA(&dc,m_rc.left-dx,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,m_rc.left-dx,point.y,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break; 
	case Right:
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_pWnd->GetCapturePos().x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,point.x,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case BottomRight:
		DrawChordSEA(&dc,m_rc.left,m_rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,m_rc.left,m_rc.top,point.x,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Bottom:
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case BottomLeft:
		DrawChordSEA(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_pWnd->GetCapturePos().y,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,point.y,m_fStartAngel,m_fEndAngel);
		break;
	case Left:
		DrawChordSEA(&dc,m_pWnd->GetCapturePos().x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		DrawChordSEA(&dc,point.x,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,m_fEndAngel);
		break;
	case Start:
		{
			CPointF pt = GetStartPoint();
			pt.Offset(x,y);
			DrawChordEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,pt.x,pt.y,m_fEndAngel);
			pt.Offset(x1,y1);
			DrawChordEA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,pt.x,pt.y,m_fEndAngel);
		}
		break;
	case End: 
		{
			CPointF pt(GetEndPoint());
			pt.Offset(x,y);
			DrawChordSA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,pt.x,pt.y);
			pt.Offset(x1,y1);
			DrawChordSA(&dc,m_rc.left-dx,m_rc.top-dy,m_rc.right-dx,m_rc.bottom-dy,m_fStartAngel,pt.x,pt.y);	
		}	
		break;
	case Body:
		{
			CRectF rc(m_rc);
			rc.OffsetRect(x,y);
			DrawChordSEA(&dc,rc.left,rc.top,rc.right,rc.bottom,m_fStartAngel,m_fEndAngel);
			rc.OffsetRect(x1,y1);		
			DrawChordSEA(&dc,rc.left,rc.top,rc.right,rc.bottom,m_fStartAngel,m_fEndAngel);
		}

		break;
	default:
		ASSERT(FALSE);
		break;
	} 

}

BOOL CChord::OnDragEnd(int nHitTest,CPointF point)
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

void CChord::Draw(CDC *pDC)
{
	DrawChordSEA(pDC,m_rc.left,m_rc.top,m_rc.right,m_rc.bottom,m_fStartAngel,m_fEndAngel);
}

void CChord::DrawSelect(CDC *pDC)
{
	DrawSelectRect(pDC);

	CDiamondSelector diamondSelector(pDC);
	DrawDiamondMark(pDC,GetStartPoint());
	DrawDiamondMark(pDC,GetEndPoint()); 
}


void CChord::GetBoundsRect(CRectF &rect) const
{
	rect = m_rc;
}

void CChord::SetBoundsRect(const CRectF &rect)
{
	m_rc = rect;	
}

CElem* CChord::Clone(void) const 
{
	CChord *pChord = new CChord(*this);
	return pChord;
}

void CChord::SetStartAngel(REAL fAngel)
{
	m_fStartAngel = fAngel;
}

void CChord::SetEndAngel(REAL fAngel)
{
	m_fEndAngel = fAngel;
}

CPointF CChord::GetStartPoint(void) const
{
	CPointF pt;
	EllipseHelper::Angel(m_rc,m_fStartAngel,pt.x,pt.y);
	return pt;
}

CPointF CChord::GetEndPoint(void) const
{
	CPointF pt;
	EllipseHelper::Angel(m_rc,m_fEndAngel,pt.x,pt.y);
	return pt;
}

void CChord::DrawChordSEA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fStartAngel,REAL fEndAngel)
{
	CRectF rc(left,top,right,bottom);
	if (rc.IsRectEmpty())
		return;

	CPointF ptStart;
	EllipseHelper::Angel(rc,fStartAngel,ptStart.x,ptStart.y);

	CPointF ptEnd;
	EllipseHelper::Angel(rc,fEndAngel,ptEnd.x,ptEnd.y);
 
	pDC->Chord((int)rc.left,(int)rc.top,(int)rc.right,(int)rc.bottom,(int)ptStart.x,(int)ptStart.y,(int)ptEnd.x,(int)ptEnd.y);
}

void CChord::DrawChordEA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL xStart,REAL yStart,REAL fEndAngel)
{
	CRectF rc(left,top,right,bottom);
	if (rc.IsRectEmpty())
		return;

	CPointF ptStart(xStart,yStart);

	CPointF ptEnd;
	EllipseHelper::Angel(rc,fEndAngel,ptEnd.x,ptEnd.y);
 
	pDC->Chord((int)rc.left,(int)rc.top,(int)rc.right,(int)rc.bottom,(int)ptStart.x,(int)ptStart.y,(int)ptEnd.x,(int)ptEnd.y);
}

void CChord::DrawChordSA(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom,REAL fStartAngel,REAL xEnd,REAL yEnd)
{
	CRectF rc(left,top,right,bottom);
	if (rc.IsRectEmpty())
		return;

	CPointF ptStart;
	EllipseHelper::Angel(rc,fStartAngel,ptStart.x,ptStart.y);

	EllipseHelper::Angel(rc,xEnd,yEnd,xEnd,yEnd);
	CPointF ptEnd(xEnd,yEnd);
 
	pDC->Chord((int)rc.left,(int)rc.top,(int)rc.right,(int)rc.bottom,(int)ptStart.x,(int)ptStart.y,(int)ptEnd.x,(int)ptEnd.y);
}

