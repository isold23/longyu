#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListSumupReportDlg.h"

 

CListSumupReportDlg::CListSumupReportDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListSumupReportDlg::IDD, pParent)
{

}

CListSumupReportDlg::~CListSumupReportDlg()
{
}

void CListSumupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListSumupReportDlg, CReportPageDlg)
END_MESSAGE_MAP()
