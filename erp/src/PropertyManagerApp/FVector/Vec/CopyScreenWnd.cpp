#include "StdAfx.h"
#include "CopyScreenWnd.h"
#include <Commdlg.h>
#include "resource.h"



inline void NormalizeRect(RECT &rc)
{
	LONG temp;
	if (rc.left > rc.right)
	{
		temp = rc.left;
		rc.left = rc.right;
		rc.right = temp;
	}

	if (rc.top > rc.bottom)
	{
		temp = rc.top;
		rc.top = rc.bottom;
		rc.bottom = temp;
	}
}



HBITMAP CopyScreen(RECT &rc)
{
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	HDC hScreenDC = ::CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	HDC hMemDC = ::CreateCompatibleDC(hScreenDC);
	HBITMAP hBmp = ::CreateCompatibleBitmap(hScreenDC,cx,cy);

	::SelectObject(hMemDC,hBmp);
	::BitBlt(hMemDC,rc.left,rc.top,cx,cy,hScreenDC,rc.left,rc.top,SRCCOPY);

	::DeleteDC(hMemDC);
	::DeleteDC(hScreenDC);
 
	return hBmp;
}


BOOL SaveBitmap(HDC hDC,HBITMAP hBmp,const RECT &rect,LPCTSTR pcsszFilePath)
{
	// Create a file to hold the bitmap
	HANDLE hFile = CreateFile(pcsszFilePath,GENERIC_WRITE,
		FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if( hFile == INVALID_HANDLE_VALUE )
		return FALSE;

	BITMAP bmp;
	::GetObject(hBmp,sizeof(BITMAP),&bmp);

	RECT rc = rect;
	NormalizeRect(rc);
	if (rc.left < 0) rc.left = 0;
	if (rc.right > bmp.bmWidth) rc.right = bmp.bmHeight;
	if (rc.top < 0) rc.top  = 0;
	if (rc.bottom > bmp.bmHeight) rc.bottom = bmp.bmHeight;

	UINT uScanStart = bmp.bmHeight-rc.bottom;
	rc.bottom = rc.bottom -rc.top + uScanStart;
	rc.top = uScanStart;

	UINT nDestWidth = rc.right - rc.left;
	UINT cScanLines = rc.bottom - rc.top; 

	// Get bitmap info 

	BITMAPINFO bmi;
	ZeroMemory(&bmi,sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = bmp.bmWidth;
	bmi.bmiHeader.biHeight = bmp.bmHeight;
	bmi.bmiHeader.biBitCount = bmp.bmBitsPixel;
  	if (!::GetDIBits(hDC,hBmp,rc.top,cScanLines,NULL,&bmi,DIB_RGB_COLORS))
	{
		::CloseHandle(hFile);
		return FALSE;
	}

	// Get bitmap bits
	UINT cbBit = bmi.bmiHeader.biBitCount >> 3;
	UINT cbSrcScanLine =bmi.bmiHeader.biWidth*cbBit;
	DWORD cbSrcBuf = cbSrcScanLine*cScanLines;
	BYTE *pSrcBuf = new BYTE[cbSrcBuf];
 	::GetDIBits(hDC,hBmp,rc.top,cScanLines,pSrcBuf,&bmi,DIB_RGB_COLORS);
  
	// Alloc buffer for destination buffer
	UINT cbDestScanLine = nDestWidth*cbBit;
	DWORD cbDestBuf = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
				+ cbSrcScanLine*cScanLines;
	BYTE *pDestBuf = new BYTE[cbDestBuf];
	BYTE *pDest = pDestBuf;

	// Write out the file header
	BITMAPFILEHEADER *bfh = reinterpret_cast<BITMAPFILEHEADER*>(pDest);
	memset(bfh, 0, sizeof(BITMAPFILEHEADER));
	bfh->bfType = 'MB';
	bfh->bfSize = cbDestBuf ;
	bfh->bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
	pDest += sizeof(BITMAPFILEHEADER);

	// Write the bitmap format
	BITMAPINFOHEADER *bih = reinterpret_cast<BITMAPINFOHEADER*>(pDest);
	memset(bih,0,sizeof(BITMAPINFOHEADER));
	bih->biSize = sizeof(BITMAPINFOHEADER);
	bih->biWidth = nDestWidth;
	bih->biHeight = cScanLines;
	bih->biPlanes = 1;
	bih->biBitCount = bmi.bmiHeader.biBitCount; 
	pDest += sizeof(BITMAPINFOHEADER);
	 
	BYTE *pSrc = pSrcBuf + rc.left*cbBit; 
	for (UINT i=0; i<cScanLines; ++i,pSrc+=cbSrcScanLine,pDest+=cbDestScanLine)
		memcpy(pDest,pSrc,cbDestScanLine);
		
	DWORD dwWritten;
	::WriteFile(hFile,pDestBuf,cbDestBuf, &dwWritten, NULL);
	
	delete[] pSrcBuf;
	delete[] pDestBuf;  
	::CloseHandle(hFile);

	return TRUE;
}

CCopyScreenWnd::CCopyScreenWnd(void)
	:m_wndInfo(this),
	 m_hScreenBmp(NULL),
	 m_Tracking(Non)
{
	EmptyTrack();
}

CCopyScreenWnd::~CCopyScreenWnd(void)
{
	if (m_wndNon.m_hWnd != NULL)
		m_wndNon.DestroyWindow(); 
	if (m_hScreenBmp != NULL)
		::DeleteObject(m_hScreenBmp); 

}

BOOL CCopyScreenWnd::Create(void)
{
	m_wndNon.Create(NULL,NULL,NULL,WS_POPUP,WS_EX_TOPMOST);

	HWND hWnd = CWindowImpl<CCopyScreenWnd>::Create(m_wndNon.m_hWnd,NULL,NULL,
		WS_POPUP/*,WS_EX_TOPMOST*/);	

	ATLASSERT(hWnd != NULL);
	m_wndInfo.Create(hWnd,NULL,NULL,WS_POPUP);

	return 0;
}

void CCopyScreenWnd::Show(BOOL bShow)
{
	ShowWindow(bShow ? SW_SHOW:SW_HIDE);
	//m_wndInfo.ShowWindow(bShow ? SW_SHOW:SW_HIDE);	
	EmptyTrack();
}

LRESULT CCopyScreenWnd::OnNcCreate(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	RECT rc;
	rc.left = rc.top = 0;
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(NULL,0,0,rc.right,rc.bottom,0);

	m_hScreenBmp = CopyScreen(rc);
	return TRUE;
}

LRESULT CCopyScreenWnd::OnPaint(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);
	OnDraw(hDC);
	EndPaint(&ps);

	bHandled = FALSE;
	return 0;
}


LRESULT CCopyScreenWnd::OnEraseBkgnd(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	return TRUE;
}

LRESULT CCopyScreenWnd::OnMouseMove(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);

	if (HasTrack())
	{
		RECT rcOld = m_rcTrack;
		if (m_Tracking != Non)
		{
			switch (m_Tracking)
			{
			case TopLeft:
				m_rcTrack.left = pt.x;
				m_rcTrack.top = pt.y;
				break;
			case Top:
				m_rcTrack.top = pt.	y;
				break;
			case TopRight:
				m_rcTrack.right = pt.x;
				m_rcTrack.top = pt.y;
				break;
			case Right:
				m_rcTrack.right = pt.x;
				break;
			case BottomRight:
				m_rcTrack.right = pt.x;
				m_rcTrack.bottom = pt.y;
				break;
			case Bottom:
				m_rcTrack.bottom = pt.y;
				break;
			case BottomLeft:
				m_rcTrack.left = pt.x;
				m_rcTrack.bottom = pt.y;
				break;
			case Left:
				m_rcTrack.left = pt.x;
				break;
			case Body:
				m_rcTrack.left += pt.x - m_ptTracking.x;
				m_rcTrack.right += pt.x - m_ptTracking.x;
				m_rcTrack.top += pt.y - m_ptTracking.y;
				m_rcTrack.bottom += pt.y - m_ptTracking.y;
				m_ptTracking = pt;
				break;
			case NEW:
				m_rcTrack.right = pt.x;
				m_rcTrack.bottom = pt.y; 
				break;
			default:
				ATLASSERT(FALSE);
				break;
			}
 
			InvalidateRect(NULL,FALSE);
		}
	}

	m_wndInfo.UpdatePos(&pt);

	return 0;
}

LRESULT CCopyScreenWnd::OnLButtonDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	::SetCapture(m_hWnd);
	
	POINT pt;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);

	if (!HasTrack())
	{
		m_rcTrack.left = m_rcTrack.right = pt.x;
		m_rcTrack.top = m_rcTrack.bottom = pt.y; 
		m_Tracking = NEW;
		InvalidateRect(NULL,FALSE);
	}
	else
	{
		m_Tracking = HitTestTrackRect(pt.x,pt.y);
		m_ptTracking = pt;	
	}

	return 0;
}

LRESULT CCopyScreenWnd::OnLButtonUp(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{ 
	m_Tracking = Non;
	::ReleaseCapture();
	return 0;
}

LRESULT CCopyScreenWnd::OnLButtonDBClick(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	OPENFILENAME ofn;       
	TCHAR szFile[MAX_PATH];       
  
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = _T('\0');
	ofn.nMaxFile = _countof(szFile);
	ofn.lpstrFilter = _T("BMPλͼ(*.bmp)\0*.bmp\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;

	if (::GetOpenFileName(&ofn)) 
	{
		RECT rc;
		rc.left = 640;
		rc.top = 100;
		rc.right = 1280;
		rc.bottom = 400;

		HDC hDC = ::GetDC(m_hWnd);
		SaveBitmap(hDC,m_hScreenBmp,m_rcTrack,szFile);
		::ReleaseDC(m_hWnd,hDC);
	}

	Show(FALSE);
	return 0;
}

LRESULT CCopyScreenWnd::OnKeyDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	if (wParam == VK_ESCAPE)
	{
		if (HasTrack())
		{
			EmptyTrack();
			InvalidateRect(NULL,FALSE);
		}
		else
		{
			Show(FALSE);
		}	
	}
	return 0;
}

LRESULT CCopyScreenWnd::OnSetCursor(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	if (!HasTrack())
	{
		bHandled = FALSE;
		return FALSE;
	}
	
	POINT pt;
	::GetCursorPos(&pt);

	int nHitTest = HitTestTrackRect(pt.x,pt.y);
	if (nHitTest == Non)
	{
		bHandled = FALSE;
		return FALSE;
	}

	::SetCursor(GetTrackCursor(nHitTest));
	return TRUE;
}


void CCopyScreenWnd::OnDraw(HDC hDC)
{
	RECT rc;
	GetClientRect(&rc);

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBmp = ::CreateCompatibleBitmap(hDC,rc.right-rc.left,rc.bottom-rc.top);
	::SelectObject(hMemDC,hMemBmp);

	HDC hBmpDC = ::CreateCompatibleDC(hDC);
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBmpDC,m_hScreenBmp);

	int cx = ::GetSystemMetrics(SM_CXSCREEN);
	int cy = ::GetSystemMetrics(SM_CYSCREEN);

	::BitBlt(hMemDC,0,0,cx,cy,hBmpDC,0,0,SRCCOPY);
	::DeleteDC(hBmpDC);



	if (HasTrack())
	{
		DrawTrack(hMemDC);
	}
	::BitBlt(hDC,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,hMemDC,0,0,SRCCOPY);
	::DeleteObject(hMemBmp);
	::DeleteDC(hMemDC);
}


void CCopyScreenWnd::DrawMark(HDC hDC,int x,int y)
{
	int left = x - MARK_SIZE;
	int top = y - MARK_SIZE;
	int right = x + MARK_SIZE;
	int bottom = y + MARK_SIZE;
	::Rectangle(hDC,left,top,right,bottom);
}

void CCopyScreenWnd::Rect(HDC hDC,const RECT &rc)
{
 
}

void CCopyScreenWnd::DrawTrack(HDC hDC)
{
	RECT rc = m_rcTrack;
	::InflateRect(&rc,MARK_SIZE,MARK_SIZE);

	SIZE sz = {rc.right-rc.left,rc.bottom-rc.top};

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBmp = ::CreateCompatibleBitmap(hDC,sz.cx,sz.cy);
	::SelectObject(hMemDC,hMemBmp);


	HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
	::SelectObject(hMemDC,hBrush);

	::OffsetRect(&rc,-rc.left,-rc.top);
	::InflateRect(&rc,-MARK_SIZE,-MARK_SIZE);

	::Rectangle(hMemDC,rc.left,rc.top,rc.right,rc.bottom);

	BLENDFUNCTION  bf;
	bf.BlendOp = 0;
	bf.SourceConstantAlpha = 80;
	bf.BlendFlags = AC_SRC_OVER;
	bf.AlphaFormat = AC_SRC_ALPHA;
	::AlphaBlend(hDC,m_rcTrack.left-MARK_SIZE,m_rcTrack.top-MARK_SIZE,sz.cx,sz.cy,hMemDC,0,0,sz.cx,sz.cy,bf);
	::DeleteObject(hBrush);
	::DeleteObject(hMemBmp);
	::DeleteDC(hMemDC);	

	::SelectObject(hDC,::GetStockObject(NULL_PEN));
	hBrush = ::CreateSolidBrush(RGB(100,100,255));
	::SelectObject(hDC,hBrush);

	int nCenterX = (m_rcTrack.left+m_rcTrack.right)/2;
	int nCenterY = (m_rcTrack.top+m_rcTrack.bottom)/2;
	DrawMark(hDC,m_rcTrack.left,m_rcTrack.top);
	DrawMark(hDC,nCenterX,m_rcTrack.top);
	DrawMark(hDC,m_rcTrack.right,m_rcTrack.top);
	DrawMark(hDC,m_rcTrack.right,nCenterY);
	DrawMark(hDC,m_rcTrack.right,m_rcTrack.bottom);
	DrawMark(hDC,nCenterX,m_rcTrack.bottom);
	DrawMark(hDC,m_rcTrack.left,m_rcTrack.bottom);
	DrawMark(hDC,m_rcTrack.left,nCenterY);

	::DeleteObject(hBrush);
}

int CCopyScreenWnd::HitTestTrackRect(int x,int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;

	RECT rc = m_rcTrack;
	NormalizeRect(rc);

	int nCenterX = (m_rcTrack.left + m_rcTrack.right)/2;
	int nCenterY = (m_rcTrack.top + m_rcTrack.bottom)/2;

	if (PtInMark(m_rcTrack.left,m_rcTrack.top,x,y))
		return TopLeft;
	else if (PtInMark(nCenterX,m_rcTrack.top,x,y))
		return Top;
	else if (PtInMark(m_rcTrack.right,m_rcTrack.top,x,y))
		return TopRight;
	else if (PtInMark(m_rcTrack.right,nCenterY,x,y))
		return Right;
	else if (PtInMark(m_rcTrack.right,m_rcTrack.bottom,x,y))
		return BottomRight;
	else if (PtInMark(nCenterX,m_rcTrack.bottom,x,y))
		return Bottom;
	else if (PtInMark(m_rcTrack.left,m_rcTrack.bottom,x,y))
		return BottomLeft;
	else if (PtInMark(m_rcTrack.left,nCenterY,x,y))
		return Left;
	else if (::PtInRect(&rc,pt))
		return Body;
	else
		return Non;
}


BOOL CCopyScreenWnd::PtInMark(int xCircle,int yCirlce,int x,int y)
{
	POINT pt = {x,y};
	RECT rc = {xCircle-MARK_SIZE,yCirlce-MARK_SIZE,xCircle+MARK_SIZE,yCirlce+MARK_SIZE};
	return ::PtInRect(&rc,pt);
}

HCURSOR CCopyScreenWnd::GetTrackCursor(int nHitTest)
{
	HINSTANCE hInst = ::GetModuleHandle(NULL);

	ATLASSERT(nHitTest>=TopLeft && nHitTest<=NEW);
	static HCURSOR curs[] = {
		NULL,
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURTLBR)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURTB)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURBLTR)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURLR)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURTLBR)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURTB)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURBLTR)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURLR)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURM)),
		::LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURTLBR))
	};
	return curs[nHitTest];
}



 