// PenWidthCombo.cpp : implementation file
//

#include "stdafx.h"
#include "PenWidthCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PenWidthCombo

PenWidthCombo::PenWidthCombo()
{
}

PenWidthCombo::~PenWidthCombo()
{
}


BEGIN_MESSAGE_MAP(PenWidthCombo, CComboBox)
	//{{AFX_MSG_MAP(PenWidthCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PenWidthCombo message handlers

void PenWidthCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
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

    DWORD width = (DWORD)GetItemData(lpDrawItemStruct->itemID);
    CPen pen(PS_SOLID, width, RGB(0,0,0));
    
    dc.SelectObject(&pen);
    
    if (width)
    {
        CPoint start, end;
        start.x = rc.left;
        end.x = rc.right;
        start.y = end.y = (rc.bottom + rc.top) / 2;
        dc.MoveTo(start);
        dc.LineTo(end);
    }

	dc.RestoreDC(nIndexDC);
	dc.Detach();
}

void PenWidthCombo::Init()
{
    static int style[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14};
    static LPCTSTR name[] = {_T("0"), _T("1"), _T("2"), _T("3"), _T("4"), _T("5"),
		_T("6"), _T("7"), _T("8"), _T("9"),_T("10"),_T("11"),_T("12"),_T("13"),_T("14")};
    int count = sizeof(style)/sizeof(int);
    for (int i=0; i<count; ++i)
    {
        int index = AddString(name[i]);
        SetItemData(index, style[i]);
    }
}

int PenWidthCombo::GetWidth()
{
    return (DWORD)GetItemData(GetCurSel());
}

void PenWidthCombo::SetWidth(int index)
{
    SetCurSel(index);
}
