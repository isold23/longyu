#pragma once

#include "resource.h"

class CMMShowApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()

public:
	CMMShowApp(void);

private:
	virtual BOOL InitInstance(void);
	virtual int ExitInstance(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	HACCEL m_hAccelTable;
	HACCEL m_hMenuAccelTable;
};

extern CMMShowApp theApp;