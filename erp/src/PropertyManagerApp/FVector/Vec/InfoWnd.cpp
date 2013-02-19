#include "StdAfx.h"
#include "InfoWnd.h"


CInfoWnd::CInfoWnd(CWindow *pNotifyWnd,BOOL bLeft)
	:m_pNotifyWnd(pNotifyWnd),
	 m_bLeft(bLeft)
{ 
}

CInfoWnd::~CInfoWnd(void)
{
}

LRESULT CInfoWnd::OnCreate(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
 	CalcRect(); 
	 SetWindowPos(NULL,m_rcWnd.left,m_rcWnd.top,m_rcWnd.right-m_rcWnd.left,m_rcWnd.bottom-m_rcWnd.top,0);
	return 0;
}


LRESULT CInfoWnd::OnPaint(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

 
	//HDC hMemDC = ::CreateCompatibleDC(hDC);

	//HBITMAP hBmp = ::LoadBitmap(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_INFOBK));
	//BITMAP bmp;
	//::GetObject(hBmp,sizeof(BITMAP),&bmp);

	//::SelectObject(hMemDC,hBmp);
	//::StretchBlt(hDC,0,0,m_rcWnd.right-m_rcWnd.left,m_rcWnd.bottom-m_rcWnd.top,
	//		hMemDC,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);

	//::DeleteObject(hBmp);
	//::DeleteDC(hMemDC);
	 
	

	EndPaint(&ps);
	return 0;
}

LRESULT CInfoWnd::OnEraseBkgnd(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	return TRUE;
}
 
void CInfoWnd::UpdatePos(const POINT* pt)
{
	if (pt == NULL || ::PtInRect(&m_rcWnd,*pt))
	{
		m_bLeft = !m_bLeft;
		CalcRect();
		SetWindowPos(NULL,m_rcWnd.left,m_rcWnd.top,m_rcWnd.right-m_rcWnd.left,m_rcWnd.bottom-m_rcWnd.top,0);
	}

}

LRESULT CInfoWnd::OnMouseMove(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	UpdatePos();
	return 0;
}

LRESULT CInfoWnd::OnKeyDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	if (wParam == VK_ESCAPE)
		m_pNotifyWnd->PostMessage(uMsg,wParam,lParam);
	return 0;
}




void CInfoWnd::CalcRect(void)
{
	const int CX = 100;
	const int CY = 100;

	if (m_bLeft)
	{
		m_rcWnd.left = m_rcWnd.top = 0;
		m_rcWnd.right = CX;
		m_rcWnd.bottom = CY;
	}
	else
	{
		int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);
		int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);

		m_rcWnd.left = cxScreen - CX;
		m_rcWnd.top = 0;
		m_rcWnd.right = cxScreen;
		m_rcWnd.bottom = CY;
	}
}