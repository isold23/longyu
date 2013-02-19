#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "MapListbox.h"
#include "DrawHelper.h"
#include "NavigatorBar.h"
#include "../MapWnd/MapWnd.h"

 

CMapListbox::CMapListbox()
	:CPaneTreeCtrl(FALSE) 
{

}

CMapListbox::~CMapListbox(void)
{
}
 
BEGIN_MESSAGE_MAP(CMapListbox, CPaneTreeCtrl)
	ON_WM_CREATE() 	 
END_MESSAGE_MAP()
 
 

int CMapListbox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nRet = CPaneTreeCtrl::OnCreate(lpCreateStruct);
	if (nRet < 0)
		return nRet;
 

	m_imageList.Create(ICON_CX,ICON_CY,ILC_MASK|ILC_COLOR32,0,11);
 	SetImageList(&m_imageList,TVSIL_NORMAL);

	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HOUSE));
	HTREEITEM hRootItem = InsertItem(CTinyString(IDS_BUILDING),0,0); 
	SetItemData(hRootItem,IDC_BTN_BKGNDMAIN);

	UINT cmds[] = { IDS_WAY,IDS_GREEN,IDS_ELECTRONIC,IDS_WATER,IDS_WARM,IDS_OTHER };
	for (int i=1; i<_countof(cmds); ++i)
	{
		m_imageList.Add(AfxGetApp()->LoadIcon(cmds[i]));
		HTREEITEM hTreeItem = InsertItem(CTinyString(cmds[i]),i,i,hRootItem);
		SetItemData(hTreeItem,cmds[i]);
	}

	Expand(hRootItem,TVE_EXPAND);
	SelectItem(hRootItem);
	ModifyStyle(0,TVS_FULLROWSELECT); 

	SetItemHeight(80);
 
	return nRet;
}
  
 
 