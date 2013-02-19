// SMClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMClient.h"
#include "SMClientDlg.h"

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


// CSMClientDlg dialog




CSMClientDlg::CSMClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMClientDlg::IDD, pParent)
	, m_strAddUserName(_T(""))
	, m_strAddPhoneNumber(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bLogin = false;
}

void CSMClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_UserName);
	DDX_Control(pDX, IDC_EDIT3, m_UserPassword);
	DDX_Control(pDX, IDC_BTN_LOGIN, m_BtnLogin);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_EditContent);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_BtnSend);
	DDX_Control(pDX, IDC_STATIC_CONTENT, m_StaticContent);
	DDX_Control(pDX, IDC_TREE_CLIENT, m_TreeClient);
	DDX_Control(pDX, IDC_STATIC_PASSWORD, m_StaticPassword);
	DDX_Control(pDX, IDC_STATIC_NAME, m_StaticUserName);
	DDX_Control(pDX, IDC_STATIC_ADD_NAME, m_StaticAddUserName);
	DDX_Control(pDX, IDC_STATIC_PHONE_NUMBER, m_StaticAddPhoneNo);
	DDX_Control(pDX, IDC_EDIT_ADD_NAME, m_EditAddUserName);
	DDX_Control(pDX, IDC_EDIT_PHONE_NUMBER, m_EditAddPhoneNo);
	DDX_Control(pDX, IDC_STATIC_ADD_MESSAGE, m_StaticAddMessage);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_BtnAddClient);
	DDX_Control(pDX, IDC_BTN_ADD, m_BtnAdd);
	DDX_Text(pDX, IDC_EDIT_ADD_NAME, m_strAddUserName);
	DDX_Text(pDX, IDC_EDIT_PHONE_NUMBER, m_strAddPhoneNumber);
}

BEGIN_MESSAGE_MAP(CSMClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CSMClientDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CSMClientDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BTN_ADD, &CSMClientDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSMClientDlg::OnBnClickedButtonSend)
	//ON_NOTIFY(TVN_SELCHANGED,   IDC_TREE_CLIENT, OnTreeCtrlSelectChange)

	ON_NOTIFY( NM_RCLICK,IDC_TREE_CLIENT, OnTreeCtrlSelectChange )

END_MESSAGE_MAP()


// CSMClientDlg message handlers

BOOL CSMClientDlg::OnInitDialog()
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
	//m_NetSession.SetRecvHandle(m_Receiver);
	//PrintLog(_LOG_LEVEL_DEBUG, "初始化窗口");
	SetLogin();
	m_bIsAddMessage = true;
	bool bRet = m_NetSession.Connect();
	if (!bRet) return TRUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMClientDlg::OnPaint()
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
HCURSOR CSMClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/************************************************************************/
/* void CCaseTreeCtrl::OnRClick(NMHDR *pNMHDR, LRESULT* pResult)
{
enum SUBMENU_POS{PRJ_MENU_POS,CASE_MENU_POS,FOLDER_MENU_POS,FILE_MENU_POS};

// Get tree item clicked
const MSG *pMsg;
CPoint pos;
HTREEITEM hTreeItem;

pMsg = GetCurrentMessage();
pos = pMsg->pt;
ScreenToClient(&pos);
hTreeItem = HitTest(pos);

// If no tree item is clicked just return
if (hTreeItem == NULL)
return;

// Show context menu according to the tree node type
CNewMenu menu;
CMenu *pSubMenu;
SUBMENU_POS menuPos; 	
CASEOBJ_TYPE type;

type = reinterpret_cast<CCaseObject*>(GetItemData(hTreeItem))->Type;
switch(type)
{
case CASEOBJ_FILE:
menuPos = FILE_MENU_POS;
break;
case CASEOBJ_FOLDER:
menuPos = FOLDER_MENU_POS;
break;
case CASEOBJ_CASE:
menuPos = CASE_MENU_POS;
break;
default:
return;
} 

// Select the item
SelectItem(hTreeItem);
// Load menu and pop up the menu
menu.LoadMenu(IDR_MENUPROJECTEXPLORER);
pSubMenu = menu.GetSubMenu(menuPos);

if (menuPos == CASE_MENU_POS)
pSubMenu->RemoveMenu(ID_CASE_REMOVECASE,MF_BYCOMMAND);

pSubMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pMsg->pt.x,pMsg->pt.y, this);

}                                                                     */
/************************************************************************/
void CSMClientDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bLogin) return;
	// CPoint   pt;   
	//CMenu   menu;   
	//UINT   nFlags;   
	//  
	//                  HTREEITEM   SelItem   =   m_Tree.HitTest(   pt,     &nFlags   );   
	//if   (SelItem   ==   NULL)     return   ;//未选中树形控件，则返回   
	//m_Tree.SelectItem(SelItem)   ;//取得当前所选节点   
	//  
	//menu.CreatePopupMenu();   
	//menu.AppendMenu(0,IDR_MENU1,"菜单一");   
	//GetCursorPos(&pt);   
	//menu.TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);   
	//*pResult   =   0; 
	//GetCurrentMessage();
	//

	CPoint cp;
	::GetCursorPos(&cp);
	m_TreeClient.ScreenToClient(&cp);
	HTREEITEM SelectItem = m_TreeClient.HitTest(point, &nFlags);
	m_TreeClient.ClientToScreen(&cp);
	if (SelectItem == NULL) return;//未选中树形控件，则返回

	PrintLog(_LOG_LEVEL_DEBUG, "你点击了鼠标右键");
	CSMClientDlg::OnRButtonDown(nFlags, point);
}

void CSMClientDlg::OnBnClickedBtnLogin()
{
	// TODO: Add your control notification handler code here
	SetSendMessage();
	CSendMsg msg;
	CHeader header;
	header.uid = 0;
	header.prefix = protocol::PREFIX;
	header.notype = 0;
	header.cmd = protocol::COM_LOGIN;
	header.length = sizeof(CHeader) + sizeof(CLogin);
	CLogin login;
	CString temp("");
	m_UserName.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("用户名不能为空", "提示");
		return;
	}
	memcpy(login.m_UserName, temp.GetString(), temp.GetLength());
	m_UserPassword.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("密码不能为空", "提示");
		return;
	}
	memcpy(login.m_UserPassword, temp.GetBuffer(), temp.GetLength());
	msg.m_Header = &header;
	msg.m_pProBase = &login;
	m_NetSession.SendMsgBuffer(msg);
	m_bLogin = true;
}

void CSMClientDlg::OnLoginRtn()
{

}

void CSMClientDlg::OnLogoutRtn()
{
	CDialog::OnDestroy();
}

void CSMClientDlg::SetLogin()
{
	MoveWindow(100, 100, 200, 250);
	m_StaticUserName.MoveWindow(20, 60, 50, 20);
	m_UserName.MoveWindow(75, 60, 100, 20);
	m_StaticPassword.MoveWindow(20, 90, 50, 20);
	m_UserPassword.MoveWindow(75, 90, 100, 20);
	m_BtnLogin.MoveWindow(60, 150, 80, 25);

	m_TreeClient.ShowWindow(SW_HIDE);
	m_StaticContent.ShowWindow(SW_HIDE);
	m_EditContent.ShowWindow(SW_HIDE);
	m_BtnSend.ShowWindow(SW_HIDE);
	m_BtnAddClient.ShowWindow(SW_HIDE);

	m_StaticAddMessage.ShowWindow(SW_HIDE);
	m_StaticAddUserName.ShowWindow(SW_HIDE);
	m_StaticAddPhoneNo.ShowWindow(SW_HIDE);
	m_EditAddUserName.ShowWindow(SW_HIDE);
	m_EditAddPhoneNo.ShowWindow(SW_HIDE);
	m_BtnAdd.ShowWindow(SW_HIDE);
}
void CSMClientDlg::SetAddClient()
{
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, 450, 300);
	m_StaticUserName.ShowWindow(SW_HIDE);
	m_UserName.ShowWindow(SW_HIDE);
	m_StaticPassword.ShowWindow(SW_HIDE);
	m_UserPassword.ShowWindow(SW_HIDE);
	m_BtnLogin.ShowWindow(SW_HIDE);

	m_TreeClient.ShowWindow(SW_SHOW);
	m_StaticContent.ShowWindow(SW_SHOW);
	m_EditContent.ShowWindow(SW_SHOW);
	m_BtnSend.ShowWindow(SW_SHOW);
	m_BtnAddClient.ShowWindow(SW_SHOW);

	m_StaticAddMessage.ShowWindow(SW_SHOW);
	m_StaticAddUserName.ShowWindow(SW_SHOW);
	m_StaticAddPhoneNo.ShowWindow(SW_SHOW);
	m_EditAddUserName.ShowWindow(SW_SHOW);
	m_EditAddPhoneNo.ShowWindow(SW_SHOW);
	m_BtnAdd.ShowWindow(SW_SHOW);
}

void CSMClientDlg::SetSendMessage()
{
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, 295, 300);
	m_StaticUserName.ShowWindow(SW_HIDE);
	m_UserName.ShowWindow(SW_HIDE);
	m_StaticPassword.ShowWindow(SW_HIDE);
	m_UserPassword.ShowWindow(SW_HIDE);
	m_BtnLogin.ShowWindow(SW_HIDE);

	m_TreeClient.ShowWindow(SW_SHOW);
	m_StaticContent.ShowWindow(SW_SHOW);
	m_EditContent.ShowWindow(SW_SHOW);
	m_BtnSend.ShowWindow(SW_SHOW);
	m_BtnAddClient.ShowWindow(SW_SHOW);

	m_StaticAddMessage.ShowWindow(SW_HIDE);
	m_StaticAddUserName.ShowWindow(SW_HIDE);
	m_StaticAddPhoneNo.ShowWindow(SW_HIDE);
	m_EditAddUserName.ShowWindow(SW_HIDE);
	m_EditAddPhoneNo.ShowWindow(SW_HIDE);
	m_BtnAdd.ShowWindow(SW_HIDE);

	InitTreeControl();
}

void CSMClientDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	if(m_bIsAddMessage)
	{
		m_bIsAddMessage = false;
		SetAddClient();
	}
	else
	{
		m_bIsAddMessage = true;
		SetSendMessage();
	}
}

void CSMClientDlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_strAddUserName.IsEmpty() || m_strAddPhoneNumber.IsEmpty())
	{
		MessageBox("用户名, 密码不能为空", "提示");
		return;
	}

	strstream sql;
	int id = db.GetTableCount("clientinfo") + 1;
	sql<<"INSERT INTO clientinfo VALUES("<<id<<",'"<<m_strAddUserName.GetBuffer(0)<<"','"
		<<m_strAddPhoneNumber.GetBuffer(0)<<"')"<<ends;
	bool bRet = db.Execute(sql.str(), database::CDataBase::ADD);
	if (bRet)
	{
		AddClient(string(m_strAddUserName.GetBuffer(0)), 
			string(m_strAddPhoneNumber.GetBuffer(0)));
		AfxMessageBox("添加成功");
	}
	else
	{
		AfxMessageBox("添加失败");
	}
	UpdateData(FALSE);
}

void CSMClientDlg::GetClientsInfo(vector<cds::db_clientinfo> &vecClientInfos)
{


}

void CSMClientDlg::InitTreeControl(void)
{
	UpdateData(TRUE);
	if (m_TreeClient.GetCount() != 0) return;
	SetWindowLong(m_TreeClient.m_hWnd, GWL_STYLE, WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS);
	HTREEITEM hRootClient = m_TreeClient.InsertItem (_T("客户信息"), 0, 0);
	HTREEITEM hRootUser = m_TreeClient.InsertItem(_T("用户信息"), 1, 1);
	m_TreeClient.SetItemState (hRootClient, TVIS_BOLD, TVIS_BOLD);
	//HTREEITEM hSub = m_TreeClient.InsertItem (_T("王立伟"), 1, 1, hRoot);
	//m_TreeClient.InsertItem (_T("张龙仙"), 2, 2, hRoot);
	UpdateClient();
	m_TreeClient.SelectItem(hRootClient);
	UpdateData(FALSE);
}

void CSMClientDlg::AddClient(std::string &strUserName, std::string &strPhoneNumber)
{
	UpdateData(TRUE);
	int nIndex = m_TreeClient.GetCount();
	HTREEITEM hRootClient = m_TreeClient.GetRootItem();
	assert(hRootClient != NULL);
	m_TreeClient.InsertItem(_T(strUserName.c_str()), nIndex, nIndex, hRootClient);
	UpdateData(FALSE);
}

void CSMClientDlg::UpdateClient()
{
	UpdateData(TRUE);
	int nIndex = m_TreeClient.GetCount();
	HTREEITEM hRootClient = m_TreeClient.GetRootItem();
	assert(hRootClient != NULL);
	vector<cds::db_clientinfo> vecClientInfos;
	strstream sql;
	sql<<"SELECT * FROM clientinfo"<<ends;
	BOOL bRet = db.GetClientInfos(sql.str(), vecClientInfos);
	if (bRet)
	{
		vector<cds::db_clientinfo>::iterator iter = vecClientInfos.begin();
		for (; iter != vecClientInfos.end(); iter++)
		{
			cds::db_clientinfo clientInfo = static_cast<cds::db_clientinfo>(*iter);
			AddClient(string(clientInfo.m_ClientName), string(clientInfo.m_ClientTelphone));
		}
	}
	UpdateData(FALSE);
}


void CSMClientDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	CString strContent = "";
	m_EditContent.GetWindowText(strContent);
	if (strContent.IsEmpty())
	{
		MessageBox("发送的消息不能为空，1-100个汉字","提示");
		return;
	}
}
void CSMClientDlg::OnTreeCtrlSelectChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	PrintLog(_LOG_LEVEL_DEBUG, "hit tree");
}