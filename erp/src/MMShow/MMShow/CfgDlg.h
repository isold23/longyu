#pragma once

#include "CamCfgDlg.h"
#include "OutputCfgDlg.h"
#include "RecordCfgDlg.h"
#include "UiCfgDlg.h"

 
class CCfgDlg : public CDialog
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_CFG };
	enum {Cam,Output,Record,Ui};

public:
	CCfgDlg(CWnd* pParent = NULL);  
	virtual ~CCfgDlg(void);
 
	void SetForceCamCfg(BOOL bForce);
	void SetStartIndex(int nIndex);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual void OnOK(void);
	virtual void OnCancel(void);

	afx_msg void OnTabSelChange(NMHDR *pNM,LRESULT *pResult);

	CCamCfgDlg m_camDlg;
	COutputCfgDlg m_outputDlg;
	CRecordCfgDlg m_recordDlg;
	CUiCfgDlg m_uiDlg;

	CTabCtrl m_tab;
	int m_nStartIndex;
	BOOL m_bForceCamCfg;
};

inline void CCfgDlg::SetStartIndex(int nIndex) {
	ASSERT(m_nStartIndex>=0 && m_nStartIndex<=Ui);
	m_nStartIndex = nIndex;
}

inline void CCfgDlg::SetForceCamCfg(BOOL bForce) {
	m_bForceCamCfg = bForce;
}