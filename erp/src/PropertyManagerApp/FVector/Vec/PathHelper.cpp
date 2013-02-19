#include "stdafx.h"
#include "PathHelper.h"
#include "GraphAlgorithm.h"


CPathHelper::CPathHelper(CWnd *pWnd)
	:m_dc(pWnd)
{
#ifdef _DEBUG
	m_bEnded = FALSE;
#endif
	m_dc.BeginPath();
}

CDC* CPathHelper::operator->(void)
{
	ASSERT(!m_bEnded);
	return &m_dc;
}

void CPathHelper::BoundsRect(CRectF &rc)
{
	ASSERT(!m_bEnded);
	ASSERT(m_bEnded = TRUE);

	m_dc.EndPath();
	m_dc.FlattenPath();

	int cnt;
	CArray<POINT,POINT> pts;
	CArray<BYTE,BYTE> bts;

	cnt = m_dc.GetPath(NULL,NULL,0);

	if (cnt == 0)
	{
		rc.SetRectEmpty();
	}
	else
	{
		pts.SetSize(cnt);
		bts.SetSize(cnt);

		m_dc.GetPath(pts.GetData(),bts.GetData(),cnt); 

		rc.left = rc.right = (REAL)pts[0].x;
		rc.top = rc.bottom = (REAL)pts[0].y;

		for (int i=1; i<cnt; ++i)
		{
			if (rc.left > (REAL)pts[i].x)
				rc.left = (REAL)pts[i].x;
			else if (rc.right < pts[i].x)
				rc.right = (REAL)pts[i].x;

			if (rc.top > (REAL)pts[i].y)
				rc.top = (REAL)pts[i].y;
			else if (rc.bottom < (REAL)pts[i].y)
				rc.bottom = (REAL)pts[i].y;
		}
	}
}

void CPathHelper::Region(CRgn &rgn)
{
	ASSERT(!m_bEnded);
	ASSERT(m_bEnded = TRUE);

	if (rgn.GetSafeHandle() != NULL)
		rgn.DeleteObject();

	m_dc.EndPath();
	rgn.CreateFromPath(&m_dc);
}

BOOL CPathHelper::Near(CPointF point,REAL fMaxDist)
{
	ASSERT(!m_bEnded);
	ASSERT(m_bEnded = TRUE);

	m_dc.EndPath();
	m_dc.FlattenPath();

	int cnt;
	CArray<POINT,POINT> pts;
	CArray<BYTE,BYTE> bts;

	cnt = m_dc.GetPath(NULL,NULL,0);
	if (cnt != 0)
	{
		pts.SetSize(cnt);
		bts.SetSize(cnt);

		m_dc.GetPath(pts.GetData(),bts.GetData(),cnt); 

		if (bts[0] == PT_MOVETO && bts[cnt-1]&PT_CLOSEFIGURE)
			pts.Add(pts[0]);
		cnt = (int)(pts.GetCount()) - 1; 

		for (int i=0; i<cnt; ++i)
		{
			CPointF pt1((REAL)pts[i].x,(REAL)pts[i].y);
			CPointF pt2((REAL)pts[i+1].x,(REAL)pts[i+1].y);		
			if (LineHelper::GetDistFromPointToShortLine(pt1,pt2,point) < fMaxDist)
				return TRUE;
		} 
	}

	return FALSE;
}