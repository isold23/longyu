#pragma once
#include <windows.h>
class CWndBase
{
private:
	HWND AllocateHWnd(WNDPROC apWndProc);
	LRESULT DeallocateHWnd();
	static LRESULT CALLBACK SelfWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	HWND m_hWndWindow;
	CWndBase();
	virtual ~CWndBase();
	virtual LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};