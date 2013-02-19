// PenStyleCombo.cpp : implementation file
//

#include "stdafx.h"
#include "PenStyleCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PenStyleCombo

PenStyleCombo::PenStyleCombo()
{
}

PenStyleCombo::~PenStyleCombo()
{
}


BEGIN_MESSAGE_MAP(PenStyleCombo, CComboBox)
	//{{AFX_MSG_MAP(PenStyleCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PenStyleCombo message handlers

void PenStyleCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX); 
	CRect rc = lpDrawItemStruct->rcItem;
	
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	if (lpDrawItemStruct->itemState & ODS_FOCUS)
		dc.DrawFocusRect(&rc);
	
	if (lpDrawItemStruct->itemID == -1)
    {
	    dc.Detach();
		return;
    }

	int nIndexDC = dc.SaveDC();
	
	CBrush br;	
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		br.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
	else
		br.CreateSolidBrush(dc.GetBkColor());
    
    dc.SetBkMode(TRANSPARENT);
    dc.FillRect(&rc, &br);

    DWORD_PTR style = GetItemData(lpDrawItemStruct->itemID);
    CPen pen((int)style, 1, RGB(0,0,0));
    
    dc.SelectObject(&pen);
    
    CPoint start, end;
    start.x = rc.left;
    end.x = rc.right;
    start.y = end.y = (rc.bottom + rc.top) / 2;
    dc.MoveTo(start);
    dc.LineTo(end);

	dc.RestoreDC(nIndexDC);
	dc.Detach();
}

void PenStyleCombo::Init()
{
    static int style[] = {PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_USERSTYLE};
    static LPCTSTR name[] = {_T("Solid"), _T("Dash"), _T("Dot"), _T("DashDot"), _T("DashDotDot"), _T("Custom")};
    int count = sizeof(style)/sizeof(int);
    for (int i=0; i<count; ++i)
    {
        int index = AddString(name[i]);
        SetItemData(index, style[i]);
    }
}

int PenStyleCombo::GetStyle()
{
    return (int)GetItemData(GetCurSel());
}

void PenStyleCombo::SetStyle(int index)
{
    SetCurSel(index);
}
