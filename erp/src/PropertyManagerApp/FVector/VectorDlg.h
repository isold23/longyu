// VectorDlg.h : Í·ÎÄ¼þ
//

#pragma once

#include "Vec\VecWnd.h"
#include "Vec\CopyScreenWnd.h"
#include "combo\ColourPickerXP.h"
#include "combo\PenStyleCombo.h"
#include "combo\PenWidthCombo.h"


class CVectorDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_VECTOR_DIALOG };

	CVectorDlg(CWnd* pParent = NULL);
private: 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOPCommand(UINT uCmd); 
	afx_msg void OnEraseElem(void);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLoad(void);
	afx_msg void OnSave(void);
	afx_msg void OnAdd(void);
	afx_msg void OnRemove(void);
	afx_msg void OnClone(void);
	afx_msg void OnCapture(void);
	afx_msg void OnZoom(UINT uCmd);
	afx_msg void OnAbout(void);
	afx_msg void OnSetTopmost(void);
	afx_msg void OnSetDownmost(void);
	afx_msg void OnBnClickedChkoutline();
	afx_msg void OnBnClickedChkfill();
	afx_msg void OnVecWndSelChange(NMHDR *pNM, LRESULT *pResult);
	afx_msg void OnVecWndHoverChange(NMHDR *pNM, LRESULT *pResult);
	afx_msg void OnCBOutlineStyle(void);
	afx_msg void OnCBOutlineWidth(void);
	afx_msg void OnBkgndImage(void);
	afx_msg LRESULT OnCPSelChang(WPARAM wParam,LPARAM lParam); 
	afx_msg BOOL OnToolTipText(UINT nID,NMHDR* pNMHDR, LRESULT*pResult);
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

CButton m_chkOutline;
	PenStyleCombo	m_cbOutlineStyle;
	PenWidthCombo	m_cbOutlineWidth;
	CColourPickerXP	m_cpOutlineColor;
	CColourPickerXP m_cpBkColor;
	CEdit m_editCustomData;
	CEdit m_editDesc;
	CToolTipCtrl m_tip;

	CButton m_chkFill;
	
	CColourPickerXP	m_cpFillColor;

	CToolBar m_tb;
	CVecWnd m_wndVec;
	CCopyScreenWnd m_wndCapture;
	UINT m_nOP;     
};
