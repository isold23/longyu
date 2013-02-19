#pragma once
#include "../ReportPageDlg.h"


class CListIncomRecordDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_INCOME_RECORD };

public:
	CListIncomRecordDlg(CWnd* pParent = NULL);   
	virtual ~CListIncomRecordDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
