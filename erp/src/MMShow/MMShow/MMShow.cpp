#include "stdafx.h"
#include "MMShow.h"
#include "MMShowDlg.h"
#include "Cfg.h"
#include "CfgDlg.h"
#include "Devices.h"
#include "Cams.h"
#include "CrashGenerator.h"
#include "FileHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef _DEBUG
		#pragma comment(lib,"UtilsUD.lib")
		#pragma comment(lib,"ResizableLibUD.lib")
		#pragma comment(lib,"StrmBaseUD.lib")
#else
		#pragma comment(lib,"UtilsU.lib")		
		#pragma comment(lib,"ResizableLibU.lib")
		#pragma comment(lib,"StrmBaseU.lib")
#endif


#pragma comment(lib,"gdiplus.lib")

BEGIN_MESSAGE_MAP(CMMShowApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CMMShowApp::CMMShowApp(void)
{
#if 0
#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$","w+t",stdout); 
	freopen("CONOUT$","w+t",stderr); 
#endif
#endif

}


CMMShowApp theApp;

BOOL CMMShowApp::InitInstance(void)
{
	Fh::CdAppDirectory();

	InstallCrashGenerator();

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
 
	CWinApp::InitInstance();

	AfxOleInit();

	CDevices::Load();

	m_hAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR));
	m_hMenuAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_MENU_MAIN));

	AfxEnableControlContainer();
	if (!gsys.Load())
	{
		CString str;
		str.Format(_T("加载程序配置文件 %s 失败，程序将退出"),gsys.GetPath());
		AfxMessageBox(str,MB_ICONERROR);
		return FALSE;
	}

	gcfg.Load();

	if (gcfg.GetCam0().IsEmpty() || !gcams.Init())
	{
		AfxMessageBox(_T("采集卡未正确设置，请重新设置"),MB_ICONWARNING);

		CCfgDlg cfgDlg;
		cfgDlg.SetForceCamCfg(TRUE);
		cfgDlg.SetStartIndex(CCfgDlg::Cam);
		if (cfgDlg.DoModal() == IDCANCEL)
			return FALSE;
	}

	gcams.Init();

	CMMShowDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}


	return FALSE;
}

int CMMShowApp::ExitInstance(void)
{
	if (gcfg.IsModified())
		gcfg.Save();

	gcams.Free();

	AfxOleTerm();
	return CWinApp::ExitInstance();	
}

BOOL CMMShowApp::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN || pMsg->message==WM_SYSKEYDOWN)
		if (GetKeyState(VK_LMENU) < 0)
		{
			m_pMainWnd->SetFocus();
			return m_pMainWnd->PreTranslateMessage(pMsg);
		}

	if (TranslateAccelerator(m_pMainWnd->GetSafeHwnd(),m_hAccelTable,pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);

}
