#pragma once
#include "CfgChildDlg.h"
#include "afxwin.h"

class CUiCfgDlg : public CCfgChildDlg
{ 
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_CFG_UI };

public:
	CUiCfgDlg(CWnd* pParent = NULL);   
	virtual ~CUiCfgDlg();
 
	LPCTSTR GetCaption(void) const;

	virtual BOOL SaveCfg(CString &strTip);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);     

	CComboBox m_cbDefCam;
	CComboBox m_cbDefPreview;
	CComboBox m_cbDefOperated;
	CButton m_chkTransparentGauge;
	CButton m_chkGuage;
	CButton m_chkSaveHistory;
	CButton m_chkOpenPreview;
	CButton m_chkShowCursor;
};

inline LPCTSTR CUiCfgDlg::GetCaption(void) const {
	return _T("ΩÁ√Ê");
}