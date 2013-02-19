#pragma once
#include "../ReportCtrl.h"
#include "../ReportPageDlg.h"

class CBkgndOpDlg : public CReportPageDlg
{
	DECLARE_MESSAGE_MAP()
  

public:
	enum { IDD = IDD_BKGND_OP };

public:
	CBkgndOpDlg(CWnd* pParent = NULL);
	virtual ~CBkgndOpDlg(void);


protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);    

	afx_msg void OnBnClickedBtnPrint(void);
	afx_msg void OnOpItemButtonClick(NMHDR * pNotifyStruct, LRESULT *pResult);

	void InitOpList(void); 

	CXTPButton m_btnPrint;

	CReportCtrl m_listOp;
 
};
