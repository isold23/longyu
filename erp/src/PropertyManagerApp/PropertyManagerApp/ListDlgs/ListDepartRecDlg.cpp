#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListDepartRecDlg.h"

 

CListDepartRecDlg::CListDepartRecDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListDepartRecDlg::IDD, pParent)
{

}

CListDepartRecDlg::~CListDepartRecDlg()
{
}

void CListDepartRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListDepartRecDlg, CReportPageDlg)
END_MESSAGE_MAP()
