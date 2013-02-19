#pragma once

class CRenderStatic : public CStatic
{
	DECLARE_MESSAGE_MAP()

public:
	enum { FILETER_MESSAGE = WM_LBUTTONDBLCLK};

public:
	CRenderStatic(void);
	virtual ~CRenderStatic(void);

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSize(UINT nType, int cx, int cy);
};
