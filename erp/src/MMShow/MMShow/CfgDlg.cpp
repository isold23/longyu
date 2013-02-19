#include "stdafx.h"
#include "resource.h"
#include "CfgDlg.h"
#include "Cfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CCfgDlg::CCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgDlg::IDD, pParent)
{
	m_nStartIndex = 0;
	m_bForceCamCfg = FALSE;
}

CCfgDlg::~CCfgDlg()
{
}

void CCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TAB,m_tab);
}


BEGIN_MESSAGE_MAP(CCfgDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE,IDC_TAB,&CCfgDlg::OnTabSelChange)
END_MESSAGE_MAP()

BOOL CCfgDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	m_camDlg.Create(CCamCfgDlg::IDD,this);
	m_outputDlg.Create(COutputCfgDlg::IDD,this);
	m_recordDlg.Create(CRecordCfgDlg::IDD,this);
	m_uiDlg.Create(CUiCfgDlg::IDD,this);

	CRect rc;
	GetDlgItem(IDC_STC_CONTENT)->GetWindowRect(&rc);
	ScreenToClient(rc);

	m_camDlg.MoveWindow(rc);
	m_outputDlg.MoveWindow(rc);
	m_recordDlg.MoveWindow(rc);
	m_uiDlg.MoveWindow(rc);

	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT,m_tab.GetItemCount(),
		m_camDlg.GetCaption(),0,(LPARAM)(CDialog*)&m_camDlg);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT,m_tab.GetItemCount(),
		m_outputDlg.GetCaption(),0,(LPARAM)(CDialog*)&m_outputDlg);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT,m_tab.GetItemCount(),
		m_recordDlg.GetCaption(),0,(LPARAM)(CDialog*)&m_recordDlg);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT,m_tab.GetItemCount(),
		m_uiDlg.GetCaption(),0,(LPARAM)(CDialog*)&m_uiDlg);

	m_tab.SetCurSel(m_nStartIndex);
	m_camDlg.ShowWindow(SW_SHOW);
	m_camDlg.BringWindowToTop();

	return FALSE;
}

void CCfgDlg::OnTabSelChange(NMHDR *pNM,LRESULT *pResult)
{
	m_camDlg.ShowWindow(SW_HIDE);
	m_outputDlg.ShowWindow(SW_HIDE);
	m_recordDlg.ShowWindow(SW_HIDE);
	m_uiDlg.ShowWindow(SW_HIDE);

	int nIndex = m_tab.GetCurSel();

	TCITEM ti;
	ti.mask = TCIF_PARAM;
	m_tab.GetItem(nIndex,&ti);
	CDialog *pDlg = (CDialog*)ti.lParam;

	pDlg->ShowWindow(SW_SHOW);
	pDlg->BringWindowToTop();
	*pResult = TRUE;
}

void CCfgDlg::OnOK(void)
{
	CString strTips;
	
	CString strTip;
	if (!m_camDlg.SaveCfg(strTip))
		strTips += _T("\r\n") + strTip;

	if (!m_outputDlg.SaveCfg(strTip))
		strTips += _T("\r\n") + strTip;

	if (!m_recordDlg.SaveCfg(strTip))
		strTips += _T("\r\n") + strTip;

	if (!m_uiDlg.SaveCfg(strTip))
		strTips += _T("\r\n") + strTip;

	if (!strTips.IsEmpty())
		MessageBox(strTips,_T("提示信息"),MB_ICONINFORMATION);
	else
		CDialog::OnOK();
}

void CCfgDlg::OnCancel(void)
{
	if (!m_bForceCamCfg)
	{
		CDialog::OnCancel();
	}
	else
	{
		if (gcfg.GetCam0().IsEmpty() || gcfg.GetCam1().IsEmpty() || gcfg.GetCam2().IsEmpty())
		{
			if (MessageBox(_T("采集卡未正确设置，确定退出程序？"),_T("信息提示"),MB_ICONINFORMATION|MB_OKCANCEL) == IDOK)
				CDialog::OnCancel();
		}
		else
		{
			CDialog::OnCancel();
		}
	}
}
