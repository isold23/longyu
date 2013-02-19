// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "longyuim.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog dialog

IMPLEMENT_DYNAMIC(CLoginDialog, CDialogEx)

CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDialog::IDD, pParent)
{

}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialogEx)
	ON_BN_CLICKED(IDLOGIN, &CLoginDialog::OnBnClickedLogin)
	ON_BN_CLICKED(IDCLOSE, &CLoginDialog::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON_SET_NET, &CLoginDialog::OnBnClickedButtonSetNet)
END_MESSAGE_MAP()


// CLoginDialog message handlers


void CLoginDialog::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	return;
}


void CLoginDialog::OnBnClickedClose()
{
	//ÍË³ö
	OnCancel();
}


void CLoginDialog::OnBnClickedButtonSetNet()
{
	// TODO: Add your control notification handler code here
}
