// MultiConfirmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MMShow.h"
#include "MultiConfirmDlg.h"


// CMultiConfirmDlg 对话框

IMPLEMENT_DYNAMIC(CMultiConfirmDlg, CDialog)

CMultiConfirmDlg::CMultiConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiConfirmDlg::IDD, pParent)
{

}

CMultiConfirmDlg::~CMultiConfirmDlg()
{
}

void CMultiConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMultiConfirmDlg, CDialog)
END_MESSAGE_MAP()


// CMultiConfirmDlg 消息处理程序
