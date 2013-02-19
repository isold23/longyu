#include "stdafx.h"
#include "Resource.h"
#include "UiCfgDlg.h"
#include "Cfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUiCfgDlg::CUiCfgDlg(CWnd* pParent /*=NULL*/)
	: CCfgChildDlg(CUiCfgDlg::IDD, pParent)
{

}

CUiCfgDlg::~CUiCfgDlg()
{
}

void CUiCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CCfgChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_DEF_OPRATED, m_cbDefOperated);
	DDX_Control(pDX, IDC_DEF_PREVIEW, m_cbDefPreview);
	DDX_Control(pDX, IDC_CB_DEF_CAM, m_cbDefCam);
	DDX_Control(pDX, IDC_CHK_TRASPARENT_GAUGE, m_chkTransparentGauge);
	DDX_Control(pDX, IDC_CHK_GAUGE, m_chkGuage);
	DDX_Control(pDX, IDC_CHK_SAVE_HISTORY, m_chkSaveHistory);
	DDX_Control(pDX, IDC_CHK_PREVIEW, m_chkOpenPreview);
	DDX_Control(pDX, IDC_CHK_SHOW_CURSOR, m_chkShowCursor);
}


BEGIN_MESSAGE_MAP(CUiCfgDlg, CCfgChildDlg)
END_MESSAGE_MAP()
 
BOOL CUiCfgDlg::OnInitDialog(void)
{
	CCfgChildDlg::OnInitDialog();
	
	m_cbDefOperated.AddString(_T("网页"));
	m_cbDefOperated.AddString(_T("视频文件"));
	m_cbDefOperated.AddString(_T("图像"));
	m_cbDefOperated.AddString(_T("视频流"));
	m_cbDefOperated.SetCurSel(gcfg.GetUiOpDefaut());

	m_cbDefPreview.AddString(_T("网页"));
	m_cbDefPreview.AddString(_T("视频文件"));
	m_cbDefPreview.AddString(_T("图像"));
	m_cbDefPreview.AddString(_T("视频流"));
	m_cbDefPreview.SetCurSel(gcfg.GetUiPreviewDefault());

	m_cbDefCam.AddString(_T("采集卡 1"));
	m_cbDefCam.AddString(_T("采集卡 2"));
	m_cbDefCam.AddString(_T("采集卡 3"));
	m_cbDefCam.SetCurSel(gcfg.GetUiLiveDefault());


	m_chkTransparentGauge.SetCheck(gcfg.GetUiOpTransparentGauge() ? BST_CHECKED:BST_UNCHECKED);
	m_chkGuage.SetCheck(gcfg.GetUiOpShowGauge() ? BST_CHECKED:BST_UNCHECKED);
	m_chkSaveHistory.SetCheck(gcfg.GetUiOpAutoSaveHistory() ? BST_CHECKED:BST_UNCHECKED);
	m_chkOpenPreview.SetCheck(gcfg.GetUiPreviewOpen() ? BST_CHECKED:BST_UNCHECKED);
	m_chkShowCursor.SetCheck(gcfg.GetUiPreviewShowCursor() ? BST_CHECKED:BST_UNCHECKED);
	
	return FALSE;
}

BOOL CUiCfgDlg::SaveCfg(CString &strTip)
{
	gcfg.SetUiOpDefaut(m_cbDefOperated.GetCurSel());
	gcfg.SetUiPreviewDefault(m_cbDefPreview.GetCurSel());
	gcfg.SetUiLiveDefault(m_cbDefCam.GetCurSel());
	gcfg.SetUiOpTransparentGauge((m_chkTransparentGauge.GetCheck()==BST_CHECKED));
	gcfg.SetUiOpShowGauge((m_chkGuage.GetCheck()==BST_CHECKED));
	gcfg.SetUiOpAutoSaveHistory((m_chkSaveHistory.GetCheck()==BST_CHECKED));
	gcfg.SetUiPreviewOpen((m_chkOpenPreview.GetCheck()==BST_CHECKED));
	gcfg.SetUiPreviewShowCursor((m_chkShowCursor.GetCheck()==BST_CHECKED));

	return TRUE;
}
