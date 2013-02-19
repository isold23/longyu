#pragma once
#include "vectypes.h"

class CPathHelper
{
public:
	CPathHelper(CWnd *pWnd);
	BOOL Near(CPointF point,REAL fMaxDist);
	void Region(CRgn &rgn);
	void BoundsRect(CRectF &rc);
	CDC* operator->(void);
private:
#ifdef _DEBUG
	BOOL m_bEnded;
#endif
	CClientDC m_dc;
};