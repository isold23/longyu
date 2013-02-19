#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListReceiptSumupQueryDlg.h"

 

CListReceiptSumupQueryDlg::CListReceiptSumupQueryDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListReceiptSumupQueryDlg::IDD, pParent)
{

}

CListReceiptSumupQueryDlg::~CListReceiptSumupQueryDlg()
{
}

void CListReceiptSumupQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListReceiptSumupQueryDlg, CReportPageDlg)
END_MESSAGE_MAP()
