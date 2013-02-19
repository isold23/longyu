#pragma once
#include "../ReportPageDlg.h"


class CListDepartRecDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_DEPART_REC };

public:
	CListDepartRecDlg(CWnd* pParent = NULL);   
	virtual ~CListDepartRecDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
