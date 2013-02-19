#pragma once
#include "../ReportPageDlg.h"


class CListRepairDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_REPAIR  };

public:
	CListRepairDlg(CWnd* pParent = NULL);   
	virtual ~CListRepairDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
