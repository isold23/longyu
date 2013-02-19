#pragma once
#include "LiveSrcChildDlg.h"
#include "Cams.h"
#include "mthelp.h"

class COutputDlg;
 
class CLiveSrcDlg :
	public CResizableDialog,
	public CCamSampleListener
{
	DIALOG_MASK_OKCANCEL()
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_LIVE_SRC };

public:
	CLiveSrcDlg(CWnd* pParent = NULL);    
	virtual ~CLiveSrcDlg(void);

	void SetRefOutputDlg(COutputDlg *pOutputDlg);

	void SampleRef(BOOL bRef);
	void SetOutput(COutputDlg *pOutputDlg);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);  

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnWannaBig(WPARAM wParam,LPARAM lParam);

	virtual void OnSample(CCamExt *pCamExt);

	CLiveSrcChildDlg* GetBig(void);
	CLiveSrcChildDlg* GetAttached(CStatic &stc);

	CLiveSrcChildDlg x_dlg0;
	CLiveSrcChildDlg x_dlg1;
	CLiveSrcChildDlg x_dlg2;

	CLiveSrcChildDlg *m_pBig;

	CStatic m_stcBig;
	CStatic m_stcSmall;
	CStatic m_stcSmall2;

	COutputDlg *m_pOutputDlg;
	COutputDlg *m_pRefOutputDlg;
	CCriticalSection m_cs;
};


inline void CLiveSrcDlg::SetRefOutputDlg(COutputDlg *pOutputDlg) {
	m_pRefOutputDlg = pOutputDlg;
}

inline CLiveSrcChildDlg* CLiveSrcDlg::GetBig(void) {
	return m_pBig;
}

