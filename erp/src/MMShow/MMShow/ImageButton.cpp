#include "stdafx.h"
#include <GdiPlus.h>
#include "ImageButton.h"
#include "SimpleToolTip.h"
#include "SysDefault.h"

static CSimpleToolTip &ToolTip(void)
{
	static CSimpleToolTip tip;
	if (tip.GetSafeHwnd() == NULL)
		tip.Create();
	return tip;
}


CImageButton::CImageButton(BOOL bAutoCheck)
	:m_bMouseTracking(FALSE),
	 m_pImage(NULL),
	 m_pCheckedImage(NULL),
	 m_pDisabledImage(NULL),
	 m_bChecked(FALSE),
	 m_pBuddy(NULL),
	 m_bAutoCheck(bAutoCheck)
{
}

CImageButton::CImageButton(CImageButton *pBuddy)
	:m_bMouseTracking(FALSE),
	 m_pImage(NULL),
	 m_pCheckedImage(NULL),
	 m_pDisabledImage(NULL),
	 m_bChecked(FALSE),
	 m_pBuddy(pBuddy),
	 m_bAutoCheck(TRUE)
{
}

CImageButton::~CImageButton(void)
{
	DestroyImages();
}

void CImageButton::DestroyImages(void)
{
	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	
	if (m_pDisabledImage != NULL)
	{
		delete m_pDisabledImage;
		m_pDisabledImage = NULL;
	}

	if (m_pCheckedImage != NULL)
	{
		delete m_pCheckedImage;
		m_pCheckedImage = NULL;
	}
}

BOOL CImageButton::SetImageRes(LPCTSTR pcszNormal,LPCTSTR pcszChecked)
{
	DestroyImages();

	m_pImage = ImageFromRes(pcszNormal);
	if (m_pImage!=NULL && pcszChecked!=NULL)
		m_pCheckedImage = ImageFromRes(pcszChecked);
	return (m_pImage != NULL);

}

void CImageButton::SetChecked(BOOL bChecked)
{
	if (m_bChecked != bChecked)
	{
		m_bChecked = bChecked;
		Invalidate();

		if (gsys.ButtonShowTip())
			ToolTip().UpdateTip(this,GetTip());

		if (m_bChecked && m_pBuddy!=NULL)
			m_pBuddy->BuddyChecked(this);
	}
}



const CString& CImageButton::GetTip(void) const
{
	if (!m_bChecked)
		return m_strTip;

	if (m_strCheckedTip.IsEmpty())
		return m_strTip;

	return m_strCheckedTip;
}


void CImageButton::BuddyChecked(CImageButton *pBuddy)
{
	if (pBuddy != this)
	{
		if (m_bChecked)
		{
			m_bChecked = FALSE;
			Invalidate();
			
			if (gsys.ButtonShowTip())
				ToolTip().UpdateTip(this,GetTip());
		}
		if(m_pBuddy != NULL)
			m_pBuddy->BuddyChecked(pBuddy);
	}
}


BOOL CImageButton::SetImageFile(LPCTSTR pcszNormal,LPCTSTR pcszChecked)
{
	DestroyImages();

	m_pImage = ImageFromFile(pcszNormal);
	
	if (m_pImage!=NULL && pcszChecked!=NULL)
		m_pCheckedImage = ImageFromFile(pcszChecked);
	return (m_pImage != NULL);
}
	
Gdiplus::Bitmap* CImageButton::ImageFormated(Gdiplus::Bitmap* pImage)
{
	INT pf = pImage->GetPixelFormat();
	if (pf==PixelFormat32bppARGB || pf==PixelFormat32bppRGB || pf==PixelFormat32bppPARGB)
	{
		return pImage;
	}
	else
	{
		Gdiplus::Rect rc(0,0,pImage->GetWidth(),pImage->GetHeight());
		return pImage->Clone(rc,PixelFormat32bppRGB);
	}
}

Gdiplus::Bitmap* CImageButton::ImageFromFile(LPCTSTR pcszPath)
{
	Gdiplus::Bitmap *pImage = Gdiplus::Bitmap::FromFile(pcszPath);
	if (pImage == NULL)
		return NULL;

	Gdiplus::Bitmap *pFormatedImage = ImageFormated(pImage);
	if (pFormatedImage != pImage)
		delete pImage;
	return pFormatedImage;
}

Gdiplus::Bitmap* CImageButton::ImageFromRes(LPCTSTR pcszResId)
{
	Gdiplus::Bitmap *pImage = Gdiplus::Bitmap::FromResource(AfxGetResourceHandle(),pcszResId);
	if (pImage == NULL)
		return NULL;

	Gdiplus::Bitmap *pFormatedImage = ImageFormated(pImage);
	if (pFormatedImage != pImage)
		delete pImage;
	return pFormatedImage;
}


static void Rgb32ToGray(void *src,void *dst,int nPixelCount)
{
	BYTE *rs = (BYTE*)src;
	BYTE *rd = (BYTE*)dst;
	for (int i=0; i<nPixelCount; ++i)
	{
		BYTE *gs = rs + 1;
		BYTE *bs = rs + 2;
		BYTE *as = rs + 3;
		
		BYTE *gd = rd + 1;
		BYTE *bd = rd + 2;
		BYTE *ad = rd + 3;

		BYTE gray = ((WORD)(*rs+*gs+*bs))/3;
		*ad = *as; *rd = *gd = *bd = gray;

		rs += 32/8; rd += 32/8;
	}
}

Gdiplus::Bitmap* CImageButton::CloneGrayImage(Gdiplus::Bitmap *pImage)
{
	if (pImage == NULL)
	{
		return NULL;
	}
	else
	{
		int pf = pImage->GetPixelFormat();
		Gdiplus::Rect rc(0,0,pImage->GetWidth(),pImage->GetHeight());
		Gdiplus::Bitmap *pCloneImage = new Gdiplus::Bitmap(rc.Width,rc.Height,pf);

		Gdiplus::BitmapData bds,bdd;

		pImage->LockBits(&rc,Gdiplus::ImageLockModeRead,pf,&bds);
		pCloneImage->LockBits(&rc,Gdiplus::ImageLockModeWrite,pf,&bdd);

		Rgb32ToGray(bds.Scan0,bdd.Scan0,rc.Width*rc.Height);
		
		pCloneImage->UnlockBits(&bdd);
		pImage->UnlockBits(&bds);

		return pCloneImage;
	}
}

inline Gdiplus::Bitmap* CImageButton::GetDisabledImage(void)
{
	if (m_pDisabledImage == NULL)
		m_pDisabledImage = CloneGrayImage(m_pImage);
	return m_pDisabledImage;
}

BEGIN_MESSAGE_MAP(CImageButton,CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_CONTROL_REFLECT_EX(BN_CLICKED,&CImageButton::OnClicked)
END_MESSAGE_MAP()

   
BOOL CImageButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.hwndTrack = m_hWnd ;
		tme.dwHoverTime = 80;
		m_bMouseTracking = ::_TrackMouseEvent (&tme);
	}

	CWnd::OnMouseMove(nFlags,point);
}

void CImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	Invalidate();
	if (gsys.ButtonShowTip())
		ToolTip().ShowTip(this,GetTip());
	CWnd::OnMouseHover(nFlags,point);
}

void CImageButton::OnMouseLeave(void)
{
	m_bMouseTracking = FALSE;

	const CString &strTip = GetTip();
	if (gsys.ButtonShowTip())
		if (!strTip.IsEmpty())
			ToolTip().CancelTip(this);

	Invalidate();
	CWnd::OnMouseLeave();
}

BOOL CImageButton::OnClicked(void)
{
	if (!m_bAutoCheck)
	{
		ASSERT(m_pBuddy == NULL);
		return FALSE;
	}

	if (m_pBuddy == NULL)
	{
		m_bChecked = !m_bChecked;
		Invalidate();

		if (gsys.ButtonShowTip())
			ToolTip().UpdateTip(this,GetTip());

		return FALSE;
	}
	else if (m_bChecked)
	{
		return TRUE;
	}
	else
	{
		m_bChecked = TRUE;
		Invalidate();
		if (m_pBuddy != NULL)
			m_pBuddy->BuddyChecked(this);
		return FALSE;
	}
}

#define GdiplusColor(clr) Gdiplus::Color(Gdiplus::Color(GetRValue(clr),GetGValue(clr),GetBValue(clr)))
void CImageButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{	
	const int FocusMagin = 1;
	const int MouseOpOffset = 1;
	const int ContentMargin = 3;
	const COLORREF ClrFocusBkgnd = 0x00D8802B; 

	UINT nState = lpDIS->itemState;
	Gdiplus::Bitmap *pImage = m_pImage;
	
	if (m_bChecked && m_pCheckedImage!=NULL)
		pImage = m_pCheckedImage;
	else if (nState & ODS_DISABLED)
		pImage = GetDisabledImage();

	Gdiplus::Graphics g(lpDIS->hDC);

	const RECT &rcDIS = lpDIS->rcItem;
	Gdiplus::Rect rect(rcDIS.left,rcDIS.top,rcDIS.right-rcDIS.left,rcDIS.bottom-rcDIS.top);
	rect.Inflate(-ContentMargin,-ContentMargin);

	g.Clear(GdiplusColor(nState&ODS_FOCUS ? ClrFocusBkgnd : ::GetSysColor(COLOR_3DFACE)));
 
	if (nState & ODS_SELECTED)
		rect.Offset(MouseOpOffset,MouseOpOffset);
	else if (m_bMouseTracking)
		rect.Offset(-MouseOpOffset,-MouseOpOffset);

	if (pImage != NULL)
	{
		g.DrawImage(pImage,rect);
	}
	else
	{
		CString str;
		GetWindowText(str);
		::SelectObject(lpDIS->hDC,(HFONT)::GetStockObject(DEFAULT_GUI_FONT));

		::SetBkMode(lpDIS->hDC,TRANSPARENT);
		CRect rc(rect.X,rect.Y,rect.X+rect.Width,rect.Y+rect.Height);
		::DrawText(lpDIS->hDC,str,str.GetLength(),&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
}
