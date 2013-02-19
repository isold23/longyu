#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListRepairDlg.h"

 

CListRepairDlg::CListRepairDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListRepairDlg::IDD, pParent)
{

}

CListRepairDlg::~CListRepairDlg()
{
}

void CListRepairDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListRepairDlg, CReportPageDlg)
END_MESSAGE_MAP()
