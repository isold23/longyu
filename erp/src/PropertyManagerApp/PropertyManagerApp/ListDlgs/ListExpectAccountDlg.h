#pragma once
#include "../ReportPageDlg.h"


class CListExpectAccountDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_EXPECT_ACCOUNT };

public:
	CListExpectAccountDlg(CWnd* pParent = NULL);   
	virtual ~CListExpectAccountDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
