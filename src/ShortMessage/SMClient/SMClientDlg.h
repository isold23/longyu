// SMClientDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "net/netsession.h"
#include "afxcmn.h"
//#include "net/receiver.h"


#include "DB/database.h"
using namespace database;

// CSMClientDlg dialog
class CSMClientDlg : public CDialog
{
	// Construction
public:
	CSMClientDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_SMCLIENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnLoginRtn();
	afx_msg void OnLogoutRtn();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void SetLogin(void);
	void SetSendMessage();
	void SetAddClient();
	void GetClientsInfo(vector<cds::db_clientinfo> &vecClientInfos);
	void InitTreeControl(void);
	void AddClient(string &strUserName, string &strPhoneNumber);
	void UpdateClient(void);
public:
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnTreeCtrlSelectChange(NMHDR* pNMHDR, LRESULT* pResult);  


public:
	CEdit m_UserName;
public:
	CEdit m_UserPassword;
public:
	CButton m_BtnLogin;

	CNetSession m_NetSession;
	//CReceiver m_Receiver;
public:
	CEdit m_EditContent;
public:
	CButton m_BtnSend;
public:
	CStatic m_StaticContent;
public:
	CTreeCtrl m_TreeClient;
public:
	CStatic m_StaticPassword;
public:
	CStatic m_StaticUserName;
public:
	CStatic m_StaticAddUserName;
public:
	CStatic m_StaticAddPhoneNo;
public:
	CEdit m_EditAddUserName;
public:
	CEdit m_EditAddPhoneNo;
public:
	CStatic m_StaticAddMessage;
public:
	CButton m_BtnAddClient;
public:
	afx_msg void OnBnClickedButtonAdd();
private:
	bool m_bIsAddMessage;
	CButton m_BtnAdd;
	afx_msg void OnBnClickedBtnAdd();
	CString m_strAddUserName;
	CString m_strAddPhoneNumber;
	afx_msg void OnBnClickedButtonSend();
	bool m_bLogin;
};
