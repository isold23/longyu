#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListPane.h"
#include "../ListDlgs/ListDlg.h"
#include "DrawHelper.h"

	



CListPane::CListPane(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CListPane::IDD, pParent),
		m_pListDlg(NULL)
{

}

CListPane::~CListPane(void)
{
}

void CListPane::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CMD, m_btnCmd);
	DDX_Control(pDX, IDC_BTN_DETAILS, m_btnDetails);
	DDX_Control(pDX, IDC_TREE_CMD, m_treeCmd);
	DDX_Control(pDX, IDC_TREE_DETAILS, m_treeDetails);
}


BEGIN_MESSAGE_MAP(CListPane, CXTPResizeDialog) 
	ON_BN_CLICKED(IDC_BTN_CMD, &CListPane::OnBnClickedBtnCmd)
	ON_BN_CLICKED(IDC_BTN_DETAILS, &CListPane::OnBnClickedBtnDetails) 
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DETAILS, &CListPane::OnNMClickTreeDetails)
END_MESSAGE_MAP()

void CListPane::SetBindWnd(CListDlg *pListDlg)
{
	m_pListDlg = pListDlg;
	m_treeCmd.SetTargetCmdWnd(pListDlg);
}

BOOL CListPane::OnInitDialog(void)
{
	CXTPResizeDialog::OnInitDialog();

	SetResize(IDC_BTN_CMD,XTP_ANCHOR_BOTTOMLEFT,XTP_ANCHOR_BOTTOMCENTER);
	SetResize(IDC_BTN_DETAILS,XTP_ANCHOR_BOTTOMCENTER,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_TREE_CMD,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_TREE_DETAILS,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);

	InitTrees();

	m_btnCmd.SetIcon(CSize(32,32),IDI_MANAGER);
	m_btnDetails.SetIcon(CSize(32,32),ID_LIST_HOME);
	return TRUE;
}

void CListPane::InitTrees(void)
{
	int i;
	CString str; 

	m_ilDetails.Create(24,24,ILC_MASK|ILC_COLOR32,0,11);
	m_ilDetails.Add(AfxGetApp()->LoadIcon(ID_LIST_PROJECT));
	m_ilDetails.Add(AfxGetApp()->LoadIcon(ID_LIST_ZONE));
	m_ilDetails.Add(AfxGetApp()->LoadIcon(ID_LIST_BLOCK));
	m_ilDetails.Add(AfxGetApp()->LoadIcon(ID_LIST_APARTMENT));
	m_ilDetails.Add(AfxGetApp()->LoadIcon(ID_LIST_HOME));

	m_treeDetails.SetImageList(&m_ilDetails,TVSIL_NORMAL);
	HTREEITEM hRootItem = m_treeDetails.InsertItem(_T("物业项目"),0,0);
	for (int nZone=1; nZone<=10; ++nZone)
	{
		str.Format(_T("管理局%d区"),nZone);
		HTREEITEM hZoneItem = m_treeDetails.InsertItem(str,1,1,hRootItem);
		for (int nBlock=1; nBlock<=20; ++nBlock)
		{
			str.Format(_T("%d号楼"),nBlock);
			HTREEITEM hBlockItem = m_treeDetails.InsertItem(str,2,2,hZoneItem);
			for (int nUnit=1; nUnit<=6; ++nUnit)
			{
				str.Format(_T("%d单元"),nUnit);
				HTREEITEM hUnitItem = m_treeDetails.InsertItem(str,3,3,hBlockItem);
			}
		}
	}

	UINT nIcons[] = {	IDI_MANAGER,
						IDI_EDIT,		IDI_REPAIR_MGR,	
						IDI_REPAIR_INFO,IDI_EDIT1,	
						IDI_MEMBER,		IDI_HOUSE,
						IDI_FAMILY,		
						IDI_GO };
	m_ilCmd.Create(40,40,ILC_COLOR32|ILC_MASK,10,5);
	for (i=0; i<_countof(nIcons); ++i)
		m_ilCmd.Add(AfxGetApp()->LoadIcon(nIcons[i]));

	struct { UINT cmd; UINT img; } cmds[] =  {
		{ IDC_BTN_LIST_MAIN,				0 },

		{ IDC_BTN_LIST_INCOME_RECORD,			1 },
		{ IDC_BTN_LIST_REPAIR,					2 },
		{ IDC_BTN_LIST_REPAIR_SUM,				3 },
		{ IDC_BTN_LIST_MATERIAL_REC,				4 },
		{ IDC_BTN_LIST_MEMBER_REC,				5 },
		{ IDC_BTN_LIST_DEPART_REC,				6 },

		{ IDC_BTN_LIST_PROPOWNER,				7 },

		{ IDC_BTN_LIST_RECEIPT_SUMUP_QUERY,		8 },	
		{ IDC_BTN_LIST_EXPECT_SUMUP_QUERY,		8 },
		{ IDC_BTN_LIST_STATE_CHART,				8 },		
		{ IDC_BTN_LIST_RECEIPT_DETAILS_QUERY,	8 },
		{ IDC_BTN_LIST_EXPECT_ACCOUNT,			8 },	
		{ IDC_BTN_LIST_SUMUP_REPORT,				8 }
	};

	m_treeCmd.SetImageList(&m_ilCmd,TVSIL_NORMAL);
	hRootItem = m_treeCmd.InsertItem(CTinyString(cmds[0].cmd),cmds[0].img,cmds[0].img);
	m_treeCmd.SetItemData(hRootItem,cmds[0].cmd);
	for (i=1; i<_countof(cmds); ++i)
	{
		HTREEITEM hTreeItem = m_treeDetails.InsertItem(CTinyString(cmds[i].cmd),cmds[i].img,cmds[i].img,hRootItem);
		m_treeCmd.SetItemData(hTreeItem,cmds[i].cmd);
	}
	m_treeCmd.SetItemHeight(50);

	m_treeCmd.Expand(hRootItem,TVE_EXPAND);
	m_treeCmd.SelectItem(hRootItem);

	m_treeDetails.SetBkColor(RGB(208,228,255));
}

void CListPane::OnBnClickedBtnCmd(void)
{ 
	m_treeCmd.ShowWindow(SW_SHOW);
	m_treeDetails.ShowWindow(SW_HIDE);

}

void CListPane::OnBnClickedBtnDetails(void)
{
	m_treeCmd.ShowWindow(SW_HIDE);
	m_treeDetails.ShowWindow(SW_SHOW);
}

void CListPane::OnTvnDBClickCmd(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = TRUE;
}
 
 
void CListPane::OnNMClickTreeDetails(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = TRUE;
}
