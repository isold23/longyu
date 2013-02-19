#include "stdafx.h"
#include "PropertyManagerApp.h"
#include "LoginDlg.h"
#include "LoginHistory.h"
#include "User.h"
#include "Options.h"
#include "WorkerDlg.h"
#include "sql/sql.h"

#define CTRLID_LOGIN_END (111 + 11)


class CLoginWorker : public CWorkerDlg::CWorker
{
	struct CoHelper {
		CoHelper(void) { ::CoInitialize(NULL); }
		~CoHelper(void) { ::CoUninitialize(); }
	};
public:
	enum { ErrOK, ErrConn=-1, ErrCheck=-2 };

	CLoginWorker(CLoginDlg *pLoginDialog)
		:m_pLoginDlg(pLoginDialog),m_nErrorCode(ErrOK)
	{
	}

	void SetLoginInfo(const CString &strAddr,const CString &strName,const CString &strPassword)
	{
		m_strAdddr = strAddr;
		m_strName = strName;
		m_strPassword = strPassword;
	}


	void GetLoginInfo(CString &strAddr,CString &strName,CString &strPassword)
	{
		strAddr = m_strAdddr;
		strName = m_strName;
		strPassword = m_strPassword;
	}



	virtual DWORD Run(void)
	{
		m_nErrorCode = ErrOK;

		CoHelper coHelper;
		

		if (!g_sp.Open(g_ops.GetDBConnString(m_strAdddr),3,TRUE))
		{
			m_nErrorCode = ErrConn;
			m_pLoginDlg->PostMessage(WM_COMMAND,CTRLID_LOGIN_END);
			return 0;
		}

		DWORD dwStartTick = ::GetTickCount(); 
		while (!g_sp.IsConnected())
		{
			Sleep(200);

			if (GetTickCount()-dwStartTick > 5000)
			{ 
				m_nErrorCode = ErrConn;
				m_pLoginDlg->PostMessage(WM_COMMAND,CTRLID_LOGIN_END);
				return 0;
			}
		}
 
		m_nUserId = g_sp.RVCheckUser(m_strName,m_strPassword);
		if (m_nUserId <= 0)
			m_nErrorCode = ErrCheck;
				
		m_pLoginDlg->PostMessage(WM_COMMAND,CTRLID_LOGIN_END);
		return 0;
	}

	LPCTSTR GetErrorString(void) const
	{
		LPCTSTR ErrStrings[] = {_T(""), _T("连接数据库时发生错误，请检查网络状况"), _T("登录验证失败，请重新输入")};
		return ErrStrings[-m_nErrorCode];
	}

	int GetError(void) const 
	{
		return m_nErrorCode;
	}

	int GetUserId(void) const 
	{
		return m_nUserId;
	}
private:
	CLoginDlg *m_pLoginDlg;

	int m_nUserId;
	int m_nErrorCode;
	CString m_strAdddr;
	CString m_strName;
	CString m_strPassword;
};

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	m_pLoginWorker = new CLoginWorker(this);
}

CLoginDlg::~CLoginDlg(void)
{
	delete m_pLoginWorker;
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_SAVE_PWD, m_chkSavePwd);
	DDX_Control(pDX, IDC_CHK_AUTO_LOGIN, m_chkAutoLogin);
	DDX_Control(pDX, IDC_CB_NAME, m_cbName);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_editDBAddr);
	DDX_Control(pDX, IDC_CHK_EXPAND, m_chkExpand);
	DDX_Control(pDX, IDC_BTN_STC, m_btnImg);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog) 
	ON_COMMAND(CTRLID_LOGIN_END,&CLoginDlg::OnLoginEnd)
	ON_BN_CLICKED(IDC_CHK_AUTO_LOGIN, &CLoginDlg::OnBnClickedChkAutoLogin)
	ON_CBN_SELCHANGE(IDC_CB_NAME,&CLoginDlg::OnCbNameSelChange)
	ON_BN_CLICKED(IDC_CHK_EXPAND, &CLoginDlg::OnBnClickedChkExpand)
END_MESSAGE_MAP()

BOOL CLoginDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	m_progressDlg.Create(CWorkerDlg::IDD,this);

	m_chkExpand.SetFlatStyle(TRUE);
	m_chkExpand.SetIcon(CSize(16,16),IDI_CFG);
	
	m_btnImg.SetFlatStyle(TRUE);
	m_btnImg.SetIcon(CSize(128,128),IDI_LOGIN);

	OnBnClickedChkExpand();

	g_ops.Load();
	g_lhistory.Load();

	m_editDBAddr.SetWindowText(g_ops.GetDBAddr());

	for (int i=0; i<g_lhistory.GetRecordCount(); ++i)
	{
		const CLoginHistory::Record &rec = g_lhistory.GetRecord(i);
		int nIndex = m_cbName.AddString(rec.User);
		//m_cbName.SetItemDataPtr(nIndex,const_cast<CLoginHistory::Record*>(&rec));
	}

	if (g_lhistory.GetRecordCount() > 0)
		m_cbName.AddString(_T("清空登录信息......"));

	int nIndex = g_lhistory.GetAutoLogin();
	if (nIndex >= 0)
		m_cbName.SetCurSel(nIndex);
	else if (g_lhistory.GetRecordCount() > 0)
		m_cbName.SetCurSel(0);
	 

	OnCbNameSelChange();

	if (nIndex >= 0)
		OnOK();
	return TRUE;
}
  

void CLoginDlg::OnCbNameSelChange(void)
{
	int nIndex = m_cbName.GetCurSel();
	if (nIndex < 0)
		return ;

	if (nIndex == m_cbName.GetCount()-1)
	{
		g_lhistory.Clear();
		m_cbName.ResetContent();
		m_editPwd.SetWindowText(NULL);
		return;
	}

	const CLoginHistory::Record &rec = g_lhistory.GetRecord(nIndex);
	if (nIndex != g_lhistory.GetAutoLogin())
	{
		m_chkAutoLogin.SetCheck(BST_UNCHECKED);
		m_chkSavePwd.EnableWindow(TRUE);
		m_chkSavePwd.SetCheck(rec.SavePwd ? BST_CHECKED:BST_UNCHECKED);
	}
	else
	{
		m_chkAutoLogin.SetCheck(BST_CHECKED);
		OnBnClickedChkAutoLogin();
	} 

	if (rec.SavePwd)
		m_editPwd.SetWindowText(rec.Pwd);


}

void CLoginDlg::OnBnClickedChkAutoLogin(void)
{ 
	if (m_chkAutoLogin.GetCheck() == BST_UNCHECKED)
	{
		m_chkSavePwd.EnableWindow(TRUE);
	}
	else
	{
		m_chkSavePwd.EnableWindow(FALSE);
		m_chkSavePwd.SetCheck(BST_CHECKED);
	}
}

 
void CLoginDlg::OnOK(void)
{
	CString strName;
	m_cbName.GetWindowText(strName);
	if (strName.IsEmpty())
	{
		MessageBox(_T("请正确填写登录帐户"),_T("登录失败"),MB_ICONSTOP);
		return ;
	}

	CString strPwd;
	m_editPwd.GetWindowText(strPwd);
	if (strPwd.IsEmpty())
	{
		MessageBox(_T("请正确填写登录密码"),_T("登录失败"),MB_ICONSTOP);
		return ;
	}

	CString strDBAddr;
	m_editDBAddr.GetWindowText(strDBAddr);
	if (strDBAddr.IsEmpty())
	{
		MessageBox(_T("请正确填写服务器地址"),_T("登录失败"),MB_ICONSTOP);
		return ;
	}

#if 0
	if (!g_sp.Open(g_ops.GetDBConnString(strDBAddr)))
	{
		MessageBox(_T("连接数据库时发生错误，请检查网络状况"),_T("登录失败"),MB_ICONSTOP);
		return ;
	}
 
	int nUserId = g_sp.RVCheckUser(strName,strPwd);
	if (nUserId < 0)
	{
		MessageBox(_T("登录验证失败，请重新输入"),_T("登录失败"),MB_ICONSTOP);
		return ;
	}
#endif

	m_pLoginWorker->SetLoginInfo(strDBAddr,strName,strPwd); 
	ShowMainWnd(FALSE);

	CXTPClientRect rc(this);
	m_progressDlg.MoveWindow(rc,FALSE);
	m_progressDlg.ShowWindow(SW_SHOW);
	m_progressDlg.BringWindowToTop();
	 

	m_progressDlg.ShowWorker(m_pLoginWorker,_T("正在进行密码校验......"));
	

}

void CLoginDlg::ShowMainWnd(BOOL bVisible)
{
	int nCmdShow = bVisible ? SW_SHOW : SW_HIDE;

	UINT nControlIds[] = {
		IDC_BTN_STC,	IDC_STC1,		IDC_STC2,			IDC_STC3, IDC_STC4,
		IDC_CB_NAME,	IDC_EDIT_PWD,	IDC_CHK_SAVE_PWD,	IDC_CHK_AUTO_LOGIN,
		IDOK,			IDC_CHK_EXPAND, IDC_MARK,			IDC_EDIT_ADDR
	};

	for (int i=0; i<_countof(nControlIds); ++i)
		::ShowWindow(::GetDlgItem(m_hWnd,nControlIds[i]),nCmdShow);
}

void CLoginDlg::OnLoginEnd(void)
{ 

	int nErrCode = m_pLoginWorker->GetError();
	if (nErrCode != CLoginWorker::ErrOK)
	{
		m_progressDlg.ShowWindow(SW_HIDE);
		ShowMainWnd(TRUE);
		MessageBox(m_pLoginWorker->GetErrorString(),_T("登录失败"),MB_ICONSTOP);

		if (nErrCode != CLoginWorker::ErrCheck)
			CDialog::OnCancel();
	}
	else
	{
		CString strDBAddr,strName,strPassword;
		m_pLoginWorker->GetLoginInfo(strDBAddr,strName,strPassword);

		int nUserId = m_pLoginWorker->GetUserId();
		g_user.SetId(nUserId,strName);

		g_lhistory.Add(strName,strPassword,m_chkSavePwd.GetCheck()==BST_CHECKED,m_chkAutoLogin.GetCheck()==BST_CHECKED);
		g_lhistory.Save();

		_RecordsetPtr rst;
		int GroupId;
		CString GroupName;
		CString GroupIntro;

		g_sp.VRGetUserGroup(rst,nUserId,GroupId,GroupName,GroupIntro);
		g_user.SetUserInfo(GroupId,GroupName,GroupIntro);

		g_ops.SetDBAddr(strDBAddr);
		g_ops.Save();
		CDialog::OnOK();
	}
}


void CLoginDlg::OnBnClickedChkExpand(void)
{	
	CXTPWindowRect rect(this);
	if (m_chkExpand.GetCheck() == BST_CHECKED)
		rect.bottom = CXTPWindowRect(m_editDBAddr).bottom + 20;
	else
		rect.bottom = CXTPWindowRect(GetDlgItem(IDC_MARK)).top;
	
	MoveWindow(rect);
}

//void CLoginDlg::OnCancel(void)
//{
//	CDialog::OnCancel();
//}
