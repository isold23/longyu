#pragma once
#include <afxhtml.h>

class CHtmlCtrl : public CHtmlView 
{
	DECLARE_MESSAGE_MAP() 
	DECLARE_EVENTSINK_MAP()

public:
	enum {WM_HTMLCTRL=WM_USER+101};
	enum {ON_DOCCOMPLETE,ON_ZOOMOP};

	static const int ZoomFactor[];
	static const int ZoomFactorCount;
	static const int ZoomFactorDefIndex;

	static LPCTSTR GetBlankUrl(void);
public:
	CHtmlCtrl(void);
	~CHtmlCtrl(void);

	BOOL Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID);
 
	void Navigate(LPCTSTR lpszURL,DWORD dwFlags=0,LPCTSTR lpszTargetFrameName=NULL,
		LPCTSTR lpszHeaders=NULL,LPVOID lpvPostData=NULL,DWORD dwPostDataLen=0);
	
	BOOL LoadFromResource(LPCTSTR pcszResName,BOOL bResId=TRUE);
	
	BOOL SetHtmlContent(CString strHtml);

	int GetZoomFactorIndex(void) const;
	BOOL SetZoomFactorIndex(int nIndex);
	const CString& GetUrl(void) const;

	IWebBrowser2* GetWebBrowser(void);
	CWnd* GetWebBrowserWnd(void);
private:
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL,DWORD nFlags,LPCTSTR lpszTargetFrameName,
		CByteArray& baPostedData,LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	virtual void PostNcDestroy(void);
	virtual BOOL OnHyperLink(LPCTSTR lpszHyperLink);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void NewWindow3(IDispatch **ppDisp,VARIANT_BOOL *Cancel,DWORD dwFlags,BSTR bstrUrlContext,BSTR bstrUrl);
 
	afx_msg void OnDestroy(void); 
	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message);
 
	BOOL Zoom(int nPercent);

	BOOL m_bPassiveNavigate;
	CString m_strUrl;
	int m_nZoomFactorIndex;
};
 
inline const CString& CHtmlCtrl::GetUrl(void) const {
	return m_strUrl;
}

inline int CHtmlCtrl::GetZoomFactorIndex(void) const {
	return m_nZoomFactorIndex;
}

inline CWnd* CHtmlCtrl::GetWebBrowserWnd(void)  {
	return &m_wndBrowser;
}

