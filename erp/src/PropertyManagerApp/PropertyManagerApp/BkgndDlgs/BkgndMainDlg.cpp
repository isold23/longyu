#include "stdafx.h"
#include "../User.h"
#include "../PropertyManagerApp.h"
#include "BkgndMainDlg.h"
#include "../Sql/sql.h"

 

CBkgndMainDlg::CBkgndMainDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CBkgndMainDlg::IDD, pParent)
{

}

CBkgndMainDlg::~CBkgndMainDlg(void)
{
}

void CBkgndMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_OPMGR, m_btnOpMgr);
	DDX_Control(pDX, IDC_BTN_GROUPMGR, m_btnGroupMgr);
	DDX_Control(pDX, IDC_BTN_USERMGR, m_btnUserMgr);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editUser);
	DDX_Control(pDX, IDC_EDIT_OLD_PWD, m_editOldPwd);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_PWD2, m_editPwd2);
	DDX_Control(pDX, IDC_CHK_CHANGE_PWD, m_chkChangePwd);
	DDX_Control(pDX, IDC_BTN_SUBMIT, m_btnSubmit);
	DDX_Control(pDX, IDC_STC_NAME, m_stcName);
	DDX_Control(pDX, IDC_STC_PWD3, m_stcPWD3);
	DDX_Control(pDX, IDC_STC_PWD, m_stcPwd1);
	DDX_Control(pDX, IDC_STC_PWD2, m_stcPwd2);
	DDX_Control(pDX, IDC_LIST_OP, m_listOp);
	DDX_Control(pDX, IDC_EDIT_GROUP, m_editGroup); 
}


BEGIN_MESSAGE_MAP(CBkgndMainDlg, CReportPageDlg)
	ON_BN_CLICKED(IDC_BTN_SUBMIT, &CBkgndMainDlg::OnBnClickedBtnSubmit)
	ON_BN_CLICKED(IDC_CHK_CHANGE_PWD, &CBkgndMainDlg::OnBnClickedChkChangePwd)
	ON_COMMAND_RANGE(IDC_BTN_OPMGR,IDC_BTN_LVLMGR,&CBkgndMainDlg::OnShowSubWnd)
END_MESSAGE_MAP()

BOOL CBkgndMainDlg::OnInitDialog(void)
{
	CReportPageDlg::OnInitDialog();
  

	m_btnGroupMgr.SetFlatStyle(TRUE);
	m_btnGroupMgr.SetIcon(CSize(128,128),IDI_GRADE);
	m_btnGroupMgr.SetTextImageRelation(xtpButtonImageAboveText);

	m_btnUserMgr.SetFlatStyle(TRUE);
	m_btnUserMgr.SetIcon(CSize(128,128),IDI_USERS);
	m_btnUserMgr.SetTextImageRelation(xtpButtonImageAboveText);

	m_btnOpMgr.SetFlatStyle(TRUE);
	m_btnOpMgr.SetIcon(CSize(128,128),IDI_OPS);
	m_btnOpMgr.SetTextImageRelation(xtpButtonImageAboveText);

	m_btnSubmit.SetFlatStyle(TRUE);
	m_btnSubmit.SetIcon(CSize(16,16),IDI_OK);
	m_btnSubmit.SetTextImageRelation(xtpButtonImageBeforeText);


 
	SetResize(IDC_BTN_OPMGR, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_GROUPMGR, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_USERMGR, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_EDIT_NAME, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_EDIT_GRADE, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_EDIT_OLD_PWD, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_EDIT_PWD, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_EDIT_PWD2, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_CHK_CHANGE_PWD, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_BTN_SUBMIT, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_MAIN, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_NAME, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_GRADE, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_PWD3, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_PWD, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_PWD2, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_LIST_OP, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_OP, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_CHK_MGR, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_CHK_GROUP, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_CHK_OP, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_CHK_USER, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_EDIT_GROUP, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);
	SetResize(IDC_STC_GROUP, XTP_ANCHOR_MIDDLECENTER, XTP_ANCHOR_MIDDLECENTER);

	SetUserInfo();
	return TRUE;
}

void CBkgndMainDlg::SetUserInfo(void)
{
	m_editUser.SetWindowText(g_user.GetName());
 	m_editGroup.SetWindowText(g_user.GetGroupName());

	m_listOp.AllowEdit(FALSE);
	m_listOp.ShowHeader(FALSE); 
	m_listOp.SelectionEnable(FALSE);

	CXTPReportColumn *pCol = new CXTPReportColumn(0,NULL,80,FALSE);
	m_listOp.GetColumns()->Add(pCol);
	pCol = new CXTPReportColumn(1,NULL,50);
	m_listOp.GetColumns()->Add(pCol);
 
	_RecordsetPtr rst;
	int GroupId = g_user.GetGroupId();
	CString GroupName;
	CString GroupIntro;

	g_sp.RRGetUserOps(rst,g_user.GetId());

	if (rst != NULL)
	{
		CString str;
		while (!rst->adoEOF)
		{
			CXTPReportRecord *pRec = new CXTPReportRecord();

			str = rst->Fields->Item[L"OpName"]->Value;
			CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
			pItem->SetCaption(str);
			pItem->SetTextColor(RGB(100,100,150));
			pRec->AddItem(pItem);

			str = rst->Fields->Item[L"OpIntro"]->Value;
			pItem = new CXTPReportRecordItem();
			pItem->SetCaption(str);
			pItem->SetTextColor(RGB(100,150,100));
			pRec->AddItem(pItem);

			rst->MoveNext();

			m_listOp.AddRecord(pRec);
		}
		m_listOp.Populate();
	}


}


void CBkgndMainDlg::OnBnClickedBtnSubmit(void)
{
	CString strPwd;
	m_editPwd.GetWindowText(strPwd);
	if (strPwd.IsEmpty())
	{
		MessageBox(_T("密码不能为空"),_T("错误提示"),MB_ICONSTOP);
		return;
	}
	
	CString strPwd2;
	m_editPwd2.GetWindowText(strPwd2);
	if (strPwd != strPwd2)
	{
		MessageBox(_T("两次输入密码不一致"),_T("错误提示"),MB_ICONSTOP);
		return;
	}

	CString strOldPwd;
	m_editOldPwd.GetWindowText(strOldPwd);
	if (g_sp.RVUpdateUserPwd(g_user.GetId(),strOldPwd,strPwd,strPwd2) < 0)
		MessageBox(strPwd2,_T("错误提示"),MB_ICONSTOP);
}

void CBkgndMainDlg::ShowChangePassord(BOOL bShow)
{
	UINT nShowCmd = (bShow ? SW_SHOW : SW_HIDE);
	m_btnSubmit.ShowWindow(nShowCmd);
	m_editOldPwd.ShowWindow(nShowCmd);
	m_editPwd.ShowWindow(nShowCmd);
	m_editPwd2.ShowWindow(nShowCmd); 
	m_stcPWD3.ShowWindow(nShowCmd);
	m_stcPwd1.ShowWindow(nShowCmd);
	m_stcPwd2.ShowWindow(nShowCmd);

	if (m_chkChangePwd.GetChecked() != bShow)
		m_chkChangePwd.SetChecked(bShow);

}

void CBkgndMainDlg::OnBnClickedChkChangePwd()
{
	ShowChangePassord(m_chkChangePwd.GetChecked());

}

void CBkgndMainDlg::OnShowSubWnd(UINT nCmd)
{
	GetParent()->PostMessage(WM_COMMAND,nCmd);
}