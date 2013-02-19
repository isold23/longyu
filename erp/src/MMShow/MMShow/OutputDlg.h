#pragma once

#include "ResizableDialog.h"
#include "MediaFileWriter.h"
#include "AudioCapture.h"
#include "CardWriter.h"
#include "RenderStatic.h"
#include "ImageButton.h"
#include "WindowRender.h"
#include "CurCfg.h"

class CPreviewDlg;
class CLiveSrcDlg;


class COutputDlg :
	public CResizableDialog,
	public CAudioCapture::Callback
{
	DIALOG_MASK_OKCANCEL()
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_OUTPUT };

public:
	COutputDlg(CWnd* pParent = NULL);   
	virtual ~COutputDlg(void);

	void SetSourceDlg(CPreviewDlg *pPreviewDlg,CLiveSrcDlg *pLiveSrcDlg);
	
	void ClearVideo(void);
	
	HWND GetRenderWindow(void);
	void WriteMediaVideo(LPCVOID buf,CSize size,int stride);

	void RenderVideo(LPCVOID buf,CSize size,int stride);

	void ChangeSrcTo(BOOL bPreviewer);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);   
	virtual void onAudioData(LPCVOID data,int len);

	afx_msg void OnDestroy(void);
	afx_msg void OnChangeSrc(void);
	afx_msg void OnOutputSelChange(void);
	afx_msg void OnBnClickedBtnRecord(void);
	afx_msg void OnBnClickedBtnSelRecFile(void);
	afx_msg void OnOutputCfg(void);

	afx_msg LRESULT OnOutputCfgFininshed(WPARAM wParam,LPARAM lParam);

	CRenderStatic m_stcVideo;
	CWindowRender m_windowRender;

	CEdit m_editRecPath;

	CComboBox m_cbOutput;
	CImageButton m_btnOpen;
	CImageButton m_chkRecord;
	CImageButton m_btnCfg;;

	CImageButton m_rdLive;
	CImageButton m_rdPreview;

	int  m_nOutputIndex;

	CPreviewDlg *m_pPreviewDlg;
	CLiveSrcDlg *m_pLiveSrcDlg;

	CAudioCapture m_audioCapture;

	CCardWriter m_cardWriter;
	CMediaFileWriter m_mediaFileWriter;

	CCurCfg s_curCfg;


	HANDLE m_hOutputThread;
	BOOL m_bOutputStop;
	LPCVOID m_pOutputBuf;
	CSize m_sizeOfOutput;
	int m_nOutputStride;
	CEvent m_eventOutput;
	void OutptutThreadProc(void);
	static DWORD WINAPI OutptutWorkerThreadProc(LPVOID pv);
};

inline void COutputDlg::ClearVideo(void) {
	m_stcVideo.Invalidate();
}

inline HWND COutputDlg::GetRenderWindow(void) {
	return m_stcVideo;
}

