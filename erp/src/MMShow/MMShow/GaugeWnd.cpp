
#include "stdafx.h"
#include "Resource.h"
#include "GaugeWnd.h"
#include "DrawHelper.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static LPCTSTR WND_CLASSNAME = _T("GaugeWnd");


static const int DEF_BORDER_WIDTH = 10;
static const COLORREF CLR_BORDER = RGB(255,0,0);

static const COLORREF CLR_TRANSPARENT = RGB(255,0,255);
static const BYTE ALPHA_TRANSPARENT = 125;
 


CGaugeWnd::CGaugeWnd(void)
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInst, WND_CLASSNAME, &wndcls)))
	{
		wndcls.style            = CS_DBLCLKS;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = 0;
		wndcls.cbWndExtra		= 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH)COLOR_WINDOW;
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = WND_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}

	m_bShowManual = TRUE;
 
	m_clrBorder = CLR_BORDER;
	m_nBorderWidth = DEF_BORDER_WIDTH;
	m_nHitTest = Non;
	m_pHostWnd = NULL;

	m_rcWindow = CRect(0,0,0,0);
	m_ptTopLeft.x = m_ptTopLeft.y = 0.0f;
	m_ptBottomRight.x = m_ptBottomRight.y = 1.0f;;
}

CGaugeWnd::~CGaugeWnd(void)
{
}


BEGIN_MESSAGE_MAP(CGaugeWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN() 
	ON_WM_MOUSEACTIVATE()
	//ON_WM_SETCURSOR()
END_MESSAGE_MAP()

 


 
BOOL CGaugeWnd::Create(CWnd *pHostWnd,BOOL bTransparent,CWnd *pVisibleWnd)
{
	CWnd* pWnd = this;
	m_rcWindow = CWindowRect(pHostWnd);
	DWORD dwExtStyle = WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE;
	if (bTransparent)
		dwExtStyle |= WS_EX_LAYERED;
	if (!pWnd->CreateEx(dwExtStyle,WND_CLASSNAME,NULL, WS_POPUP,m_rcWindow,pHostWnd,NULL))
		return FALSE;

	ValidateRgn(m_rcWindow.Width(),m_rcWindow.Height());
	m_pHostWnd = pHostWnd;
	m_pVisibleWnd = (pVisibleWnd==NULL ? pHostWnd:pVisibleWnd);
	if (bTransparent)
		SetLayeredWindowAttributes(0,ALPHA_TRANSPARENT,LWA_ALPHA);

	m_bTransparent = bTransparent;
	return TRUE;
}

void CGaugeWnd::ResetWindowRect(const CRect &rc,BOOL bFromOuter)
{
	if (rc.right<0 && rc.bottom<0)
		return ;

	if (CWindowRect(this) != rc)
	{
		ValidateRgn(rc.Width(),rc.Height());
		MoveWindow(rc,FALSE);
		Invalidate();
		m_pHostWnd->Invalidate();
		m_rcWindow = rc;

		if (!bFromOuter)
		{
			CWindowRect rcHost(m_pHostWnd);
			m_ptTopLeft.x = (rc.left-rcHost.left)/(float)rcHost.Width();
			m_ptTopLeft.y = (rc.top-rcHost.top)/(float)rcHost.Height();
			m_ptBottomRight.x = (rc.right-rcHost.left)/(float)rcHost.Width();
			m_ptBottomRight.y = (rc.bottom-rcHost.top)/(float)rcHost.Height();
		}

		m_dwSampleTick = GetTickCount();
	}
}


void CGaugeWnd::ValidateRgn(int cx,int cy)
{
	CRect rc(0,0,cx,cy);
	CRgn rgn;
	rgn.CreateRectRgn(0,0,cx,cy);

	CRgn rgnHollow;
	rc.DeflateRect(m_nBorderWidth,m_nBorderWidth);
	rgnHollow.CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
	rgn.CombineRgn(&rgn,&rgnHollow,RGN_DIFF);

	SetWindowRgn(rgn,FALSE);
}


void CGaugeWnd::Show(BOOL bShow)
{
	if (bShow == IsWindowVisible())
		return;

	if (!bShow)
		ShowWindow(SW_HIDE);
	else if (m_bShowManual)
		SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE);
}

void CGaugeWnd::ShowManual(BOOL bShow)
{
	if (m_bShowManual != bShow)
	{
		m_bShowManual = bShow;
		if (bShow && m_pVisibleWnd->IsWindowVisible())
			SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE);
		if (!bShow && IsWindowVisible())
			ShowWindow(SW_HIDE);
	}
}

BOOL CGaugeWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	static HCURSOR curs[] = {
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE),	// TopLeft-BottomRight
		AfxGetApp()->LoadStandardCursor(IDC_SIZENS),	// Top-Bottom
		AfxGetApp()->LoadStandardCursor(IDC_SIZENESW),	// TopRight-BottomLeft	
		AfxGetApp()->LoadStandardCursor(IDC_SIZEWE),	// Let-Right
		AfxGetApp()->LoadStandardCursor(IDC_SIZEALL)	// Body	
	};

	nHitTest = m_nHitTest;
	if (m_nHitTest == 0)
		nHitTest = HitTest(CCurorPos(this));
	
	switch (nHitTest)
	{
	case TopLeft:
	case BottomRight:
		nHitTest = 1;
		break;
	case Top:
	case Bottom:
		nHitTest = 2;
		break;
	case BottomLeft:
	case TopRight:
		nHitTest = 3;
		break;
	case Left:
	case Right:
		nHitTest = 4;
		break;
	case Body:
		nHitTest = 5;
		break;
	default:
		nHitTest = 0;
		break;
	}
	
	SetCursor(curs[nHitTest]);
	return TRUE;
 }

static inline BOOL Near(CPoint pt1,CPoint pt2)
{
	CSize size = pt1 - pt2;
	return (size.cx*size.cx + size.cy*size.cy <= DEF_BORDER_WIDTH*DEF_BORDER_WIDTH);
}

int CGaugeWnd::HitTest(CPoint point)
{
	CRect rc(m_rcWindow);
	rc.MoveToXY(0,0);

	CPoint ptCenter = rc.CenterPoint();

	if (Near(rc.TopLeft(),point))
		return TopLeft;
	else if (Near(CPoint(ptCenter.x,rc.top),point))
		return Top;
	else if (Near(CPoint(rc.right,rc.top),point))
		return TopRight;
	else if (Near(CPoint(rc.right,ptCenter.y),point))
		return Right;
	else if (Near(rc.BottomRight(),point))
		return BottomRight;
	else if (Near(CPoint(ptCenter.x,rc.bottom),point))
		return Bottom;
	else if (Near(CPoint(rc.left,rc.bottom),point))
		return BottomLeft;
	else if (Near(CPoint(rc.left,ptCenter.y),point))
		return Left;
	else
		return Body;
}

BOOL CGaugeWnd::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CGaugeWnd::OnPaint(void)
{ 
	CPaintDC dc(this);

	/*CWindowRect*/CRect rc(m_rcWindow);
	rc.MoveToXY(0,0);
	dc.FillSolidRect(rc,m_clrBorder);

	CCircleSelector circleSelector(&dc);
	
	CPoint ptCenter= rc.CenterPoint();
	ptCenter -= CPoint(DEF_BORDER_WIDTH/2,DEF_BORDER_WIDTH/2);

	CRect rect(0,0,DEF_BORDER_WIDTH,DEF_BORDER_WIDTH);

	rc.BottomRight() -= CPoint(DEF_BORDER_WIDTH,DEF_BORDER_WIDTH);

	rect.MoveToXY(rc.TopLeft());
	dc.Rectangle(rect);

	rect.MoveToXY(CPoint(ptCenter.x,rc.top));
	dc.Rectangle(rect);

	rect.MoveToXY(CPoint(rc.right,rc.top));
	dc.Rectangle(rect);

	rect.MoveToXY(CPoint(rc.right,ptCenter.y));
	dc.Rectangle(rect);

	rect.MoveToXY(rc.BottomRight());
	dc.Rectangle(rect);

	rect.MoveToXY(CPoint(ptCenter.x,rc.bottom));
	dc.Rectangle(rect);

	rect.MoveToXY(CPoint(rc.left,rc.bottom));
	dc.Rectangle(rect);

	rect.MoveToXY(CPoint(rc.left,ptCenter.y));
	dc.Rectangle(rect);
}




void CGaugeWnd::SetBorder(COLORREF clr)
{
	if (m_clrBorder != clr)
	{
		m_clrBorder = clr;

		if (GetSafeHwnd() != NULL)
			Invalidate(FALSE);
	}
}
 


void CGaugeWnd::OnLButtonDown(UINT nFlags,CPoint point)
{
	m_nHitTest = HitTest(point);
	m_ptCapture = point;
	SetCapture();
	
	CWindowRect rc(m_pHostWnd);
	ClipCursor(&rc);
	CWnd::OnLButtonDown(nFlags,point);
}

void CGaugeWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nHitTest = Non;
	ReleaseCapture();
	ClipCursor(NULL);
	m_pHostWnd->SetActiveWindow();
	CWnd::OnLButtonUp(nFlags,point);
}

void CGaugeWnd::OnDrag(CPoint point)
{
	if (m_nHitTest != Non)
	{
		CRect rc(m_rcWindow);
		CWindowRect rcRef(m_pHostWnd);
		CSize offset(point-m_ptCapture);

	 	switch (m_nHitTest)
		{
		case TopLeft:
			rc.TopLeft() += offset;
			break;
		case Top:
			rc.top += offset.cy;
			break;
		case TopRight:
			rc.top += offset.cy;
			rc.right += offset.cx;
			m_ptCapture.x = point.x;
			break; 
		case Right:
			rc.right += offset.cx;
			m_ptCapture.x = point.x;
			break;
		case BottomRight:
			rc.BottomRight() += offset;
			m_ptCapture = point;
			break;
		case Bottom:
			rc.bottom += offset.cy;
			m_ptCapture.y = point.y;
			break;
		case BottomLeft:
			rc.left += offset.cx;
			rc.bottom += offset.cy;
			m_ptCapture.y = point.y;
			break;
		case Left:
			rc.left += offset.cx;
			break;
		case Body: 
			rc.OffsetRect(offset);
			if (rc.left < rcRef.left)
			{
				rc.left = rcRef.left;
				rc.right = rc.left + m_rcWindow.Width();
			}
			else if (rc.right > rcRef.right)
			{
				rc.right = rcRef.right;
				rc.left = rc.right- m_rcWindow.Width();
			} 

			if(rc.top < rcRef.top)
			{
				rc.top = rcRef.top;
				rc.bottom = rc.top + m_rcWindow.Height();
			}
			else if (rc.bottom > rcRef.bottom)
			{
				rc.bottom = rcRef.bottom;
				rc.top = rc.bottom - m_rcWindow.Height();
			} 

			break;
		}

		if (m_nHitTest != Body)
		{
			int nMinWidth = m_nBorderWidth*3;
			if (m_nHitTest&Left && rc.Width()<nMinWidth)
				rc.left = rc.right-nMinWidth;

			if (m_nHitTest&Right && rc.Width()<nMinWidth)
				rc.right = rc.left + nMinWidth;

			if (m_nHitTest&Top && rc.Height()<nMinWidth)
				rc.top = rc.bottom - nMinWidth;

			if (m_nHitTest&Bottom && rc.Height()<nMinWidth)
				rc.bottom = rc.top + nMinWidth;

			if (rc.left < rcRef.left)
				rc.left = rcRef.left;
			if (rc.top < rcRef.top)
				rc.top= rcRef.top;
			if (rc.right > rcRef.right)
				rc.right = rcRef.right;
			if (rc.bottom > rcRef.bottom)
				rc.bottom = rcRef.bottom;
		}

		ResetWindowRect(rc);
	}
}

void CGaugeWnd::RecalcWindowRect(void)
{
	CRect rc;
	CWindowRect rcHost(m_pHostWnd);

	rc.left = rcHost.left + (long)(rcHost.Width()*m_ptTopLeft.x);
	rc.top = rcHost.top + (long)(rcHost.Height()*m_ptTopLeft.y);
	rc.right =  rcHost.left + (long)(rcHost.Width()*m_ptBottomRight.x);
	rc.bottom =  rcHost.top + (long)(rcHost.Height()*m_ptBottomRight.y);

	ResetWindowRect(rc,TRUE);
}

void CGaugeWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	OnDrag(point);
	CWnd::OnMouseMove(nFlags,point);
}

int CGaugeWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE;
}
 