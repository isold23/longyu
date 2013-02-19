#include "stdafx.h"
#include "PropertyManagerApp.h"
#include "PropertyManagerAppDoc.h"
#include "PropertyManagerAppView.h"
#include "MainFrm.h"
#include "FileHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 
IMPLEMENT_DYNCREATE(CPropertyManagerAppView,CXTPResizeFormView)

CPropertyManagerAppView::CPropertyManagerAppView()
	: CXTPResizeFormView(IDD_FORM),
	  m_pActiveChild(NULL)
{ 
}

CPropertyManagerAppView::~CPropertyManagerAppView()
{
}
  

BEGIN_MESSAGE_MAP(CPropertyManagerAppView, CXTPResizeFormView) 
	ON_WM_SIZE()
END_MESSAGE_MAP() 

CPropertyManagerAppDoc* CPropertyManagerAppView::GetDocument() const  
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropertyManagerAppDoc)));
	return (CPropertyManagerAppDoc*)m_pDocument;
} 

BOOL CPropertyManagerAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_BORDER;
	return CXTPResizeFormView::PreCreateWindow(cs);
}

BOOL CPropertyManagerAppView::OnInitDialog(void)
{
	CXTPResizeFormView::OnInitDialog();

	const UINT MAPWND_ID = 2562;
	const UINT PICTRL_ID = MAPWND_ID+1;
	const UINT BKGNDDLG_ID = PICTRL_ID+1;
	const UINT LISTDLG_ID = BKGNDDLG_ID+1;

	CXTPClientRect rc(this);
	m_mapWnd.Create(WS_CHILD,rc,this,MAPWND_ID);
	m_mapWnd.MoveWindow(rc);

	m_mapWnd.Load(Fh::ToAppDirectory(_T("../TestRes/vec.xml")));
	//for (UINT i=0,cnt=m_mapWnd.GetElemCount(); i<cnt; ++i)
	{
		//CElem *pElem = m_mapWnd.GetElemByIndex(i);
		//pElem->SetDrawFlag(CElem::DrawCustomNon);
	}


	m_listDlg.Create(CListDlg::IDD,this);
	m_listDlg.SetDlgCtrlID(LISTDLG_ID);
	m_listDlg.MoveWindow(rc);

	m_picCtrl.SetBkgndColor(RGB(0,0,0));
	m_picCtrl.Create(WS_CHILD,rc,this,PICTRL_ID);
	m_picCtrl.Show(Fh::ToAppDirectory(_T("../TestRes/cad.jpg")),CPictureCtrl::DrawHCenter|CPictureCtrl::DrawVCenter);
	m_picCtrl.MoveWindow(rc);

	m_bkgndDlg.Create(CBkgndDlg::IDD,this);
	m_bkgndDlg.SetDlgCtrlID(BKGNDDLG_ID);
	m_bkgndDlg.MoveWindow(rc);

	SetResize(MAPWND_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(PICTRL_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(LISTDLG_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(BKGNDDLG_ID,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);

	SetActiveChild(&m_mapWnd);
	
	return FALSE;
}


 

void CPropertyManagerAppView::SetActiveChild(CWnd *pChild)
{
	if (m_pActiveChild != pChild)
	{
		if (m_pActiveChild != NULL)
			m_pActiveChild->ShowWindow(SW_HIDE);
		
		m_pActiveChild = pChild;

		if (m_pActiveChild != NULL)
		{
			m_pActiveChild->BringWindowToTop();
			m_pActiveChild->ShowWindow(SW_SHOW);
		}
	}
} 

void CPropertyManagerAppView::OnMapToolbarCommand(UINT nCmd)
{
	const REAL Scale = 0.9f;
	const REAL fScaleOut = Scale;
	const REAL fScaleIn = 1.0f/Scale;

	switch (nCmd)
	{
	case ID_MAP_NON:
		m_mapWnd.SetOPType(CElem::UnknownElem);
		break;

	case ID_MAP_ZOOMOUT:
		m_mapWnd.Zoom(fScaleIn,fScaleIn);
		break;

	case ID_MAP_ZOOMIN:
		m_mapWnd.Zoom(fScaleOut,fScaleOut);
		break;

	case ID_MAP_ZOOMRESET:
		m_mapWnd.SetScale(CSizeF(1.0f,1.0f));
		break;

	case ID_MAP_ZOOMFIT:
		{
			CRectF rc;
			m_mapWnd.GetElemsBoudsRect(rc);
			if (!rc.IsRectEmpty())
			{
				CRect rect;
				m_mapWnd.GetWindowRect(rect);
				rect.OffsetRect(-rect.TopLeft()); 
				m_mapWnd.Zoom(rect.right/rc.right,rect.bottom/rc.bottom);
			}
		}
		break;

	case ID_MAP_GAUGE:
		m_mapWnd.SetOPType(CElem::Gauge);
		break;

	case ID_MAP_ERASE:
		{
			CElem *pElem = m_mapWnd.GetSelectedElem();
			if (pElem!=NULL && pElem->GetType()==CElem::Gauge)
				m_mapWnd.RemoveSelected();
		}
		break;
	default:
		break;
	}
}