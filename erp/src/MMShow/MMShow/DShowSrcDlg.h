#pragma once
#include "VideoSrcBaseDialog.h"
#include "RenderStatic.h"
#include "CamExt.h"
 
class CDShowSrcDlg :
	public CVideoSrcBaseDialog,
	public CCamSampleListener
{
	DECLARE_MESSAGE_MAP()

	static const int CamCount = 3;
public:
	enum { IDD = IDD_DSHOW };

public:
	CDShowSrcDlg(CWnd* pParent = NULL);  
	virtual ~CDShowSrcDlg(void);

	virtual void SampleRef(BOOL bRef);
	virtual DWORD GetSampleTick(void);
	virtual BOOL GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnCbCamSelChange(void);

	BOOL m_bSampleRef;
	CComboBox m_cbCam;
	int m_nCurSel;
	CRenderStatic m_stcCams[CamCount];
};
