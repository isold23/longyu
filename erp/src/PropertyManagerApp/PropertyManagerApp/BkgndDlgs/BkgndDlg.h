#pragma once
#include "BkgndGroupDlg.h"
#include "BkgndMainDlg.h"
#include "BkgndOpDlg.h"
#include "BkgndUserDlg.h"

class CBkgndDlg : public CXTPResizeDialog
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_BKGND };

public:
	CBkgndDlg(CWnd* pParent = NULL);    
	virtual ~CBkgndDlg();
 
	CBkgndGroupDlg& GetGradeDlg(void);
	CBkgndMainDlg& GetMainDlg(void);
	CBkgndOpDlg& GetOpDlg(void);
	CBkgndUserDlg& GetUserDlg(void);


	void SetActiveChild(CWnd *pChild);

protected: 
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);   

	afx_msg void OnShowSubWnd(UINT nCmd); 

 
	CBkgndGroupDlg m_dlgGrade;
	CBkgndMainDlg m_dlgMain;
	CBkgndOpDlg m_dlgOp;
	CBkgndUserDlg m_dlgUser;

	CWnd *m_pActiveChild;
};
 

inline CBkgndGroupDlg& CBkgndDlg::GetGradeDlg(void) {
	return m_dlgGrade;
}

inline CBkgndMainDlg& CBkgndDlg::GetMainDlg(void) {
	return m_dlgMain;
}

inline CBkgndOpDlg& CBkgndDlg::GetOpDlg(void) {
	return m_dlgOp;
}

inline CBkgndUserDlg& CBkgndDlg::GetUserDlg(void) {
	return m_dlgUser;
}

