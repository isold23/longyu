#include "stdafx.h"
#include "Resource.h"
#include "VideoSrcDlg.h"
#include "DrawHelper.h"
#include "Cfg.h"
#include "FileHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



IMPLEMENT_DYNAMIC(CVideoSrcDlg, CResizableDialog)

CVideoSrcDlg::CVideoSrcDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CVideoSrcDlg::IDD, pParent)
{
}

CVideoSrcDlg::~CVideoSrcDlg()
{
}

void CVideoSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_SLD_VOLUME, m_sliderVolume);
	DDX_Control(pDX, IDC_CHK_MUTE, m_chkMute);

}


BEGIN_MESSAGE_MAP(CVideoSrcDlg, CResizableDialog)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHK_MUTE,&CVideoSrcDlg::OnMute)
	ON_NOTIFY(TCN_SELCHANGE,IDC_TAB,&CVideoSrcDlg::OnTabSelChanged)
	ON_NOTIFY(TCN_SELCHANGING,IDC_TAB,&CVideoSrcDlg::OnTabSelChanging)
	ON_MESSAGE(CVolumeSetter::WM_VOLUME_CHANGED,&CVideoSrcDlg::OnMixerControlChange)
END_MESSAGE_MAP()

BOOL CVideoSrcDlg::OnInitDialog(void)
{
	CResizableDialog::OnInitDialog();

	m_webBrowserDlg.Create(CWebBrowserSrcDlg::IDD,this);
	m_mediaPlayerDlg.Create(CMediaPlayerSrcDlg::IDD,this);
	m_dshowDlg.Create(CDShowSrcDlg::IDD,this);
	m_picDlg.Create(CPicSrcDlg::IDD,this);

	Fh::Cder cder(gsys.PicPath());
	m_imageList.Create(24,24,ILC_COLOR32,4,1);
	m_imageList.Add((HICON)LoadImage(NULL,_T("WebBrowser.ico"),IMAGE_ICON,0,0,LR_LOADFROMFILE));
	m_imageList.Add((HICON)LoadImage(NULL,_T("MediaFile.ico"),IMAGE_ICON,0,0,LR_LOADFROMFILE));
	m_imageList.Add((HICON)LoadImage(NULL,_T("Picture.ico"),IMAGE_ICON,0,0,LR_LOADFROMFILE));
	m_imageList.Add((HICON)LoadImage(NULL,_T("CaptureDevice.ico"),IMAGE_ICON,0,0,LR_LOADFROMFILE));

	m_tab.SetImageList(&m_imageList);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT|TCIF_IMAGE,0,m_webBrowserDlg.GetName(),0,(LPARAM)(CVideoSrcBaseDialog*)&m_webBrowserDlg);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT|TCIF_IMAGE,1,m_mediaPlayerDlg.GetName(),1,(LPARAM)(CVideoSrcBaseDialog*)&m_mediaPlayerDlg);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT|TCIF_IMAGE,2,m_picDlg.GetName(),2,(LPARAM)(CVideoSrcBaseDialog*)&m_picDlg);
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT|TCIF_IMAGE,3,m_dshowDlg.GetName(),3,(LPARAM)(CVideoSrcBaseDialog*)&m_dshowDlg);
	m_tab.SetCurSel(gcfg.GetUiOpDefaut());

	m_tab.SetItemSize(CSize(-1,28));

	OnTabSelChanged(NULL,NULL);

	AddAnchor(IDC_TAB,TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_STC_CONTENT,TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(m_chkMute,TOP_RIGHT);
	AddAnchor(m_sliderVolume,TOP_RIGHT);

	m_chkMute.SetImageFile(_T("Unmuted.png"),_T("Muted.png"));
	m_chkMute.SetTip(_T("¾²Òô"),_T("È¡Ïû¾²Òô"));


	if (m_volSetter.Init(GetSafeHwnd()))
	{
		m_sliderVolume.EnableWindow(TRUE);
		m_sliderVolume.SetRange(m_volSetter.GetMinVol(),m_volSetter.GetMaxVol());
		m_sliderVolume.SetPos(m_volSetter.GetCurVol());

		m_chkMute.EnableWindow(TRUE);

		m_chkMute.SetChecked(m_volSetter.IsMute());
	} 
	return TRUE;
}
 

void CVideoSrcDlg::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType,cx,cy);

	if (::IsWindow(m_tab.m_hWnd))
	{
		CVideoSrcBaseDialog *pWnd = GetCurSel();
		CWindowRect rc(GetDlgItem(IDC_STC_CONTENT));	
		ScreenToClient(rc);
		pWnd->MoveWindow(rc);
	}
}

void CVideoSrcDlg::RepositionChildren(void)
{
	if (m_webBrowserDlg.GetSafeHwnd() != NULL)
	{
		m_webBrowserDlg.RepositionChildren();
		m_mediaPlayerDlg.RepositionChildren();
		m_dshowDlg.RepositionChildren();
		m_picDlg.RepositionChildren();
	}
}


void CVideoSrcDlg::OnTabSelChanging(NMHDR *pNM, LRESULT *pResult)
{
	GetCurSel()->ShowWindow(SW_HIDE);
	*pResult = FALSE;
}

void CVideoSrcDlg::OnTabSelChanged(NMHDR *pNM, LRESULT *pResult)
{
	CVideoSrcBaseDialog *pWnd = GetCurSel();
	CWindowRect rc(GetDlgItem(IDC_STC_CONTENT));	
	ScreenToClient(rc);
	pWnd->MoveWindow(rc);
	pWnd->ShowWindow(SW_SHOW);
	pWnd->BringWindowToTop();

	CWnd *pDefCtrl = pWnd->GetDefaultCtrl();
	if (pDefCtrl != NULL)
		pDefCtrl->SetFocus();

	if (pResult != NULL)
		*pResult = TRUE;
}
	
void CVideoSrcDlg::SwitchTabTo(int nIndex)
{
	if (m_tab.GetCurSel() != nIndex)
	{
		LRESULT lResult;
		OnTabSelChanging(NULL,&lResult);
		m_tab.SetCurSel(nIndex);
		OnTabSelChanged(NULL,&lResult);
	}
}

void CVideoSrcDlg::OpenVideoFile(const CString &strPath) 
{
	SwitchTabTo(1);
	m_mediaPlayerDlg.OpenVideoFile(strPath);
}

void CVideoSrcDlg::OpenWebPage(const CString &strPath) 
{
	SwitchTabTo(0);
	m_webBrowserDlg.OpenWebPage(strPath);
}
	
void CVideoSrcDlg::OnMute(void)
{
	m_volSetter.Mute(!m_volSetter.IsMute());
}

void CVideoSrcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() == m_sliderVolume.GetSafeHwnd())
	{
		m_volSetter.SetCurVol(m_sliderVolume.GetPos());
	}
}


 
LRESULT CVideoSrcDlg::OnMixerControlChange(WPARAM wParam,LPARAM lParam)
{
	if (m_volSetter.IsVolControl(lParam))
		m_sliderVolume.SetPos(m_volSetter.GetCurVol());
	else if (m_volSetter.IsMuteControl(lParam))
		m_chkMute.SetChecked(m_volSetter.IsMute());
	return CResizableDialog::Default();
}