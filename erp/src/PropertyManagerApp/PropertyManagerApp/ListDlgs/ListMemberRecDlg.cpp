#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListMemberRecDlg.h"

 

CListMemberRecDlg::CListMemberRecDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListMemberRecDlg::IDD, pParent)
{

}

CListMemberRecDlg::~CListMemberRecDlg()
{
}

void CListMemberRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListMemberRecDlg, CReportPageDlg)
END_MESSAGE_MAP()
