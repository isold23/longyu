// SMServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMServer.h"
#include "SMServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDataBase db;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSMServerDlg dialog




CSMServerDlg::CSMServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_USER_MANAGE_BUTTON, m_BtnUserManager);
	DDX_Control(pDX, IDC_LIST_CONTENT, m_ListContent);
}

BEGIN_MESSAGE_MAP(CSMServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_USER_MANAGE_BUTTON, &CSMServerDlg::OnBnClickedUserManageButton)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY, &CSMServerDlg::OnBnClickedButtonHistory)
END_MESSAGE_MAP()


// CSMServerDlg message handlers

BOOL CSMServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ListContent.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListContent.InsertColumn(0, "发送者", LVCFMT_LEFT, 80);
	m_ListContent.InsertColumn(1, "发送内容", LVCFMT_LEFT, 80);
	m_ListContent.InsertColumn(2, "发送时间", LVCFMT_LEFT, 80);

	int nCount = db.GetTableCount("historymsg");
	if (nCount > 1000)
	{
		AfxMessageBox("您的历史记录太多了， 要先删除一些。");
	}

	vector<cds::db_history> historys;
	strstream sql;
	sql<<"SELECT * FROM historymsg"<<ends;
	db.GetHistoryMsg(sql.str(), historys);
	vector<cds::db_history>::iterator iter = historys.begin();
	for(int i = 0;iter != historys.end(); iter++, i++)
	{
		m_ListContent.InsertItem(i, ((cds::db_history)(*iter)).m_UserName);
		m_ListContent.SetItemText(i, 1, ((cds::db_history)(*iter)).m_Content);
		m_ListContent.SetItemText(i, 2, ((cds::db_history)(*iter)).m_Data);
	}
	UpdateData(FALSE);

	//初始话网络
	m_NetSession.Start();
	m_NetSession.WaitForEnd(10);

	m_NetSession.StartServer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CSMServerDlg::OnDestroy()
{
	m_NetSession.StopServer();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSMServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSMServerDlg::OnBnClickedUserManageButton()
{
	// TODO: Add your control notification handler code here
	CUserManageDlg UserManageDlg;
	UserManageDlg.DoModal();
}

void CSMServerDlg::OnBnClickedButtonHistory()
{
	// TODO: Add your control notification handler code here
}
