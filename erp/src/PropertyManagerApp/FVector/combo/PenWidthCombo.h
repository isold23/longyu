#if !defined(AFX_PENWIDTHCOMBO_H_INCLUDED_)
#define AFX_PENWIDTHCOMBO_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PenWidthCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PenWidthCombo window

class PenWidthCombo : public CComboBox
{
// Construction
public:
	PenWidthCombo();

// Attributes
public:

// Operations
public:

// Overrides
	//{{AFX_VIRTUAL(PenWidthCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
    int GetWidth();
	void SetWidth(int);
	void Init();
	virtual ~PenWidthCombo();

protected:
	//{{AFX_MSG(PenWidthCombo)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_PENWIDTHCOMBO_H_INCLUDED_)
