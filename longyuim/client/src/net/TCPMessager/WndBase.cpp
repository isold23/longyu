#include "stdafx.h"
#include "WndBase.h"
#include <list>
using namespace std;

static list<CWndBase*> s_hInstanceList;
CWndBase::CWndBase()
{
	m_hWndWindow = NULL;
	m_hWndWindow = AllocateHWnd(SelfWndProc);
	s_hInstanceList.push_back(this);
}
CWndBase::~CWndBase()
{
	s_hInstanceList.remove(this);
	DeallocateHWnd();
}
HWND CWndBase::AllocateHWnd(WNDPROC apWndProc)
{	
	BOOL m_bClassIsRegistered;
	WNDCLASS lpTempClass;
		
	MEMORY_BASIC_INFORMATION   mbi;   
	VirtualQuery((LPCVOID)SelfWndProc,&mbi,sizeof(mbi)); 
	HMODULE hModule = (HMODULE)mbi.AllocationBase;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;
	wcex.lpfnWndProc = apWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hModule;//(HINSTANCE)GetModuleHandle(NULL);
	wcex.hIcon = 0;
	wcex.hCursor = 0;
	wcex.hbrBackground = 0;
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"TPUtilWindow";
	wcex.hIconSm = 0;

	m_bClassIsRegistered = GetClassInfo(hModule/*(HINSTANCE)GetModuleHandle(NULL)*/, wcex.lpszClassName, &lpTempClass);
	if(!m_bClassIsRegistered || lpTempClass.lpfnWndProc != apWndProc)
	{
		if(m_bClassIsRegistered)
			UnregisterClass(lpTempClass.lpszClassName, hModule/*(HINSTANCE)GetModuleHandle(NULL)*/);
		RegisterClassEx(&wcex);
	}
	m_hWndWindow = CreateWindowEx(WS_EX_TOOLWINDOW, wcex.lpszClassName,
						L"", WS_POPUP, 0, 0, 0, 0, 0, 0, hModule/*(HINSTANCE)GetModuleHandle(NULL)*/, NULL);
	int i = GetLastError();

	return m_hWndWindow;

}
LRESULT CWndBase::DeallocateHWnd()
{
	if(m_hWndWindow != NULL)
		DestroyWindow(m_hWndWindow);
	return S_OK;
}
LRESULT CALLBACK CWndBase::SelfWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	list<CWndBase*>::iterator iter;
	for(iter = s_hInstanceList.begin(); iter != s_hInstanceList.end(); iter++)
	{
		if((*iter)->m_hWndWindow == hWnd)
			return (*iter)->WndProc(hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CWndBase::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}