// UserList.cpp : 实现文件
//

#include "stdafx.h"
#include "../UCChatRoom.h"
#include "UserList.h"
#include "../UI/Drawer.h"

extern CUCChatRoomApp theApp; 
// CUserList 对话框

IMPLEMENT_DYNAMIC(CUserList, CDialog)

CUserList::CUserList(CWnd* pParent /*=NULL*/)
	: CDialog(CUserList::IDD, pParent)
{
	mpTreeCtrl = NULL;
	mbTrackLeaveMsg = false;
}

CUserList::~CUserList()
{
}

void CUserList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserList, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CUserList 消息处理程序

BOOL CUserList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mpTreeCtrl = new CBaseTree(GetSafeHwnd());
	CRect lrcClient;
	GetClientRect(lrcClient);
	mpTreeCtrl->SetRect(lrcClient.left, lrcClient.top, lrcClient.Width(), lrcClient.Height());
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUserList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	RECT rc;
	GetClientRect(&rc);
	CDrawer drawer(dc.GetSafeHdc(), &rc);
	HGDIOBJ hfont = drawer.SelectObject(theApp.mpRoomData->m_Font.GetSafeHandle());
	drawer.FillSolidRect(&rc, RGB(239, 247, 255));
	if(mpTreeCtrl)
		mpTreeCtrl->Paint(drawer.GetSafeHdc());
	drawer.SelectObject(hfont);
}

void CUserList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mpTreeCtrl)
		mpTreeCtrl->OnLButtonDown(nFlags, point);
	SetFocus();
	CDialog::OnLButtonDown(nFlags, point);
}

void CUserList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mpTreeCtrl)
		mpTreeCtrl->OnLButtonUp(nFlags, point);

	CDialog::OnLButtonUp(nFlags, point);
}

void CUserList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mpTreeCtrl)
		mpTreeCtrl->OnMouseMove(nFlags, point);

	if(!mbTrackLeaveMsg)
	{
		mbTrackLeaveMsg = true;

		TRACKMOUSEEVENT tme;       
		tme.cbSize = sizeof(TRACKMOUSEEVENT);       
		tme.dwFlags = TME_HOVER |  TME_LEAVE;       
		tme.dwHoverTime = HOVER_DEFAULT;     
		tme.hwndTrack = m_hWnd;   
		_TrackMouseEvent(&tme); 
	}	

	CDialog::OnMouseMove(nFlags, point);
}

BOOL CUserList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mpTreeCtrl)
	{
		ScreenToClient(&pt);
		mpTreeCtrl->OnMouseWheel(nFlags, zDelta, pt);
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

LRESULT CUserList::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{	
	mbTrackLeaveMsg = false;
	if(mpTreeCtrl)
		mpTreeCtrl->OnMouseLeave();
	return S_OK;
}

void CUserList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mpTreeCtrl)
		mpTreeCtrl->OnTimer(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}

void CUserList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect lrcClient;
	GetClientRect(lrcClient);
	if(mpTreeCtrl)
		mpTreeCtrl->SetRect(lrcClient.left, lrcClient.top, lrcClient.Width(), lrcClient.Height());
}

void CUserList::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if(mpTreeCtrl)
	{
		delete mpTreeCtrl;
		mpTreeCtrl = NULL;
	}
}

void CUserList::Initialize()
{
	if(mpTreeCtrl)
		mpTreeCtrl->ClearAllItems();
}

void CUserList::AddUser(void* pDate)
{
	CTreeNode* pNode = new CTreeNode();
	pNode->mpData = pDate;
	mpTreeCtrl->InsertItem(pNode);
}

void CUserList::DelUser(__int64 ai64UserID)
{
	mpTreeCtrl->DeleteItem(ai64UserID);
}
void CUserList::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(mpTreeCtrl)
		mpTreeCtrl->OnRButtonUp(nFlags, point);
	CDialog::OnRButtonUp(nFlags, point);
}
