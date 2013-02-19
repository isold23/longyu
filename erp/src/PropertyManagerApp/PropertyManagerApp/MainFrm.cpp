
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PropertyManagerApp.h"
#include "PropertyManagerAppView.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMainFrame, CXTPFrameWnd)

 
BEGIN_MESSAGE_MAP(CMainFrame, CXTPFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(XTP_ID_CUSTOMIZE, &CMainFrame::OnCustomize)  
	ON_MESSAGE(XTPWM_SHORTCUTBAR_NOTIFY, &CMainFrame::OnShortcutBarNotify)
	ON_COMMAND_RANGE(ID_MAP_NON,ID_MAP_ERASE,&CMainFrame::OnMapToolbarCommand)
	ON_COMMAND(ID_OPTIONS,&CMainFrame::OnOptions) 
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,          
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
 
CMainFrame::CMainFrame(void)
	:m_pView(NULL),
	 m_pToolbar(NULL)/*,
	 m_pMapToolbar(NULL)*/
{
}

CMainFrame::~CMainFrame(void)
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{ 
	if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this))
		return -1;

	if (!m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
		return -1;
	
	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return -1;


	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(CTinyString(IDS_MENUBAR), IDR_MAINFRAME);
	if(pMenuBar == NULL)
		return -1;

	m_pToolbar = (CXTPToolBar*) pCommandBars->Add(CTinyString(IDS_STANDARD), xtpBarTop);
	if (!m_pToolbar || !m_pToolbar->LoadToolBar(IDR_MAINFRAME))
		return -1;
	m_pToolbar->ShowTextBelowIcons();
	m_pToolbar->EnableCustomization(FALSE);
	  
	//m_pMapToolbar = (CXTPToolBar*) pCommandBars->Add(CTinyString(IDS_MAP), xtpBarTop);
	//if (!m_pMapToolbar || !m_pMapToolbar->LoadToolBar(IDR_MAP))
	//	return -1;
	//m_pMapToolbar->ShowTextBelowIcons(); 

 
 
	pCommandBars->GetCommandBarsOptions()->bAlwaysShowFullMenus = FALSE;
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);
 
	LoadCommandBars(_T("CommandBars"));
 	m_paneManager.InstallDockingPanes(this);

	CXTPPaintManager::SetTheme(xtpThemeRibbon);

	m_wndNavigatorBar.SetTheme(xtpShortcutThemeOffice2007);

//	EnableOffice2007Frame(GetCommandBars());
 
	m_wndNavigatorBar.SetBindWnd(&m_pView->GetMapWnd(),&m_pView->GetListDlg(),
		&m_pView->GetBkgndDlg(),&m_pView->GetPicCtrl());

	return 0;
}
 
 
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	m_wndNavigatorBar.Create(&m_wndSplitter,CRect(0,0,0,0),m_wndSplitter.IdFromRowCol(0,0));


	m_wndSplitter.SetColumnInfo(0, 250,0);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CPropertyManagerAppView),CSize(0,0),pContext);

	m_pView = (CPropertyManagerAppView*)m_wndSplitter.GetPane(0,1);
	ASSERT(m_pView != NULL);
 

	return TRUE;
}

  
void CMainFrame::OnClose(void)
{
	if (m_wndNavigatorBar.BeforeClose())
	{
		CXTPFrameWnd::OnClose();
	}
	else
	{
		m_wndNavigatorBar.SetFocus();
		PostMessage(WM_CLOSE);
	}

}

 
 

void CMainFrame::OnCustomize(void)
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		CXTPCustomizeSheet dlg(pCommandBars);

		CXTPCustomizeKeyboardPage pageKeyboard(&dlg);
		dlg.AddPage(&pageKeyboard);
		pageKeyboard.AddCategories(IDR_MAINFRAME);

		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_MAINFRAME);
 
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
		pCommands->InsertNewMenuCategory();

		dlg.DoModal();
	}
}

void CMainFrame::OnMapToolbarCommand(UINT nCmd)
{
	m_pView->OnMapToolbarCommand(nCmd);
}

 
void CMainFrame::ShowMapButtons(BOOL bShow)
{
	BOOL bMapCtrl = FALSE;
	for (int i=0,cnt=m_pToolbar->GetControlCount(); i<cnt; ++i)
	{
		CXTPControl *pCtrl = m_pToolbar->GetControl(i);
		if (!bMapCtrl && pCtrl->GetID()==IDR_EMPTY)
			bMapCtrl = TRUE;

		if (bMapCtrl)
			pCtrl->SetVisible(bShow);
	}
}

LRESULT CMainFrame::OnShortcutBarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case XTP_SBN_MINIMIZEBUTTONCLICKED:
		{
			m_wndSplitter.SetColumnInfo(0, m_wndNavigatorBar.IsShortcutBarMinimized() ? 250 : 32, 0);
			m_wndSplitter.RecalcLayout();
		}
		return TRUE;

	case XTP_SBN_SELECTION_CHANGED:
		{
			CXTPShortcutBarItem* pItem = (CXTPShortcutBarItem*)lParam;
			if (pItem!=NULL && m_pView!=NULL)
			{
				CWnd *pActiveChild = m_pView->GetActiveChild();
				CWnd *pToActiveChild = (CWnd*)pItem->GetItemData();
				
				if (pActiveChild != pToActiveChild)
				{
					if (pActiveChild == &m_pView->GetMapWnd())
						ShowMapButtons(FALSE);
					if (pToActiveChild == &m_pView->GetMapWnd())
						ShowMapButtons(TRUE);
					m_pView->SetActiveChild(pToActiveChild);
				}
			}
		}
		return TRUE;
	}
	return 0;
} 

void CMainFrame::OnOptions(void)
{ 
}


