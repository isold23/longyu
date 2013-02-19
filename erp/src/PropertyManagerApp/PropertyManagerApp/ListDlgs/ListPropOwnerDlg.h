#pragma once
#include "../ReportPageDlg.h"


class CListPropOwnerDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_PROPOWNER  };

public:
	CListPropOwnerDlg(CWnd* pParent = NULL);   
	virtual ~CListPropOwnerDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
