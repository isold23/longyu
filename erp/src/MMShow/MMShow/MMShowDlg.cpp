#include "stdafx.h"
#include "Resource.h"
#include "MMShowDlg.h"
#include "DrawHelper.h"
#include "Program.h" 
#include "CfgDlg.h"
#include "FileHelper.h"
#include "Cams.h"
#include "Cfg.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/*
	*------------***************************------------*
		*--------------****CAboutDlg*****------------*
	*------------***************************------------*
*/	
class CAboutDlg : public CDialog
{
public:
	CAboutDlg(void) 
		: CDialog(IDD_ABOUTBOX) {
	}
 };
 



/*
	*------------***************************------------*
		*--------------****CMMShowDlg*****------------*
	*------------***************************------------*
*/	
 
CMMShowDlg::CMMShowDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CMMShowDlg::IDD, pParent)
{
}

void CMMShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX); 

	DDX_Control(pDX,IDM_SAVE_THIS,m_btnSave);
	DDX_Control(pDX,IDM_OPEN_THIS,m_btnOpen);
	DDX_Control(pDX,IDM_RELOAD_THIS,m_btnReload);
	DDX_Control(pDX,IDM_SAVEAS_THIS,m_btnSaveAs);
	DDX_Control(pDX,IDM_EXIT_THIS,m_btnExit);
	DDX_Control(pDX,IDM_PROP_THIS,m_btnProp);
	DDX_Control(pDX,IDM_ABOUT_THIS,m_btnAbout);
	DDX_Control(pDX,IDM_OPTION_THIS,m_btnOption);
	DDX_Control(pDX,IDM_NEW_THIS,m_btnNew);
}



BEGIN_MESSAGE_MAP(CMMShowDlg, CResizableDialog)
	ON_WM_MOVE() 
	ON_COMMAND(IDM_EXIT_THIS,&CMMShowDlg::OnMenuExit)
	ON_COMMAND(IDM_ABOUT_THIS,&CMMShowDlg::OnMenuAbout)
	ON_COMMAND(IDM_OPTION_THIS, &CMMShowDlg::OnMenuOption)
	ON_MESSAGE(CProgramDlg::WM_OPEN_CONTENTLINK,&CMMShowDlg::OnOpenContentLink)
	ON_COMMAND_RANGE(IDM_NEW_THIS,IDM_SAVE_THIS,&CMMShowDlg::OnProgramMenu)
END_MESSAGE_MAP()

BOOL CMMShowDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	CWindowRect rcProgram(GetDlgItem(IDC_STC_PROGRAM));
	ScreenToClient(rcProgram);
	m_programDlg.Create(CProgramDlg::IDD,this);
	m_programDlg.MoveWindow(rcProgram);
	m_programDlg.ShowWindow(SW_SHOW);
	
	CWindowRect rcVideoSrc(GetDlgItem(IDC_STC_VIDEO_SRC));
	ScreenToClient(rcVideoSrc);
	m_videoSrcDlg.Create(CVideoSrcDlg::IDD,this);
	m_videoSrcDlg.MoveWindow(rcVideoSrc);
	m_videoSrcDlg.ShowWindow(SW_SHOW);

	CWindowRect rcPreview(GetDlgItem(IDC_STC_PREVIEW));
	ScreenToClient(rcPreview);
	m_previewDlg.Create(CPreviewDlg::IDD,this);
	m_previewDlg.MoveWindow(rcPreview);
	m_previewDlg.ShowWindow(SW_SHOW);

	CWindowRect rcDShow(GetDlgItem(IDC_STC_LIVE));
	ScreenToClient(rcDShow);
	m_liveSrcDlg.Create(CLiveSrcDlg::IDD,this);
	m_liveSrcDlg.MoveWindow(rcDShow);
	m_liveSrcDlg.ShowWindow(SW_SHOW);
	m_liveSrcDlg.SetRefOutputDlg(&m_outputDlg);



	CWindowRect rcOutput(GetDlgItem(IDC_STC_OUTPUT));
	ScreenToClient(rcOutput);
	m_outputDlg.Create(COutputDlg::IDD,this);
	m_outputDlg.MoveWindow(rcOutput);
	m_outputDlg.ShowWindow(SW_SHOW);

	m_previewDlg.SetImageList(&m_videoSrcDlg.GetImageList());
	for (int i=0,cnt=m_videoSrcDlg.GetItemCount(); i<cnt; ++i)
		m_previewDlg.AddSrcItem(m_videoSrcDlg.GetItem(i));
	m_previewDlg.EndAddSrcItem();
	m_previewDlg.SetRefOutputDlg(&m_outputDlg);

	m_outputDlg.SetSourceDlg(&m_previewDlg,&m_liveSrcDlg);

	AddAnchor(m_programDlg,TOP_LEFT,CSize(25,100));

	AddAnchor(m_videoSrcDlg,CSize(25,0), CSize(75,63));
	AddAnchor(m_liveSrcDlg,CSize(25,63),CSize(75,100));
	AddAnchor(m_previewDlg,CSize(75,0), CSize(100,50));
	AddAnchor(m_outputDlg,CSize(75,50),BOTTOM_RIGHT);

	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),TRUE);

	Fh::Cder cder(gsys.PicPath());
	
	m_btnOpen.SetTip(_T("打开...")); 
	m_btnOpen.SetImageFile(_T("MenuOpen.png"));

	m_btnNew.SetTip(_T("新建"));
	m_btnNew.SetImageFile(_T("MenuNew.png"));

	m_btnSave.SetTip(_T("保存"));
	m_btnSave.SetImageFile(_T("MenuSave.png"));

	m_btnSaveAs.SetTip(_T("另存为..."));
	m_btnSaveAs.SetImageFile(_T("MenuSaveAs.png"));

	m_btnReload.SetTip(_T("重新加载"));
	m_btnReload.SetImageFile(_T("MenuReload.png"));

	m_btnExit.SetTip(_T("退出"));
	m_btnExit.SetImageFile(_T("MenuExit.png"));

	m_btnProp.SetTip(_T("属性"));
	m_btnProp.SetImageFile(_T("MenuProp.png"));

	m_btnAbout.SetTip(_T("关于"));
	m_btnAbout.SetImageFile(_T("MenuAbout.png"));

	m_btnOption.SetTip(_T("选项"));
	m_btnOption.SetImageFile(_T("MenuOption.png"));



	ShowWindow(SW_MAXIMIZE);
	gcams.Start();
	return TRUE;  
}

void CMMShowDlg::OnMove(int x, int y)
{
	CResizableDialog::OnMove(x,y);
	m_videoSrcDlg.RepositionChildren();
}

void CMMShowDlg::OnProgramMenu(UINT nCmdId)
{
	switch (nCmdId)
	{
	case IDM_NEW_THIS:
		m_programDlg.OpenNew();
		break;
	case IDM_RELOAD_THIS:
		m_programDlg.Reload();
		break;
	case IDM_OPEN_THIS:
		m_programDlg.OpenProgramFile();
		break;
	case IDM_SAVEAS_THIS:
		m_programDlg.SaveAs();
		break;
	case IDM_PROP_THIS:
		m_programDlg.ShowProp();
		return;
	case IDM_SAVE_THIS:
		m_programDlg.Save();
		break;
	}

	CString strPath = m_programDlg.GetProgram().GetFilePath();
	if (strPath.IsEmpty())
		strPath = _T("新建节目单");
	CString str;
	str.Format(_T("节目单 - %s"),strPath);
	SetWindowText(str);
}


void CMMShowDlg::OnMenuExit(void)
{
	OnCancel();
}

void CMMShowDlg::OnMenuAbout(void)
{
	CAboutDlg dlg;
	dlg.DoModal();
}



void CMMShowDlg::OnMenuOption()
{
	CCfgDlg dlg;
	if (dlg.DoModal() == IDOK)
	{

	}
}

LRESULT CMMShowDlg::OnOpenContentLink(WPARAM wParam,LPARAM lParam)
{
	ContentLink *cl = (ContentLink*)wParam;
	if (cl->GetType() == _T("VideoFile"))
		m_videoSrcDlg.OpenVideoFile(cl->GetFilePath());
	else
		m_videoSrcDlg.OpenWebPage(cl->GetFilePath());
	return TRUE;
}

void CMMShowDlg::OnCancel(void)
{
	if (m_programDlg.QuitConfirm())
	{
		gcams.Free();
		CResizableDialog::OnCancel();
	}
}
