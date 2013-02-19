#pragma once
#include "PaneTreeCtrl.h"

class CMapWnd;

class CMapListbox : public CPaneTreeCtrl
{ 
	DECLARE_MESSAGE_MAP()

	static const int ICON_CX = 48;
	static const int ICON_CY = 48;
public:
	CMapListbox(void);
	virtual ~CMapListbox(void);
 

protected: 
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); 
	 
 

	CImageList m_imageList;
 
};
 

