#pragma once
#include "../ReportPageDlg.h"


class CListMemberRecDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_MEMBER_REC };

public:
	CListMemberRecDlg(CWnd* pParent = NULL);   
	virtual ~CListMemberRecDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
