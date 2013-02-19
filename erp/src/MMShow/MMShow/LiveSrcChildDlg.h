#pragma once
#include "ResizableDialog.h"
#include "RenderStatic.h"
#include "CamExt.h"

class CLiveSrcChildDlg  : public CResizableDialog
{
	DECLARE_MESSAGE_MAP()
	DIALOG_MASK_OKCANCEL()
	
public:
	enum { IDD = IDD_LIVE_CHILD };
	enum {WM_WANNABIG = WM_USER+11};

public:
	CLiveSrcChildDlg(void);
	virtual ~CLiveSrcChildDlg(void);
 
	void SetCam(CCamSampleListener *pListener,BOOL bNotify,CCamExt *pCamEx=NULL);

	void AttachTo(CWnd *pWnd);
	CWnd* GetAttachTo(void);
	void FollowAttach(void);

	//CCamExt* GetCamEx(void);
	void SampleRef(BOOL bRef);
protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);  
	 
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	CRenderStatic m_stcCam;
 
	int m_nIndex;
	CWnd *m_pAttachTo;

	CCamExt *m_pCamEx;
};

inline CWnd* CLiveSrcChildDlg::GetAttachTo(void) {
	return m_pAttachTo;
}

//inline CCamExt* CLiveSrcChildDlg::GetCamEx(void) {
//	return m_pCamEx;
//}

inline void CLiveSrcChildDlg::SampleRef(BOOL bRef) {
	m_pCamEx->SampleRef(bRef);
}