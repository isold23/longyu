#pragma once
#include "PaneTreeCtrl.h"

class CListDlg;


class CListPane : public CXTPResizeDialog
{ 
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_LIST_PANE };

public:
	CListPane(CWnd* pParent = NULL); 
	virtual ~CListPane(void);

	void SetBindWnd(CListDlg *pListDlg);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);   

	afx_msg void OnBnClickedBtnCmd(void);
	afx_msg void OnBnClickedBtnDetails(void);
	afx_msg void OnTvnDBClickCmd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedCmd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTreeDetails(NMHDR *pNMHDR, LRESULT *pResult); 

	void InitTrees(void);
 
	CPaneTreeCtrl m_treeCmd;
	CTreeCtrl m_treeDetails;

	CImageList m_ilCmd;
	CImageList m_ilDetails;

	CXTPButton m_btnCmd;
	CXTPButton m_btnDetails;

	CListDlg *m_pListDlg;
};
 