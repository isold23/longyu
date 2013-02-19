#include "stdafx.h"
#include "VecWnd.h"
#include <cfloat>
#include "../Utils/FileHelper.h"

#define XML_LS
#ifdef XML_LS
	#include "VecLS\XMLVecLS.h"
	#define CVecLS CXMLVecLS
#else
	#include "VecLS/BinVecLS.h"
	#define CVecLS CBinVecLS
#endif

#define BATCH_DRAW_BEGIN() 	{ BOOL bOrgDrawPaused = PauseDraw(TRUE);
#define BATCH_DRAW_END()	m_bDrawPaused = bOrgDrawPaused; } 	Redraw(); 

/*
	* Background image display optimization
	* Distance calculate
	* Center view while zooming
	* Custom version selection handle
*/

CGdiplusInit GdiPlusInit;

static REAL ZoomInFactor = 1.0f/0.985f;

static const REAL LineScrollPixel = 10.0f;
static const REAL PageScrollPixel = 150.0f;


LPCTSTR CVecWnd::VECWND_CLASSNAME = _T("VecWnd");
 
CElem* CVecWnd::GetPrototype(int nOPType)
{
	switch (nOPType)
	{
	case CElem::Gauge:
		return new CGauge(this);

#if VW_VER_CURRENT == VW_VER_DESIGNER
	case CElem::Line:
		return new CLine(this);
	case CElem::FreeLine:
		return new CFreeLine(this);
	case CElem::Bezier:
		return new CBezier(this);
	case CElem::Region:
		return new CRegion(this);
	case CElem::Arc:
		return new CArc(this);
	case CElem::Poly:
		return new CPoly(this);
	case CElem::Rectangle:
		return new CRectangle(this);
	case CElem::RoundRect:
		return new CRoundRect(this);
	case CElem::Ellipse:
		return new CEllipse(this);
	case CElem::Chord:
		return new CChord(this);
	case CElem::Pie:
		return new CPie(this);
	case CElem::UnknownElem:
		return NULL;
#endif
	default:
		return NULL;
	}
}

CVecWnd::CVecWnd(void)
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInst, VECWND_CLASSNAME, &wndcls)))
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
		wndcls.lpszClassName    = VECWND_CLASSNAME;

		if (!AfxRegisterClass(
			&wndcls))
		{
			AfxThrowResourceException();
			return ;
		}
	}
 
	m_scale = CSizeF(1.0f,1.0f);
	m_pSelElem = NULL;
	m_pHoverElem = NULL;
	m_nDragHitTest = -1;
	m_bLButtonDown = FALSE;
	m_nOPType = CElem::UnknownElem;
	
	const COLORREF DEF_BK_COLOR = RGB(0,0,0);
	m_clrBk = DEF_BK_COLOR; 

	m_pImgBkgnd = NULL;
	m_dwUserData = 0;
	m_dwCustomData = 0;
	m_ptStart.x = m_ptStart.y = 0.0f;

	m_bDrawPaused = FALSE;

#if VW_VER_CURRENT == VW_VER_CUSTOMER
	m_bTicked = FALSE;
#endif  
 
} 
	
void CVecWnd::ResetMemember(void)
{
	SetScale(CSizeF(1.0f,1.0f));
	m_pSelElem = NULL;
	m_pHoverElem = NULL;
	m_nDragHitTest = -1;
	m_bLButtonDown = FALSE;
	m_nOPType = CElem::UnknownElem;

	const COLORREF DEF_BK_COLOR = RGB(0,0,0);
	m_clrBk = DEF_BK_COLOR; 

	m_pImgBkgnd = NULL;
	m_dwUserData = 0;
	m_dwCustomData = 0;
	m_ptStart.x = m_ptStart.y = 0.0f;

	m_bDrawPaused = FALSE;

}

CVecWnd::~CVecWnd(void)
{
	RemoveAllElem();
}


BEGIN_MESSAGE_MAP(CVecWnd, CWnd)
	ON_WM_MOUSEWHEEL()	
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE() 
	ON_WM_SETCURSOR()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


void CVecWnd::Zoom(REAL fXScale,REAL fYScale)
{

	if (RealEqual(fXScale,1.0f) && RealEqual(fYScale,1.0f))
		return;

	m_scale.cx *= fXScale;
	m_scale.cy *= fYScale;

	CRectF rc;
	for (int i=0; i<m_elems.GetCount(); ++i)
	{
		m_elems[i]->GetBoundsRect(rc);
		rc.left *= fXScale;
		rc.right *= fXScale;
		rc.top *= fYScale;
		rc.bottom *= fYScale;
		m_elems[i]->SetBoundsRect(rc);
	}

	CPointF ptStart(m_ptStart);
	ptStart.x *= fXScale;
	ptStart.y *= fYScale;
 
	BATCH_DRAW_BEGIN()
	ResetStartPos(ptStart);
	BATCH_DRAW_END()

}

void CVecWnd::EnsureVisible(CElem *pElem)
{
	CRectF rc;
	m_pSelElem->GetBoundsRect(rc);
	ResetStartPos(rc.TopLeft());
}

void CVecWnd::SetSelectedElem(CElem *pElem)
{
	if (m_pSelElem != pElem)
	{
		CElem *pObject = m_pSelElem;
		m_pSelElem = pElem;
		NotifyChange(VWN_SELCHANGE,pObject);
	}

	BATCH_DRAW_BEGIN()
	if (m_pSelElem != NULL)
		EnsureVisible(pElem);
	BATCH_DRAW_END()
}

void CVecWnd::GetElemsBoudsRect(CRectF &rc)
{
	rc.SetRectEmpty();
	if (m_pImgBkgnd != NULL)
	{
		rc.right = (REAL)m_pImgBkgnd->GetWidth()*m_scale.cx;
		rc.bottom = (REAL)m_pImgBkgnd->GetHeight()*m_scale.cy;
	}

	if (!m_elems.IsEmpty())
	{
		CRectF rect; 
		rc.NormalizeRect();
		for (int i=0; i<m_elems.GetCount(); ++i)
		{
			m_elems[i]->GetBoundsRect(rect);
			rect.NormalizeRect();
			if (rc.left > rect.left)
				rc.left = rect.left;
			if (rc.top > rect.top)
				rc.top = rect.top;
			if (rc.right < rect.right)
				rc.right = rect.right;
			if (rc.bottom < rect.bottom)
				rc.bottom = rect.bottom;
		}
	}
}
 

void CVecWnd::SetBkColor(COLORREF clr)
{
	if (m_clrBk != clr)
	{
		m_clrBk = clr;
		Redraw();
	}
}

BOOL CVecWnd::SetBkgndImage(const CString &path)
{
	if (m_pImgBkgnd != NULL)
		delete m_pImgBkgnd;

	m_pImgBkgnd = Gdiplus::Bitmap::FromFile(path);
	if (m_pImgBkgnd == NULL)
		return FALSE;
 	
	m_strBkgndImagePath = path;
	Redraw();
	return TRUE;
}

void CVecWnd::RemoveAllElem(void)
{
	if (m_nOPType!=CElem::UnknownElem)
		delete m_pSelElem;
	for (int i=0; i<(int)m_elems.GetCount(); ++i)
		delete m_elems[i];
	m_elems.RemoveAll();

	m_pSelElem = NULL;
	m_nOPType = CElem::UnknownElem;
}

BOOL CVecWnd::Load(LPCTSTR pcszFileName)
{ 
	RemoveAllElem();

	stVecParam param;
	if (!CVecLS::Load(pcszFileName,param,m_elems))
		return FALSE;
 
	for (int i=0; i<m_elems.GetCount(); ++i)
		m_elems[i]->SetWnd(this);

	Fh::GetAbsolutePath(param.strBkgndImage,Fh::GetFolderPath(pcszFileName),m_strBkgndImagePath);
	SetBkgndImage(m_strBkgndImagePath);
	
	m_clrBk = param.clrBk;
	m_dwCustomData = param.dwCustomData;
	m_strDesc = param.strDesc;
	m_scale = param.scale;

	SetScale(CSizeF(1.0f,1.0f));
	return TRUE;
}

BOOL CVecWnd::Save(LPCTSTR pcszFileName)
{
	CString strRelativePath;

	Fh::GetRelativePath(m_strBkgndImagePath,Fh::GetFolderPath(pcszFileName),strRelativePath);

	stVecParam param;
	param.clrBk = m_clrBk;
	param.dwCustomData = m_dwCustomData;
	param.scale = m_scale;
	param.strBkgndImage = strRelativePath;
	param.strDesc = m_strDesc;
	return CVecLS::Save(pcszFileName,param,m_elems);
}

void CVecWnd::SetOPType(int nOPType)
{
	if (m_nOPType != CElem::UnknownElem)
	{
		delete m_pSelElem;
		m_pSelElem = NULL;
	}

	m_nOPType = nOPType;
	if (m_pSelElem != NULL)
	{
		CElem *pObject = m_pSelElem;
		m_pSelElem = NULL;
		NotifyChange(VWN_SELCHANGE,pObject);
		Redraw();
	}
}
CElem* CVecWnd::CloneSelectedElem(void)
{
	if (GetSelectedElem() == NULL)
		return NULL;

	CElem *pElem = GetSelectedElem()->Clone();
	m_elems.Add(pElem);
	Redraw();
	return pElem;
}

void CVecWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
		RemoveSelected();
	CWnd::OnKeyUp(nChar,nRepCnt,nFlags);
}

void CVecWnd::RemoveAt(UINT nIndex)
{
	CElem *pElem = m_elems[nIndex];
	m_elems.RemoveAt(nIndex);

	if (pElem == m_pHoverElem)
	{
		m_pHoverElem = NULL;
	}
	else if (pElem == m_pSelElem)
	{
		m_pSelElem = NULL;
		m_nOPType = CElem::UnknownElem;
	}
	
	Redraw();
	delete pElem;
}

void CVecWnd::RemoveSelected(void)
{
	if (m_pSelElem != NULL)
	{
		for (int i=0,cnt=(int)m_elems.GetCount(); i<cnt; ++i)
		{
			if (m_elems[i] == m_pSelElem)
			{
				m_elems.RemoveAt(i);
				break;
			}
		}

		delete m_pSelElem;
		m_pSelElem = NULL;
		m_nOPType = CElem::UnknownElem;
		Redraw();
	}
}


void CVecWnd::SetSelectTopmost(void)
{
	if (m_pSelElem != NULL)
	{
		for (int i=0,cnt=(int)m_elems.GetCount(); i<cnt; ++i)
		{
			if (m_elems[i] == m_pSelElem)
			{
				m_elems.RemoveAt(i);
				m_elems.InsertAt(0,m_pSelElem);
				Redraw();
				break;
			}
		}
	}
}


void CVecWnd::SetSelectDownmost(void)
{
	if (m_pSelElem != NULL)
	{
		for (int i=0,cnt=(int)m_elems.GetCount(); i<cnt; ++i)
		{
			if (m_elems[i] == m_pSelElem)
			{
				m_elems.RemoveAt(i);
				m_elems.Add(m_pSelElem);
				Redraw();
				break;
			}
		}
	}

}

CElem* CVecWnd::HitTest(CPointF point,int &nHitTest)
{ 
	nHitTest = -1; 
	point += m_ptStart;

	CRectF rcBounds;
	for (int i=0; i<m_elems.GetCount(); ++i)
	{
		CElem *pElem = m_elems[i];
#if VW_VER_CURRENT == VW_VER_CUSTOMER
		if (!m_bTicked && !pElem->IsHidden())
#endif
		{
			pElem->GetBoundsRect(rcBounds);
			if (rcBounds.PtInRect(point))
			{
				nHitTest = m_elems[i]->HitTest(point,m_pSelElem==pElem);
				if (nHitTest != -1)
					return pElem;
			}
		}
	}
	return NULL;
}

void CVecWnd::NotifyChange(UINT uNotifyCode,void *data)
{
	NMOBJECTNOTIFY nmn;
	NMHDR  &nm = nmn.hdr;
	nm.code = uNotifyCode;
	nm.idFrom = GetDlgCtrlID();
	nm.hwndFrom = GetSafeHwnd();
	nmn.pObject = data;
	GetParent()->SendMessage(WM_NOTIFY,nm.idFrom,reinterpret_cast<LPARAM>(&nmn));
}



BOOL CVecWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CWnd* pWnd = this;
	return pWnd->Create(VECWND_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID);
}


BOOL CVecWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CVecWnd::DrawBkgndImage(CDC *pDC)
{
	if (m_pImgBkgnd != NULL)
	{		

		Gdiplus::Graphics graphics(pDC->GetSafeHdc());
		Gdiplus::RectF rect;
		rect.X = rect.Y = 0.0f;
		rect.Width = m_pImgBkgnd->GetWidth()*m_scale.cx;
		rect.Height = m_pImgBkgnd->GetHeight()*m_scale.cy;

		graphics.DrawImage(m_pImgBkgnd,rect);
	}
}


void CVecWnd::OnPaint(void)
{
	CPaintDC dc(this);
	dc.SetBkColor(m_clrBk);

	dc.SetPolyFillMode(VM_DEF_POLY_FILLMODE);

	CFont font;
	font.CreatePointFont(90,_T("Ms Serif"));
	dc.SelectObject(&font);
	
	CRect rc;
	GetClientRect(rc);

	CPointF ptStart = GetStartPos();

	CxMemDC dcMem(dc,rc,TRUE);
	CxMemDC dcAux(dcMem,rc,FALSE);
 
	dcMem.SetWindowOrg((int)ptStart.x,(int)ptStart.y);

	DrawBkgndImage(&dcMem); 

	CRectF rcWnd(rc);
	rcWnd.OffsetRect(GetStartPos());

	CRectF rcBounds; 


#if VW_VER_CURRENT == VW_VER_DESIGNER
	for (int i=(int)m_elems.GetCount()-1; i>=0; --i)
	{
		CElem *pElem = m_elems[i];
		pElem->GetBoundsRect(rcBounds);
		if (rcBounds.IntersectRect(rcWnd))
		{
			if (m_pSelElem == pElem)
				pElem->OnDraw(&dcMem, CElem::DrawSelected,&dcAux);
			else 
				pElem->OnDraw(&dcMem,CElem::DrawNormal,&dcAux);
		}
	}

#else
	if (m_bTicked)
	{	
		for (int i=(int)m_elems.GetCount()-1; i>=0; --i)
		{ 
			CElem *pElem = m_elems[i];
			if (pElem->IsTicked())
			{
				pElem->GetBoundsRect(rcBounds);
				if (rcBounds.IntersectRect(rcWnd)) 
					pElem->OnDraw(&dcMem, CElem::DrawTick,&dcAux);
			}
		} 

	}
	else
	{
		for (int i=(int)m_elems.GetCount()-1; i>=0; --i)
		{ 
			CElem *pElem = m_elems[i];
			if (!pElem->IsHidden())
			{
				pElem->GetBoundsRect(rcBounds);
				if (rcBounds.IntersectRect(rcWnd))
				{
					if (m_pSelElem == pElem)
						pElem->OnDraw(&dcMem, CElem::DrawSelected,&dcAux);
					else if (m_pHoverElem == pElem)
						pElem->OnDraw(&dcMem, CElem::DrawHover,&dcAux);
					else if (pElem->GetType() == CElem::Gauge)
						pElem->OnDraw(&dcMem, CElem::DrawNormal,&dcAux);

				}
			}
		} 
	}
#endif


	if (m_nOPType!=CElem::UnknownElem && m_pSelElem!=NULL)
		m_pSelElem->OnDraw(&dcMem,CElem::DrawNormal,&dcAux);
 
	dcMem.SetWindowOrg(0,0); 
}

void CVecWnd::OnLButtonDown(UINT nFlags, CPoint point)
{  
	SetFocus();

	CPointF pt((REAL)point.x,(REAL)point.y);  

	if (m_nOPType != CElem::UnknownElem)
	{
		if (m_pSelElem != NULL)
		{
			m_pSelElem->InitReDrag(pt);
		}
		else
		{
			m_pSelElem = GetPrototype(m_nOPType);
			if (m_pSelElem != NULL)
				m_pSelElem->InitDrag(pt);
			else
				m_nOPType = CElem::UnknownElem;
		}
		m_ptCapture = pt;
	}
	else
	{ 
		CElem *pElem = HitTest(pt,m_nDragHitTest);
		if (m_pSelElem != pElem)
		{
			CElem *pObject = m_pSelElem;
			m_pSelElem = pElem;
			NotifyChange(VWN_SELCHANGE,pObject);
			Redraw();
		}

		if (m_pSelElem == NULL)
		{
			m_nDragHitTest = 0;
			m_ptMark = m_ptCapture = pt;
		}
		else
		{ 
			ASSERT(m_nDragHitTest != -1);	
#if VW_VER_CURRENT == VW_VER_CUSTOMER	
			if ( m_pSelElem->GetType() == CElem::Gauge) 
#endif
			if (m_pSelElem->OnDragStart(m_nDragHitTest,pt))
				m_ptMark = pt;
			m_ptCapture = pt;
		}
	}

	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}

void CVecWnd::OnLButtonUp(UINT nFlags, CPoint point)
{ 	
	CPointF pt((REAL)point.x,(REAL)point.y); 

	if (m_nOPType != CElem::UnknownElem)
	{
		if (m_pSelElem == NULL)
		{
			CWnd::OnLButtonUp(nFlags,point);
			return;
		}	
		else if (m_pSelElem->InitPauseDrag(pt))
		{
			m_nOPType = CElem::UnknownElem;
			m_elems.InsertAt(0,m_pSelElem); 
			NotifyChange(VWN_SELCHANGE,NULL);
			Redraw();
		} 
	}
	else if (m_nDragHitTest != -1)
	{ 
		if (m_pSelElem != NULL)
#if VW_VER_CURRENT == VW_VER_CUSTOMER	
			if ( m_pSelElem->GetType() == CElem::Gauge) 
#endif
			if (m_pSelElem->OnDragEnd(m_nDragHitTest,pt))
				Redraw();
		m_nDragHitTest = -1;
	}

	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CVecWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest != HTCLIENT)
		return CWnd::OnSetCursor(pWnd,nHitTest,message);
	
	HCURSOR hCursor = NULL;
	if (m_pSelElem!=NULL && m_nDragHitTest != -1)
	{
#if VW_VER_CURRENT == VW_VER_CUSTOMER
		if (m_pSelElem->GetType() == CElem::Gauge)
#endif
		hCursor = m_pSelElem->GetCursor(m_nDragHitTest);
	}
	else
	{
		CPoint curPos;
		::GetCursorPos(&curPos);
		ScreenToClient(&curPos);
		CPointF pt((REAL)curPos.x,(REAL)curPos.y);

		int ht;
		CElem *pElem = HitTest(pt,ht);
		if (pElem != NULL)
#if VW_VER_CURRENT == VW_VER_CUSTOMER
			if (pElem->GetType() == CElem::Gauge)
#endif
			hCursor = pElem->GetCursor(ht);
	}

	if (hCursor == NULL)
		return CWnd::OnSetCursor(pWnd,nHitTest,message);
 
	SetCursor(hCursor);
	return TRUE;
}

void CVecWnd::OnHover(CPointF pt,BOOL bRedraw)
{
	int nHitTest;
	CElem *pElem = HitTest(pt,nHitTest);
	if (m_pHoverElem != pElem)
	{
		m_pHoverElem = pElem;
		if (bRedraw)
			Redraw();
		NotifyChange(VWN_HOVERCHANGE,pElem);
	}
}


void CVecWnd::OnMouseMove(UINT nFlags, CPoint point)
{   
	CPointF pt((REAL)point.x,(REAL)point.y);  

	if (m_nOPType != CElem::UnknownElem)
	{
		if (m_pSelElem != NULL)
		{
			m_pSelElem->InitDragging(pt);
			m_ptCapture = pt;
		}
	}
	else if (m_nDragHitTest == -1)
	{
		OnHover(pt,TRUE);
	}
	else
	{
		if (point.x>0 && point.y>0)
		{
#if VW_VER_CURRENT == VW_VER_CUSTOMER	
			BOOL bProcessed = FALSE;
#endif
			if (m_pSelElem != NULL)				
			{
#if VW_VER_CURRENT == VW_VER_CUSTOMER	
				if ( m_pSelElem->GetType() == CElem::Gauge) 
#endif
				{	
					m_pSelElem->OnDrag(m_nDragHitTest,pt);
#if VW_VER_CURRENT == VW_VER_CUSTOMER	
					bProcessed = TRUE;
#endif
				}
				m_ptCapture = pt;

			}
#if VW_VER_CURRENT == VW_VER_CUSTOMER	
			if (!bProcessed)
#else
			else  
#endif
			{
				m_pSelElem = NULL;
				CSizeF offset;
				offset.cx = point.x - m_ptCapture.x;
				offset.cy = point.y - m_ptCapture.y;

				CPointF ptStart(m_ptStart - offset);
				ResetStartPos(ptStart);
				m_ptCapture = pt;
			}
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CVecWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SetFocus();

	CPointF pt((REAL)point.x,(REAL)point.y);  

	if (m_nOPType != CElem::UnknownElem)
	{
		ASSERT(m_pSelElem != NULL);
		m_pSelElem->InitEndDrag(pt);
		m_elems.InsertAt(0,m_pSelElem); 
		m_nOPType = CElem::UnknownElem;
		NotifyChange(VWN_SELCHANGE,NULL);
		Redraw();
	}
	else
	{
		int nHitTest;
		CElem *pElem = HitTest(pt,nHitTest);
		if (m_pSelElem != pElem)
		{
			void *pObject = m_pSelElem;
			m_pSelElem = pElem;
			NotifyChange(VWN_SELCHANGE,pObject);
		}

		if (m_pSelElem != NULL)
		{ 
			ASSERT(nHitTest != -1);
			m_pSelElem->OnOption(nHitTest,pt);
		}
		else
		{
			Zoom(ZoomInFactor,ZoomInFactor);
		}
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}



BOOL CVecWnd::ResetStartPos(CPointF ptStart)
{
	CRectF rc;
	GetElemsBoudsRect(rc);

	CRect rcWnd;
	GetClientRect(rcWnd);

	if (rcWnd.right > rc.right)
		ptStart.x = 0.0f;
	if (rcWnd.bottom > rc.bottom)
		ptStart.y = 0.0f;
	
	const CPointF ptMin(0.0f,0.0f);
	CPointF ptMax(rc.right-rcWnd.right,rc.bottom-rcWnd.bottom);
	ptMax.x = max(0,ptMax.x);
	ptMax.y = max(0,ptMax.y);

	ptStart.x = max(ptMin.x,ptStart.x);
	ptStart.y = max(ptMin.y,ptStart.y);
	ptStart.x = min(ptMax.x,ptStart.x);
	ptStart.y = min(ptMax.y,ptStart.y);

	if (RealEqual(ptStart.x,m_ptStart.x) && RealEqual(ptStart.y,m_ptStart.y))
		return FALSE;
		
	m_ptStart = ptStart;
	Redraw();
	return TRUE;
}

void CVecWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{ 
	CPointF ptStart(m_ptStart);
	switch(nChar)
	{
	case VK_HOME: 
		ptStart = CPointF(FLT_MIN,FLT_MIN);
		break;
	case VK_END: 
		ptStart = CPointF(FLT_MAX,FLT_MAX);
		break;
	case VK_UP: 
		ptStart.y -= LineScrollPixel;
		break;
	case VK_DOWN: 
		ptStart.y += LineScrollPixel;
		break;
	case VK_LEFT:
		ptStart.x -= LineScrollPixel;
		break;
	case VK_RIGHT:
		ptStart.x +=  LineScrollPixel;
		break;
	case VK_PRIOR: 
		ptStart.y -= PageScrollPixel;
		break;
	case VK_NEXT: 
		ptStart.y +=  PageScrollPixel;
		break;
	default:
		return ;
	}

	ResetStartPos(ptStart);
}

BOOL CVecWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{ 
	if (nFlags & MK_CONTROL)
	{
		REAL fScale = ZoomInFactor;
		if ( zDelta < 0)
			fScale = 1/fScale;
		Zoom(fScale,fScale);
	}
	else
	{
		CPointF ptStart(m_ptStart);
		ptStart.y += (zDelta<0 ? LineScrollPixel: -LineScrollPixel);
		ResetStartPos(ptStart);
	}
	return 0;
}
 

UINT CVecWnd::OnGetDlgCode(void)
{
	return DLGC_WANTALLKEYS;
}


 