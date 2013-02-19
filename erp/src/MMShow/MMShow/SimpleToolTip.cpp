#include "stdafx.h"
#include "SimpleToolTip.h"
#include "DrawHelper.h"
 

const int DELAY_TIME = 100;
const int DURATION_TIME = 3000;

const int TIMER_ID = 1;

const int BORDER_WIDHT = 5;
const int WND_OFFSET	= 2;

enum STATUS{IDLE,DELAY,DURATION};

static LPCTSTR ClassName;

CSimpleToolTip::CSimpleToolTip(void)
{

}

CSimpleToolTip::~CSimpleToolTip(void)
{
}

BOOL CSimpleToolTip::Create(void)
{
	return CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,AfxRegisterWndClass(CS_DBLCLKS),
		NULL,WS_POPUP,CRect(0,0,0,0),AfxGetMainWnd(),NULL,NULL);
}

BEGIN_MESSAGE_MAP(CSimpleToolTip,CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


void CSimpleToolTip::ShowTip(CWnd *pRefWnd,const CString &strTip)
{
	m_pRefWnd = pRefWnd;
	m_strTip = strTip;

	if (m_status != IDLE)
	{
		Show(FALSE);
		KillTimer(TIMER_ID);
	}

	if (!m_strTip.IsEmpty())
	{
		m_status = DELAY;
		SetTimer(TIMER_ID,DELAY_TIME,NULL);
	}
}

void CSimpleToolTip::UpdateTip(CWnd *pRefWnd,const CString &strTip)
{
	if (m_pRefWnd == pRefWnd)
	{
		ShowTip(pRefWnd,strTip);
	}
}

void CSimpleToolTip::CancelTip(CWnd *pRefWnd)
{
	//if (pRefWnd==NULL || pRefWnd==m_pRefWnd)
	//	if (m_status != IDLE)
	//	{
	//		m_status = IDLE;
	//		KillTimer(TIMER_ID);
	//		Show(FALSE);
	//	}
}



 
 
void CSimpleToolTip::OnPaint(void)
{
	CPaintDC dc(this);
	CClientRect rc(this);

	CPen pen(PS_SOLID,1,RGB(200,200,200));
	dc.SelectObject(&pen);
	dc.SelectObject(GetSysColorBrush(COLOR_INFOBK));
	dc.Rectangle(rc);

	dc.SelectObject(GetParent()->GetFont());

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor((GetSysColor(COLOR_INFOTEXT)));

	CRect rect;
	rect.SetRectEmpty();
	dc.DrawText(m_strTip,rect,DT_CALCRECT);

	rect.OffsetRect(rc.CenterPoint()-rect.CenterPoint());
	dc.DrawText(m_strTip,rect,DT_WORDBREAK);
}

void CSimpleToolTip::OnTimer(UINT nIDEvent)
{
	ASSERT(nIDEvent == TIMER_ID);
	
	switch(m_status)
	{
	case DELAY:
		m_status = DURATION;
		KillTimer(TIMER_ID);
		Show(TRUE);
		SetTimer(TIMER_ID,DURATION_TIME,NULL);
		break;
	case DURATION:
		m_status = IDLE;
		KillTimer(TIMER_ID);
		Show(FALSE);
		break;
	}
	CWnd::OnTimer(nIDEvent);
}

void CSimpleToolTip::Show(BOOL bShow)
{
	if (!bShow)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CRect rc;
		rc.SetRectEmpty();

		CClientDC dc(this);
		dc.SelectObject(GetParent()->GetFont());

		dc.DrawText(m_strTip,rc,DT_CALCRECT);
		rc.InflateRect(BORDER_WIDHT,BORDER_WIDHT);

		CWindowRect rect(m_pRefWnd);
		rc.top = rect.top - rc.Height();
		rc.bottom = rect.top;

		int nWidth = rc.Width();
		rc.left = rect.left + (rect.Width()-nWidth)/2;
		rc.right = rc.left + nWidth;

		SetWindowPos(&CWnd::wndTop,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,
					SWP_SHOWWINDOW|SWP_NOACTIVATE|SWP_NOZORDER);

		RedrawWindow();
	}
}

void CSimpleToolTip::OnLButtonDown(UINT nFlags,CPoint point)
{
	Show(FALSE);
	CWnd::OnLButtonDown(nFlags,point);
}

void CSimpleToolTip::OnKillFocus(CWnd* pNewWnd)
{
	Show(FALSE);
	CWnd::OnKillFocus(pNewWnd);
}

BOOL CSimpleToolTip::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

int CSimpleToolTip::OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message)
{
	return MA_NOACTIVATE;
}
