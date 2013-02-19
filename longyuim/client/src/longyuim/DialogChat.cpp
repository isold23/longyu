// DialogChat.cpp : implementation file
//

#include "stdafx.h"
#include "longyuim.h"
#include "DialogChat.h"
#include "afxdialogex.h"


// CDialogChat dialog

IMPLEMENT_DYNAMIC(CDialogChat, CDialogEx)

CDialogChat::CDialogChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogChat::IDD, pParent)
{

}

CDialogChat::~CDialogChat()
{
}

void CDialogChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogChat, CDialogEx)
END_MESSAGE_MAP()


// CDialogChat message handlers
