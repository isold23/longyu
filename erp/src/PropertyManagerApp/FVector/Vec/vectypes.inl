

#ifndef _VECTYPES_INL__
#define _VECTYPES_INL__

#pragma once

 

#ifndef __VECTYPES_H__
#error vectypes.inl requires vectypes.h to be included first
#endif	// __VECTYPES_H__

// CSizeF
VECTYPES_INLINE CSizeF::CSizeF() throw()
{ /* random filled */ }
VECTYPES_INLINE CSizeF::CSizeF(REAL initCX, REAL initCY) throw()
{ cx = initCX; cy = initCY; }
VECTYPES_INLINE CSizeF::CSizeF(SIZEF initSize) throw()
{ *(SIZEF*)this = initSize; }
VECTYPES_INLINE CSizeF::CSizeF(POINTF initPt) throw()
{ *(POINTF*)this = initPt; }

VECTYPES_INLINE BOOL CSizeF::operator==(SIZEF size) const throw()
{ return (cx == size.cx && cy == size.cy); }
VECTYPES_INLINE BOOL CSizeF::operator!=(SIZEF size) const throw()
{ return (cx != size.cx || cy != size.cy); }
VECTYPES_INLINE void CSizeF::operator+=(SIZEF size) throw()
{ cx += size.cx; cy += size.cy; }
VECTYPES_INLINE void CSizeF::operator-=(SIZEF size) throw()
{ cx -= size.cx; cy -= size.cy; }
VECTYPES_INLINE void CSizeF::SetSize(REAL CX, REAL CY) throw()
{ cx = CX; cy = CY; }	
VECTYPES_INLINE CSizeF CSizeF::operator+(SIZEF size) const throw()
{ return CSizeF(cx + size.cx, cy + size.cy); }
VECTYPES_INLINE CSizeF CSizeF::operator-(SIZEF size) const throw()
{ return CSizeF(cx - size.cx, cy - size.cy); }
VECTYPES_INLINE CSizeF CSizeF::operator-() const throw()
{ return CSizeF(-cx, -cy); }
VECTYPES_INLINE CPointF CSizeF::operator+(POINTF point) const throw()
{ return CPointF(cx + point.x, cy + point.y); }
VECTYPES_INLINE CPointF CSizeF::operator-(POINTF point) const throw()
{ return CPointF(cx - point.x, cy - point.y); }
VECTYPES_INLINE CRectF CSizeF::operator+(const RECTF* lpRect) const throw()
{ return CRectF(lpRect) + *this; }
VECTYPES_INLINE CRectF CSizeF::operator-(const RECTF* lpRect) const throw()
{ return CRectF(lpRect) - *this; }

// CPointF
VECTYPES_INLINE CPointF::CPointF() throw()
{ /* random filled */ }
VECTYPES_INLINE CPointF::CPointF(REAL initX, REAL initY) throw()
{ x = initX; y = initY; }
VECTYPES_INLINE CPointF::CPointF(POINTF initPt) throw()
{ *(POINTF*)this = initPt; }
VECTYPES_INLINE CPointF::CPointF(POINT initPt) throw()
{ x = (REAL)initPt.x; y=(REAL)initPt.y; }
VECTYPES_INLINE CPointF::CPointF(SIZEF initSize) throw()
{ *(SIZEF*)this = initSize; }
 
VECTYPES_INLINE void CPointF::Offset(REAL xOffset, REAL yOffset) throw()
{ x += xOffset; y += yOffset; }
VECTYPES_INLINE void CPointF::Offset(POINTF point) throw()
{ x += point.x; y += point.y; }
VECTYPES_INLINE void CPointF::Offset(SIZEF size) throw()
{ x += size.cx; y += size.cy; }
VECTYPES_INLINE void CPointF::SetPoint(REAL X, REAL Y) throw()
{ x = X; y = Y; }
VECTYPES_INLINE BOOL CPointF::operator==(POINTF point) const throw()
{ return (x == point.x && y == point.y); }
VECTYPES_INLINE BOOL CPointF::operator!=(POINTF point) const throw()
{ return (x != point.x || y != point.y); }
VECTYPES_INLINE void CPointF::operator+=(SIZEF size) throw()
{ x += size.cx; y += size.cy; }
VECTYPES_INLINE void CPointF::operator-=(SIZEF size) throw()
{ x -= size.cx; y -= size.cy; }
VECTYPES_INLINE void CPointF::operator+=(POINTF point) throw()
{ x += point.x; y += point.y; }
VECTYPES_INLINE void CPointF::operator-=(POINTF point) throw()
{ x -= point.x; y -= point.y; }
VECTYPES_INLINE CPointF CPointF::operator+(SIZEF size) const throw()
{ return CPointF(x + size.cx, y + size.cy); }
VECTYPES_INLINE CPointF CPointF::operator-(SIZEF size) const throw()
{ return CPointF(x - size.cx, y - size.cy); }
VECTYPES_INLINE CPointF CPointF::operator-() const throw()
{ return CPointF(-x, -y); }
VECTYPES_INLINE CPointF CPointF::operator+(POINTF point) const throw()
{ return CPointF(x + point.x, y + point.y); }
VECTYPES_INLINE CSizeF CPointF::operator-(POINTF point) const throw()
{ return CSizeF(x - point.x, y - point.y); }
VECTYPES_INLINE CRectF CPointF::operator+(const RECTF* lpRect) const throw()
{ return CRectF(lpRect) + *this; }
VECTYPES_INLINE CRectF CPointF::operator-(const RECTF* lpRect) const throw()
{ return CRectF(lpRect) - *this; }

// CRectF
VECTYPES_INLINE CRectF::CRectF() throw()
{ /* random filled */ }
VECTYPES_INLINE CRectF::CRectF(REAL l, REAL t, REAL r, REAL b) throw()
{ left = l; top = t; right = r; bottom = b; }
VECTYPES_INLINE CRectF::CRectF(const RECTF& srcRect) throw()
{ ::CopyRect(this, &srcRect); }
VECTYPES_INLINE CRectF::CRectF(const RECT& srcRect) throw()
{ left=(REAL)srcRect.left; top=(REAL)srcRect.top; right=(REAL)srcRect.right; bottom=(REAL)srcRect.bottom;}
VECTYPES_INLINE CRectF::CRectF(LPCRECTF lpSrcRect) throw()
{ ::CopyRect(this, lpSrcRect); }
VECTYPES_INLINE CRectF::CRectF(POINTF point, SIZEF size) throw()
{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
VECTYPES_INLINE CRectF::CRectF(POINTF topLeft, POINTF bottomRight) throw()
{ left = topLeft.x; top = topLeft.y;
right = bottomRight.x; bottom = bottomRight.y; }
VECTYPES_INLINE REAL CRectF::Width() const throw()
{ return right - left; }
VECTYPES_INLINE REAL CRectF::Height() const throw()
{ return bottom - top; }
VECTYPES_INLINE CSizeF CRectF::Size() const throw()
{ return CSizeF(right - left, bottom - top); }
VECTYPES_INLINE CPointF& CRectF::TopLeft() throw()
{ return *((CPointF*)this); }
VECTYPES_INLINE CPointF& CRectF::BottomRight() throw()
{ return *((CPointF*)this+1); }
VECTYPES_INLINE const CPointF& CRectF::TopLeft() const throw()
{ return *((CPointF*)this); }
VECTYPES_INLINE const CPointF& CRectF::BottomRight() const throw()
{ return *((CPointF*)this+1); }
VECTYPES_INLINE CPointF CRectF::CenterPoint() const throw()
{ return CPointF((left+right)/2, (top+bottom)/2); }
VECTYPES_INLINE void CRectF::SwapLeftRight() throw()
{ SwapLeftRight(LPRECTF(this)); }
VECTYPES_INLINE void WINAPI CRectF::SwapLeftRight(LPRECTF lpRect) throw()
{ REAL temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
VECTYPES_INLINE CRectF::operator LPRECTF() throw()
{ return this; }
VECTYPES_INLINE CRectF::operator LPCRECTF() const throw()
{ return this; }
VECTYPES_INLINE BOOL CRectF::IsRectEmpty() const throw()
{ return ::IsRectEmpty(this); }
VECTYPES_INLINE BOOL CRectF::IsRectNull() const throw()
{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
VECTYPES_INLINE BOOL CRectF::PtInRect(POINTF point) const throw()
{ return ::PtInRect(this, point); }
VECTYPES_INLINE void CRectF::SetRect(REAL x1, REAL y1, REAL x2, REAL y2) throw()
{ ::SetRect(this, x1, y1, x2, y2); }
VECTYPES_INLINE void CRectF::SetRect(POINTF topLeft, POINTF bottomRight) throw()
{ ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
VECTYPES_INLINE void CRectF::SetRectEmpty() throw()
{ ::SetRectEmpty(this); }
VECTYPES_INLINE void CRectF::CopyRect(LPCRECTF lpSrcRect) throw()
{ ::CopyRect(this, lpSrcRect); }
VECTYPES_INLINE BOOL CRectF::EqualRect(LPCRECTF lpRect) const throw()
{ return ::EqualRect(this, lpRect); }
VECTYPES_INLINE void CRectF::InflateRect(REAL x, REAL y) throw()
{ ::InflateRect(this, x, y); }
VECTYPES_INLINE void CRectF::InflateRect(SIZEF size) throw()
{ ::InflateRect(this, size.cx, size.cy); }
VECTYPES_INLINE void CRectF::DeflateRect(REAL x, REAL y) throw()
{ ::InflateRect(this, -x, -y); }
VECTYPES_INLINE void CRectF::DeflateRect(SIZEF size) throw()
{ ::InflateRect(this, -size.cx, -size.cy); }
VECTYPES_INLINE void CRectF::OffsetRect(REAL x, REAL y) throw()
{ ::OffsetRect(this, x, y); }
VECTYPES_INLINE void CRectF::OffsetRect(POINTF point) throw()
{ ::OffsetRect(this, point.x, point.y); }
VECTYPES_INLINE void CRectF::OffsetRect(SIZEF size) throw()
{ ::OffsetRect(this, size.cx, size.cy); }
VECTYPES_INLINE void CRectF::MoveToY(REAL y) throw()
{ bottom = Height() + y; top = y; }
VECTYPES_INLINE void CRectF::MoveToX(REAL x) throw()
{ right = Width() + x; left = x; }
VECTYPES_INLINE void CRectF::MoveToXY(REAL x, REAL y) throw()
{ MoveToX(x); MoveToY(y); }
VECTYPES_INLINE void CRectF::MoveToXY(POINTF pt) throw()
{ MoveToX(pt.x); MoveToY(pt.y); }

VECTYPES_INLINE BOOL CRectF::IntersectRect(LPCRECTF lpRect) throw()
{CRectF copyRect = *this;return copyRect.IntersectRect(copyRect,lpRect);}
VECTYPES_INLINE BOOL CRectF::IntersectRect(LPCRECTF lpRect1, LPCRECTF lpRect2) throw()
{ return ::IntersectRect(this, lpRect1, lpRect2);}
VECTYPES_INLINE BOOL CRectF::UnionRect(LPCRECTF lpRect1, LPCRECTF lpRect2) throw()
{ return ::UnionRect(this, lpRect1, lpRect2); }
VECTYPES_INLINE void CRectF::operator=(const RECTF& srcRect) throw()
{ ::CopyRect(this, &srcRect); }
VECTYPES_INLINE BOOL CRectF::operator==(const RECTF& rect) const throw()
{ return ::EqualRect(this, &rect); }
VECTYPES_INLINE BOOL CRectF::operator!=(const RECTF& rect) const throw()
{ return !::EqualRect(this, &rect); }
VECTYPES_INLINE void CRectF::operator+=(POINTF point) throw()
{ ::OffsetRect(this, point.x, point.y); }
VECTYPES_INLINE void CRectF::operator+=(SIZEF size) throw()
{ ::OffsetRect(this, size.cx, size.cy); }
VECTYPES_INLINE void CRectF::operator+=(LPCRECTF lpRect) throw()
{ InflateRect(lpRect); }
VECTYPES_INLINE void CRectF::operator-=(POINTF point) throw()
{ ::OffsetRect(this, -point.x, -point.y); }
VECTYPES_INLINE void CRectF::operator-=(SIZEF size) throw()
{ ::OffsetRect(this, -size.cx, -size.cy); }
VECTYPES_INLINE void CRectF::operator-=(LPCRECTF lpRect) throw()
{ DeflateRect(lpRect); }
VECTYPES_INLINE void CRectF::operator&=(const RECTF& rect) throw()
{ ::IntersectRect(this, this, &rect); }
VECTYPES_INLINE void CRectF::operator|=(const RECTF& rect) throw()
{ ::UnionRect(this, this, &rect); }
VECTYPES_INLINE CRectF CRectF::operator+(POINTF pt) const throw()
{ CRectF rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
VECTYPES_INLINE CRectF CRectF::operator-(POINTF pt) const throw()
{ CRectF rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
VECTYPES_INLINE CRectF CRectF::operator+(SIZEF size) const throw()
{ CRectF rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
VECTYPES_INLINE CRectF CRectF::operator-(SIZEF size) const throw()
{ CRectF rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
VECTYPES_INLINE CRectF CRectF::operator+(LPCRECTF lpRect) const throw()
{ CRectF rect(this); rect.InflateRect(lpRect); return rect; }
VECTYPES_INLINE CRectF CRectF::operator-(LPCRECTF lpRect) const throw()
{ CRectF rect(this); rect.DeflateRect(lpRect); return rect; }
VECTYPES_INLINE CRectF CRectF::operator&(const RECTF& rect2) const throw()
{ CRectF rect; ::IntersectRect(&rect, this, &rect2);
return rect; }
VECTYPES_INLINE CRectF CRectF::operator|(const RECTF& rect2) const throw()
{ CRectF rect; ::UnionRect(&rect, this, &rect2);
return rect; }
VECTYPES_INLINE BOOL CRectF::SubtractRect(LPCRECTF lpRectSrc1, LPCRECTF lpRectSrc2) throw()
{ return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }

VECTYPES_INLINE void CRectF::NormalizeRect() throw()
{
	REAL nTemp;
	if (left > right)
	{
		nTemp = left;
		left = right;
		right = nTemp;
	}
	if (top > bottom)
	{
		nTemp = top;
		top = bottom;
		bottom = nTemp;
	}
}

VECTYPES_INLINE void CRectF::InflateRect(LPCRECTF lpRect) throw()
{
	left -= lpRect->left;		top -= lpRect->top;
	right += lpRect->right;		bottom += lpRect->bottom;
}

VECTYPES_INLINE void CRectF::InflateRect(REAL l, REAL t, REAL r, REAL b) throw()
{
	left -= l;			top -= t;
	right += r;			bottom += b;
}

VECTYPES_INLINE void CRectF::DeflateRect(LPCRECTF lpRect) throw()
{
	left += lpRect->left;	top += lpRect->top;
	right -= lpRect->right;	bottom -= lpRect->bottom;
}

VECTYPES_INLINE void CRectF::DeflateRect(REAL l, REAL t, REAL r, REAL b) throw()
{
	left += l;		top += t;
	right -= r;		bottom -= b;
}

VECTYPES_INLINE CRectF CRectF::Multiply(REAL fMultiplier) const throw()
{
	return CRectF(
		left*fMultiplier,
		top*fMultiplier,
		right*fMultiplier,
		bottom*fMultiplier
		);
}


#endif	// _VECTYPES_INL__
