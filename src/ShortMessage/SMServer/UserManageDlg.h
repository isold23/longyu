#pragma once
#include "afxcmn.h"

#include "DB/database.h"
using namespace database;
// CUserManageDlg dialog

class CUserManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserManageDlg)

public:
	CUserManageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserManageDlg();
	
// Dialog Data
	enum { IDD = IDD_USER_MANAGE_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_UserList;
public:
	afx_msg void OnBnClickedAddButton();
public:
	afx_msg void OnBnClickedDeleteButton();
public:
	afx_msg void OnBnClickedRtnButton();
public:
	CString m_strUserName;
public:
	CString m_strPassword;
};
