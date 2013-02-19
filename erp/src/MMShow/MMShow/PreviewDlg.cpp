#include "stdafx.h"
#include "Resource.h"
#include "PreviewDlg.h"
#include "VideoSrcDlg.h"
#include "DrawHelper.h"
#include "OutputDlg.h"
#include "MediaFormatDef.h" 
#include "Cfg.h"
#include "FileHelper.h"
#include "CurCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*
	*------------***************************------------*
		  *--------------*CPreviewDlg*------------*
	*------------***************************------------*
*/	

const UINT_PTR TIMER_CAPTURE_ID = 100;

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CPreviewDlg::IDD, pParent),
		m_nFrameCount(0),
		m_pCurSelVideoDlg(NULL),
		m_pOutputDlg(NULL),
		m_chkCursor(TRUE),
		m_chkGauge(TRUE),
		m_chkPreview(TRUE),
		m_pRefOutputDlg(NULL)
{
}
 
CPreviewDlg::~CPreviewDlg(void)
{
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TAB,m_tab);
	DDX_Control(pDX,IDC_STC_PREVIEW,m_stcPreview);
	DDX_Control(pDX,IDC_CHK_PREVIEW,m_chkPreview);
	DDX_Control(pDX,IDC_CHK_CURSOR,m_chkCursor);
	DDX_Control(pDX,IDC_CHK_GAUGE,m_chkGauge);
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CResizableDialog) 
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	//ON_WM_CTLCOLOR() 
	ON_NOTIFY(TCN_SELCHANGE,IDC_TAB,&CPreviewDlg::OnTabSelChange)
	ON_NOTIFY(TCN_SELCHANGING,IDC_TAB,&CPreviewDlg::OnTabSelChanging)
	ON_BN_CLICKED(IDC_CHK_PREVIEW,&CPreviewDlg::OnChkPreview)
	ON_BN_CLICKED(IDC_CHK_CURSOR,&CPreviewDlg::OnChkCursor)
	ON_BN_CLICKED(IDC_CHK_GAUGE,&CPreviewDlg::OnChkGauge)
	
END_MESSAGE_MAP()

 
BOOL CPreviewDlg::OnInitDialog(void)
{
	CResizableDialog::OnInitDialog();
  
	AddAnchor(m_tab,TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(m_stcPreview,TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(m_chkPreview,BOTTOM_LEFT);
	AddAnchor(m_chkCursor,BOTTOM_LEFT);
	AddAnchor(m_chkGauge,BOTTOM_LEFT);
	AddAnchor(IDC_BTN_CLEAR,BOTTOM_LEFT);
	
	Fh::Cder cder(gsys.PicPath());

	m_chkPreview.SetImageFile(_T("PreviewOff.png"),_T("PreviewOn.png"));
	m_chkPreview.SetTip(_T("预览"),_T("取消预览"));

	m_chkGauge.SetImageFile(_T("PreviewGaugeOff.png"),_T("PreviewGaugeOn.png"));
	m_chkGauge.SetTip(_T("显示选择框"),_T("隐藏选择框"));

	m_chkCursor.SetImageFile(_T("PreviewCursorOff.png"),_T("PreviewCursorOn.png"));
	m_chkCursor.SetTip(_T("显示光标"),_T("隐藏光标"));


	m_tab.SetItemSize(CSize(-1,28));

	m_windowRender.Start(m_stcPreview);
	return TRUE;
}

void CPreviewDlg::OnTabSelChanging(NMHDR *pNM,LRESULT *pResult)
{
	if (IsPreviewing())
		m_pCurSelVideoDlg->SampleRef(FALSE);
	if (pResult != NULL)
		*pResult = FALSE;
}

void CPreviewDlg::OnTabSelChange(NMHDR *pNM,LRESULT *pResult)
{
	int nIndex = m_tab.GetCurSel();
	m_pCurSelVideoDlg = GetVideoDlgAt(nIndex);
	GetDlgItem(IDC_CHK_CURSOR)->ShowWindow(nIndex==0 ? SW_SHOW:SW_HIDE);
	if (m_pOutputDlg != NULL)
		m_pOutputDlg->ClearVideo();

	if (IsPreviewing())
		m_pCurSelVideoDlg->SampleRef(TRUE);

	m_stcPreview.Invalidate(TRUE);
	if (pResult != NULL)
		*pResult = TRUE;
}

HBRUSH CPreviewDlg::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() != IDC_EDIT_DESC)
		return hBrush;

	pDC->SetTextColor(GetSysColor(COLOR_WINDOW));
	pDC->SetBkMode(TRANSPARENT);
	return GetSysColorBrush(COLOR_WINDOW);
}

void CPreviewDlg::SetImageList(CImageList *pImageList) 
{
	m_tab.SetImageList(pImageList);
} 

void CPreviewDlg::AddSrcItem(CVideoSrcBaseDialog *pVideBaseDialog)
{
	int nIndex = m_tab.GetItemCount();
	m_tab.InsertItem(TCIF_PARAM|TCIF_TEXT|TCIF_IMAGE,m_tab.GetItemCount(),
	  pVideBaseDialog->GetName(),nIndex,(LPARAM)pVideBaseDialog);
}

void CPreviewDlg::EndAddSrcItem(void)
{
	m_tab.SetCurSel(gcfg.GetUiPreviewDefault());
	OnTabSelChange(NULL,NULL);
	
	m_chkPreview.SetChecked(gcfg.GetUiPreviewOpen());
	m_chkGauge.SetChecked(gcfg.GetUiOpShowGauge());
	m_chkCursor.SetChecked(gcfg.GetUiPreviewShowCursor());

	if (m_chkPreview.IsChecked())
		OnChkPreview();
}

void CPreviewDlg::SetFps(UINT nFps)
{
	if (IsPreviewing())
	{
		KillTimer(TIMER_CAPTURE_ID);
		SetTimer(TIMER_CAPTURE_ID,1000/nFps,NULL);
	}
}

CVideoSrcBaseDialog* CPreviewDlg::GetVideoDlgAt(int nIndex)
{
	TCITEM ti;
	ti.mask = TCIF_PARAM;
	m_tab.GetItem(nIndex,&ti);
	return (CVideoSrcBaseDialog*)ti.lParam;
}



void CPreviewDlg::OnChkPreview(void)
{
	if (IsPreviewing())
	{
		SetTimer(TIMER_CAPTURE_ID,1000/gsys.VideoFpses()[gcfg.GetOutputVideoFps()],NULL);
		m_dwSampleTick = -1;
		m_pCurSelVideoDlg->SampleRef(TRUE);
		//DrawSample();
	}
	else
	{
		m_pCurSelVideoDlg->SampleRef(FALSE);
		KillTimer(TIMER_CAPTURE_ID);
		m_nFrameCount = 0;
		m_stcPreview.Invalidate(TRUE);
	}
}


void CPreviewDlg::OnChkCursor(void)
{
	for (int i=0,cnt=m_tab.GetItemCount(); i<cnt; ++i)
		GetVideoDlgAt(i)->SetDrawCursor(!m_chkCursor.IsChecked());
}


void CPreviewDlg::OnChkGauge(void)
{
	for (int i=0,cnt=m_tab.GetItemCount(); i<cnt; ++i)
		GetVideoDlgAt(i)->ShowGauge(m_chkGauge.IsChecked());
}


static BYTE ImageBuffer[1920*1080*def_vBytesPerPixel];
BOOL CPreviewDlg::DrawSample(CDC &dc,BOOL bForce)
{	
	DWORD dwSampleTick = m_pCurSelVideoDlg->GetSampleTick();
	//if (!bForce && dwSampleTick!=0 && m_dwSampleTick==dwSampleTick)
	//	return FALSE;


	CStaticBuffer buf(ImageBuffer,sizeof(ImageBuffer)); 
	int nStride; CSize sizeFull; CRect rcSample;
	if (!m_pCurSelVideoDlg->GetSample(buf,nStride,sizeFull,rcSample))
		return FALSE;

	m_windowRender.Fill(buf.Ptr(),rcSample.Size(),nStride);

#if 0
	m_windowRender.Render();
	if (m_pOutputDlg != NULL)
		m_pOutputDlg->RenderVideo(buf.Ptr(),rcSample.Size(),nStride);
#else
	if (m_pOutputDlg == NULL)
	{
		m_windowRender.Render();
	}
	else
	{
		HWND renderWnds[] = { m_stcPreview,m_pOutputDlg->GetRenderWindow() };
		m_windowRender.Render(renderWnds,_countof(renderWnds));
		m_pOutputDlg->WriteMediaVideo(buf.Ptr(),rcSample.Size(),nStride);
	}
#endif

	m_dwSampleTick = dwSampleTick;
	return TRUE;
}

void CPreviewDlg::DrawSample(void)
{
	DrawSample(CClientDC(&m_stcPreview));
}

void CPreviewDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_CAPTURE_ID)
	{
		DrawSample();
	}

	CResizableDialog::OnTimer(nIDEvent);
}

void CPreviewDlg::OnDestroy(void)
{
	m_windowRender.Stop();
	CResizableDialog::OnDestroy();
}

 

void CPreviewDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_pRefOutputDlg->ChangeSrcTo(TRUE);
	CResizableDialog::OnLButtonDblClk(nFlags,point);
}