#pragma once

namespace Gdiplus {class Bitmap;}

class CImageButton : public CButton
{
	DECLARE_MESSAGE_MAP()

public:
	CImageButton(BOOL bAutoCheck=FALSE);
	CImageButton(CImageButton *pBuddy);
	~CImageButton(void);

	BOOL IsChecked(void) const;
	void SetChecked(BOOL bChecked = TRUE);
	void ToggleChecked(void);

	void SetTip(LPCTSTR pcszNormal,LPCTSTR pcszChecked=NULL);

	BOOL SetImageRes(LPCTSTR pcszNormal,LPCTSTR pcszChecked=NULL);
	BOOL SetImageFile(LPCTSTR pcszNormal,LPCTSTR pcszChecked=NULL);

private:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave(void);
	afx_msg BOOL OnClicked(void);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void DestroyImages(void);
	Gdiplus::Bitmap* ImageFromFile(LPCTSTR pcszPath);
	Gdiplus::Bitmap* ImageFromRes(LPCTSTR pcszResId);
	Gdiplus::Bitmap* ImageFormated(Gdiplus::Bitmap* pImage);
	Gdiplus::Bitmap* CloneGrayImage(Gdiplus::Bitmap *pImage);
	void BuddyChecked(CImageButton *pBuddy);


	const CString& GetTip(void) const;
	Gdiplus::Bitmap* GetDisabledImage(void);

	BOOL m_bMouseTracking;

	Gdiplus::Bitmap *m_pImage;
	Gdiplus::Bitmap *m_pDisabledImage;
	Gdiplus::Bitmap *m_pCheckedImage;

	CString m_strTip;
	CString m_strCheckedTip;

	BOOL m_bChecked;
	BOOL m_bAutoCheck;
	CImageButton *m_pBuddy;
};

inline BOOL CImageButton::IsChecked(void) const {
	return m_bChecked;
}


inline void CImageButton::ToggleChecked(void) {
	SetChecked(!IsChecked());
}

inline void CImageButton::SetTip(LPCTSTR pcszNormal,LPCTSTR pcszChecked) {
	m_strTip = pcszNormal;
	m_strCheckedTip = pcszChecked;
}
