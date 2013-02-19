#pragma once
#include "MediaPlayer.h"
#include "HistoryCtrl.h"
#include "VideoSrcBaseDialog.h"
#include "ImageButton.h"
 

class CMediaPlayerSrcDlg : public CVideoSrcBaseDialog
{
	DIALOG_MASK_CANCEL()
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_MIDEAPLAYER };

public:
	CMediaPlayerSrcDlg(CWnd* pParent = NULL);
	virtual ~CMediaPlayerSrcDlg(void);

	BOOL OpenVideoFile(const CString &strPath);

	virtual void SampleRef(BOOL bRef);

	virtual DWORD GetSampleTick(void);
	virtual BOOL GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample);

	virtual CString GetDesc(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog(void);
	virtual void OnOK(void);
 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnSelectFile(void);
	afx_msg void OnCBHistorySelChange(void);
	afx_msg void OnBnClickedBtnPlay(void);
	afx_msg void OnBnClickedBtnStop(void);
	afx_msg void OnBnClickedBtnStep(void);
	afx_msg void OnBnClickedBtnMute(void);
	afx_msg void OnBnClickedBtnSkipBackward(void);
	afx_msg void OnBnClickedBtnSkipForword(void);
	afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar *pScrollBar);


	void RepositionVideo(void);
	void Play(const CString &strFilePath);
 
private:
 
	CHistoryCtrl m_cbHistory;
	CMediaPlayer m_mediaPlayer;
	
	CSliderCtrl m_sliderProgress;
	CSliderCtrl m_sliderVolume;
	CStatic m_stcVideo;

	CImageButton m_chkPlay;
	CImageButton m_btnStop;
	CImageButton m_btnStep;
	CImageButton m_chkMute;
	CImageButton m_btnSkipBackward;
	CImageButton m_btnSkipForeward;

	CImageButton m_btnOpen;

	UINT_PTR m_nTimerMpChecker;
};
inline BOOL CMediaPlayerSrcDlg::OpenVideoFile(const CString &strPath) {
	Play(strPath);
	return TRUE;
}
