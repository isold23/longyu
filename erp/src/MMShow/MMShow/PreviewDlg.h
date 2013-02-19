#pragma once
#include "ResizableDialog.h"
#include "WindowRender.h"
#include "RenderStatic.h"
#include "ImageButton.h"

class COutputDlg;

class CVideoSrcBaseDialog;
class CPreviewDlg : public CResizableDialog
{ 
	DIALOG_MASK_OKCANCEL()
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_PREVIEW };

public:
	CPreviewDlg(CWnd* pParent = NULL);   
	virtual ~CPreviewDlg(void);

	void SetImageList(CImageList *pImageList);
	void EndAddSrcItem(void);
	void AddSrcItem(CVideoSrcBaseDialog *pVideBaseDialog);

	BOOL IsPreviewing(void);
	void SetFps(UINT nFps);
	void SetOutput(COutputDlg *pOutputDlg);

	void SetRefOutputDlg(COutputDlg *pOutputDlg);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnDestroy(void);
	afx_msg void OnChkPreview(void); 
	afx_msg void OnChkCursor(void); 
	afx_msg void OnChkGauge(void);  
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTabSelChange(NMHDR *pNM,LRESULT *pResult);
	afx_msg void OnTabSelChanging(NMHDR *pNM,LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void DrawSample(void);	
	BOOL DrawSample(CDC &dc,BOOL bForce=FALSE);
	CVideoSrcBaseDialog* GetVideoDlgAt(int nIndex); 

	CTabCtrl m_tab;
 

	CImageButton m_chkPreview;
	CImageButton m_chkCursor;
	CImageButton m_chkGauge;

	CRenderStatic m_stcPreview;
	CWindowRender m_windowRender;

	CVideoSrcBaseDialog *m_pCurSelVideoDlg; 

	UINT m_nFrameCount;

	DWORD m_dwSampleTick;

	COutputDlg *m_pOutputDlg;
	COutputDlg *m_pRefOutputDlg;
};



inline BOOL CPreviewDlg::IsPreviewing(void) {
	return m_chkPreview.IsChecked();
}

inline void CPreviewDlg::SetOutput(COutputDlg *pOutputDlg) {
	m_pOutputDlg = pOutputDlg;
}

inline void CPreviewDlg::SetRefOutputDlg(COutputDlg *pOutputDlg) {
	m_pRefOutputDlg = pOutputDlg;
}
