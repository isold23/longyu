#pragma once
#include "../ReportPageDlg.h"


class CListRepairSumDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_REPAIR_SUM  };

public:
	CListRepairSumDlg(CWnd* pParent = NULL);   
	virtual ~CListRepairSumDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
