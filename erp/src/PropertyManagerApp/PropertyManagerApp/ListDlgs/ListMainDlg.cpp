#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListMainDlg.h"

  
CListMainDlg::CListMainDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListMainDlg::IDD, pParent)
{

}

CListMainDlg::~CListMainDlg()
{
}
 
void CListMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_BTN_LIST_RECEIPT_SUMUP_QUERY,m_btnReceiptSumUpQuery);
	DDX_Control(pDX,IDC_BTN_LIST_EXPECT_SUMUP_QUERY,m_btnExpectSumUpQuery);
	DDX_Control(pDX,IDC_BTN_LIST_STATE_CHART,m_btnStateChart);
	DDX_Control(pDX,IDC_BTN_LIST_RECEIPT_DETAILS_QUERY,m_btnReceiptDetailsQuery);
	DDX_Control(pDX,IDC_BTN_LIST_EXPECT_ACCOUNT,m_btnExpectAccount);
	DDX_Control(pDX,IDC_BTN_LIST_SUMUP_REPORT,m_btnSumUpReport);

	DDX_Control(pDX,IDC_BTN_LIST_INCOME_RECORD,m_btnIncomRecord);
	DDX_Control(pDX,IDC_BTN_LIST_REPAIR,m_btnRepair);
	DDX_Control(pDX,IDC_BTN_LIST_REPAIR_SUM,m_btnRepairSum);
	DDX_Control(pDX,IDC_BTN_LIST_MATERIAL_REC,m_btnMaterialRec);
	DDX_Control(pDX,IDC_BTN_LIST_MEMBER_REC,m_btnMemberRec);
	DDX_Control(pDX,IDC_BTN_LIST_DEPART_REC,m_btnDepartRec);
	DDX_Control(pDX,IDC_BTN_LIST_PROPOWNER,m_btnPropOwner);


	DDX_Control(pDX,IDC_STC_BUTTON1,m_stc1);
	DDX_Control(pDX,IDC_STC_BUTTON2,m_stc2);
	DDX_Control(pDX,IDC_STC_BUTTON3,m_stc3);
	DDX_Control(pDX,IDC_STC_BUTTON4,m_stc4);

	DDX_Control(pDX,IDC_BTN_LIST_MAIN,m_stcDaily);



} 
BEGIN_MESSAGE_MAP(CListMainDlg, CReportPageDlg)
	ON_COMMAND_RANGE(IDC_BTN_LIST_INCOME_RECORD,IDC_BTN_LIST_MAIN,&CListMainDlg::OnCmdShowChild)
END_MESSAGE_MAP()


BOOL CListMainDlg::OnInitDialog(void)
{
	CReportPageDlg::OnInitDialog();

	SetResize(IDC_BTN_LIST_MAIN,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);

	SetResize(IDC_BTN_LIST_RECEIPT_SUMUP_QUERY,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_EXPECT_SUMUP_QUERY,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_STATE_CHART,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_RECEIPT_DETAILS_QUERY,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_EXPECT_ACCOUNT,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_SUMUP_REPORT,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);

	SetResize(IDC_BTN_LIST_INCOME_RECORD,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_REPAIR,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_REPAIR_SUM,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_MATERIAL_REC,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_DEPART_REC,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_MEMBER_REC,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_LIST_PROPOWNER,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);

	SetResize(IDC_STC_BUTTON1,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_BUTTON2,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_BUTTON3,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_BUTTON4,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);

	SetResize(IDC_STC_LINE,XTP_ANCHOR_MIDDLECENTER,XTP_ANCHOR_MIDDLECENTER);

	m_btnReceiptSumUpQuery.SetIcon(CSize(32,32),IDI_GO);
	m_btnExpectSumUpQuery.SetIcon(CSize(32,32),IDI_GO);
	m_btnStateChart.SetIcon(CSize(32,32),IDI_GO);
	m_btnReceiptDetailsQuery.SetIcon(CSize(32,32),IDI_GO);
	m_btnExpectAccount.SetIcon(CSize(32,32),IDI_GO);
	m_btnSumUpReport.SetIcon(CSize(32,32),IDI_GO);

	m_btnReceiptSumUpQuery.SetTheme(xtpControlThemeResource);

	m_btnReceiptSumUpQuery.SetFlatStyle(TRUE);
	m_btnExpectSumUpQuery.SetFlatStyle(TRUE);
	m_btnStateChart.SetFlatStyle(TRUE);
	m_btnReceiptDetailsQuery.SetFlatStyle(TRUE);
	m_btnExpectAccount.SetFlatStyle(TRUE);
	m_btnSumUpReport.SetFlatStyle(TRUE);

	m_btnIncomRecord.SetIcon(CSize(32,32),IDI_EDIT);
	m_btnRepair.SetIcon(CSize(32,32),IDI_REPAIR_MGR);
	m_btnRepairSum.SetIcon(CSize(32,32),IDI_REPAIR_INFO);
	m_btnMaterialRec.SetIcon(CSize(32,32),IDI_EDIT1);
	m_btnMemberRec.SetIcon(CSize(32,32),IDI_MEMBER);
	m_btnDepartRec.SetIcon(CSize(32,32),IDI_HOUSE);

	m_btnPropOwner.SetIcon(CSize(48,48),IDI_FAMILY);

	m_btnIncomRecord.SetFlatStyle(TRUE);
	m_btnRepair.SetFlatStyle(TRUE);
	m_btnRepairSum.SetFlatStyle(TRUE);
	m_btnMaterialRec.SetFlatStyle(TRUE);
	m_btnMemberRec.SetFlatStyle(TRUE);
	m_btnDepartRec.SetFlatStyle(TRUE);
	m_btnPropOwner.SetFlatStyle(TRUE);

	m_btnIncomRecord.SetTextImageRelation(xtpButtonImageAboveText);
	m_btnRepair.SetTextImageRelation(xtpButtonImageAboveText);
	m_btnRepairSum.SetTextImageRelation(xtpButtonImageAboveText);
	m_btnMaterialRec.SetTextImageRelation(xtpButtonImageAboveText);
	m_btnMemberRec.SetTextImageRelation(xtpButtonImageAboveText);
	m_btnDepartRec.SetTextImageRelation(xtpButtonImageAboveText);
	m_btnPropOwner.SetTextImageRelation(xtpButtonImageAboveText);

	m_stc1.SetIcon(CSize(32,32),IDI_FWD);
	m_stc2.SetIcon(CSize(32,32),IDI_FWD);
	m_stc3.SetIcon(CSize(32,32),IDI_FWD);
	m_stc4.SetIcon(CSize(32,32),IDI_FWD);
	m_stc1.SetFlatStyle(TRUE);
	m_stc2.SetFlatStyle(TRUE);
	m_stc3.SetFlatStyle(TRUE);
	m_stc4.SetFlatStyle(TRUE);


	m_stcDaily.SetFlatStyle(TRUE);
	m_stcDaily.SetIcon(CSize(128,128),IDI_MANAGER);


	return TRUE;
}


void CListMainDlg::OnCmdShowChild(UINT nCmd)
{
	GetParent()->PostMessage(WM_COMMAND,nCmd);
} 