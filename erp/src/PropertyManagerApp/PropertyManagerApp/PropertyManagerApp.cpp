#include "stdafx.h"
#include "afxwinappex.h"
#include "PropertyManagerApp.h"
#include "MainFrm.h"
#include "LoginDlg.h"

#include "PropertyManagerAppDoc.h"
#include "PropertyManagerAppView.h"
#include "Sql/sql.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



 
SpComLib libSp_____;

 BEGIN_MESSAGE_MAP(CPropertyManagerAppApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPropertyManagerAppApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

 
CPropertyManagerAppApp::CPropertyManagerAppApp(void)
{
}
 
CPropertyManagerAppApp theApp;



BOOL CPropertyManagerAppApp::InitInstance(void)
{ 
	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();

	AfxOleInit();

 	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings();  

	CLoginDlg dlgLogin;
	if (dlgLogin.DoModal() != IDOK)
	{
		TerminateProcess(GetCurrentProcess(),0);
		return FALSE;
	}

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPropertyManagerAppDoc),
		RUNTIME_CLASS(CMainFrame),      
		RUNTIME_CLASS(CPropertyManagerAppView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

 
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

 	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->SendMessageToDescendants(WM_XTP_SETCONTROLTHEME, xtpControlThemeResource, 0);

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();


	return TRUE;
}



 class CAboutDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_ABOUTBOX };

	CAboutDlg(void) : CDialog(CAboutDlg::IDD)
	{
	}
  
};
 
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

 void CPropertyManagerAppApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
 
 

