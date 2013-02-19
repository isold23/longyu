#pragma once 
#include "ListMainDlg.h"
#include "ListDepartRecDlg.h" 
#include "ListPropOwnerDlg.h"
#include "ListReceiptDetailsQueryDlg.h"
#include "ListExpectAccountDlg.h"
#include "ListReceiptSumupQueryDlg.h"
#include "ListExpectSumupQueryDlg.h"
#include "ListRepairDlg.h"
#include "ListIncomRecordDlg.h"
#include "ListRepairSumDlg.h"
#include "ListMainDlg.h"
#include "ListStateChartDlg.h"
#include "ListMaterialRecDlg.h"
#include "ListSumupReportDlg.h"
#include "ListMemberRecDlg.h"

class CListDlg : public CXTPResizeDialog
{
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST };

	CListDlg(CWnd* pParent = NULL);  
	virtual ~CListDlg(void);

private:
	virtual BOOL OnInitDialog(void);

	afx_msg void OnCmdShowChild(UINT nCmd);
 
	void SetActiveChild(CWnd *pChild);

	CListMainDlg m_dlgMain;
	CListDepartRecDlg m_dlgDepartRec;
	CListExpectAccountDlg m_dlgExpectAccount;
	CListExpectSumupQueryDlg m_dlgExpectSumupQuery;
	CListIncomRecordDlg m_dlgIncomRecord;
	CListMaterialRecDlg m_dlgMaterialRec;
	CListMemberRecDlg m_dlgMemberRec;
	CListPropOwnerDlg m_dlgPropOwner;
	CListReceiptDetailsQueryDlg m_dlgReceiptDetailsQuery;
	CListReceiptSumupQueryDlg m_dlgReceiptSumupQuery;
	CListRepairDlg m_dlgRepair;
	CListRepairSumDlg m_dlgRepairSum;
	CListStateChartDlg m_dlgStateChart;
	CListSumupReportDlg m_dlgSumupReport;

	CWnd *m_pActiveChild;
};
