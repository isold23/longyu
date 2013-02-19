#include "stdafx.h"
#include "VideoSrcBaseDialog.h"
#include "DrawHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CVideoSrcBaseDialog::CVideoSrcBaseDialog(void)
	:m_pcszName(NULL)
{
}

CVideoSrcBaseDialog::CVideoSrcBaseDialog(UINT nIDTemplate, CWnd* pParentWnd)
	:CResizableDialog(nIDTemplate,pParentWnd),m_pcszName(NULL)
{

}

CVideoSrcBaseDialog::CVideoSrcBaseDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	:CResizableDialog(lpszTemplateName,pParentWnd),m_pcszName(NULL)
{

}


CVideoSrcBaseDialog::~CVideoSrcBaseDialog(void)
{
}
 

BEGIN_MESSAGE_MAP(CVideoSrcBaseDialog, CResizableDialog)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CVideoSrcBaseDialog::RepositionChildren(void)
{
	if (m_gaugeWnd.GetSafeHwnd() != NULL)
		m_gaugeWnd.RecalcWindowRect();
}

void CVideoSrcBaseDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	m_bVisible = bShow;
	if (m_gaugeWnd.GetSafeHwnd() != NULL)
		m_gaugeWnd.Show(bShow);
	CResizableDialog::OnShowWindow(bShow,nStatus);
}
 

void CVideoSrcBaseDialog::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType,cx,cy);
	RepositionChildren();
}	

CWnd* CVideoSrcBaseDialog::GetDefaultCtrl(void)
{
	return NULL;
}


DWORD CVideoSrcBaseDialog::GetSampleTick(void)
{
	return 0;
}

void CVideoSrcBaseDialog::SetDrawCursor(BOOL bDraw)
{
}

CString CVideoSrcBaseDialog::GetDesc(void)
{
	return CString();
}

void CVideoSrcBaseDialog::SampleRef(BOOL bRef)
{

}

void CVideoSrcBaseDialog::OnGaugeChanged(void)
{

}