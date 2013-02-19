#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListReceiptDetailsQueryDlg.h"

 

CListReceiptDetailsQueryDlg::CListReceiptDetailsQueryDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListReceiptDetailsQueryDlg::IDD, pParent)
{

}

CListReceiptDetailsQueryDlg::~CListReceiptDetailsQueryDlg()
{
}

void CListReceiptDetailsQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListReceiptDetailsQueryDlg, CReportPageDlg)
END_MESSAGE_MAP()
