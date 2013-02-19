#include "StdAfx.h"
#include "PictureCtrl.h"
#include "DrawHelper.h"
#include "MediaFormatDef.h"
#include <Gdiplus.h>

class CGdiplusInit
{
public:
	CGdiplusInit(void)
	{
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartupOutput output;

		Gdiplus::GdiplusStartup(&m_lGdiPlusToken,&input,&output);
	}
	~CGdiplusInit(void)
	{
		Gdiplus::GdiplusShutdown (m_lGdiPlusToken);
	}

private:
	ULONG_PTR m_lGdiPlusToken;
} CGdiplusInit_XXX;

 
LPCTSTR CPictureCtrl::WND_CLASSNAME = _T("PictureCtrl");


static const UINT_PTR TIMER_ID = 100;

CPictureCtrl::CPictureCtrl(void)
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInst, WND_CLASSNAME, &wndcls)))
	{
		wndcls.style            = CS_DBLCLKS;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = 0;
		wndcls.cbWndExtra		= 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH)COLOR_WINDOW;
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = WND_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}

	m_bStretch = TRUE;
	m_pImage = NULL;
	m_clrBkgnd = ::GetSysColor(COLOR_WINDOW);
	m_nTimerId = 0; 
}

CPictureCtrl::~CPictureCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CPictureCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CPictureCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CWnd* pWnd = this;
	return pWnd->Create(WND_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID);
}

BOOL CPictureCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CPictureCtrl::OnPaint(void)
{
 	CPaintDC dc(this);

	CxMemDC dcMem(dc,this);
	
	dcMem.Fill(m_clrBkgnd);

	if (m_pImage == NULL)
		return;

	Gdiplus::Graphics grahics(dcMem.GetSafeHdc());
	

	if (!m_bStretch)
	{
		grahics.DrawImage(m_pImage,0,0);
	}
	else
	{
		const CRect &rc = dcMem.Rect();
		Gdiplus::Rect rect(rc.left,rc.top,rc.Width(),rc.Height());
		grahics.DrawImage(m_pImage,rect);
	}


}

void CPictureCtrl::OnTimer(UINT_PTR nIDEvent)
{
	ASSERT(m_pImage!=NULL && m_nFrameCount>1);

	++m_nCurFrame;
	if (m_nCurFrame >= m_nFrameCount)
		m_nCurFrame = 0;

	m_pImage->SelectActiveFrame(&m_dimGuid,m_nCurFrame);
	m_dwSampleTick = GetTickCount();

	KillTimer(m_nTimerId);
	m_nTimerId = SetTimer(TIMER_ID,GetFrameDelay(),NULL);

	if (IsWindowVisible())
		Invalidate(FALSE);

	CWnd::OnTimer(nIDEvent);
}

BOOL CPictureCtrl::Show(LPCTSTR pcszFile,BOOL bStretch)
{
	USES_CONVERSION;

	if (pcszFile == NULL)
	{
		if (m_nTimerId != 0)
		{
			KillTimer(m_nTimerId);
			m_nTimerId = 0;
		}

		if (m_pImage != NULL)
		{
			delete m_pImage;
			m_pImage = NULL;
			Invalidate(FALSE);
		}
			
		m_strFilePath.Empty();
		return TRUE;
	}
	else
	{
		Gdiplus::Bitmap *pSrcImage = Gdiplus::Bitmap::FromFile(T2CW(pcszFile));
		if (pSrcImage == NULL)
			return FALSE;

		if (pSrcImage->GetLastStatus() != Gdiplus::Ok)
		{
			delete pSrcImage;
			return FALSE;
		}

		Gdiplus::Bitmap *pImage = pSrcImage->Clone(0,0,pSrcImage->GetWidth(),
			pSrcImage->GetHeight(),def_gplusPixFormat);
		delete pSrcImage;
		if (pSrcImage == NULL)
			return FALSE;
		
		Show(NULL);
		m_bStretch = bStretch;
		m_pImage = pImage;

		UINT nDimCount = m_pImage->GetFrameDimensionsCount();
		
		CArray<GUID,GUID&> dimGuids;
		dimGuids.SetSize(nDimCount);
 
		m_pImage->GetFrameDimensionsList(dimGuids.GetData(), nDimCount);
		m_nFrameCount = pImage->GetFrameCount(dimGuids.GetData());
	
		if (m_nFrameCount > 1)
		{
			m_dimGuid = dimGuids[0];

			int nSize = pImage->GetPropertyItemSize(PropertyTagFrameDelay);
			m_propItem.SetSize(nSize); 

			pImage->GetPropertyItem(PropertyTagFrameDelay, nSize, 
				(Gdiplus::PropertyItem*)m_propItem.GetData());

			m_nCurFrame = 0;
			m_nTimerId = SetTimer(TIMER_ID,GetFrameDelay(),NULL);
		} 
 
		Invalidate(FALSE);
		m_dwSampleTick = GetTickCount();

		m_strFilePath = pcszFile;
		return TRUE;
	}
}

int CPictureCtrl::GetFrameDelay(void)
{
	Gdiplus::PropertyItem *pPropItem = (Gdiplus::PropertyItem*)m_propItem.GetData();
	int nFrameDelay = ((int*)pPropItem->value)[m_nCurFrame]*10;
	if (nFrameDelay == 0)
		nFrameDelay = 100;
	return nFrameDelay;

}
