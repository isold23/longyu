// downloadfileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "downloadfile.h"
#include "downloadfileDlg.h"

#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CdownloadfileDlg 对话框




CdownloadfileDlg::CdownloadfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdownloadfileDlg::IDD, pParent)
	, m_strUrl(_T(""))
	, m_strLocal(_T(""))
	, m_strProxyIp(_T(""))
	, m_strProxyPort(_T(""))
	, m_strProxyPassword(_T(""))
	, m_strProxyUserName(_T(""))
	, m_strUploadFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdownloadfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strUrl);
	DDX_Text(pDX, IDC_EDIT2, m_strLocal);
	DDX_Text(pDX, IDC_EDIT3, m_strProxyIp);
	DDX_Text(pDX, IDC_EDIT4, m_strProxyPort);
	DDX_Text(pDX, IDC_EDIT6, m_strProxyPassword);
	DDX_Text(pDX, IDC_EDIT5, m_strProxyUserName);
	DDX_Text(pDX, IDC_EDIT7, m_strUploadFileName);
}

BEGIN_MESSAGE_MAP(CdownloadfileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CdownloadfileDlg::OnBnClickedBtnDownload)
	ON_BN_CLICKED(IDC_BUTTON2, &CdownloadfileDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CdownloadfileDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, &CdownloadfileDlg::OnBnClickedBtnUpload)
END_MESSAGE_MAP()


// CdownloadfileDlg 消息处理程序

BOOL CdownloadfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdownloadfileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdownloadfileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CdownloadfileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CdownloadfileDlg::OnBnClickedBtnDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!m_strLocal.IsEmpty())
	{
		std::string strUrl = (m_strUrl.GetBuffer(0));
		std::string strFileName = (m_strLocal.GetBuffer(0));
		CHttpDownload *pHttpDownload = new CHttpDownload;
		if (!m_strProxyIp.IsEmpty())
		{
			pHttpDownload->SetProxyInfo(0, m_strProxyIp.GetBuffer(0), atoi(m_strProxyPort.GetBuffer(0)), "", "");
		}

		if (!m_strProxyUserName.IsEmpty() && !m_strProxyIp.IsEmpty())
		{
			pHttpDownload->SetProxyInfo(0, m_strProxyIp.GetBuffer(0), atoi(m_strProxyPort.GetBuffer(0)), 
				m_strProxyUserName.GetBuffer(0), m_strProxyPassword.GetBuffer(0));
		}

		pHttpDownload->DownloadFile(strUrl, strFileName);
		delete pHttpDownload;
		pHttpDownload = NULL;
	}
	else if (!m_strUploadFileName.IsEmpty())
	{
		std::string strUrl = (m_strUrl.GetBuffer(0));
		std::string strFileName = (m_strUploadFileName.GetBuffer(0));
		CHttpDownload *pHttpUpload = new CHttpDownload;
		if (!m_strProxyIp.IsEmpty())
		{
			pHttpUpload->SetProxyInfo(0, m_strProxyIp.GetBuffer(0), atoi(m_strProxyPort.GetBuffer(0)), "", "");
		}

		if (!m_strProxyUserName.IsEmpty() && !m_strProxyIp.IsEmpty())
		{
			pHttpUpload->SetProxyInfo(0, m_strProxyIp.GetBuffer(0), atoi(m_strProxyPort.GetBuffer(0)), 
				m_strProxyUserName.GetBuffer(0), m_strProxyPassword.GetBuffer(0));
		}

		pHttpUpload->UploadFile(strUrl, strFileName);
		delete pHttpUpload;
		pHttpUpload = NULL;
	}

	UpdateData(FALSE);
}

void CdownloadfileDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CdownloadfileDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	char szDir[256];
	memset(szDir, 0, 256);
	LPMALLOC pMalloc;   
	SHGetMalloc(&pMalloc);
	BROWSEINFO bi;
	ITEMIDLIST *pidl;

	bi.hwndOwner = m_hWnd;     
	bi.pidlRoot = NULL;     
	bi.pszDisplayName = szDir;     
	bi.lpszTitle = "选择保存路径：";     
	bi.ulFlags = BIF_RETURNONLYFSDIRS;     
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL)
	{
		if (!SHGetPathFromIDList(pidl, szDir)) 
		{
			szDir[0]   =   '\0';
		}
	}
	m_strLocal = szDir;
	pMalloc->Free(pidl);
	pMalloc->Release();
	UpdateData(FALSE);
}

void CdownloadfileDlg::OnBnClickedBtnUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char szFilters[] = "All Files (*.*)|*.*||";

	CFileDialog OpenFileDlg (TRUE, "", "",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	if (OpenFileDlg.DoModal() == IDOK)
	{
		m_strUploadFileName = OpenFileDlg.GetPathName();
	}
	UpdateData(FALSE);
}
