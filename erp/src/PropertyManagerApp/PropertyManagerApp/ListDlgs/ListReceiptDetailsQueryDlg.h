#pragma once
#include "../ReportPageDlg.h"


class CListReceiptDetailsQueryDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_RECEIPT_DETAILS_QUERY };

public:
	CListReceiptDetailsQueryDlg(CWnd* pParent = NULL);   
	virtual ~CListReceiptDetailsQueryDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
