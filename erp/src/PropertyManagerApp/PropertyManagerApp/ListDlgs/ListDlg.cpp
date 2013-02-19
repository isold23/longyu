#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListDlg.h"


CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
		: CXTPResizeDialog(CListDlg::IDD, pParent),
		  m_pActiveChild(NULL)
{

}

CListDlg::~CListDlg()
{
}


BEGIN_MESSAGE_MAP(CListDlg, CXTPResizeDialog)
	ON_COMMAND_RANGE(IDC_BTN_LIST_INCOME_RECORD,IDC_BTN_LIST_MAIN,&CListDlg::OnCmdShowChild)
END_MESSAGE_MAP()

BOOL CListDlg::OnInitDialog(void)
{
	CXTPResizeDialog::OnInitDialog();

	const UINT BASE_ID = 0xABC;
	struct { CDialog *dlg; UINT tid; } dlgs[] = {
		{ &m_dlgMain,				CListMainDlg::IDD },
		{ &m_dlgDepartRec,			CListDepartRecDlg::IDD },
		{ &m_dlgExpectAccount,		CListExpectAccountDlg::IDD },
		{ &m_dlgExpectSumupQuery,	CListExpectSumupQueryDlg::IDD },
		{ &m_dlgIncomRecord,		CListIncomRecordDlg::IDD },
		{ &m_dlgMaterialRec,		CListMaterialRecDlg::IDD },
		{ &m_dlgMemberRec,			CListMemberRecDlg::IDD },
		{ &m_dlgPropOwner,			CListPropOwnerDlg::IDD },
		{ &m_dlgReceiptDetailsQuery,CListReceiptDetailsQueryDlg::IDD },
		{ &m_dlgReceiptSumupQuery,	CListReceiptSumupQueryDlg::IDD },
		{ &m_dlgRepair,				CListRepairDlg::IDD },
		{ &m_dlgRepairSum,			CListRepairSumDlg::IDD },
		{ &m_dlgStateChart,			CListStateChartDlg::IDD },
		{ &m_dlgSumupReport,		CListSumupReportDlg::IDD }
	};


	CXTPClientRect rc(this);

	for (int i=0; i<_countof(dlgs); ++i)
	{
		dlgs[i].dlg->Create(dlgs[i].tid,this);
		dlgs[i].dlg->SetDlgCtrlID(BASE_ID + i);
		dlgs[i].dlg->MoveWindow(CXTPClientRect(this));
		SetResize(BASE_ID + i,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	}


 
	SetActiveChild(&m_dlgMain);
	return TRUE;
}

void CListDlg::SetActiveChild(CWnd *pChild)
{
	if (m_pActiveChild != pChild)
	{
		if (m_pActiveChild != NULL)
			m_pActiveChild->ShowWindow(SW_HIDE);

		m_pActiveChild = pChild;

		if (m_pActiveChild != NULL)
		{
			m_pActiveChild->BringWindowToTop();
			m_pActiveChild->ShowWindow(SW_SHOW);
		}
	}
} 

void CListDlg::OnCmdShowChild(UINT nCmd)
{
	struct { UINT cmd; CWnd *wnd; } ms[] = {
		{ IDC_BTN_LIST_MAIN,					&m_dlgMain },
		{ IDC_BTN_LIST_DEPART_REC,				&m_dlgDepartRec },
		{ IDC_BTN_LIST_EXPECT_ACCOUNT,			&m_dlgExpectAccount },
		{ IDC_BTN_LIST_EXPECT_SUMUP_QUERY,		&m_dlgExpectSumupQuery },
		{ IDC_BTN_LIST_INCOME_RECORD,			&m_dlgIncomRecord },
		{ IDC_BTN_LIST_MATERIAL_REC,			&m_dlgMaterialRec },
		{ IDC_BTN_LIST_MEMBER_REC,				&m_dlgMemberRec },
		{ IDC_BTN_LIST_PROPOWNER,				&m_dlgPropOwner },
		{ IDC_BTN_LIST_RECEIPT_DETAILS_QUERY,	&m_dlgReceiptDetailsQuery },
		{ IDC_BTN_LIST_RECEIPT_SUMUP_QUERY,		&m_dlgReceiptSumupQuery },
		{ IDC_BTN_LIST_REPAIR,					&m_dlgRepair },
		{ IDC_BTN_LIST_REPAIR_SUM,				&m_dlgRepairSum },
		{ IDC_BTN_LIST_STATE_CHART,				&m_dlgStateChart },
		{ IDC_BTN_LIST_SUMUP_REPORT,			&m_dlgSumupReport }
	};

	for (int i=0; i<_countof(ms); ++i)
		if (ms[i].cmd == nCmd)
		{
			SetActiveChild(ms[i].wnd);
			return;
		}
  
	ASSERT(!_T("CListDlg::OnCmdShowChild"));
}