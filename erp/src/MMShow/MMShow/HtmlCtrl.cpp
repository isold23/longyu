#include "StdAfx.h"
#include "HtmlCtrl.h"
#include <ExDispid.h>
  
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#ifndef WM_MOUSEHWHEEL
//#define WM_MOUSEHWHEEL 0x020A
//#endif


const int CHtmlCtrl::ZoomFactor[] = { 20,30,40,50,60,70,80,90,100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500 };
const int CHtmlCtrl::ZoomFactorCount = _countof(ZoomFactor);
const int CHtmlCtrl::ZoomFactorDefIndex = 8/*100*/;

LPCTSTR CHtmlCtrl::GetBlankUrl(void)
{
	return _T("about:blank");
}

CHtmlCtrl::CHtmlCtrl(void)
{
}
 
CHtmlCtrl::~CHtmlCtrl(void)
{
}


BEGIN_MESSAGE_MAP(CHtmlCtrl, CHtmlView)
	ON_WM_DESTROY()
	//ON_WM_MOUSEACTIVATE() 
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CHtmlCtrl, CHtmlView) 
	ON_EVENT(CHtmlCtrl,AFX_IDW_PANE_FIRST,DISPID_NEWWINDOW3,NewWindow3,VTS_PDISPATCH VTS_PBOOL VTS_I4 VTS_BSTR VTS_BSTR) 
END_EVENTSINK_MAP() 

BOOL CHtmlCtrl::Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID)
{
	CWnd *pWnd = this;
	if (!pWnd->Create(NULL, NULL,dwStyle,rect,pParentWnd,nID,NULL))
		return FALSE;

	Navigate(GetBlankUrl(),NULL,NULL,NULL,NULL);
 
	SetSilent(TRUE);

	m_nZoomFactorIndex = ZoomFactorDefIndex;
	return TRUE;
}

void CHtmlCtrl::OnDestroy(void)
{
	CWnd::OnDestroy();
}

void CHtmlCtrl::PostNcDestroy(void)
{
}
   

void CHtmlCtrl::OnBeforeNavigate2(LPCTSTR lpszURL,DWORD nFlags,LPCTSTR lpszTargetFrameName, 
							CByteArray& baPostedData,LPCTSTR lpszHeaders,BOOL *pbCancel)
{
	*pbCancel = m_bPassiveNavigate ? OnHyperLink(lpszURL) : FALSE;
}

 
void CHtmlCtrl::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
	CComPtr<IUnknown> unk;
	pDisp->QueryInterface(__uuidof(IUnknown),(void**)&unk);
	
	CComPtr<IUnknown> unkWebBrowser;
	m_pBrowserApp.QueryInterface(&unkWebBrowser);

	CString str(V_BSTR(URL));
	if (unk == unkWebBrowser)
		GetParent()->SendMessage(WM_HTMLCTRL,MAKEWPARAM(GetDlgCtrlID(),ON_DOCCOMPLETE),(LPARAM)m_strUrl.GetString());
	OnDocumentComplete(str);
}

BOOL CHtmlCtrl::OnHyperLink(LPCTSTR lpszHyperLink)
{
	return FALSE;
}


BOOL CHtmlCtrl::SetHtmlContent(CString strHtml)
{ 
	CComPtr<IDispatch> disp = GetHtmlDocument();
	if (disp == NULL)
		return FALSE;

	CComPtr<IHTMLDocument2> doc;
	disp->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&doc);
	if (doc == NULL)
		return FALSE;

	COleSafeArray sa;
	CComVariant var(strHtml.GetString());
	sa.CreateOneDim(VT_VARIANT,1,&var);

	return SUCCEEDED(doc->write(sa.parray));
}


void CHtmlCtrl::Navigate(LPCTSTR lpszURL, DWORD dwFlags,LPCTSTR lpszTargetFrameName,
				LPCTSTR lpszHeaders,LPVOID lpvPostData,DWORD dwPostDataLen)
{
	m_strUrl = lpszURL;

	CComBSTR bstrUrl(lpszURL);

	COleSafeArray vPostData;
	if (lpvPostData != NULL)
	{
		if (dwPostDataLen == 0) dwPostDataLen = lstrlen((LPCTSTR) lpvPostData);
		vPostData.CreateOneDim(VT_UI1, dwPostDataLen, lpvPostData);
	}

	m_bPassiveNavigate = FALSE;
	m_pBrowserApp->Navigate(bstrUrl,&CComVariant(dwFlags),&CComVariant(lpszTargetFrameName),vPostData,&CComVariant(lpszHeaders));
	
	m_bPassiveNavigate = TRUE;
}

BOOL CHtmlCtrl::LoadFromResource(LPCTSTR pcszResName,BOOL bResId)
{
	CString strUrl;
	TCHAR szModule[MAX_PATH];

	GetModuleFileName(AfxGetResourceHandle(), szModule, MAX_PATH);

	strUrl.Format(bResId ? _T("res://%s/%d") : _T("res://%s/%s"), szModule, pcszResName);
	Navigate(strUrl, 0, 0, 0);

	return TRUE;
}


IWebBrowser2* CHtmlCtrl::GetWebBrowser(void)
{
	return m_pBrowserApp;
}

BOOL CHtmlCtrl::PreTranslateMessage(MSG* pMsg)
{ 
	if (pMsg->message != WM_MOUSEWHEEL)
	{
		return CHtmlView::PreTranslateMessage(pMsg);
	}
	else
	{
		UINT fFlags = GET_KEYSTATE_WPARAM(pMsg->wParam);
		short zDelta = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		CPoint point(pMsg->lParam);
		  
		if ((m_pBrowserApp!=NULL) && (fFlags&MK_CONTROL))
		{ 
			SetZoomFactorIndex(zDelta<0  ?  m_nZoomFactorIndex-1:m_nZoomFactorIndex+1);
			return TRUE;
		}
		 
		return CHtmlView::PreTranslateMessage(pMsg); 
	}
}

BOOL CHtmlCtrl::SetZoomFactorIndex(int nIndex)
{
	if (nIndex >= ZoomFactorCount)
		nIndex = ZoomFactorCount;
	else if (nIndex < 0)
		nIndex = 0;

	if (nIndex != m_nZoomFactorIndex)
	{
		m_nZoomFactorIndex = nIndex;
		Zoom(ZoomFactor[m_nZoomFactorIndex]);
		GetParent()->SendMessage(WM_HTMLCTRL,MAKEWPARAM(GetDlgCtrlID(),ON_ZOOMOP),(LPARAM)GetZoomFactorIndex());
	}

	return TRUE;
}

//int CHtmlCtrl::GetZoom(void)
//{
//	if (m_pBrowserApp == NULL)
//		return -1;
//
//	CComVariant varZoom;
//	m_pBrowserApp->ExecWB(OLECMDID_OPTICAL_ZOOM, OLECMDEXECOPT_DODEFAULT, NULL, &varZoom);
//	return varZoom.intVal;
//}

BOOL CHtmlCtrl::Zoom(int nPercent)
{
	if (m_pBrowserApp == NULL)
		return FALSE;
 
	CComVariant varZoom(nPercent);	
	return SUCCEEDED(m_pBrowserApp->ExecWB(OLECMDID_OPTICAL_ZOOM, OLECMDEXECOPT_DODEFAULT, &varZoom, NULL));
}

void CHtmlCtrl::NewWindow3(IDispatch **ppDisp,VARIANT_BOOL *Cancel,DWORD dwFlags,BSTR bstrUrlContext,BSTR bstrUrl)
{  
	Navigate2((LPCTSTR)bstrUrl,NULL,NULL); 
	*Cancel = TRUE;
} 
 
int CHtmlCtrl::OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message)
{
	return MA_NOACTIVATE;
}
