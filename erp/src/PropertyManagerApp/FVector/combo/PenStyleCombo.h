#if !defined(AFX_PENSTYLECOMBO_H_INCLUDED_)
#define AFX_PENSTYLECOMBO_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PenStyleCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PenStyleCombo window

class PenStyleCombo : public CComboBox
{
// Construction
public:
	PenStyleCombo();

// Attributes
public:

// Operations
public:

// Overrides
	//{{AFX_VIRTUAL(PenStyleCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
    int GetStyle();
	void SetStyle(int);
	void Init();
	virtual ~PenStyleCombo();

protected:
	//{{AFX_MSG(PenStyleCombo)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_PENSTYLECOMBO_H_INCLUDED_)
