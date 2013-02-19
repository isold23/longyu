#include "stdafx.h"
#include "PaneTreeCtrl.h"
#include "DrawHelper.h"

CPaneTreeCtrl::CPaneTreeCtrl(BOOL bLayered)
	:m_bLayered(bLayered),
	 m_sizeImage(-1,-1),
	 m_pImagelist(NULL),
	 m_pTargetCmdWnd(NULL)
{

}

CPaneTreeCtrl::~CPaneTreeCtrl(void)
{

}

BEGIN_MESSAGE_MAP(CPaneTreeCtrl,CTreeCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_CLICK,&CPaneTreeCtrl::OnClick)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,&CPaneTreeCtrl::OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CPaneTreeCtrl::OnTvnDBClickCmd)
END_MESSAGE_MAP()

void CPaneTreeCtrl::OnTvnDBClickCmd(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = TRUE;
}
void CPaneTreeCtrl::OnClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_pTargetCmdWnd != NULL)
	{
		HTREEITEM hTreeItem = HitTest(CCurorPos(this));
		if (hTreeItem != NULL)
			m_pTargetCmdWnd->PostMessage(WM_COMMAND,GetItemData(hTreeItem));

	}
	*pResult = FALSE;
}
void CPaneTreeCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTreeCtrl::OnSize(nType,cx,cy);
	Invalidate();
}
 

void CPaneTreeCtrl::OnCustomDraw(LPNMHDR pNMHDR, LRESULT *pResult)
{
	LPNMTVCUSTOMDRAW pN = (LPNMTVCUSTOMDRAW)pNMHDR;
	NMCUSTOMDRAW &nmcd = pN->nmcd;

	*pResult = 0;
	if (nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{ 
		DrawItem((HTREEITEM)nmcd.dwItemSpec,nmcd.hdc,nmcd.rc,nmcd.uItemState); 
		*pResult = CDRF_SKIPDEFAULT;
	}

}

static GRADIENT_RECT gc = {0,1};
static TRIVERTEX vNormal[2]  = {{0,0,0xFE00,0xFB00,0xF400,0},{0,0,0xFD00,0xF400,0xE300,0}};
static TRIVERTEX vHighlight[2] = {{0,0,0xF400,0xFB00,0xFE00,0},{0,0,0xE300,0xF400,0xFD00,0}};

BOOL CPaneTreeCtrl::OnEraseBkgnd(CDC* pDC)
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

void CPaneTreeCtrl::DrawItem(HTREEITEM hItem,HDC hDC,const RECT &rect,UINT nItemState)
{
	CRect rc(rect);
	if (rc.IsRectEmpty())
		return;


	if (m_pImagelist == NULL)
		m_pImagelist = GetImageList(TVSIL_NORMAL);
	if (m_pImagelist == NULL)
		return ;


	if (m_sizeImage.cx == -1)
	{
		IMAGEINFO ii;
		m_pImagelist->GetImageInfo(0,&ii);
		m_sizeImage.cx = ii.rcImage.right;
		m_sizeImage.cy = ii.rcImage.bottom;
		m_nIndent = GetIndent();
	}

	if (m_font.GetSafeHandle() == NULL)
	{
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));     
		lf.lfHeight = 16;
		lf.lfWeight = 500;

		_tcscpy(lf.lfFaceName, _T("Arial"));       
		VERIFY(m_font.CreateFontIndirect(&lf));  
	} 
  

	CDC dc;
	dc.Attach(hDC);
	dc.SelectObject(&m_font);

	TRIVERTEX *v =  (nItemState&CDIS_FOCUS || nItemState&CDIS_SELECTED ? vHighlight : vNormal);
	v[0].x      = rc.left;
	v[0].y      = rc.top; 
	v[1].x      = rc.right;
	v[1].y      = rc.bottom;  

	if (nItemState & CDIS_NEARHOT)
	{
		TRACE(_T(""));
	}

	dc.GradientFill(v,2,&gc,1,GRADIENT_FILL_RECT_V);

	BOOL bRoot = (hItem==GetRootItem());

	int nImage,nSelectedImage;
	GetItemImage(hItem,nImage,nSelectedImage);


	CPoint pt; 
	CString strText = GetItemText(hItem);

	CRect rcCalc;
	rcCalc.SetRectEmpty();
	dc.DrawText(strText,&rcCalc,DT_CALCRECT);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));

	if (!m_bLayered)
	{
		CPoint pt;
		pt.x = rc.left + (rc.Width()-m_sizeImage.cx-ICON_TEXT_GAP-rcCalc.right)/2;
		pt.y = rc.top + (rc.Height()-m_sizeImage.cy)/2;
		m_pImagelist->Draw(&dc,nImage,pt,ILD_TRANSPARENT);

		rc.left = pt.x + m_sizeImage.cx + ICON_TEXT_GAP;
		dc.DrawText(strText,rc,DT_SINGLELINE|DT_VCENTER);
	}
	else
	{
		pt.x = rc.left + ICON_TEXT_GAP;
		pt.y = rc.top + (rc.Height()-m_sizeImage.cy)/2;
		if (!bRoot)
			pt.x += m_nIndent;
		m_pImagelist->Draw(&dc,nImage,pt,ILD_TRANSPARENT);

		rc.left =  pt.x + m_sizeImage.cy + ICON_TEXT_GAP;
		dc.DrawText(strText,rc,DT_VCENTER|DT_SINGLELINE);
	}


	dc.Detach();

}