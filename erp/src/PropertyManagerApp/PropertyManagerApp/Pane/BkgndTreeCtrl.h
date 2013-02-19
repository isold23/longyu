 #pragma once 
#include "PaneTreeCtrl.h"

class CBkgndDlg;

class CBkgndTreeCtrl : public CPaneTreeCtrl
{ 
	DECLARE_MESSAGE_MAP()

	static const int ICON_CX = 48;
	static const int ICON_CY = 48;
public:
	CBkgndTreeCtrl(void);
	virtual ~CBkgndTreeCtrl(void);
 

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);   
	CImageList m_imageList;
};
 