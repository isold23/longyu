#include "StdAfx.h"
#include "ReportPageDlg.h"

CReportPageDlg::CReportPageDlg(void)
{
}

CReportPageDlg::CReportPageDlg(const UINT nID,CWnd* pParent,const UINT nFlags)
	:CXTPResizeDialog(nID,pParent,nFlags)
{
}

CReportPageDlg::CReportPageDlg(LPCTSTR lpszTemplateName,CWnd* pParent,const UINT nFlags)	
	: CXTPResizeDialog(lpszTemplateName,pParent,nFlags)
{
}

CReportPageDlg::~CReportPageDlg(void)
{

}

BEGIN_MESSAGE_MAP(CReportPageDlg, CXTPResizeDialog)
	ON_WM_CTLCOLOR()
	//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



static GRADIENT_RECT gc = {0,1};
static TRIVERTEX vNormal[2]  = {{0,0,0xFE00,0xFB00,0xF400,0},{0,0,0xFD00,0xF400,0xE300,0}};

BOOL CReportPageDlg::OnEraseBkgnd(CDC* pDC)
{
	CXTPClientRect rc(this); 
	TRIVERTEX *v =   vNormal;
	v[0].x      = rc.left;
	v[0].y      = rc.top; 
	v[1].x      = rc.right;
	v[1].y      = rc.bottom;  

	pDC->GradientFill(v,2,&gc,1,GRADIENT_FILL_RECT_V);
	return TRUE;
}

HBRUSH CReportPageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	static CBrush brush(RGB(0xFE,0xFB,0xF4)); 
	return (HBRUSH)brush.GetSafeHandle();
}
