#pragma once
#include "../ReportPageDlg.h"


class CListExpectSumupQueryDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_EXPECT_SUMUP_QUERY };

public:
	CListExpectSumupQueryDlg(CWnd* pParent = NULL);   
	virtual ~CListExpectSumupQueryDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
