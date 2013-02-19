#pragma once

#include "InfoWnd.h"
 
class CCopyScreenWnd : public CWindowImpl<CCopyScreenWnd>
{
	class CNonWnd : public CWindowImpl<CNonWnd>
	{
		BEGIN_MSG_MAP(CNonWnd)  
		END_MSG_MAP()
	};

	static const int MARK_SIZE = 4;
	enum Tracking { Non =0,TopLeft,Top,TopRight,Right,BottomRight,Bottom,BottomLeft,Left,Body,NEW };

	BEGIN_MSG_MAP(CCopyScreenWnd) 
		MESSAGE_HANDLER(WM_NCCREATE,OnNcCreate) 
		MESSAGE_HANDLER(WM_PAINT,OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND,OnEraseBkgnd)
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONDOWN,OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP,OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnLButtonDBClick)
		MESSAGE_HANDLER(WM_KEYDOWN,OnKeyDown)
		MESSAGE_HANDLER(WM_SETCURSOR,OnSetCursor)
	END_MSG_MAP()

public:
	CCopyScreenWnd(void);
	~CCopyScreenWnd(void);

	BOOL Create(void);
	void Show(BOOL bShow=TRUE);
private: 
	LRESULT OnNcCreate(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnDestroy(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnPaint(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnMouseMove(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnLButtonDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnLButtonUp(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnLButtonDBClick(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnKeyDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnSetCursor(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);

	void OnDraw(HDC hDC);
	void Rect(HDC hDC,const RECT &rc);
	BOOL HasTrack(void) const;
	void EmptyTrack(void);

	void DrawTrack(HDC hDC);
	void DrawMark(HDC hDC,int x,int y);

	int HitTestTrackRect(int x,int y);
	BOOL PtInMark(int xCircle,int yCirlce,int x,int y);
	HCURSOR GetTrackCursor(int nHitTest);

	CNonWnd m_wndNon;
	CInfoWnd m_wndInfo;

	HBITMAP m_hScreenBmp;
 
	POINT m_ptTracking;
	int m_Tracking;
	RECT m_rcTrack;
};



 
inline BOOL CCopyScreenWnd::HasTrack(void) const {
	return (m_rcTrack.left != -INT_MAX);
}

inline void CCopyScreenWnd::EmptyTrack(void) {
	m_rcTrack.left = -INT_MAX;
}

