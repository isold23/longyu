#pragma once
#include "../ReportPageDlg.h"

 
class CListMainDlg : public CReportPageDlg
{
	DECLARE_MESSAGE_MAP() 

public:
	enum { IDD = IDD_LIST_MAIN };

public:
	CListMainDlg(CWnd* pParent = NULL);  
	virtual ~CListMainDlg();
 
private:
	virtual void DoDataExchange(CDataExchange* pDX);   
	virtual BOOL OnInitDialog(void);
 
	afx_msg void OnCmdShowChild(UINT nCmd); 

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	CXTPButton m_stcDaily;

	CXTPButton m_btnReceiptSumUpQuery;
	CXTPButton m_btnExpectSumUpQuery;
	CXTPButton m_btnStateChart;
	CXTPButton m_btnReceiptDetailsQuery;
		
	CXTPButton m_btnExpectAccount;
	CXTPButton m_btnSumUpReport;

	CXTPButton m_btnIncomRecord;
	CXTPButton m_btnRepair;
	CXTPButton m_btnRepairSum;
	CXTPButton m_btnMaterialRec;
	CXTPButton m_btnMemberRec;
	CXTPButton m_btnDepartRec;
	CXTPButton m_btnPropOwner;


	CXTPButton m_stc1;
	CXTPButton m_stc2;
	CXTPButton m_stc3;
	CXTPButton m_stc4;
};
