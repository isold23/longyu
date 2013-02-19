// UserManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMServer.h"
#include "UserManageDlg.h"

extern CDataBase db;
// CUserManageDlg dialog

IMPLEMENT_DYNAMIC(CUserManageDlg, CDialog)

CUserManageDlg::CUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManageDlg::IDD, pParent)
	, m_strUserName(_T(""))
	, m_strPassword(_T(""))
{

}

CUserManageDlg::~CUserManageDlg()
{
}

void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Text(pDX, IDC_EDIT1, m_strUserName);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
}


BEGIN_MESSAGE_MAP(CUserManageDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CUserManageDlg::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CUserManageDlg::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_RTN_BUTTON, &CUserManageDlg::OnBnClickedRtnButton)
END_MESSAGE_MAP()


BOOL CUserManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_UserList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_UserList.InsertColumn(0, "用户名称", LVCFMT_LEFT, 80);
	m_UserList.InsertColumn(1, "密码", LVCFMT_LEFT, 80);

	strstream sql;
	sql<<"SELECT * FROM clientinfo"<<ends;
	vector<cds::db_userinfo> userinfos;
	bool bRet = db.GetUserInfos(sql.str(), userinfos);
	vector<cds::db_userinfo>::iterator iter = userinfos.begin();
	for(int i = 0;iter != userinfos.end(); iter++, i++)
	{
		m_UserList.InsertItem(i, ((cds::db_userinfo)(*iter)).m_UserName);
		m_UserList.SetItemText(i, 1, ((cds::db_userinfo)(*iter)).m_UserPassword);
	}
	UpdateData(FALSE);
	return TRUE;
}
// CUserManageDlg message handlers

void CUserManageDlg::OnBnClickedAddButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_strUserName.IsEmpty() || m_strPassword.IsEmpty())
	{
		AfxMessageBox("用户名, 密码不能为空");
		return;
	}

	strstream sql;
	int id = db.GetTableCount("clientinfo") + 1;
	sql<<"INSERT INTO clientinfo VALUES("<<id<<",'"<<m_strUserName.GetBuffer(0)<<"','"
		<<m_strPassword.GetBuffer(0)<<"')"<<ends;
	bool bRet = db.Execute(sql.str(), database::CDataBase::ADD);
	if (bRet)
	{
		m_UserList.InsertItem(m_UserList.GetItemCount() + 1, m_strUserName);
		m_UserList.SetItemText(m_UserList.GetItemCount() + 1, 1, m_strPassword);
		AfxMessageBox("添加成功");
	}
	else
	{
		AfxMessageBox("添加失败");
	}
	UpdateData(FALSE);
}

void CUserManageDlg::OnBnClickedDeleteButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	if (m_UserList.GetSelectedCount() <= 0) return;
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();
	CString strUserName = "";
	while (pos)
	{
		int nItem = m_UserList.GetNextSelectedItem(pos);
		strUserName = m_UserList.GetItemText(nItem, 0);
		strstream sql;
		sql<<"DELETE FROM clientinfo WHERE NAME = '"<<strUserName.GetBuffer(0)<<"'"<<ends;
		bool bRet = db.Execute(sql.str(), database::CDataBase::DEL);
		if (bRet)
		{
			m_UserList.DeleteItem(nItem);
			AfxMessageBox("删除成功");
		}
		else
		{
			AfxMessageBox("删除失败");
		}
		
	}
	UpdateData(TRUE);
}

void CUserManageDlg::OnBnClickedRtnButton()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
