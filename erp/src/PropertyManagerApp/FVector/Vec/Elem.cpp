#include "stdafx.h"
#include "resource.h"
#include "Elem.h"
#include "VecWnd.h"
#include "GraphAlgorithm.h"


const REAL CElem::HITTEST_DIST = 3.0f;
const REAL CElem::CIRCLEMARK_RADIUS = 3.0f;
const REAL CElem::DIAMONDMARK_RADIUS = 3.0f;

 

CElem::CElem(CVecWnd *pWnd)
	:m_pWnd(pWnd),
	 m_dwCustomData(0)
	 
#if VW_VER_CURRENT == VW_VER_CUSTOMER
	 , m_dwUserData(0),
	 m_cDrawFlag(0)
#endif
{
}

CElem::~CElem(void)
{

}

void CElem::InitReDrag(CPointF point)
{
	ASSERT(FALSE);
}

BOOL CElem::InitPauseDrag(CPointF point)
{
	InitEndDrag(point);
	return TRUE;
} 

BOOL CElem::PtInCircleMark(CPointF ptMark,CPointF ptTest)
{
	return (LineHelper::LEN(ptMark,ptTest) <= CIRCLEMARK_RADIUS);
}

BOOL CElem::PtInDiamondMark(CPointF ptMark,CPointF ptTest)
{
	//			 1	
	//		    /\
	//		 0 /  \2
	//		   \  /
	//			\/
	//           3
	//

	POINTF pts[4];
	pts[0].x = ptMark.x-DIAMONDMARK_RADIUS;
	pts[0].y = ptMark.y;
	pts[1].x = ptMark.x;
	pts[1].y = ptMark.y-DIAMONDMARK_RADIUS;

	static const REAL dst = DIAMONDMARK_RADIUS*1.414213562f;

	if (LineHelper::GetDistFromPointToLine(pts[0],pts[1],ptTest) > dst)
		return FALSE;

	pts[2].x = ptMark.x+DIAMONDMARK_RADIUS;
	pts[2].y = ptMark.y;
	if (LineHelper::GetDistFromPointToLine(pts[1],pts[2],ptTest) > dst)
		return FALSE;

	pts[3].x = ptMark.x;
	pts[3].y = ptMark.y+DIAMONDMARK_RADIUS;
	if (LineHelper::GetDistFromPointToLine(pts[2],pts[3],ptTest) > dst)
		return FALSE;

	if (LineHelper::GetDistFromPointToLine(pts[3],pts[0],ptTest) > dst)
		return FALSE;

	return TRUE;
}

void CElem::DrawDiamondMark(CDC *pDC,CPointF point)
{

	POINT pts[4];
	pts[0].x = (int)(point.x-DIAMONDMARK_RADIUS);
	pts[0].y = (int)(point.y);
	pts[1].x = (int)(point.x);
	pts[1].y = (int)(point.y-DIAMONDMARK_RADIUS);
	pts[2].x = (int)(point.x+DIAMONDMARK_RADIUS);
	pts[2].y = (int)(point.y);
	pts[3].x = (int)(point.x);
	pts[3].y = (int)(point.y+DIAMONDMARK_RADIUS);

	pDC->Polygon(pts,4);
}

void CElem::DrawCircleMark(CDC *pDC,CPointF point)
{
	pDC->Ellipse((int)(point.x-CIRCLEMARK_RADIUS),(int)(point.y-CIRCLEMARK_RADIUS),
		(int)(point.x+CIRCLEMARK_RADIUS),(int)(point.y+CIRCLEMARK_RADIUS));
}

 
void CElem::DrawRect(CDC *pDC,REAL left,REAL top,REAL right,REAL bottom)
{
	if (!CRectF(left,top,right,bottom).IsRectEmpty())
		pDC->Rectangle((int)left,(int)top,(int)right,(int)bottom);
}

HCURSOR CElem::Cursor(int nHitTest)
{
	if (!between(nHitTest,0,Body))
		return NULL;

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

void CElem::DrawSelectRect(CDC *pDC)
{
	CRectF rc;
	GetBoundsRect(rc);
	CPointF ptCenter = rc.CenterPoint(); 

	CCircleSelector circleSelector(pDC);
	DrawCircleMark(pDC,rc.TopLeft());
	DrawCircleMark(pDC,CPointF(ptCenter.x,rc.top));
	DrawCircleMark(pDC,CPointF(rc.right,rc.top));
	DrawCircleMark(pDC,CPointF(rc.right,ptCenter.y));
	DrawCircleMark(pDC,rc.BottomRight());
	DrawCircleMark(pDC,CPointF(ptCenter.x,rc.bottom));
	DrawCircleMark(pDC,CPointF(rc.left,rc.bottom));
	DrawCircleMark(pDC,CPointF(rc.left,ptCenter.y));
}

int CElem::HitTestSelectRect(CPointF point)
{
#if VW_VER_CURRENT == VW_VER_CUSTOMER
	if (GetType() != Gauge)
		return -1;
#endif

	CRectF rc;
	GetBoundsRect(rc);
	CPointF ptCenter = rc.CenterPoint();

	if (PtInCircleMark(rc.TopLeft(),point))
		return TopLeft;
	else if (PtInCircleMark(CPointF(ptCenter.x,rc.top),point))
		return Top;
	else if (PtInCircleMark(CPointF(rc.right,rc.top),point))
		return TopRight;
	else if (PtInCircleMark(CPointF(rc.right,ptCenter.y),point))
		return Right;
	else if (PtInCircleMark(rc.BottomRight(),point))
		return BottomRight;
	else if (PtInCircleMark(CPointF(ptCenter.x,rc.bottom),point))
		return Bottom;
	else if (PtInCircleMark(CPointF(rc.left,rc.bottom),point))
		return BottomLeft;
	else if (PtInCircleMark(CPointF(rc.left,ptCenter.y),point))
		return Left;

	return -1;
}
 

