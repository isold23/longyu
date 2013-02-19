#pragma once

#include <math.h>
#include <cfloat>
#include "vectypes.h"
#include "../Utils/ArrayAdaptor.h"

#define pow2(x) ((x)*(x))
#ifndef M_PI 
#define M_PI 3.14159265358979323846f
#endif

#define exchange_if_great(T,a,b) if (a>b) {T tmp=a;a=b;b=tmp;}
#define exchange_if_less(T,a,b) if (a<b) {T tmp=a;a=b;b=tmp;}
#define  absx(x) x = abs(x)
#define between(v,l,r) (v>=l && v<=r)

namespace PointHelper
{
	inline CPointF Cvt(CPoint pt) {return CPointF((REAL)pt.x,(REAL)pt.y);}
	inline CPoint Cvt(CPointF pt) {return CPoint((int)pt.x,(int)pt.y);}

	void OffsetPoints(CPoints &pts,REAL dx,REAL dy);
	void OffsetPoints(CFPoints &pts,REAL dx,REAL dy);
	void ConvertPoints(const CFPoints &src,CPoints &dst);
	void ConvertPoints(const CPoints &src,CFPoints &dst);

	void CalcPointsBoundsRect(const CFPoints &pts,CRectF &rc);

	void RecalcPoints(const CRectF &srcRect,const CRectF &dstRect,const CPoints &srcPts,CPoints &dstPts);
	void RecalcPoints(const CRectF &srcRect,const CRectF &dstRect,const CFPoints &srcPts,CPoints &dstPts);
	void RecalcPoints(const CRectF &srcRect,const CRectF &dstRect,const CFPoints &srcPts,CFPoints &dstPts);
}

namespace LineHelper
{
	/////////////////////////////////////////////////////
	// Line formula y = kx + b
	/////////////////////////////////////////////////////

	inline REAL K(POINTF pt1,POINTF pt2) {
		return (pt1.y-pt2.y)/(pt1.x-pt2.x);
	}

	inline REAL B(POINTF pt1,POINTF pt2) {
		return pt1.y - K(pt1,pt2)*pt1.x;
	} 

	inline REAL X(POINTF pt1,POINTF pt2) {
		return -B(pt1,pt2)/K(pt1,pt2);
	}

	inline REAL Y(POINTF pt1,POINTF pt2) {
		return B(pt1,pt2);
	}

	inline REAL LEN(POINTF pt1,POINTF pt2) { 
		return sqrtf((pow2(pt1.x-pt2.x) + pow2(pt1.y-pt2.y)));
	}
	//////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////
	// Line formula ax + by + c=0
	/////////////////////////////////////////////////////
	inline BOOL C(POINTF pt1,POINTF pt2) {
		return (pt1.x*pt2.y != pt2.x*pt1.y);
	}

	inline REAL A2C(POINTF pt1,POINTF pt2) {
		return (pt1.y-pt2.y)/(pt1.x*pt2.y-pt2.x*pt1.y);
	}

	inline REAL B2C(POINTF pt1,POINTF pt2) {
		return (pt1.x-pt2.x)/(pt2.x*pt1.y-pt1.x*pt2.y);
	}

	inline REAL A2BNC(POINTF pt1,POINTF pt2) {
		ASSERT(C(pt1,pt2) == FALSE);
		return -pt1.y/pt1.x;
	}

	//////////////////////////////////////////////////////////////////////////

	extern void RotatePoint(POINTF &pt,POINTF ptOrg,REAL angel);
	extern REAL GetAngel(POINTF ptSrc,POINTF ptDst,POINTF ptOrg);
	extern REAL GetDistFromPointToLine(POINTF ptStart,POINTF ptEnd,POINTF point);
	extern REAL GetDistFromPointToShortLine(POINTF ptStart,POINTF ptEnd,POINTF point);

	/////////////////////////////////////////////////////
	// Line formula ax + by + c=0
	/////////////////////////////////////////////////////
	enum{Left=1,Top=2,Right=4,Bottom=8,BELONG=16};
	extern int PtToLine(POINTF ptStart,POINTF ptEnd,POINTF pt);
	extern BOOL PtInTriangle(POINTF pt1,POINTF pt2,POINTF pt3,POINTF point);
	extern BOOL PtInPoly(const CFPoints &pts,POINTF pt);
}

namespace EllipseHelper
{
	/////////////////////////////////////////////////////
	// Ellipse formula x^2/a^2 + y^2/b^2 = 1
	/////////////////////////////////////////////////////

				  


	inline REAL A(const CRectF &rect){return (rect.Width() / 2);}
	inline REAL B(const CRectF &rect){return (rect.Height() / 2);}
	inline REAL M(const CRectF &rect){return (rect.left) + (rect.Width() / 2);}
	inline REAL N(const CRectF &rect){return rect.top + (rect.Height() / 2);}
	inline REAL P(const CRectF &rect){return sqrtf(A(rect)*A(rect) - B(rect)*B(rect));}
	inline REAL D(const CRectF &rect){return sqrtf(P(rect)*P(rect) + B(rect)*B(rect));}


	extern void Angel(const CRectF &rect,REAL xAngel,REAL yAngel,REAL &x,REAL &y);
	extern void Angel(const CRectF &rect, REAL angel,REAL &x, REAL &y);
	extern REAL Angel(const CRectF &rect,CPointF pt);

	extern BOOL PtInEllipse(const CRectF &rect,POINTF point);
	extern BOOL PtInChord(const CRectF &rect,REAL fStartAngel,REAL fEndAngel,POINTF point);
	extern BOOL PtInPie(const CRectF &rect,REAL fStartAngel,REAL fEndAngel,POINTF point);
	extern BOOL PtInRoundRect(const CRectF &rect,REAL fXEllipse,REAL fYEllipse,POINTF point);
}