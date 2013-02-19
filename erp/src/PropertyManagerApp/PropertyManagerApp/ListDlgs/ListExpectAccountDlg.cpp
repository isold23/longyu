#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListExpectAccountDlg.h"

 

CListExpectAccountDlg::CListExpectAccountDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListExpectAccountDlg::IDD, pParent)
{

}

CListExpectAccountDlg::~CListExpectAccountDlg()
{
}

void CListExpectAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListExpectAccountDlg, CReportPageDlg)
END_MESSAGE_MAP()
