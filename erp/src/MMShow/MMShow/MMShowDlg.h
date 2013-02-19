#pragma once

#include "Program.h" 
#include "ProgramDlg.h"
#include "VideoSrcDlg.h"
#include "PreviewDlg.h"
#include "OutputDlg.h"
#include "LiveSrcDlg.h"
#include "ImageButton.h"
 


class CMMShowDlg : public CResizableDialog
{
	DECLARE_MESSAGE_MAP()
	DIALOG_MASK_OK()
	enum { IDD = IDD_MMSHOW_DIALOG };

public:
	CMMShowDlg(CWnd* pParent = NULL);

 
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel(void);

	afx_msg void OnMove(int x, int y);

	afx_msg void OnProgramMenu(UINT nCmdId);
	
	afx_msg void OnMenuExit(void);
	afx_msg void OnMenuAbout(void);
	afx_msg void OnMenuOption(void);
	afx_msg LRESULT OnOpenContentLink(WPARAM wParam,LPARAM lParam);

	CImageButton m_btnNew;
	CImageButton m_btnSave;
	CImageButton m_btnSaveAs;
	CImageButton m_btnReload;
	CImageButton m_btnExit;
	CImageButton m_btnProp;
	CImageButton m_btnAbout;
	CImageButton m_btnOption;
	CImageButton m_btnOpen; 
 
	CProgramDlg m_programDlg;
	CVideoSrcDlg m_videoSrcDlg;
	CPreviewDlg m_previewDlg;
	CLiveSrcDlg m_liveSrcDlg;
	COutputDlg m_outputDlg;

	HACCEL m_hAccelTable;
};
