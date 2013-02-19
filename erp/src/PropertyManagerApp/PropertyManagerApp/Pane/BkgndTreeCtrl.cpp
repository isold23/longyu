#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "BkgndTreeCtrl.h"
#include "DrawHelper.h"
#include "NavigatorBar.h"
#include "../BkgndDlgs/BkgndDlg.h"



CBkgndTreeCtrl::CBkgndTreeCtrl(void)
{
}

CBkgndTreeCtrl::~CBkgndTreeCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CBkgndTreeCtrl, CPaneTreeCtrl)
	ON_WM_CREATE()  
END_MESSAGE_MAP()



int CBkgndTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nRet = CPaneTreeCtrl::OnCreate(lpCreateStruct);
	if (nRet < 0)
		return nRet;

	SetItemHeight(ICON_CY*3/2);

	m_imageList.Create(ICON_CX,ICON_CY,ILC_MASK|ILC_COLOR32,0,11);


	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_BKGND)); 
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_OPS));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_GRADE));	
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_USERS));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_PWD));

	SetImageList(&m_imageList,TVSIL_NORMAL);

	HTREEITEM hRootItem = InsertItem(CTinyString(IDC_BTN_BKGNDMAIN),0,0);
	SetItemData(hRootItem,IDC_BTN_BKGNDMAIN);

	UINT cmds[] = { IDC_BTN_LVLMGR,IDC_BTN_OPMGR,IDC_BTN_GROUPMGR,IDC_BTN_USERMGR,IDC_CHK_CHANGE_PWD };
	for (int i=1; i<_countof(cmds); ++i)
	{
		HTREEITEM hTreeItem = InsertItem(CTinyString(cmds[i]),i,i,hRootItem);
		SetItemData(hTreeItem,cmds[i]);
	}

	Expand(hRootItem,TVE_EXPAND);
	SelectItem(hRootItem);

	ModifyStyle(0,TVS_FULLROWSELECT); 
	
	return nRet;
}
 
  
