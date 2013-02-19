// SMServerDlg.h : header file
//

#pragma once

#include "UserManageDlg.h"
#include "afxwin.h"
#include "DB/database.h"
#include "afxcmn.h"
using namespace database;

#include "net/netsession.h"

// CSMServerDlg dialog
class CSMServerDlg : public CDialog
{
// Construction
public:
	CSMServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SMSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUserManageButton();
	
public:
	CButton m_BtnUserManager;
public:
	afx_msg void OnBnClickedButtonHistory();
public:
	CListCtrl m_ListContent;
private:
	CNetSession m_NetSession;
};
