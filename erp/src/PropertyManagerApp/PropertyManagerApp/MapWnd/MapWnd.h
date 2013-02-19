#pragma once
#include "VecWnd.h"

class CMapWnd : public CVecWnd
{
	DECLARE_MESSAGE_MAP()

public:
	CMapWnd(void);
	~CMapWnd(void);


private:	
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSelTickChange(UINT nCmd);
	afx_msg void OnHoverChange(NMHDR *pNM, LRESULT *pResult);
	
	CToolTipCtrl m_tip;
};