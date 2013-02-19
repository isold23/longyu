
// PropertyManagerApp.h : PropertyManagerApp 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       

class CPropertyManagerAppApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	CPropertyManagerAppApp(void);


public:
	virtual BOOL InitInstance(void);

	afx_msg void OnAppAbout();
};

extern CPropertyManagerAppApp theApp;
