

#ifndef __VECTYPES_H__
#define __VECTYPES_H__

#pragma once

#include <vector>
/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

typedef float REAL;

typedef struct tagSIZEF
{
	REAL cx;
	REAL cy;
} 	SIZEF;
typedef struct tagSIZEF *PSIZEF;
typedef struct tagSIZEF *LPSIZEF;

//typedef struct tagPOINTF
//{
//	REAL x;
//	REAL y;
//} 	POINTF;
typedef struct tagPOINTF *PPOINTF;
typedef struct tagPOINTF *LPPOINTF;

typedef struct tagRECTF
{
	REAL left;
	REAL top;
	REAL right;
	REAL bottom;
} 	RECTF;
typedef struct tagRECTF *PRECTF;
typedef struct tagRECTF *LPRECTF;
typedef const RECTF *LPCRECTF;

inline BOOL PtInRect(LPCRECTF lprc,POINTF pt) {
	return pt.x >= lprc->left && pt.x < lprc->right &&
		pt.y >= lprc->top && pt.y < lprc->bottom;
}

inline BOOL IsRectEmpty(LPCRECTF lprc) {
	return (lprc->right-lprc->left) <= 0.0f || lprc->bottom-lprc->top <= 0.0f;
}

inline BOOL SetRectEmpty(LPRECTF lprc) {
	lprc->left = lprc->top = lprc->right = lprc->bottom = 0.0f;
	return TRUE;
}

inline void CopyRect(LPRECTF lprcDst,CONST RECTF* lprcSrc) {
	*lprcDst = *lprcSrc;
}

inline BOOL EqualRect(LPCRECTF lprc1,LPCRECTF lprc2) {
	return lprc1->left == lprc2->left &&
		lprc1->top == lprc2->top &&
		lprc1->right == lprc2->right &&
		lprc1->bottom == lprc2->bottom;
}

inline BOOL SetRect(LPRECTF lprc,REAL xLeft,REAL yTop,REAL xRight,REAL yBottom) {
	lprc->left = xLeft;
	lprc->top = yTop;
	lprc->right = xRight;
	lprc->bottom = yBottom;
	return TRUE;
}

inline BOOL OffsetRect(LPRECTF lprc,REAL dx,REAL dy) {
	lprc->left += dx;
	lprc->right += dx;
	lprc->top += dy;
	lprc->bottom += dy;
	return TRUE;
}

inline BOOL InflateRect(LPRECTF lprc,REAL dx,REAL dy) {
	lprc->left -= dx;
	lprc->right += dx;
	lprc->top -= dy;
	lprc->bottom += dy;
	return TRUE;
}

inline BOOL IntersectRect(LPRECTF lprcDst,LPCRECTF lprcSrc1,LPCRECTF lprcSrc2) {
	lprcDst->right = min(lprcSrc1->right, lprcSrc2->right);
	lprcDst->bottom = min(lprcSrc1->bottom, lprcSrc2->bottom);
	lprcDst->left = max(lprcSrc1->left, lprcSrc2->left);
	lprcDst->top = max(lprcSrc1->top, lprcSrc2->top);

	return !::IsRectEmpty(lprcDst);
}


inline BOOL UnionRect(LPRECTF lprcDst,LPCRECTF lprcSrc1,LPCRECTF lprcSrc2) {
	lprcDst->right = max(lprcSrc1->right, lprcSrc2->right);
	lprcDst->bottom = max(lprcSrc1->bottom, lprcSrc2->bottom);
	lprcDst->left = min(lprcSrc1->left, lprcSrc2->left);
	lprcDst->top = min(lprcSrc1->top, lprcSrc2->top);
 
	return !::IsRectEmpty(lprcDst);
}

inline BOOL SubtractRect(LPRECTF lprcDst,LPCRECTF lprcSrc1,LPCRECTF lprcSrc2) {
	lprcDst->left = lprcSrc1->left - lprcSrc2->left;
	lprcDst->top = lprcSrc1->top - lprcSrc2->top;
	lprcDst->right = lprcSrc1->right - lprcSrc2->right;
	lprcDst->bottom = lprcSrc1->bottom - lprcSrc2->bottom;
	return TRUE;
}

class CSizeF;
class CPointF;
class CRectF;

/////////////////////////////////////////////////////////////////////////////
// CSizeF - An extent, similar to Windows SIZEF structure.

class CSizeF : public tagSIZEF
{
public:

	// Constructors
	// construct an uninitialized size
	CSizeF() throw();
	// create from two integers
	CSizeF(REAL initCX, REAL initCY) throw();
	// create from another size
	CSizeF(SIZEF initSize) throw();
	// create from a point
	CSizeF(POINTF initPt) throw();
 
	// Operations
	BOOL operator==(SIZEF size) const throw();
	BOOL operator!=(SIZEF size) const throw();
	void operator+=(SIZEF size) throw();
	void operator-=(SIZEF size) throw();
	void SetSize(REAL CX, REAL CY) throw();

	// Operators returning CSizeF values
	CSizeF operator+(SIZEF size) const throw();
	CSizeF operator-(SIZEF size) const throw();
	CSizeF operator-() const throw();

	// Operators returning CPointF values
	CPointF operator+(POINTF point) const throw();
	CPointF operator-(POINTF point) const throw();

	// Operators returning CRectF values
	CRectF operator+(const RECTF* lpRect) const throw();
	CRectF operator-(const RECTF* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CPointF - A 2-D point, similar to Windows POINTF structure.

class CPointF : public POINTF
{
public:
	// Constructors

	// create an uninitialized point
	CPointF() throw();
	// create from two integers
	CPointF(REAL initX, REAL initY) throw();
	// create from another point
	CPointF(POINTF initPt) throw();
	CPointF(POINT initPt) throw();
	// create from a size
	CPointF(SIZEF initSize) throw();
	// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
 

	// Operations

	// translate the point
	void Offset(REAL xOffset, REAL yOffset) throw();
	void Offset(POINTF point) throw();
	void Offset(SIZEF size) throw();
	void SetPoint(REAL X, REAL Y) throw();

	BOOL operator==(POINTF point) const throw();
	BOOL operator!=(POINTF point) const throw();
	void operator+=(SIZEF size) throw();
	void operator-=(SIZEF size) throw();
	void operator+=(POINTF point) throw();
	void operator-=(POINTF point) throw();

	// Operators returning CPointF values
	CPointF operator+(SIZEF size) const throw();
	CPointF operator-(SIZEF size) const throw();
	CPointF operator-() const throw();
	CPointF operator+(POINTF point) const throw();

	// Operators returning CSizeF values
	CSizeF operator-(POINTF point) const throw();

	// Operators returning CRectF values
	CRectF operator+(const RECTF* lpRect) const throw();
	CRectF operator-(const RECTF* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CRectF - A 2-D rectangle, similar to Windows RECTF structure.

class CRectF : public tagRECTF
{
	// Constructors
public:
	// uninitialized rectangle
	CRectF() throw();
	// from left, top, right, and bottom
	CRectF(REAL l, REAL t, REAL r, REAL b) throw();
	// copy constructor
	CRectF(const RECTF& srcRect) throw();
	// copy constructor
	CRectF(const RECT& srcRect) throw();
	// from a pointer to another rect
	CRectF(LPCRECTF lpSrcRect) throw();
	// from a point and size
	CRectF(POINTF point, SIZEF size) throw();
	// from two points
	CRectF(POINTF topLeft, POINTF bottomRight) throw();

	// Attributes (in addition to RECTF members)

	// retrieves the width
	REAL Width() const throw();
	// returns the height
	REAL Height() const throw();
	// returns the size
	CSizeF Size() const throw();
	// reference to the top-left point
	CPointF& TopLeft() throw();
	// reference to the bottom-right point
	CPointF& BottomRight() throw();
	// const reference to the top-left point
	const CPointF& TopLeft() const throw();
	// const reference to the bottom-right point
	const CPointF& BottomRight() const throw();
	// the geometric center point of the rectangle
	CPointF CenterPoint() const throw();
	// swap the left and right
	void SwapLeftRight() throw();
	static void WINAPI SwapLeftRight(LPRECTF lpRect) throw();

	// convert between CRectF and LPRECTF/LPCRECTF (no need for &)
	operator LPRECTF() throw();
	operator LPCRECTF() const throw();

	// returns TRUE if rectangle has no area
	BOOL IsRectEmpty() const throw();
	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const throw();
	// returns TRUE if point is within rectangle
	BOOL PtInRect(POINTF point) const throw();

	// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(REAL x1, REAL y1, REAL x2, REAL y2) throw();
	void SetRect(POINTF topLeft, POINTF bottomRight) throw();
	// empty the rectangle
	void SetRectEmpty() throw();
	// copy from another rectangle
	void CopyRect(LPCRECTF lpSrcRect) throw();
	// TRUE if exactly the same as another rectangle
	BOOL EqualRect(LPCRECTF lpRect) const throw();

	// Inflate rectangle's width and height by
	// x units to the left and right ends of the rectangle
	// and y units to the top and bottom.
	void InflateRect(REAL x, REAL y) throw();
	// Inflate rectangle's width and height by
	// size.cx units to the left and right ends of the rectangle
	// and size.cy units to the top and bottom.
	void InflateRect(SIZEF size) throw();
	// Inflate rectangle's width and height by moving individual sides.
	// Left side is moved to the left, right side is moved to the right,
	// top is moved up and bottom is moved down.
	void InflateRect(LPCRECTF lpRect) throw();
	void InflateRect(REAL l, REAL t, REAL r, REAL b) throw();

	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect(REAL x, REAL y) throw();
	void DeflateRect(SIZEF size) throw();
	void DeflateRect(LPCRECTF lpRect) throw();
	void DeflateRect(REAL l, REAL t, REAL r, REAL b) throw();

	// translate the rectangle by moving its top and left
	void OffsetRect(REAL x, REAL y) throw();
	void OffsetRect(SIZEF size) throw();
	void OffsetRect(POINTF point) throw();
	void NormalizeRect() throw();

	// absolute position of rectangle
	void MoveToY(REAL y) throw();
	void MoveToX(REAL x) throw();
	void MoveToXY(REAL x, REAL y) throw();
	void MoveToXY(POINTF point) throw();

	BOOL IntersectRect(LPCRECTF lpRect) throw();
	// set this rectangle to intersection of two others
	BOOL IntersectRect(LPCRECTF lpRect1, LPCRECTF lpRect2) throw();

	// set this rectangle to bounding union of two others
	BOOL UnionRect(LPCRECTF lpRect1, LPCRECTF lpRect2) throw();

	// set this rectangle to minimum of two others
	BOOL SubtractRect(LPCRECTF lpRectSrc1, LPCRECTF lpRectSrc2) throw();

	// Additional Operations
	void operator=(const RECTF& srcRect) throw();
	BOOL operator==(const RECTF& rect) const throw();
	BOOL operator!=(const RECTF& rect) const throw();
	void operator+=(POINTF point) throw();
	void operator+=(SIZEF size) throw();
	void operator+=(LPCRECTF lpRect) throw();
	void operator-=(POINTF point) throw();
	void operator-=(SIZEF size) throw();
	void operator-=(LPCRECTF lpRect) throw();
	void operator&=(const RECTF& rect) throw();
	void operator|=(const RECTF& rect) throw();

	// Operators returning CRectF values
	CRectF operator+(POINTF point) const throw();
	CRectF operator-(POINTF point) const throw();
	CRectF operator+(LPCRECTF lpRect) const throw();
	CRectF operator+(SIZEF size) const throw();
	CRectF operator-(SIZEF size) const throw();
	CRectF operator-(LPCRECTF lpRect) const throw();
	CRectF operator&(const RECTF& rect2) const throw();
	CRectF operator|(const RECTF& rect2) const throw();
	CRectF Multiply(REAL fMultiplier) const throw();
};

#define VECTYPES_INLINE inline
#include "vectypes.inl"


#endif // __VECTYPES_H__
