#pragma once

class CCurCfg : public CDialog
{
	DECLARE_MESSAGE_MAP()

public:
	enum {ABitrateF=0x01,ASampleRateF=0x02,AInputF=0x04,
		VFpsF=0x08,VBitrateF=0x10,VSizeF=0x20};
	enum { IDD = IDD_INST_OUTPUT_CFG };
	enum { WM_CFG_FINISHIED = WM_USER+948};

	CCurCfg(CWnd *pParentWnd);
	virtual ~CCurCfg(void);

public: 
	static UINT ABitrate(void);
	static UINT ASampleRate(void);
	static const CString& AInput(void);

	static UINT VFps(void);
	static UINT VBitrate(void);
	static CSize VSize(void);

private:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual void OnOK(void);
	virtual void OnCancel(void);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState,CWnd* pWndOther,BOOL bMinimized);

	UINT UiToMem(void);
	void MemToUi(void);

	int m_aBitrate;
	int m_aSampleRate;
	int m_aInput;

	int m_vFps;
	int m_vBitrate;
	int m_vSize;
 
	CComboBox m_cbVFps;
	CComboBox m_cbVSize;
	CComboBox m_cbVBitrate;

	CComboBox m_cbABitrate;
	CComboBox m_cbASampleRate;
	CComboBox m_cbAInput;
	
	CButton m_chkSaveAsDefault;

	static CCurCfg *s_pInst;
};

