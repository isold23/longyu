#include "stdafx.h"
#include "Resource.h"
#include "WebBrowserSrcDlg.h"
#include "DrawHelper.h"
#include "MediaFormatDef.h"
#include <Gdiplus.h>
#include "Cfg.h"
#include "FileHelper.h"

template<typename Arg0,typename Arg1,typename Arg2>
inline Gdiplus::Bitmap *CreateBitmap(Arg0 a0,Arg1 a1,Arg2 a2)
{
	return new Gdiplus::Bitmap(a0,a1,a2);
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static const UINT HTMCTRL_ID = 1097;
static const UINT ZOOMCTRL_ID = 1098;
// {D27CDB6E-AE6D-11cf-96B8-444553540000}
static const GUID FlashObjectGuid = { 0xD27CDB6E, 0xAE6D, 0x11CF, { 0x96, 0xB8, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };


CWebBrowserSrcDlg::CWebBrowserSrcDlg(CWnd* pParent /*=NULL*/)
	: CVideoSrcBaseDialog(CWebBrowserSrcDlg::IDD, pParent),
	  m_cbHistory(_T("WebBrowserHistory"))
{
	m_pcszName = _T("网页");
	m_pBitmap  = NULL;
	m_bVisible = FALSE;
}

CWebBrowserSrcDlg::~CWebBrowserSrcDlg()
{
	if (m_pBitmap != NULL)
		delete m_pBitmap;
}

void CWebBrowserSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CVideoSrcBaseDialog::DoDataExchange(pDX); 
	DDX_Control(pDX,IDC_SLD_ZOOM,m_sliderZoom);
	DDX_Control(pDX,IDC_CB_HISTORY,m_cbHistory);

	DDX_Control(pDX,IDC_BTN_ZOOM,m_btnZoom);
	DDX_Control(pDX,IDC_BTN_GO,m_btnGo);
	DDX_Control(pDX,IDC_BTN_STOP,m_btnStop);
	DDX_Control(pDX,IDC_BTN_BACKWARD,m_btnBackward);
	DDX_Control(pDX,IDC_BTN_FORWORD,m_btnForward);

}


BEGIN_MESSAGE_MAP(CWebBrowserSrcDlg, CVideoSrcBaseDialog)
	ON_WM_HSCROLL() 
	ON_BN_CLICKED(IDC_BTN_ZOOM, &CWebBrowserSrcDlg::OnBnClickedBtnZoom)
	ON_BN_CLICKED(IDC_BTN_GO, &CWebBrowserSrcDlg::OnOK)
	ON_BN_CLICKED(IDC_BTN_STOP, &CWebBrowserSrcDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_BACKWARD, &CWebBrowserSrcDlg::OnBnClickedBtnBackward)
	ON_BN_CLICKED(IDC_BTN_FORWORD, &CWebBrowserSrcDlg::OnBnClickedBtnForward)
	ON_MESSAGE(CHtmlCtrl::WM_HTMLCTRL,&CWebBrowserSrcDlg::OnHtmlCtrl)
	ON_COMMAND(IDC_CB_HISTORY,&CWebBrowserSrcDlg::OnCBHistorySelChange)
END_MESSAGE_MAP()


BOOL CWebBrowserSrcDlg::OnInitDialog(void)
{	
	CVideoSrcBaseDialog::OnInitDialog();
 
	CWindowRect rc(GetDlgItem(IDC_STC_CONTENT));
	ScreenToClient(rc);
	m_htmlCtrl.Create(WS_CHILD|WS_VISIBLE,rc,this,HTMCTRL_ID);

	AddAnchor(m_cbHistory,TOP_LEFT,TOP_RIGHT);
	AddAnchor(m_btnGo,TOP_RIGHT);
	AddAnchor(m_btnStop,TOP_RIGHT);
	AddAnchor(m_btnBackward,TOP_RIGHT);
	AddAnchor(m_btnForward,TOP_RIGHT);
	AddAnchor(m_btnZoom,TOP_RIGHT);
	AddAnchor(m_sliderZoom,TOP_RIGHT);
	AddAnchor(m_htmlCtrl,TOP_LEFT,BOTTOM_RIGHT);

	m_gaugeWnd.Create(m_htmlCtrl.GetWebBrowserWnd(),gcfg.GetUiOpTransparentGauge());

	m_sliderZoom.SetRange(0,CHtmlCtrl::ZoomFactorCount-1);
	m_sliderZoom.SetPos(m_htmlCtrl.GetZoomFactorIndex());
	m_cbHistory.SetFocus();

	Fh::Cder cder(gsys.PicPath());

	m_btnGo.SetImageFile(_T("WebBrowserGo.png"));
	m_btnGo.SetTip(_T("浏览"));

	m_btnStop.SetImageFile(_T("WebBrowserStop.png"));
	m_btnStop.SetTip(_T("停止"));

	m_btnBackward.SetImageFile(_T("WebBrowserBackward.png"));
	m_btnBackward.SetTip(_T("前进"));

	m_btnForward.SetImageFile(_T("WebBrowserForward.png"));
	m_btnForward.SetTip(_T("后退"));

	m_btnZoom.SetTip(_T("还原缩放"));

	return TRUE;
}

void CWebBrowserSrcDlg::OnBnClickedBtnStop(void)
{
	m_htmlCtrl.Stop();
}

void CWebBrowserSrcDlg::OnBnClickedBtnBackward(void)
{
	m_htmlCtrl.GoBack();
}

void CWebBrowserSrcDlg::OnBnClickedBtnForward(void)
{
	m_htmlCtrl.GoForward();
}

void CWebBrowserSrcDlg::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar *pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() ==  m_sliderZoom.GetSafeHwnd())
		m_htmlCtrl.SetZoomFactorIndex(m_sliderZoom.GetPos());

	CVideoSrcBaseDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
 
void CWebBrowserSrcDlg::OnBnClickedBtnZoom(void)
{
	m_htmlCtrl.SetZoomFactorIndex(CHtmlCtrl::ZoomFactorDefIndex);
}


void CWebBrowserSrcDlg::OnOK(void)
{
	CString strUrl;
	m_cbHistory.GetWindowText(strUrl);
	strUrl.Trim();
	if(!strUrl.IsEmpty())
		m_htmlCtrl.Navigate(strUrl);
}

CWnd* CWebBrowserSrcDlg::GetDefaultCtrl(void)
{
	return &m_cbHistory;
}

static BOOL GetDocType(IHTMLElement *pDocElem)
{
	CComQIPtr<IHTMLDOMNode> pDocNode = pDocElem;
	if (pDocNode == NULL)
		return FALSE;

	CComQIPtr<IHTMLDOMNode> pNode;
	pDocNode->get_previousSibling(&pNode);
	while (pNode != NULL)
	{
		long type;
		pNode->get_nodeType(&type);
		if (type == 8)
			return TRUE;

		CComPtr<IHTMLDOMNode> pPrev;
		pNode->get_previousSibling(&pPrev);
		pNode = pPrev;
	}

	pNode.Release();
	pDocNode->get_nextSibling(&pNode);
	while (pNode != NULL)
	{
		long type;
		pNode->get_nodeType(&type);
		if (type == 8)
			return TRUE;

		CComPtr<IHTMLDOMNode> pNext;
		pNode->get_previousSibling(&pNext);
		pNode = pNext;
	}

	return FALSE;
}


LRESULT CWebBrowserSrcDlg::OnHtmlCtrl(WPARAM wParam,LPARAM lParam)
{
	UINT nHtmlCtrlId = LOWORD(wParam);
	UINT nNotify = HIWORD(wParam);
 
	if (nHtmlCtrlId == HTMCTRL_ID)
	{
		if (nNotify == CHtmlCtrl::ON_DOCCOMPLETE)
		{
			LPCTSTR lpcszUrl = (LPCTSTR)lParam;
			if (_tcsicmp(lpcszUrl,CHtmlCtrl::GetBlankUrl()))
				m_cbHistory.Add(lpcszUrl);

			OnDocComplete();
		}
		else if (nNotify == CHtmlCtrl::ON_ZOOMOP)
		{ 
			m_sliderZoom.SetPos(lParam);
			
			TCHAR szTmp[32];
			wsprintf(szTmp,_T("%d%%"),CHtmlCtrl::ZoomFactor[lParam]);
			SetDlgItemText(IDC_BTN_ZOOM,szTmp);
		}
	}

	return 0;
}

BOOL CWebBrowserSrcDlg::OnDocComplete(void)
{	
	m_pRender.Release();

	CComQIPtr<IHTMLDocument3> pDoc3 = m_htmlCtrl.GetHtmlDocument();
	if (pDoc3 == NULL)
		return FALSE;

	CComPtr<IHTMLElement> pElem;
	pDoc3->get_documentElement(&pElem);

	if (GetDocType(pElem))
	{
		m_pRender = pElem;
	}
	else
	{
		CComQIPtr<IHTMLDocument2> pDoc2 = pDoc3;
		if (pDoc2 == NULL)
			return FALSE;

		CComPtr<IHTMLElement> pBody;
		pDoc2->get_body(&pBody);
		if (pBody == NULL)
			return FALSE;
		m_pRender = pBody;
	}

	if (m_pRender == NULL)
		return FALSE;

	return TRUE;
}

void CWebBrowserSrcDlg::OnCBHistorySelChange(void)
{
	CString str;
	int nIndex = m_cbHistory.GetCurSel();
	m_cbHistory.GetLBText(nIndex,str); 
	m_htmlCtrl.Navigate(str);

}
 


BOOL CWebBrowserSrcDlg::GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample)
{
	if (m_pRender == NULL)
		return FALSE;

	CClientRect rcHost(m_gaugeWnd.GetHost());

	if (m_pBitmap!=NULL  && (m_pBitmap->GetWidth()!=rcHost.right 
		|| m_pBitmap->GetHeight()!=rcHost.bottom))
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	if (m_pBitmap == NULL)
		m_pBitmap = CreateBitmap(rcHost.right,rcHost.bottom,def_gplusPixFormat);

	Gdiplus::Graphics graphics(m_pBitmap);
	HDC hDC = graphics.GetHDC();
	if (hDC == NULL)
		return FALSE;

	BOOL bRet = SUCCEEDED(m_pRender->DrawToDC(hDC)); 
	if (bRet && m_bVisible && m_bDrawCursor)
	{
		CCurorPos cursorPos;
		const CRect &rcGauge = m_gaugeWnd.GetWndRect();
		if (rcGauge.PtInRect(cursorPos))
		{
			m_gaugeWnd.GetHost()->ScreenToClient(&cursorPos);
			HCURSOR hCursor = GetCursor();
			if (hCursor != NULL)
			{
				ICONINFO ii;
				::GetIconInfo(hCursor,&ii);
				cursorPos.x -= ii.xHotspot;
				cursorPos.y -= ii.yHotspot;
				::DrawIcon(hDC,cursorPos.x,cursorPos.y,hCursor);
			}
		}
	}
	graphics.ReleaseHDC(hDC);
	if (!bRet)
		return FALSE;

	rcSample = rcHost;;
	m_gaugeWnd.CalcViewRect(rcSample);

	buf.Set(rcHost.Width()*rcSample.Height()*def_vBytesPerPixel);

	Gdiplus::BitmapData bitmapData;
	bitmapData.Width = rcSample.Width();
	bitmapData.Height = rcSample.Height();
	bitmapData.PixelFormat = def_gplusPixFormat;
	bitmapData.Stride = bitmapData.Width*def_vBytesPerPixel;
	bitmapData.Scan0 = buf.Ptr();
	bitmapData.Reserved = 0;

	Gdiplus::Rect rcLock(rcSample.left,rcSample.top,bitmapData.Width,bitmapData.Height);
	m_pBitmap->LockBits(&rcLock,Gdiplus::ImageLockModeRead|Gdiplus::ImageLockModeUserInputBuf,
		def_gplusPixFormat,&bitmapData);
	m_pBitmap->UnlockBits(&bitmapData);
	nStride = -bitmapData.Stride;
	sizeFull = CSize(rcHost.right,rcHost.bottom);
	return TRUE;
}

CString CWebBrowserSrcDlg::GetDesc(void)
{
	return m_htmlCtrl.GetUrl();
}

