#pragma once 
#include <atlbase.h>
#include <atlwin.h>

class CInfoWnd : public CWindowImpl<CInfoWnd>
{
	BEGIN_MSG_MAP(CInfoWnd) 
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		MESSAGE_HANDLER(WM_PAINT,OnPaint)
		//MESSAGE_HANDLER(WM_ERASEBKGND,OnEraseBkgnd)
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnMouseMove)
		MESSAGE_HANDLER(WM_KEYDOWN,OnKeyDown)
	END_MSG_MAP()

public:
	CInfoWnd(CWindow *pNotifyWnd,BOOL bLeft = TRUE);
	~CInfoWnd(void);

	void UpdatePos(const POINT* pt = NULL);
private:
	LRESULT OnCreate(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnPaint(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnMouseMove(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnKeyDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	void CalcRect(void);

	CWindow *m_pNotifyWnd;
	BOOL m_bLeft;
	RECT m_rcWnd;
};
