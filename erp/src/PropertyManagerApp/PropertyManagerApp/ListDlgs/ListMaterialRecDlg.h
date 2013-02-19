#pragma once
#include "../ReportPageDlg.h"


class CListMaterialRecDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIST_MATERIAL_REC };

public:
	CListMaterialRecDlg(CWnd* pParent = NULL);   
	virtual ~CListMaterialRecDlg(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);     

};
