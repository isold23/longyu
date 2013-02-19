#pragma once

#include "ResizableDialog.h"
#include "Program.h"
#include "ImageButton.h"

 
class CProgramDlg : public CResizableDialog
{ 
	DECLARE_MESSAGE_MAP()
	DIALOG_MASK_OKCANCEL()

public:
	enum { IDD = IDD_PROGRAM };

	enum {WM_OPEN_CONTENTLINK=WM_USER+0x212};
public:
	CProgramDlg(CWnd* pParent = NULL);  
	virtual ~CProgramDlg();
 
	void OpenProgramFile(void);

	CProgram& GetProgram(void);

	BOOL QuitConfirm(void);
	
	BOOL OpenNew(void);
	BOOL Reload(void);
	BOOL ShowProp(void);

	BOOL Save(void);
	BOOL SaveAs(void);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);  

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		
	afx_msg void OnBnClickedBtnAdd(void);
	afx_msg void OnBnClickedBtnDown(void);
	afx_msg void OnBnClickedBtnUp(void);
	afx_msg void OnBnClickedBtnDel(void);
	afx_msg void OnBnClickedBtnProp(void);
	afx_msg void OnListProgramSelChange(void);
	afx_msg void OnListProgramDblClicked(void);

	void RefreshProgram(void);

	CEdit m_editDesc;
	CListBox m_listProgram;
	CStatic m_stcProgramName;

	CImageButton m_btnAdd;
	CImageButton m_btnDel;
	CImageButton m_btnUp;
	CImageButton m_btnDown;
	CImageButton m_btnProp;

	CProgram m_program;

	CFont m_fontDesc;
	CFont m_fontList;
};

inline CProgram& CProgramDlg::GetProgram(void) {
	return m_program;
}
