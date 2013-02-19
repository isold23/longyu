#include "stdafx.h"
#include "Resource.h"
#include "MediaPlayerSrcDlg.h"
#include "FileHelper.h"
#include "DrawHelper.h"
#include "MediaFormatDef.h"
#include "Cfg.h"
#include "FileHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static const int TIMER_MP_CHECKER = 100;
static const int ELAPSE_MP_CHECKER = 100;

 
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CMediaPlayerSrcDlg::CMediaPlayerSrcDlg(CWnd* pParent /*=NULL*/)
	: CVideoSrcBaseDialog(CMediaPlayerSrcDlg::IDD, pParent),
	  m_nTimerMpChecker(0),
	  m_cbHistory(_T("MediaPlayHistory"))
{
	m_pcszName = _T("视频文件");
}

CMediaPlayerSrcDlg::~CMediaPlayerSrcDlg(void)
{
}

void CMediaPlayerSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CVideoSrcBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_HISTORY, m_cbHistory);
	DDX_Control(pDX,IDC_STC_VIDEO, m_stcVideo);
	DDX_Control(pDX, IDC_SLD_PROGRESS, m_sliderProgress);
	DDX_Control(pDX, IDC_SLD_VOLUME, m_sliderVolume);
	DDX_Control(pDX, IDC_CHK_PLAY, m_chkPlay);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_STEP, m_btnStep);
	DDX_Control(pDX, IDC_CHK_MUTE, m_chkMute);
	DDX_Control(pDX, IDC_BTN_SKIP_BACKWARD, m_btnSkipBackward);
	DDX_Control(pDX, IDC_BTN_SKIP_FORWORD, m_btnSkipForeward);
	DDX_Control(pDX, IDC_BTN_SELECT_FILE, m_btnOpen);

}

 
BEGIN_MESSAGE_MAP(CMediaPlayerSrcDlg, CVideoSrcBaseDialog)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_CB_HISTORY,&CMediaPlayerSrcDlg::OnCBHistorySelChange)
	ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CMediaPlayerSrcDlg::OnBnClickedBtnSelectFile)
	ON_BN_CLICKED(IDC_CHK_PLAY, &CMediaPlayerSrcDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, &CMediaPlayerSrcDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_STEP, &CMediaPlayerSrcDlg::OnBnClickedBtnStep)
	ON_BN_CLICKED(IDC_CHK_MUTE, &CMediaPlayerSrcDlg::OnBnClickedBtnMute)
	ON_BN_CLICKED(IDC_BTN_SKIP_BACKWARD, &CMediaPlayerSrcDlg::OnBnClickedBtnSkipBackward)
	ON_BN_CLICKED(IDC_BTN_SKIP_FORWORD, &CMediaPlayerSrcDlg::OnBnClickedBtnSkipForword)
END_MESSAGE_MAP()
   
 
BOOL CMediaPlayerSrcDlg::OnInitDialog(void)
{
	CVideoSrcBaseDialog::OnInitDialog();

	AddAnchor(m_cbHistory,TOP_LEFT,TOP_RIGHT);
	AddAnchor(m_btnOpen,TOP_RIGHT);
	
	AddAnchor(IDC_STC_VIDEO,TOP_LEFT,BOTTOM_RIGHT);

	AddAnchor(IDC_SLD_PROGRESS,BOTTOM_LEFT,BOTTOM_RIGHT);

	AddAnchor(m_chkPlay,BOTTOM_LEFT);
	AddAnchor(m_btnStop,BOTTOM_LEFT);
	AddAnchor(m_btnStep,BOTTOM_LEFT); 
	AddAnchor(m_btnSkipBackward,BOTTOM_LEFT);
	AddAnchor(m_btnSkipForeward,BOTTOM_LEFT); 
	AddAnchor(m_chkMute,BOTTOM_RIGHT);
	AddAnchor(m_sliderVolume,BOTTOM_RIGHT);

	m_mediaPlayer.SetRenderWnd(m_stcVideo);

	m_sliderProgress.SetRange(0,200);
	m_sliderProgress.SetPageSize(5);
	m_sliderVolume.SetRange(0,100);
	m_sliderVolume.SetPos(100);

	m_gaugeWnd.Create(&m_stcVideo,gcfg.GetUiOpTransparentGauge());
	m_cbHistory.SetFocus();

	m_stcVideo.ModifyStyle(0,WS_CLIPCHILDREN);

	Fh::Cder cder(gsys.PicPath());

	m_chkPlay.SetImageFile(_T("PlayerPlay.png"),_T("PlayerPause.png"));
	m_chkPlay.SetTip(_T("播放"),_T("暂停"));

	m_btnStop.SetImageFile(_T("PlayerStop.png"));
	m_btnStop.SetTip(_T("停止"));

	m_btnStep.SetImageFile(_T("PlayerStep.png"));
	//m_btnStep.SetTip(_T("步进"));

	m_btnSkipBackward.SetImageFile(_T("PlayerBackward.png"));
	//m_btnSkipBackward.SetTip(_T("步进"));


	m_btnSkipForeward.SetImageFile(_T("PlayerForward.png"));

	m_chkMute.SetImageFile(_T("Unmuted.png"),_T("Muted.png"));
	m_chkMute.SetTip(_T("静音"),_T("取消静音"));


	m_btnOpen.SetImageFile(_T("OpenFile.png"));
	m_btnOpen.SetTip(_T("打开文件"));

	//m_chkPlay.EnableWindow(FALSE);
	//m_btnStop.EnableWindow(FALSE);
	//m_btnStep.EnableWindow(FALSE);
	//m_btnSkipBackward.EnableWindow(FALSE);
	//m_btnSkipForeward.EnableWindow(FALSE);
	//m_chkMute.EnableWindow(FALSE);
	


	return TRUE;
}

BOOL CMediaPlayerSrcDlg::OnEraseBkgnd(CDC* pDC)
{
	CWindowRect rc(m_stcVideo);
	ScreenToClient(&rc);
	pDC->ExcludeClipRect(&rc);

	return CDialog::OnEraseBkgnd(pDC);
}
 
static LPCTSTR ALL_VIDEO_FILTER = _T("MPEG文件 (*.mpg)|*.*;||");

void CMediaPlayerSrcDlg::OnBnClickedBtnSelectFile(void)
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_ENABLESIZING,ALL_VIDEO_FILTER);
	if (dlg.DoModal() == IDOK)
		Play(dlg.GetPathName());
}

void CMediaPlayerSrcDlg::Play(const CString &strFilePath)
{
	if (m_mediaPlayer.StatusMovie() != CMediaPlayer::MOVIE_NOTOPENED)
	{
		if (m_mediaPlayer.StatusMovie() != CMediaPlayer::MOVIE_STOPPED)
			m_mediaPlayer.StopMovie();
		m_mediaPlayer.CloseMovie();
	}

	if (m_mediaPlayer.OpenMovie(strFilePath))
	{
		if (!m_mediaPlayer.PlayMovie())
			m_mediaPlayer.CloseMovie();
		else
			m_cbHistory.Add(strFilePath);
		m_mediaPlayer.SetVolume(m_sliderVolume.GetPos());
	}

	if (m_mediaPlayer.StatusMovie() != CMediaPlayer::MOVIE_NOTOPENED)
	{
		if (m_nTimerMpChecker == 0)
			m_nTimerMpChecker = SetTimer(TIMER_MP_CHECKER,ELAPSE_MP_CHECKER,NULL);
	}
	else
	{
		CString str ;
		str.Format(_T("打开视频文件 \"%s\" 失败,请确认视频文件路径及格式正确"),Fh::GetFileName(strFilePath));
		MessageBox(str,_T("提示信息"),MB_ICONINFORMATION);
	}
}

void CMediaPlayerSrcDlg::RepositionVideo(void)
{
	if (m_stcVideo.GetSafeHwnd() != NULL)
	{
		CClientRect rc(m_stcVideo);
	}
}
 

void CMediaPlayerSrcDlg::OnCBHistorySelChange(void)
{
	CString str;
	int nIndex = m_cbHistory.GetCurSel();
	m_cbHistory.GetLBText(nIndex,str); 
 	Play(str);
}

void CMediaPlayerSrcDlg::OnOK(void)
{
	CString str;
	m_cbHistory.GetWindowText(str);
	str.Trim();
	if (!str.IsEmpty())
		Play(str);
}

void CMediaPlayerSrcDlg::OnSize(UINT nType, int cx, int cy)
{
	CVideoSrcBaseDialog::OnSize(nType,cx,cy);
	m_mediaPlayer.RepositionVideoWnd();
}


void CMediaPlayerSrcDlg::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar *pScrollBar)
{
	
	if (pScrollBar->GetSafeHwnd() ==  m_sliderProgress.GetSafeHwnd())
	{
		{
			int nCur = m_sliderProgress.GetPos();
			int nMax = m_sliderProgress.GetRangeMax();
			if (m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_PLAYING ||
				m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_PAUSED)
			{
				DOUBLE rf = nCur/(double)nMax;
				m_mediaPlayer.SeekToPercent(rf);
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() ==  m_sliderVolume.GetSafeHwnd())
	{  
		if (m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_PLAYING ||
			m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_PAUSED)
		{ 
			m_mediaPlayer.SetVolume(m_sliderVolume.GetPos());
		}
	}

	CVideoSrcBaseDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMediaPlayerSrcDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case TIMER_MP_CHECKER:
		if (m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_PLAYING)
		{
			DOUBLE rtCur = m_mediaPlayer.GetCurrentPosition();
			DOUBLE rtDur = m_mediaPlayer.GetDuration();

			int nMin,nMax;
			int nCur = m_sliderProgress.GetPos();
			m_sliderProgress.GetRange(nMin,nMax);

			int nTo = (int)(rtCur/rtDur*(nMax-nMin) + nMin);
			if (nCur != nTo)
				m_sliderProgress.SetPos(nTo);
		}
		break;
	}

	CVideoSrcBaseDialog::OnTimer(nIDEvent);
}

void CMediaPlayerSrcDlg::OnBnClickedBtnPlay(void)
{
	switch (m_mediaPlayer.StatusMovie())
	{
	case CMediaPlayer::MOVIE_NOTOPENED:
		{
			CString str;
			m_cbHistory.GetWindowText(str);
			str.Trim();
			if (!str.IsEmpty())
			{
				Play(str);
			}
			else
			{
				OnBnClickedBtnSelectFile();
				if (m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_PLAYING)
					m_chkPlay.SetChecked(TRUE);
			}
		}
		break;
	case CMediaPlayer::MOVIE_PLAYING:
		m_mediaPlayer.PauseMovie();
		m_chkPlay.ToggleChecked();
		break;
	case CMediaPlayer::MOVIE_PAUSED:
	case CMediaPlayer::MOVIE_STOPPED:
		m_mediaPlayer.PlayMovie();
		m_chkPlay.ToggleChecked();
		break;
	default:
		break;
	}
}

void CMediaPlayerSrcDlg::OnBnClickedBtnStop(void)
{
	switch (m_mediaPlayer.StatusMovie())
	{
	case CMediaPlayer::MOVIE_PLAYING:
	case CMediaPlayer::MOVIE_PAUSED:
		m_mediaPlayer.StopMovie();
		break;
	}
}

void CMediaPlayerSrcDlg::OnBnClickedBtnStep(void)
{
	m_mediaPlayer.FrameStepMovie();
}

void CMediaPlayerSrcDlg::OnBnClickedBtnMute(void)
{
	BOOL bMuted = !m_mediaPlayer.IsMute();
	m_mediaPlayer.Mute(bMuted);
}

void CMediaPlayerSrcDlg::OnBnClickedBtnSkipBackward(void)
{
	DOUBLE t = -1.0f;
	m_mediaPlayer.SeekOffset(t);
}

void CMediaPlayerSrcDlg::OnBnClickedBtnSkipForword(void)
{
		DOUBLE t = 1.0f;
		m_mediaPlayer.SeekOffset(t);
}

DWORD CMediaPlayerSrcDlg::GetSampleTick(void)
{
	return max(m_gaugeWnd.GetSampleTick(),m_mediaPlayer.GetSampleTick());
}

BOOL CMediaPlayerSrcDlg::GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample)
{
	if (m_mediaPlayer.StatusMovie() == CMediaPlayer::MOVIE_NOTOPENED)
		return FALSE;
	
	if (!m_mediaPlayer.GetSample(buf,sizeFull))
		return FALSE;

	rcSample = CRect(0,0,sizeFull.cx,sizeFull.cy);
	m_gaugeWnd.CalcViewRect(rcSample);

	int nHeight = rcSample.Height();
	rcSample.bottom = sizeFull.cy - rcSample.top;
	rcSample.top = rcSample.bottom - nHeight;

	nStride = sizeFull.cx*def_vBytesPerPixel;
	buf.Set(buf.Ptr()+(rcSample.left+rcSample.top*sizeFull.cx)*def_vBytesPerPixel,nStride*nHeight);

	return TRUE;
}

CString CMediaPlayerSrcDlg::GetDesc(void)
{
	return m_mediaPlayer.GetFilePath();
}

void CMediaPlayerSrcDlg::SampleRef(BOOL bRef)
{
	m_mediaPlayer.SampleRef(bRef);
}
