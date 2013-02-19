#pragma once

#include "../ReportPageDlg.h"
#include "afxwin.h"


class CBkgndMainDlg : public CReportPageDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_BKGND_MAIN };

public:
	CBkgndMainDlg(CWnd* pParent = NULL);    
	virtual ~CBkgndMainDlg(void);

	void ShowChangePassord(BOOL bShow);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);    
	
	afx_msg void OnShowSubWnd(UINT nCmd);
	afx_msg void OnBnClickedBtnSubmit(void);
	afx_msg void OnBnClickedChkChangePwd(void);

	void SetUserInfo(void);
 
	CXTPButton m_btnOpMgr;
	CXTPButton m_btnGroupMgr;
	CXTPButton m_btnUserMgr;
	CEdit m_editUser; 
	CXTPReportControl m_listOp;

	CXTPButton m_chkChangePwd;

	CXTPButton m_btnSubmit;
	CEdit m_editOldPwd;
	CEdit m_editPwd;
	CEdit m_editPwd2;
	CStatic m_stcName;
	CStatic m_stcPWD3;
	CStatic m_stcPwd1;
	CStatic m_stcPwd2;
 
	CEdit m_editGroup;

};
