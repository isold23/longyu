#pragma once
#include "CfgChildDlg.h"

class CCamCfgDlg : public CCfgChildDlg
{ 
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_CFG_CAMERA};

	static const CStringArray& GetAllCams(void);
public:
	CCamCfgDlg(CWnd* pParent = NULL);   
	virtual ~CCamCfgDlg();
 
	LPCTSTR GetCaption(void) const;

	virtual BOOL SaveCfg(CString &strTip);
	virtual BOOL CancelCfg(CString &strTip);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual BOOL OnInitDialog(void);
 
	CComboBox m_cbCam;
	CComboBox m_cbCam1;
	CComboBox m_cbCam2;
 
public:
	CComboBox m_cbCaptureSize;
};

inline LPCTSTR CCamCfgDlg::GetCaption(void) const {
	return _T("²É¼¯¿¨");
}
