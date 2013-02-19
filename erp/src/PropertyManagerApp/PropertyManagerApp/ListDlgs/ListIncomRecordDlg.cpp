#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListIncomRecordDlg.h"

 

CListIncomRecordDlg::CListIncomRecordDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListIncomRecordDlg::IDD, pParent)
{

}

CListIncomRecordDlg::~CListIncomRecordDlg()
{
}

void CListIncomRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListIncomRecordDlg, CReportPageDlg)
END_MESSAGE_MAP()
