#pragma once
#include "HistoryCtrl.h"
#include "PictureCtrl.h"
#include "VideoSrcBaseDialog.h"
#include "ImageButton.h"

class CPicSrcDlg : public CVideoSrcBaseDialog
{
	DIALOG_MASK_CANCEL()
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CPicSrcDlg)

public:
	enum { IDD = IDD_PIC };

public:
	CPicSrcDlg(CWnd* pParent = NULL);   
	virtual ~CPicSrcDlg(void);

	virtual DWORD GetSampleTick(void);
	virtual BOOL GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample);

	virtual CString GetDesc(void);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);     
	virtual void OnOK(void);

	afx_msg void OnBnClickedBtnSelectFile(void);
	afx_msg void OnCBHistorySelChange(void);	

	void Show(const CString &strFilePath);

	CHistoryCtrl m_cbHistory;
	CPictureCtrl m_pictureCtrl;
	CImageButton m_btnOpen;
};
 