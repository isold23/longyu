#pragma once
#include "CfgChildDlg.h"

class COutputCfgDlg : public CCfgChildDlg
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_CFG_OUTPUT };

public:
	COutputCfgDlg(CWnd* pParent = NULL);  
	virtual ~COutputCfgDlg();

	LPCTSTR GetCaption(void) const;

	virtual BOOL SaveCfg(CString &strTip); 

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);    

	CComboBox m_cbDefVideFps;
	CComboBox m_cbDefVideoSize;
	CComboBox m_cbDefVideoInput;
	CComboBox m_cbDefVideoOutput;
};


inline LPCTSTR COutputCfgDlg::GetCaption(void) const {
	return _T("Êä³ö");
}
