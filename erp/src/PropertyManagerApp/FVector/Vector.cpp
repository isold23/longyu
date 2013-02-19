// Vector.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Vector.h"
#include "VectorDlg.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 

BEGIN_MESSAGE_MAP(CVectorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVectorApp 构造

CVectorApp::CVectorApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CVectorApp 对象

CVectorApp theApp;


// CVectorApp 初始化

BOOL CVectorApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
 
	AfxOleInit();

	CWinApp::InitInstance();
	AfxEnableControlContainer();

	SetRegistryKey(_T("Vector"));
	
	CVectorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
 
	return FALSE;
}
