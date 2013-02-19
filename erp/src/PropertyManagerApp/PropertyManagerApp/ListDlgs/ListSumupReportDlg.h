#pragma once
#include "../ReportPageDlg.h"


class CListSumupReportDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_SUMUP_REPORT };

public:
	CListSumupReportDlg(CWnd* pParent = NULL);   
	virtual ~CListSumupReportDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
