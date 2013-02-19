#pragma once
 
 
class CPaneTreeCtrl : public CTreeCtrl
{	
	DECLARE_MESSAGE_MAP()
	static const int ICON_TEXT_GAP = 5;

public:
	CPaneTreeCtrl(BOOL bLayered=TRUE);
	virtual ~CPaneTreeCtrl(void);

	void SetTargetCmdWnd(CWnd *pTargetCmdWnd);
protected:
	virtual BOOL OnEraseBkgnd(CDC* pDC);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDraw(LPNMHDR pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnDBClickCmd(NMHDR *pNMHDR, LRESULT *pResult);

	void DrawItem(HTREEITEM hItem,HDC hDC,const RECT &rect,UINT nItemState);

	BOOL m_bLayered;
	CSize m_sizeImage;

	int m_nIndent;
	CFont m_font;

	CWnd *m_pTargetCmdWnd;
	CImageList *m_pImagelist;
};

inline void CPaneTreeCtrl::SetTargetCmdWnd(CWnd *pTargetCmdWnd) {
	m_pTargetCmdWnd = pTargetCmdWnd;
}


