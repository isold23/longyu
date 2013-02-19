#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "BkgndDlg.h"

 

CBkgndDlg::CBkgndDlg(CWnd* pParent)
	: CXTPResizeDialog(CBkgndDlg::IDD, pParent),
	  m_pActiveChild(NULL)
{

}

CBkgndDlg::~CBkgndDlg()
{
}

void CBkgndDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBkgndDlg, CXTPResizeDialog)
	ON_COMMAND_RANGE(IDC_BTN_BKGNDMAIN,IDC_CHK_CHANGE_PWD,&CBkgndDlg::OnShowSubWnd)
END_MESSAGE_MAP()
 
BOOL CBkgndDlg::OnInitDialog(void)
{
	CXTPResizeDialog::OnInitDialog();

	const UINT MAINDLG_ID = 0xABE; 
	const UINT GRADEDLG_ID = MAINDLG_ID + 1;
	const UINT OPDLG_ID = GRADEDLG_ID + 1;
	const UINT USERDLG_ID = OPDLG_ID + 1;

	CXTPClientRect rc(this);
	m_dlgMain.Create(CBkgndMainDlg::IDD,this);
	m_dlgMain.MoveWindow(rc);
	m_dlgMain.SetDlgCtrlID(MAINDLG_ID );

	 
	
	m_dlgGrade.Create(CBkgndGroupDlg::IDD,this);
	m_dlgGrade.MoveWindow(rc);
	m_dlgGrade.SetDlgCtrlID(GRADEDLG_ID);
	
	m_dlgOp.Create(CBkgndOpDlg::IDD,this);
	m_dlgOp.MoveWindow(rc);
	m_dlgOp.SetDlgCtrlID(OPDLG_ID);
	
	m_dlgUser.Create(CBkgndUserDlg::IDD,this);
	m_dlgUser.MoveWindow(rc);
	m_dlgUser.SetDlgCtrlID(USERDLG_ID);

	SetResize(MAINDLG_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT); 
	SetResize(GRADEDLG_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(OPDLG_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(USERDLG_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);


	SetActiveChild(&m_dlgMain);
	return TRUE;
}


void CBkgndDlg::SetActiveChild(CWnd *pChild)
{
	if (m_pActiveChild != pChild)
	{
		if (m_pActiveChild != NULL)
			m_pActiveChild->ShowWindow(SW_HIDE);

		m_pActiveChild = pChild;

		if (m_pActiveChild != NULL)
		{
			m_pActiveChild->BringWindowToTop();
			m_pActiveChild->MoveWindow(CXTPClientRect(this));
			m_pActiveChild->ShowWindow(SW_SHOW);
		}
	}
} 

 

void CBkgndDlg::OnShowSubWnd(UINT nCmd)
{
	switch (nCmd)
	{
	case IDC_CHK_CHANGE_PWD:
		m_dlgMain.ShowChangePassord(TRUE);
	case IDC_BTN_BKGNDMAIN:
		SetActiveChild(&m_dlgMain);
		break; 
	case IDC_BTN_GROUPMGR:
		SetActiveChild(&m_dlgGrade);
		break;
	case IDC_BTN_OPMGR:
		SetActiveChild(&m_dlgOp);
		break;
	case IDC_BTN_USERMGR:
		SetActiveChild(&m_dlgUser);
		break;
	default:
		ASSERT(!_T("CBkgndDlg::OnShowSubWnd"));
		break;
	}
}