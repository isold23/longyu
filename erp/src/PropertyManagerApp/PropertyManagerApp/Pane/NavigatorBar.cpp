#include "StdAfx.h"
#include "../Resource.h"
#include "NavigatorBar.h"
#include "DrawHelper.h"

#include "../MapWnd/MapWnd.h"
#include "../PictureCtrl.h"
#include "../ListDlgs/ListDlg.h"
#include "../BkgndDlgs/BkgndDlg.h"

CNavigatorBar::CNavigatorBar(void)
{
}

CNavigatorBar::~CNavigatorBar(void)
{
}

BEGIN_MESSAGE_MAP(CNavigatorBar,CXTPShortcutBar) 
END_MESSAGE_MAP()
 


BOOL CNavigatorBar::Create(CWnd* pParentWnd, const RECT& rect, UINT nID)
{
	
	CWnd *pOwner = pParentWnd->GetParent();

	const int ICON_CX = 32;
	const int ICON_CY = 32;
	const UINT shortcuts[] = { ID_MAP_MODE, ID_LIST_MODE, ID_ENGINEER_MODE, ID_BKGND_MANAGER };
	
	CImageList imagelist;
	imagelist.Create(ICON_CX,ICON_CY,ILC_MASK|ILC_COLOR32,0,11);
	for (int i=0; i<_countof(shortcuts); ++i)
		imagelist.Add(AfxGetApp()->LoadIcon(shortcuts[i]));
	XTPImageManager()->SetIcons(imagelist, (UINT*)shortcuts,_countof(shortcuts), CSize(ICON_CX, ICON_CY));

	CXTPShortcutBar::Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,pParentWnd,nID);
	CXTPShortcutBar::SetOwner(pOwner);
	CXTPShortcutBar::GetToolTipContext()->SetStyle(xtpToolTipOffice);

	VERIFY(m_mapListboxPane.Create(CTinyString(ID_MAP_MODE), this));
	VERIFY(m_listTreeCtrlPane.Create(CTinyString(ID_LIST_MODE), this));
	VERIFY(m_engineerListboxPane.Create(CTinyString(ID_ENGINEER_MODE), this));
	VERIFY(m_bkgndListboxPane.Create(CTinyString(ID_BKGND_MANAGER), this));
 
 
	CXTPEmptyRect rectDummy;
 
	CString str;

	VERIFY(m_mapListbox.Create(WS_CHILD|WS_VISIBLE|TVS_NOHSCROLL|TVS_SHOWSELALWAYS ,rectDummy,&m_mapListboxPane,ID_MAP_MODE));
	VERIFY(m_listPane.Create(CListPane::IDD,&m_listTreeCtrlPane));
	VERIFY(m_engineerListbox.Create(WS_CHILD|WS_VISIBLE,rectDummy,&m_engineerListboxPane,ID_ENGINEER_MODE)); 
	VERIFY(m_bkgndTreeCtrl.Create(WS_CHILD|WS_VISIBLE|TVS_NOHSCROLL|TVS_SHOWSELALWAYS ,rectDummy,&m_bkgndListboxPane,ID_MAP_MODE));
 

	m_mapListboxPane.SetIndent(0,0,0,0);
	m_mapListboxPane.AddItem(CTinyString(ID_MAP_MODE),&m_mapListbox,0)->ShowCaption(FALSE);

	m_listTreeCtrlPane.SetIndent(0,0,0,0);
	m_listTreeCtrlPane.AddItem(CTinyString(ID_LIST_MODE),&m_listPane,0)->ShowCaption(FALSE);
		
	m_engineerListboxPane.SetIndent(0,0,0,0);
	m_engineerListboxPane.AddItem(CTinyString(ID_LIST_MODE),&m_engineerListbox,0)->ShowCaption(FALSE);
		
	m_bkgndListboxPane.SetIndent(0,0,0,0);
	m_bkgndListboxPane.AddItem(CTinyString(ID_LIST_MODE),&m_bkgndTreeCtrl,0)->ShowCaption(FALSE);

	CXTPShortcutBar::GetNavigationPaneItem()->SetCaption(CTinyString(IDS_NAVIGATOR));

	CXTPShortcutBarItem* pItemMap = CXTPShortcutBar::AddItem(ID_MAP_MODE, &m_mapListboxPane);
	CXTPShortcutBar::AddItem(ID_LIST_MODE, &m_listTreeCtrlPane);
	CXTPShortcutBar::AddItem(ID_ENGINEER_MODE,&m_engineerListboxPane);
	CXTPShortcutBar::AddItem(ID_BKGND_MANAGER,&m_bkgndListboxPane);
 
	CXTPShortcutBar::AllowMinimize(TRUE);
	CXTPShortcutBar::ShowMinimizeButton(TRUE);

	CXTPShortcutBar::SelectItem(pItemMap);
	CXTPShortcutBar::SetExpandedLinesCount(CXTPShortcutBar::GetItemCount());

	return TRUE;
}

void CNavigatorBar::SetBindWnd(CMapWnd *pMapWnd,CListDlg *pListDlg,CBkgndDlg *pBkgndDlg,CPictureCtrl *pPicCtrl)
{
	CXTPShortcutBar::GetItem(0)->SetItemData((DWORD_PTR)(CWnd*)pMapWnd);
	CXTPShortcutBar::GetItem(1)->SetItemData((DWORD_PTR)(CWnd*)pListDlg);
	CXTPShortcutBar::GetItem(2)->SetItemData((DWORD_PTR)(CWnd*)pPicCtrl);
	CXTPShortcutBar::GetItem(3)->SetItemData((DWORD_PTR)(CWnd*)pBkgndDlg);

	m_mapListbox.SetTargetCmdWnd(pMapWnd);
	m_listPane.SetBindWnd(pListDlg);
	m_engineerListbox.SetBindWnd(pPicCtrl);
	m_bkgndTreeCtrl.SetTargetCmdWnd(pBkgndDlg);
}
 
BOOL CNavigatorBar::BeforeClose(void)
{
	CXTPShortcutBarItem *pItem = CXTPShortcutBar::GetNavigationPaneItem();
	if (!pItem->IsExpanded())
		return TRUE;
	
	SetFocus();
	return FALSE;
}

 
void CNavigatorBarSplitter::TrackColumnSize(int x, int col)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);

	CPoint pt(x, 0);
	ClientToScreen(&pt);
	GetPane(0, col)->ScreenToClient(&pt);
	m_pColInfo[col].nIdealSize = pt.x;     
	if (pt.x < MIN_WIDTH)
		m_pColInfo[col].nIdealSize = MIN_WIDTH; 
}

