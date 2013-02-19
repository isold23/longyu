#pragma once 

#include "WorkerDlg.h"

class CLoginWorker;

class CLoginDlg : public CDialog
{ 
	DECLARE_MESSAGE_MAP()
	enum { IDD = IDD_LOGIN };
public:
	CLoginDlg(CWnd* pParent = NULL);   
	virtual ~CLoginDlg(void);
 
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnInitDialog(void);
	
	virtual void OnOK(void);
	//virtual void OnCancel(void);

	afx_msg void OnCbNameSelChange(void); 
	afx_msg void OnBnClickedChkAutoLogin(void);
	afx_msg void OnBnClickedChkExpand(void);
  
	void OnLoginEnd(void);
	void ShowMainWnd(BOOL bVisible);

	CComboBox m_cbName;
	CEdit m_editPwd;
	CButton m_chkSavePwd;
	CButton m_chkAutoLogin;
	CEdit m_editDBAddr; 
	CXTPButton m_btnImg;
	CXTPButton m_chkExpand;

	CWorkerDlg  m_progressDlg;
	CLoginWorker *m_pLoginWorker;
};
