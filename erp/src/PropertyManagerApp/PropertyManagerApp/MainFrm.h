#pragma once 

#include "Pane/NavigatorBar.h"

class CPropertyManagerAppView;

class CMainFrame : public CXTPFrameWnd,CXTPOffice2007FrameHook
{
	DECLARE_MESSAGE_MAP()	
	DECLARE_DYNCREATE(CMainFrame)

public:
	CMainFrame(void);
	virtual ~CMainFrame(void);
 
	int GetActiveNavigator(void);

protected:
	CXTPStatusBar     m_wndStatusBar;

	CNavigatorBar	  m_wndNavigatorBar;
	CNavigatorBarSplitter m_wndSplitter;
	CXTPToolBar *m_pToolbar;
//	CXTPToolBar *m_pMapToolbar;
	CXTPDockingPaneManager m_paneManager;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCustomize(void);
	afx_msg LRESULT OnShortcutBarNotify(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnNavigatorBarMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMapToolbarCommand(UINT nCmd);
	afx_msg void OnClose(void);
	afx_msg void OnOptions(void);  
 
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	
	void CreateShortcutBar(void);

	void ShowMapButtons(BOOL bShow);
  

	CPropertyManagerAppView *m_pView;
};

inline int CMainFrame::GetActiveNavigator(void) {
	return 0;
}


