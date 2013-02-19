#pragma once
#include "../ReportPageDlg.h"


class CListStateChartDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_STATE_CHART };

public:
	CListStateChartDlg(CWnd* pParent = NULL);   
	virtual ~CListStateChartDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
