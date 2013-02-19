#pragma once 
#include "HtmlCtrl.h" 
#include "HistoryCtrl.h"
#include "VideoSrcBaseDialog.h"
#include "ImageButton.h"

namespace Gdiplus { class Bitmap;}

class CWebBrowserSrcDlg : public CVideoSrcBaseDialog
{
	DIALOG_MASK_CANCEL()
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_WEBBROWSER };
	

public:
	CWebBrowserSrcDlg(CWnd* pParent = NULL);  
	virtual ~CWebBrowserSrcDlg(void);

	BOOL OpenWebPage(const CString &strPath);
 
	BOOL GetDrawCursor(void) const;
	virtual void SetDrawCursor(BOOL bDraw);

	virtual BOOL GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample);

	virtual CString GetDesc(void);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);   

	afx_msg void OnBnClickedBtnStop(void);
	afx_msg void OnBnClickedBtnBackward(void);
	afx_msg void OnBnClickedBtnForward(void);

	afx_msg void OnCBHistorySelChange(void);
	afx_msg LRESULT OnHtmlCtrl(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedBtnZoom(void);
	afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar *pScrollBar); 

	virtual void OnOK(void);
	BOOL OnDocComplete(void);

	virtual CWnd* GetDefaultCtrl(void);
	
	BOOL m_bDrawCursor;
	CHtmlCtrl m_htmlCtrl;
	CHistoryCtrl m_cbHistory;
 
	CSliderCtrl m_sliderZoom;

	CImageButton m_btnZoom;
	CImageButton m_btnGo;
	CImageButton m_btnStop;
	CImageButton m_btnBackward;
	CImageButton m_btnForward;

	Gdiplus::Bitmap *m_pBitmap;
	CComPtr<IHTMLElementRender> m_pRender;
};

inline BOOL CWebBrowserSrcDlg::OpenWebPage(const CString &strPath) {
	m_htmlCtrl.Navigate(strPath);
	return TRUE;
}

inline BOOL CWebBrowserSrcDlg::GetDrawCursor(void) const {
	return m_bDrawCursor;
}

inline void CWebBrowserSrcDlg::SetDrawCursor(BOOL bDraw) {
	m_bDrawCursor = bDraw;
}