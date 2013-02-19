// TransmitFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TransmitFile.h"
#include "TransmitFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
wlw::CWinInit wininit;

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


// CTransmitFileDlg 对话框




CTransmitFileDlg::CTransmitFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransmitFileDlg::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_strBuddyIp(_T(""))
	, m_sBuddyPort(0)
	, m_strSelfInternetIp(_T(""))
	, m_strSelfLocalIp(_T(""))
	, m_sSelfLocalPort(0)
	, m_sSelfInternetPort(0)
	, m_strBuddyNatType(_T(""))
	, m_strSelfNatType(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransmitFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strFilePath);
	DDX_Text(pDX, IDC_EDIT2, m_strBuddyIp);
	DDX_Text(pDX, IDC_EDIT3, m_sBuddyPort);
	DDX_Text(pDX, IDC_EDIT6, m_strSelfInternetIp);
	DDX_Text(pDX, IDC_EDIT8, m_strSelfLocalIp);
	DDX_Text(pDX, IDC_EDIT9, m_sSelfLocalPort);
	DDX_Text(pDX, IDC_EDIT7, m_sSelfInternetPort);
	DDX_Text(pDX, IDC_EDIT4, m_strBuddyNatType);
	DDX_Text(pDX, IDC_EDIT5, m_strSelfNatType);
}

BEGIN_MESSAGE_MAP(CTransmitFileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_RECV_FILE, &CTransmitFileDlg::OnBnClickedBtnRecvFile)
	ON_BN_CLICKED(IDC_BTN_SEND_FILE, &CTransmitFileDlg::OnBnClickedBtnSendFile)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CTransmitFileDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_FILE_PATH, &CTransmitFileDlg::OnBnClickedBtnFilePath)
	ON_WM_DEVMODECHANGE()
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()


// CTransmitFileDlg 消息处理程序

BOOL CTransmitFileDlg::OnInitDialog()
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

void CTransmitFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTransmitFileDlg::OnPaint()
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
HCURSOR CTransmitFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTransmitFileDlg::OnBnClickedBtnRecvFile()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTransmitFileDlg::OnBnClickedBtnSendFile()
{
	// TODO: 在此添加控件通知处理程序代码
/************************************************************************/
/** 
  *获取网线连接状态
*/
/************************************************************************/
	HANDLE hand = WSACreateEvent();
	OVERLAPPED overlap;
	overlap.hEvent = WSACreateEvent();  
	DWORD dwRet = ::NotifyAddrChange(&hand, &overlap);  

	if (WaitForSingleObject(overlap.hEvent, INFINITE) == WAIT_OBJECT_0)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "ip change");
	}
/************************************************************************/
/** 
* PING 测试
*/
/************************************************************************/
	//code_net::CSocketAddr addr("20.108.22.43", 80);
	//code_net::CIcmp icmp(addr);
	//bool bReturn = icmp.ping();
	//if (bReturn)
	//{
	//	PrintLog(_LOG_LEVEL_DEBUG, "success");
	//}
	//else
	//{
	//	PrintLog(_LOG_LEVEL_DEBUG, "failed");
	//}
}

void CTransmitFileDlg::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CTransmitFileDlg::OnBnClickedBtnFilePath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char szFilters[] = "All Files (*.*)|*.*||";

	CFileDialog OpenFileDlg (TRUE, "", "",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	if (OpenFileDlg.DoModal() == IDOK)
	{
		m_strFilePath = OpenFileDlg.GetPathName();
	}
	UpdateData(FALSE);

}

BOOL CTransmitFileDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	CDialog::OnDeviceChange(nEventType, dwData);
	return TRUE;
}

void CTransmitFileDlg::OnDevModeChange(LPTSTR lpDeviceName)
{
	CDialog::OnDevModeChange(lpDeviceName);

	// TODO: 在此处添加消息处理程序代码
}
