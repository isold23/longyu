#pragma once
namespace Gdiplus {class Bitmap;}


class CPictureCtrl : public CWnd
{
	DECLARE_MESSAGE_MAP()

public:
	static LPCTSTR WND_CLASSNAME;
public:
	CPictureCtrl(void);
	~CPictureCtrl(void);

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	const CString& GetFilePath(void) const;
	BOOL Show(LPCTSTR pcszFile,BOOL bStretch=TRUE);

	void SetBkgndColor(COLORREF clr);

	Gdiplus::Bitmap* GetBitmap(void);
	DWORD GetSampleTick(void) const;
private: 
	afx_msg void OnPaint(void);	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	int GetFrameDelay(void);
 

	COLORREF m_clrBkgnd;
	BOOL m_bStretch;

	UINT_PTR m_nTimerId;
	DWORD m_dwSampleTick;
	
	Gdiplus::Bitmap *m_pImage;
	int m_nCurFrame;
	int m_nFrameCount;
	GUID m_dimGuid;
	CByteArray m_propItem;

	CString m_strFilePath;
};

inline Gdiplus::Bitmap* CPictureCtrl::GetBitmap(void) {
	return m_pImage;
}	

inline DWORD CPictureCtrl::GetSampleTick(void) const {
	return m_dwSampleTick;
}

inline const CString& CPictureCtrl::GetFilePath(void) const {
	return m_strFilePath;
}