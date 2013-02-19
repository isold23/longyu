#pragma once
#include "CfgChildDlg.h"

class CRecordCfgDlg : public CCfgChildDlg
{
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_CFG_RECORD };

public:
	CRecordCfgDlg(CWnd* pParent = NULL);    
	virtual ~CRecordCfgDlg(); 

	LPCTSTR GetCaption(void) const;

	virtual BOOL SaveCfg(CString &strTip);
	virtual BOOL CancelCfg(CString &strTip);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);    

	afx_msg void OnBnClickedBtnSelect(void);

	CComboBox m_cbFormat;
	CEdit m_editFolder;
	
	CComboBox m_cbVideoBitrate;

	CComboBox m_cbAudioBitrate;
	CComboBox m_cbAudioSampleRate; 
	CComboBox m_cbAudioInput; 
};

inline LPCTSTR CRecordCfgDlg::GetCaption(void) const {
	return _T("Â¼ÖÆ");
}