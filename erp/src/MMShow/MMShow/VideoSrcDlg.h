#pragma once

#include "WebBrowserSrcDlg.h"
#include "MediaPlayerSrcDlg.h"
#include "PicSrcDlg.h"
#include "DShowSrcDlg.h"
#include "VolumeSetter.h"
#include "ImageButton.h"
 

class CVideoSrcDlg : public CResizableDialog
{
	DIALOG_MASK_OKCANCEL()
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CVideoSrcDlg)

public:
	enum { IDD = IDD_VIDEO_SRC };

public:
	CVideoSrcDlg(CWnd* pParent = NULL);  
	virtual ~CVideoSrcDlg();
 
	void RepositionChildren(void);

	void OpenVideoFile(const CString &strPath);
	void OpenWebPage(const CString &strPath);
	
	CVideoSrcBaseDialog* GetItem(int nIndex);
	int GetItemCount(void);
	CImageList& GetImageList(void);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnMute(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTabSelChanging(NMHDR *pNM, LRESULT *pResult);
	afx_msg void OnTabSelChanged(NMHDR *pNM, LRESULT *pResult);
	afx_msg LRESULT OnMixerControlChange(WPARAM wParam,LPARAM lParam);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	CVideoSrcBaseDialog* GetCurSel(void);

	void SwitchTabTo(int nIndex);

	CTabCtrl m_tab;
	CWebBrowserSrcDlg m_webBrowserDlg;
	CMediaPlayerSrcDlg m_mediaPlayerDlg;
	CDShowSrcDlg m_dshowDlg;
	CPicSrcDlg m_picDlg;

	CImageList m_imageList;

	CImageButton m_chkMute;
	CSliderCtrl m_sliderVolume;
	CVolumeSetter m_volSetter;
};

inline CVideoSrcBaseDialog* CVideoSrcDlg::GetItem(int nIndex) {
	ASSERT(nIndex>=0 && nIndex<m_tab.GetItemCount());

	TCITEM ti;
	ti.mask = TCIF_PARAM;
	m_tab.GetItem(nIndex,&ti);

	return (CVideoSrcBaseDialog*)ti.lParam;
}

inline CVideoSrcBaseDialog* CVideoSrcDlg::GetCurSel(void) {
	return GetItem(m_tab.GetCurSel());
}

inline int CVideoSrcDlg::GetItemCount(void) {	
	return m_tab.GetItemCount();
}

inline CImageList& CVideoSrcDlg::GetImageList(void) {
	return m_imageList;
}

