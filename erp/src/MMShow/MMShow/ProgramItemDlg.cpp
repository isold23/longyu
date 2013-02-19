#include "stdafx.h"
#include "Resource.h"
#include "ProgramItemDlg.h"
#include "FileHelper.h"
#include "DrawHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


 
CProgramItemDlg::CProgramItemDlg(LPCTSTR pcszCaption,CWnd* pParent /*=NULL*/)
	: CDialog(CProgramItemDlg::IDD, pParent),
	  m_pcszCaption(pcszCaption),
	  m_bWebPage(FALSE)
{

}

CProgramItemDlg::~CProgramItemDlg()
{
}

void CProgramItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProgramItemDlg, CDialog)
	ON_BN_CLICKED(IDC_RD_WEBPAGE,&CProgramItemDlg::OnChangeType)
	ON_BN_CLICKED(IDC_RD_VIDEO_FILE,&CProgramItemDlg::OnChangeType)
	ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CProgramItemDlg::OnBnClickedBtnSelectFile)
END_MESSAGE_MAP()

BOOL CProgramItemDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	SetWindowText(m_pcszCaption);
	
	CButton *pRdFile = (CButton*)GetDlgItem(IDC_RD_VIDEO_FILE);
	pRdFile->SetCheck(m_bWebPage ? BST_UNCHECKED:BST_CHECKED);
	
	CButton *pRdWebPage = (CButton*)GetDlgItem(IDC_RD_WEBPAGE);
	pRdWebPage->SetCheck(m_bWebPage ? BST_CHECKED:BST_UNCHECKED);


	SetDlgItemText(IDC_EDIT_NAME,m_strName);
	SetDlgItemText(IDC_EDIT_PATH,m_strPath);
	SetDlgItemText(IDC_EDIT_DESC,m_strDesc);

	return FALSE;
}

void CProgramItemDlg::OnChangeType(void)
{
	CEdit *pEditName = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	CEdit *pEditPath = (CEdit*)GetDlgItem(IDC_EDIT_PATH);
	CEdit *pEditDesc = (CEdit*)GetDlgItem(IDC_EDIT_DESC);

	CButton *pRdFile = (CButton*)GetDlgItem(IDC_RD_VIDEO_FILE);
	CButton *pBtnSelect = (CButton*)GetDlgItem(IDC_BTN_SELECT_FILE);
	
	CString strName;
	pEditName->GetWindowText(strName);
	pEditName->SetWindowText(m_strName);
	m_strName = strName;

	CString strPath;
	pEditPath->GetWindowText(strPath);
	pEditPath->SetWindowText(m_strPath);
	m_strPath = strPath;

	CString strDesc;
	pEditDesc->GetWindowText(strDesc);
	pEditDesc->SetWindowText(m_strDesc);
	m_strDesc = strDesc;

	CWindowRect rcPath(pEditPath);
	CWindowRect rcSelect(pBtnSelect);
	if (pRdFile->GetCheck()==BST_CHECKED)
	{
		rcPath.right = rcSelect.left;
		pBtnSelect->ShowWindow(SW_SHOW);
	}
	else
	{
		rcPath.right = rcSelect.right;
		pBtnSelect->ShowWindow(SW_HIDE);
	}
	
	ScreenToClient(rcPath);
	pEditPath->MoveWindow(rcPath);
}

static LPCTSTR ALL_VIDEO_FILTER = _T("MPEG文件 (*.mpg)|*.*;||");
void CProgramItemDlg::OnBnClickedBtnSelectFile(void)
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_ENABLESIZING,ALL_VIDEO_FILTER);
	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH,strPathName);
		CWnd *pEditName = GetDlgItem(IDC_EDIT_NAME);
		
		CString str;
		pEditName->GetWindowText(str);
		if (str.Trim().IsEmpty())
			pEditName->SetWindowText(Fh::GetFileName(strPathName));
	}
}

void CProgramItemDlg::OnOK(void)
{
	GetDlgItemText(IDC_EDIT_NAME,m_strName);
	if (m_strName.Trim().IsEmpty())
	{
		MessageBox(_T("名称不能为空"),_T("信息提示"),MB_ICONINFORMATION);
		return;
	}

	GetDlgItemText(IDC_EDIT_PATH,m_strPath);
	if (m_strPath.Trim().IsEmpty())
	{
		MessageBox(_T("地址不能为空"),_T("信息提示"),MB_ICONINFORMATION);
		return;
	}


	CButton *pRdFile = (CButton*)GetDlgItem(IDC_RD_WEBPAGE);
	m_bWebPage = (pRdFile->GetCheck() == BST_CHECKED);

	GetDlgItemText(IDC_EDIT_DESC,m_strDesc);
	CDialog::OnOK();
}
