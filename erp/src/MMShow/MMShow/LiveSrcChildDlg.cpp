#include "stdafx.h"
#include "Resource.h"
#include "LiveSrcChildDlg.h"
#include "DrawHelper.h"
#include "LiveSrcDlg.h"
#include "Cams.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


 
CLiveSrcChildDlg::CLiveSrcChildDlg(void)
	:m_pAttachTo(NULL)
{ 
}

CLiveSrcChildDlg::~CLiveSrcChildDlg()
{
}

void CLiveSrcChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STC_CONTENT,m_stcCam);
}


BEGIN_MESSAGE_MAP(CLiveSrcChildDlg, CResizableDialog)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

BOOL CLiveSrcChildDlg::OnInitDialog(void)
{
	CResizableDialog::OnInitDialog();

	AddAnchor(IDC_STC_CAPTION,TOP_LEFT,TOP_RIGHT);
	AddAnchor(m_stcCam,TOP_LEFT,BOTTOM_RIGHT);

	return FALSE;
}
 
HBRUSH CLiveSrcChildDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return ::GetSysColorBrush(COLOR_WINDOW);
}

 

void CLiveSrcChildDlg::AttachTo(CWnd *pWnd)
{
	m_pAttachTo = pWnd;
	FollowAttach();
	SetWindowLong(m_pAttachTo->GetSafeHwnd(),GWLP_USERDATA,(DWORD_PTR)this);
}

void CLiveSrcChildDlg::FollowAttach(void)
{
	if (m_pAttachTo != NULL)
	{
		CWindowRect rc(m_pAttachTo);
		GetParent()->ScreenToClient(rc);
		MoveWindow(rc,TRUE);
	}
} 

void CLiveSrcChildDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	GetParent()->PostMessage(WM_WANNABIG,(WPARAM)this);
	CResizableDialog::OnLButtonDblClk(nFlags,point);
}


void CLiveSrcChildDlg::SetCam(CCamSampleListener *pListener,BOOL bNotify,CCamExt *pCamEx)
{
	if (pCamEx != NULL)
	{
		m_pCamEx = pCamEx;
		SetDlgItemText(IDC_STC_CAPTION,pCamEx->GetDisplayName());
	}
	m_pCamEx->SetPreview(m_stcCam.GetSafeHwnd(),pListener,bNotify);
}
