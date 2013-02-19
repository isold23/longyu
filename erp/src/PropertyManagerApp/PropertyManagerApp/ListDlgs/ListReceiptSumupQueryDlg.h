#pragma once
#include "../ReportPageDlg.h"
 

class CListReceiptSumupQueryDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_RECEIPT_SUMUP_QUERY };

public:
	CListReceiptSumupQueryDlg(CWnd* pParent = NULL);   
	virtual ~CListReceiptSumupQueryDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
