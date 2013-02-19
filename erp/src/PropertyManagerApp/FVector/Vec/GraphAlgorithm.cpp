#include "stdafx.h"
#include "GraphAlgorithm.h"

namespace PointHelper
{
void OffsetPoints(CPoints &pts,REAL dx,REAL dy)
{
	int x = (int)dx;
	int y = (int)dy;
	for (int i=0; i<pts.GetCount(); ++i)
		pts[i].Offset(x,y);
}

void OffsetPoints(CFPoints &pts,REAL dx,REAL dy) 
{
	for (int i=0; i<pts.GetCount(); ++i)
		pts[i].Offset(dx,dy);
}

void ConvertPoints(const CFPoints &src,CPoints &dst)
{
	dst.SetSize(src.GetCount());
	for (int i=0; i<src.GetCount(); ++i)
		dst[i] = CPoint((int)src[i].x,(int)src[i].y);
}

void ConvertPoints(const CPoints &src,CFPoints &dst) 
{
	dst.SetSize(src.GetCount());
	for (int i=0; i<src.GetCount(); ++i)
		dst[i] = CPointF((float)src[i].x,(float)src[i].y);
}

void CalcPointsBoundsRect(const CFPoints &pts,CRectF &rc)
{
	if (pts.IsEmpty())
	{
		rc.SetRectEmpty();
	}
	else
	{
		rc.left = rc.right = pts[0].x;
		rc.top = rc.bottom = pts[0].y;
	}

	for (int i=1; i<pts.GetCount(); ++i)
	{
		if (rc.left > pts[i].x)
			rc.left = pts[i].x;
		else if (rc.right < pts[i].x)
			rc.right = pts[i].x;

		if (rc.top > pts[i].y)
			rc.top = pts[i].y;
		else if (rc.bottom < pts[i].y)
			rc.bottom = pts[i].y;
	}
}

void RecalcPoints(const CRectF &srcRect,const CRectF &dstRect,const CPoints &srcPts,CPoints &dstPts)
{
	static const float MIN_SCALE = 0.01f;
	if ((void*)&srcPts != (void*)&dstPts)
		dstPts.SetSize(srcPts.GetCount());

	if (!srcPts.IsEmpty())
	{
		float fWidth = srcRect.Width();
		float fHeight = srcRect.Height();
		if (fWidth == 0.0f) fWidth = MIN_SCALE;
		if (fHeight == 0.0f) fHeight = MIN_SCALE;

		float fXScale = dstRect.Width()/fWidth;
		float fYScale = dstRect.Height()/fHeight;

		if (fXScale == 0.0f) fXScale = MIN_SCALE;
		if (fYScale == 0.0f) fYScale = MIN_SCALE;

		for (int i=0; i<srcPts.GetCount(); ++i)
		{
			dstPts[i].x = (int)(dstRect.left + fXScale*(srcPts[i].x-srcRect.left));
			dstPts[i].y = (int)(dstRect.top + fYScale*(srcPts[i].y-srcRect.top));
		}
	}

}

void RecalcPoints(const CRectF &srcRect,const CRectF &dstRect,const CFPoints &srcPts,CPoints &dstPts)
{
	static const float MIN_SCALE = 0.01f;
	if ((void*)&srcPts != (void*)&dstPts)
		dstPts.SetSize(srcPts.GetCount());

	if (!srcPts.IsEmpty())
	{
		float fWidth = srcRect.Width();
		float fHeight = srcRect.Height();
		if (fWidth == 0.0f) fWidth = MIN_SCALE;
		if (fHeight == 0.0f) fHeight = MIN_SCALE;

		float fXScale = dstRect.Width()/fWidth;
		float fYScale = dstRect.Height()/fHeight;

		if (fXScale == 0.0f) fXScale = MIN_SCALE;
		if (fYScale == 0.0f) fYScale = MIN_SCALE;

		for (int i=0; i<srcPts.GetCount(); ++i)
		{
			dstPts[i].x = (int)(dstRect.left + fXScale*(srcPts[i].x-srcRect.left));
			dstPts[i].y = (int)(dstRect.top + fYScale*(srcPts[i].y-srcRect.top));
		}
	}
}

void RecalcPoints(const CRectF &srcRect,const CRectF &dstRect,const CFPoints &srcPts,CFPoints &dstPts)
{
	static const float MIN_SCALE = 0.01f;
	if ((void*)&srcPts != (void*)&dstPts)
		dstPts.SetSize(srcPts.GetCount());

	if (!srcPts.IsEmpty())
	{
		float fWidth = srcRect.Width();
		float fHeight = srcRect.Height();
		if (fWidth == 0.0f) fWidth = MIN_SCALE;
		if (fHeight == 0.0f) fHeight = MIN_SCALE;

		float fXScale = dstRect.Width()/fWidth;
		float fYScale = dstRect.Height()/fHeight;

		if (fXScale == 0.0f) fXScale = MIN_SCALE;
		if (fYScale == 0.0f) fYScale = MIN_SCALE;

		for (int i=0; i<srcPts.GetCount(); ++i)
		{
			dstPts[i].x = (dstRect.left + fXScale*(srcPts[i].x-srcRect.left));
			dstPts[i].y = (dstRect.top + fYScale*(srcPts[i].y-srcRect.top));
		}
	}
}
}

namespace LineHelper
{
	REAL GetAngel(POINTF ptSrc,const POINTF& ptDst,POINTF ptOrg) 
	{
		REAL s2 = pow2(ptSrc.x-ptOrg.x) + pow2(ptSrc.y-ptOrg.y);
		REAL d2 = pow2(ptDst.x-ptOrg.x) + pow2(ptDst.y-ptOrg.y);
		REAL sd2 = pow2(ptSrc.x-ptDst.x) + pow2(ptSrc.y-ptDst.y);
		REAL val = acosf((s2+d2-sd2)/(2.0f*sqrtf(s2*d2)));
		return (ptDst.x<ptSrc.x? -val : val);
	}

	REAL GetDistFromPointToLine(POINTF ptStart,POINTF ptEnd,POINTF point) 
	{
		if (C(ptStart,ptEnd))
		{
			REAL a = A2C(ptStart,ptEnd);
			REAL b = B2C(ptStart,ptEnd);
			return sqrtf(pow2(a*point.x+b*point.y+1)/(pow2(a)+pow2(b))); 
		}
		else
		{
			REAL a = -ptStart.y/ptStart.x;
			return sqrtf(pow2(a*point.x+point.y)/(pow2(a)+1.0f));
		}
	}

	void RotatePoint(POINTF &pt,POINTF ptOrg,double angel)
	{
		// Algorithm using line formula 
		//CLine line(pt,ptOrg);
		//double fAngelPt = atanf(line.K());
		//double fAngelNew = fAngelPt + angel;
		//double fLen = line.LEN();
		//pt.x = ptOrg.x - fLen*cosf(fAngelNew);
		//pt.y = ptOrg.y - fLen*sinf(fAngelNew);


		// Algorithm using right-angle triangle 
		REAL x = pt.x-ptOrg.x;
		REAL y = pt.y-ptOrg.y;

		double a = atan2(y,x);
		a -= angel;

		REAL len = sqrtf(pow2(x) + pow2(y));
		pt.x = (REAL)(len*cos(a));
		pt.y = (REAL)(len*sin(a));

		pt.x += ptOrg.x;
		pt.y += ptOrg.y; 

	}

	REAL GetDistFromPointToShortLine(POINTF ptStart,POINTF ptEnd,POINTF point)
	{
		REAL xMin,xMax,yMin,yMax;

		if (ptStart.x<ptEnd.x)
			xMin = ptStart.x,xMax = ptEnd.x;
		else
			xMin = ptEnd.x,xMax = ptStart.x;

		if (ptStart.y<ptEnd.y)
			yMin = ptStart.y,yMax = ptEnd.y;
		else
			yMin = ptEnd.y,yMax = ptStart.y;

		REAL a,b,c,x,y;
		if (C(ptStart,ptEnd))
		{
			a = A2C(ptStart,ptEnd);
			b = B2C(ptStart,ptEnd);
			c = a*point.y - b*point.x; 
			x = -(a+b*c)/(pow2(a)+pow2(b));
			y = (a*c-b)/(pow2(a)+pow2(b));
		}
		else
		{
			a = A2BNC(ptStart,ptEnd);
			b = 1.0;
			c = a*point.y-point.x;
			x = -c/(pow2(a)+1);
			y = a*c/(pow2(a)+1);
		}

		if (ceil(x)>=xMin && x<=xMax && ceil(y)>=yMin && y<=yMax)
		{
			return LEN(point,CPointF(x,y));	
		}
		else
		{
			REAL dist1 = LEN(ptStart,point);
			REAL dist2 = LEN(ptEnd,point);
			return (dist1<dist2 ? dist1:dist2);
		}
	}

	int PtToLine(POINTF ptStart,POINTF ptEnd,POINTF pt)
	{
		if (ptStart.x == ptEnd.x)
		{
			if (pt.x > ptStart.x)
				return Right;
			else if (pt.x < ptStart.x)
				return Left;
			else
				return BELONG;
		}
		else if (ptStart.y == ptEnd.y)
		{
			if (pt.y > ptStart.y)
				return Top;
			else if (pt.y < ptStart.y)
				return Bottom;
			else
				return BELONG;
		}
		else
		{
			int nRet;
			double k = K(ptStart,ptEnd);
			double b = B(ptStart,ptEnd);
			double y = k*pt.x + b;

			if (pt.y > y)
				nRet = Top;
			else if (pt.y < y)
				nRet = Bottom;
			else
				return BELONG;

			double x = (pt.y-b)/k; 
			if (pt.x < x)
				return (nRet | Left);
			else 
				return (nRet | Right);
		}
	}	


	BOOL PtInTriangle(POINTF pt1,POINTF pt2,POINTF pt3,POINTF point)
	{
		int r1 = PtToLine(pt2,pt3,point);
		if (r1 == BELONG)
			return TRUE;
		int r2 = PtToLine(pt1,pt3,point);
		if (r2 == BELONG)
			return TRUE;
		int r3 = PtToLine(pt1,pt2,point);
		if (r3 == BELONG)
			return TRUE;

		if (r1 != PtToLine(pt2,pt3,pt1))
			return FALSE;
		if (r2 != PtToLine(pt1,pt3,pt2))
			return FALSE;
		if (r3 != PtToLine(pt3,pt1,pt2))
			return FALSE;
		return TRUE;
	} 

	BOOL PtInPoly(const CFPoints &pts,POINTF pt)
	{
		int cnt = 0;
		double xinters;
		POINTF p1,p2;
		p1 = pts[0];
		for (int i=1;i<=pts.GetCount();i++) 
		{
			p2 = pts[i % pts.GetCount()];
			if (pt.y>min(p1.y,p2.y) && pt.y<=max(p1.y,p2.y) &&
				pt.x<=max(p1.x,p2.x) && p1.y!=p2.y) 
			{
				xinters = (pt.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
				if (p1.x == p2.x || pt.x <= xinters)
					cnt++;
			}

			p1 = p2;
		}
		return cnt % 2;
	}
}

namespace EllipseHelper
{
	void Angel(const CRectF &rect,REAL xAngel,REAL yAngel,REAL &x,REAL &y)
	{ 
		CPointF ptOrg = rect.CenterPoint();
		REAL a = rect.Width()/2.0f;
		REAL b = rect.Height()/2.0f;

		xAngel -= ptOrg.x;
		yAngel -= ptOrg.y;

		if (yAngel == 0)
		{
			y = 0.0f;
			x = a;
		}
		else if (xAngel == 0)
		{
			x = 0.0f;
			y = b;
		}
		else
		{
			REAL k = yAngel/xAngel;
			x = (REAL)sqrt(pow2((double)(a*b))/((double)pow2(b)+pow2(double(a*k))));
			y = (x==0.0f ? b : abs(k*x));
		}	


		// Coordinate conversion
		if (xAngel < 0)
			x =-x;
		if (yAngel < 0)
			y = -y;

		y += ptOrg.y;
		x += ptOrg.x;
	}
	void Angel(const CRectF &rect, REAL angel,REAL &x, REAL &y)
	{	
		CPointF ptOrg = rect.CenterPoint();
		REAL a = rect.Width()/2.0f;
		REAL b = rect.Height()/2.0f;


		REAL k = tanf(angel);
		if (k == 0.0f)
		{
			y = 0.0f;
			x = a;
		}
		else if (_isnan(k))
		{
			x = 0.0f;
			y = b;
		}
		else
		{
			x = (REAL)sqrt(pow2((double)(a*b))/((double)pow2(b)+pow2(double(a*k))));
			y = (x==0.0f ? b : abs(k*x));
		}	

		// Coordinate conversion
		if (angel>0 && angel<=M_PI/2)
			y = -y;
		else if (angel>M_PI/2 && angel<=M_PI)
			x = -x, y = -y;
		else if (angel>M_PI && angel<=M_PI*3/2)
			x = -x;

		y += ptOrg.y;
		x += ptOrg.x;
	}

	REAL Angel(const CRectF &rect,CPointF pt)
	{
		CPointF ptOrg = rect.CenterPoint();

		pt.x -= ptOrg.x;
		pt.y -= ptOrg.y;
		REAL angel = (REAL)-atan2((double)pt.y,(double)pt.x);

		// Coordinate conversion
		//if (pt.x <=0 && pt.y >= 0)
		//	angel = M_PI*2-angel ;
		//else
		//angel = -angel;

		if (angel < 0)
			angel += M_PI*2; 

		//TRACE(_T("\n%f\n"),angel);
		return angel;
	}

	BOOL PtInEllipse(const CRectF &rect,POINTF point)
	{
		CRectF rc(rect);
		rc.NormalizeRect();
		if (!rc.PtInRect(point))
			return FALSE;

		CPointF ptOrg = rc.CenterPoint();

		REAL a,b;
		a = rc.Width() / 2.0f;
		b = rc.Height() /2.0f;

		REAL x = point.x - ptOrg.x;
		REAL y = point.y - ptOrg.y;

		return (pow2(y) <= pow2(b) -pow2(x*b)/pow2(a));
	}

	BOOL PtInChord(const CRectF &rect,REAL fStartAngel,REAL fEndAngel,POINTF point)
	{
		if (!EllipseHelper::PtInEllipse(rect,point))
			return FALSE;
		if (fStartAngel == fEndAngel)
			return TRUE;

		CPointF ptStart;
		EllipseHelper::Angel(rect,fStartAngel,ptStart.x,ptStart.y);

		CPointF ptEnd;
		EllipseHelper::Angel(rect,fEndAngel,ptEnd.x,ptEnd.y);

		REAL fHalfAngel;
		if (fEndAngel > fStartAngel)
			fHalfAngel = (fEndAngel-fStartAngel)/2+fStartAngel;
		else
			fHalfAngel = (M_PI*2-fStartAngel+fEndAngel)/2 + fStartAngel - M_PI*2;

		CPointF ptHalf;
		EllipseHelper::Angel(rect,fHalfAngel,ptHalf.x,ptHalf.y);

		int nPtToLine = LineHelper::PtToLine(ptStart,ptEnd,point);
		if (nPtToLine == LineHelper::BELONG)
			return TRUE;

		int nHalfPtToLine = LineHelper::PtToLine(ptStart,ptEnd,ptHalf);
		return (nPtToLine == nHalfPtToLine);
	}

	BOOL PtInPie(const CRectF &rect,REAL fStartAngel,REAL fEndAngel,POINTF point)
	{
		if (!EllipseHelper::PtInEllipse(rect,point))
			return FALSE;

		double angel = Angel(rect,point);
		if (fStartAngel == fEndAngel)
			return TRUE;
		if (fStartAngel < fEndAngel)
			return (angel>fStartAngel && angel<fEndAngel);
		else 
			return (angel>fStartAngel || angel<fEndAngel);
	}


	BOOL PtInRoundRect(const CRectF &rect,REAL fXEllipse,REAL fYEllipse,POINTF point)
	{ 
		CRectF rct(rect);
		rct.NormalizeRect();
		if (!rct.PtInRect(point))
			return FALSE;

		REAL cx = (rct.Width()*fXEllipse/2);
		REAL cy = (rct.Height()*fYEllipse/2);

		CRectF rc;
		rc.SetRect(rct.left+cx,rct.top,rct.right-cx,rct.bottom);
		//rc.NormalizeRect();
		if (rc.PtInRect(point))
			return TRUE;

		rc.SetRect(rct.left,rct.top+cy,rct.left+cx,rct.bottom-cy);
		//rc.NormalizeRect();
		if (rc.PtInRect(point))
			return TRUE;

		rc.SetRect(rct.right-cx,rct.top+cy,rct.right,rct.bottom-cy);
		//rc.NormalizeRect();
		if (rc.PtInRect(point))
			return TRUE;


		cx *= 2;
		cy *= 2;

		rc.SetRect(rct.left,rct.top,rct.left+cx,rct.top+cy);
		//rc.NormalizeRect();
		if (PtInEllipse(rc,point))
			return TRUE;

		rc.SetRect(rct.right-cx,rct.top,rct.right,rct.top+cy);
		//rc.NormalizeRect();
		if (PtInEllipse(rc,point))
			return TRUE;

		rc.SetRect(rct.right-cx,rct.bottom-cy,rct.right,rct.bottom);
		//rc.NormalizeRect();
		if (PtInEllipse(rc,point))
			return TRUE;

		rc.SetRect(rct.left,rct.bottom-cy,rct.left+cx,rct.bottom);
		//rc.NormalizeRect();
		if (PtInEllipse(rc,point))
			return TRUE;

		return FALSE;

	}
}