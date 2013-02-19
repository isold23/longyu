#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "BkgndOpDlg.h"
#include "DrawHelper.h"
#include "../User.h"
#include "../Sql/sql.h"


CBkgndOpDlg::CBkgndOpDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CBkgndOpDlg::IDD, pParent)
{

}

CBkgndOpDlg::~CBkgndOpDlg()
{
}

void CBkgndOpDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_OP_LIST, m_listOp);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
}


BEGIN_MESSAGE_MAP(CBkgndOpDlg, CReportPageDlg) 
	ON_NOTIFY(XTP_NM_REPORT_ITEMBUTTONCLICK, IDC_OP_LIST, &CBkgndOpDlg::OnOpItemButtonClick)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CBkgndOpDlg::OnBnClickedBtnPrint)
END_MESSAGE_MAP()

BOOL CBkgndOpDlg::OnInitDialog(void)
{
	CReportPageDlg::OnInitDialog();
	m_btnPrint.SetIcon(CSize(32,32),IDI_PRINTER); 


	InitOpList();
	return TRUE;
}

static CReportCtrl::ColInfo OpListCols[] = { 
	{ _T("±êÊ¶"),	60,		TRUE,	TRUE,		_T("Id"),		FALSE,	TRUE,	CReportCtrl::FmtId		},
	{ _T("Ãû³Æ"),	60,		FALSE,	FALSE,		_T("Name"),		FALSE,	TRUE,	CReportCtrl::FmtIdStr	},
	{ _T("ÃèÊö"),	150,	FALSE,	FALSE,		_T("Intro"),	FALSE,	TRUE }
};

void CBkgndOpDlg::InitOpList(void)
{ 
	SetResize(IDC_STC_OPS,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_OP_LIST,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT); 

	m_listOp.Initialize(OpListCols,_countof(OpListCols),CReportCtrl::OpDelete|CReportCtrl::OpModify|CReportCtrl::OpAdd|CReportCtrl::OpId);

	_RecordsetPtr rst;
	CString ErrDesc;
	if (g_sp.RRGetOps(rst,g_user.GetId(),ErrDesc) >= 0)
		m_listOp.FillRecordset(rst);

}
  
 
  

void CBkgndOpDlg::OnOpItemButtonClick(NMHDR * pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	CXTPReportRecordItem *pItem = pItemNotify->pItem;

	int nRet = 0;
	CString strErrDesc;
	CXTPReportRecord *pRec = pItemNotify->pRow->GetRecord();
	if (m_listOp.IsAddOpRecord(pRec))
	{
		ASSERT(m_listOp.IsSubmitOpCol(pItem));
		nRet = g_sp.RVAddOp(g_user.GetId(),IntRec(pRec,0),StrRec(pRec,1), StrRec(pRec,2),strErrDesc);
		if (nRet >= 0)
			m_listOp.TransferAddRecord();
	}
	else if (m_listOp.IsDeleteOpCol(pItem))
	{
		nRet = g_sp.RVDelOp(g_user.GetId(),RecId(pRec),strErrDesc);
		if (nRet >= 0)
			m_listOp.DeleteRecord(pRec);
	}
	else 
	{
		ASSERT(m_listOp.IsSubmitOpCol(pItem));
		nRet = g_sp.RVUpdateOp(g_user.GetId(),RecId(pRec),IntRec(pRec,0),StrRec(pRec,1),StrRec(pRec,2),strErrDesc);
		if (nRet >=0)
			CopyRecId(pRec);
	}

	if (nRet < 0)
		m_listOp.AlertError(strErrDesc);

}
void CBkgndOpDlg::OnBnClickedBtnPrint()
{
	m_listOp.DoPrint();
}
