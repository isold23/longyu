#include "stdafx.h"
#include "Multi.h"
#include "resource.h"
#include "VecWnd.h"
#include "PathHelper.h"
#include "GraphAlgorithm.h"



CMulti::CMulti(CVecWnd *pWnd)
	: CElem(pWnd)
{

}

CMulti::~CMulti(void)
{

}


int CMulti::HitTest(CPointF point,BOOL bSelect)
{
	if (bSelect)
	{
		CRectF rc;
		GetBoundsRect(rc);

		REAL fCenterX = (rc.left + rc.right)/2.0f;
		REAL fCenterY = (rc.top + rc.bottom)/2.0f;

		if (PtInCircleMark(rc.TopLeft(),point))
			return TopLeft;
		else if (PtInCircleMark(CPointF(fCenterX,rc.top),point))
			return Top;
		else if (PtInCircleMark(CPointF(rc.right,rc.top),point))
			return TopRight;
		else if (PtInCircleMark(CPointF(rc.right,fCenterY),point))
			return Right;
		else if (PtInCircleMark(rc.BottomRight(),point))
			return BottomRight;
		else if (PtInCircleMark(CPointF(fCenterX,rc.bottom),point))
			return Bottom;
		else if (PtInCircleMark(CPointF(rc.left,rc.bottom),point))
			return BottomLeft;
		else if (PtInCircleMark(CPointF(rc.left,fCenterY),point))
			return Left;
	}
 
	for (int i=0; i<m_elems.GetCount(); ++i)
		if (m_elems[i]->HitTest(point,bSelect) != -1)
			return Body;

	return -1;
}

HCURSOR CMulti::GetCursor(int nHitTest)
{
	ASSERT(nHitTest>=TopLeft && nHitTest<=Body); 
	static HCURSOR curs[] = {
		NULL,
		AfxGetApp()->LoadCursor(IDC_CURTLBR),
		AfxGetApp()->LoadCursor(IDC_CURTB),
		AfxGetApp()->LoadCursor(IDC_CURBLTR),
		AfxGetApp()->LoadCursor(IDC_CURLR),
		AfxGetApp()->LoadCursor(IDC_CURTLBR),
		AfxGetApp()->LoadCursor(IDC_CURTB),
		AfxGetApp()->LoadCursor(IDC_CURBLTR),
		AfxGetApp()->LoadCursor(IDC_CURLR),
		AfxGetApp()->LoadCursor(IDC_CURM)
	};
	return curs[nHitTest]; 
}


void CMulti::InitDrag(CPointF point)
{
	ASSERT(FALSE);
}

void CMulti::InitDragging(CPointF point)
{
	ASSERT(FALSE);
}

void CMulti::InitEndDrag(CPointF point)
{
	ASSERT(FALSE);
}

BOOL CMulti::OnDragStart(int nHitTest,CPointF point)
{
	ASSERT(m_elems.GetCount() >= 2);

	BOOL bRet = TRUE;

	CClientDC dc(m_pWnd);
	CPen pen(PS_DOT,1,RGB(0,0,0));
	CPen *pOldPen = dc.SelectObject(&pen);
	int nDrawMode = dc.SetROP2(R2_NOTXORPEN);

	CRectF rc;
	GetBoundsRect(rc);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	switch (nHitTest)
	{	
	case TopLeft:
		DrawRect(&dc,point.x,point.y,rc.right-dx,rc.bottom-dy);
		break;
	case Top:
		DrawRect(&dc,rc.left-dx,point.y,rc.right-dx,rc.bottom-dy);
		break;
	case TopRight:
		DrawRect(&dc,rc.left-dx,point.y,point.x,rc.bottom-dy);
		break; 
	case Right:
		DrawRect(&dc,rc.left-dx,rc.top-dy,point.x,rc.bottom-dy);
		break;
	case BottomRight:
		DrawRect(&dc,rc.left-dx,rc.top-dy,point.x,point.y);
		break;
	case Bottom:
		DrawRect(&dc,rc.left-dx,rc.top-dy,rc.right-dx,point.y);
		break;
	case BottomLeft:
		DrawRect(&dc,point.x,rc.top-dy,rc.right-dx,point.y);
		break;
	case Left:
		DrawRect(&dc,point.x,rc.top-dy,rc.right-dx,rc.bottom-dy);
		break;
	case Body:
		DrawRect(&dc,rc.left-dx,rc.top-dy,rc.right-dx,rc.bottom-dy);
		bRet = TRUE;
		break;
	}

	dc.SetROP2(nDrawMode);
	dc.SelectObject(pOldPen);
	return bRet;

}

void CMulti::OnDrag(int nHitTest,CPointF point)
{
	ASSERT(m_elems.GetCount() >= 2);

	CClientDC dc(m_pWnd);

	CPen pen(PS_DOT,1,RGB(0,0,0));
	CPen *pOldPen = dc.SelectObject(&pen);
	int nDrawMode = dc.SetROP2(R2_NOTXORPEN);

	CRectF rc;
	GetBoundsRect(rc);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	REAL x = m_pWnd->GetCapturePos().x - m_pWnd->GetMarkPos().x - dx;
	REAL y = m_pWnd->GetCapturePos().y - m_pWnd->GetMarkPos().y - dy;
	REAL x1 = point.x-m_pWnd->GetMarkPos().x - x -dx;
	REAL y1 = point.y-m_pWnd->GetMarkPos().y - y - dy;

	switch (nHitTest)
	{ 
	case TopLeft:
		DrawRect(&dc,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y,rc.right-dx,rc.bottom-dy);
		DrawRect(&dc,point.x,point.y,rc.right-dx,rc.bottom-dy);
		break;
	case Top:
		DrawRect(&dc,rc.left-dx,m_pWnd->GetCapturePos().y,rc.right-dx,rc.bottom-dy);
		DrawRect(&dc,rc.left-dx,point.y,rc.right-dx,rc.bottom-dy);
		break;
	case TopRight:
		DrawRect(&dc,rc.left-dx,m_pWnd->GetCapturePos().y,m_pWnd->GetCapturePos().x,rc.bottom-dy);
		DrawRect(&dc,rc.left-dx,point.y,point.x,rc.bottom-dy);
		break; 
	case Right:
		DrawRect(&dc,rc.left-dx,rc.top-dy,m_pWnd->GetCapturePos().x,rc.bottom-dy);
		DrawRect(&dc,rc.left-dx,rc.top-dy,point.x,rc.bottom-dy);
		break;
	case BottomRight:
		DrawRect(&dc,rc.left,rc.top,m_pWnd->GetCapturePos().x,m_pWnd->GetCapturePos().y);
		DrawRect(&dc,rc.left,rc.top,point.x,point.y);
		break;
	case Bottom:
		DrawRect(&dc,rc.left-dx,rc.top-dy,rc.right-dx,m_pWnd->GetCapturePos().y);
		DrawRect(&dc,rc.left-dx,rc.top-dy,rc.right-dx,point.y);
		break;
	case BottomLeft:
		DrawRect(&dc,m_pWnd->GetCapturePos().x,rc.top-dy,rc.right-dx,m_pWnd->GetCapturePos().y);
		DrawRect(&dc,point.x,rc.top-dy,rc.right-dx,point.y);
		break;
	case Left:
		DrawRect(&dc,m_pWnd->GetCapturePos().x,rc.top-dy,rc.right-dx,rc.bottom-dy);
		DrawRect(&dc,point.x,rc.top-dy,rc.right-dx,rc.bottom-dy);
		break;
	case Body:
		rc.OffsetRect(x,y);
		DrawRect(&dc,rc.left,rc.top,rc.right,rc.bottom);
		rc.OffsetRect(x1,y1);		
		DrawRect(&dc,rc.left,rc.top,rc.right,rc.bottom);
		break;
	default:
		ASSERT(FALSE);
		break;
	} 


	dc.SetROP2(nDrawMode);
	dc.SelectObject(pOldPen);
}

BOOL CMulti::OnDragEnd(int nHitTest,CPointF point)
{
	ASSERT(m_elems.GetCount() >= 2);

	REAL dx = m_pWnd->GetStartPos().x;
	REAL dy = m_pWnd->GetStartPos().y;

	CRectF rc;
	GetBoundsRect(rc);

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
		rc.OffsetRect(point.x-m_pWnd->GetMarkPos().x,point.y-m_pWnd->GetMarkPos().y);
		break;
	default:
		ASSERT(FALSE);
	}

	SetBoundsRect(rc);
	return TRUE;

}

void CMulti::Draw(CDC *pDC,UINT nDrawFlag)
{
	 
}

void CMulti::GetBoundsRect(CRectF &rect) const
{
	ASSERT(m_elems.GetCount() >= 2);

	int cnt = (int)m_elems.GetCount();
	CRectF rc;
	m_elems[0]->GetBoundsRect(rect);
	rect.NormalizeRect();
	for (int i=1; i<m_elems.GetCount(); ++i)
	{
		m_elems[i]->GetBoundsRect(rc);
		rc.NormalizeRect();
		if (rect.left > rc.left)
			rect.left = rc.left;
		if (rect.top > rc.top)
			rect.top = rc.top;
		if (rect.right < rc.right)
			rect.right = rc.right;
		if (rect.bottom < rc.bottom)
			rect.bottom = rc.bottom;
	}
}

void CMulti::SetBoundsRect(const CRectF &rect)
{
	const float MIN_SCALE = 0.01f;

	ASSERT(m_elems.GetCount() >= 2);

	CRectF rc;
	GetBoundsRect(rc);

	if (rc != rect)
	{
		float fWidth = rc.Width();
		float fHeight = rc.Height();
		if (fWidth == 0.0f)
			fWidth = MIN_SCALE;
		if (fHeight == 0.0f)
			fHeight = MIN_SCALE;

		float fXScale = rect.Width()/fWidth;
		float fYScale = rect.Height()/fHeight;

		if (fXScale == 0.0f)
			fXScale = MIN_SCALE;
		if (fYScale == 0.0f)
			fYScale = MIN_SCALE;

		CRectF rcElem,rcBase;
		rcBase.left = (rect.left - rc.left)*fXScale;
		rcBase.right  =  (rect.right - rc.right)*fXScale;
		rcBase.top = (rect.top - rc.top)*fYScale;
		rcBase.bottom = (rect.bottom - rc.bottom)*fYScale;
		for (int i=0; i<m_elems.GetCount(); ++i)
		{
			m_elems[i]->GetBoundsRect(rcElem);
			rcBase += rcBase;
			m_elems[i]->SetBoundsRect(rcElem);

		}
	}
}

CElem* CMulti::Clone(void) const 
{
	return NULL;/*
	CMulti *pMulti = new CMulti(m_pWnd);
	pMulti->m_elems.SetSize(m_elems.GetCount());
	for (int i=0; i<pMulti->m_elems.GetCount(); ++i)
		pMulti->m_elems[i] = m_elems[i]->Clone();
	return pMulti;*/
}


int CMulti::IndexOf(CElem *pElem)
{
	int i; 
	for (i=0; i<m_elems.GetCount(); ++i)
		if (m_elems[i] == pElem)
			break;

	return (i == m_elems.GetCount() ? -1:i);
}

void CMulti::AddElem(CElem *pElem)
{
	m_elems.Add(pElem);
}

CElem* CMulti::RemoveElem(int nIndex)
{ 
	CElem *pElem = m_elems[nIndex];
	m_elems.RemoveAt(nIndex);
	return pElem;
}

void CMulti::RemoveElem(CElem *pElem)
{
	int nIndex = IndexOf(pElem);
	ASSERT(nIndex != -1);
	RemoveElem(nIndex);
}

 