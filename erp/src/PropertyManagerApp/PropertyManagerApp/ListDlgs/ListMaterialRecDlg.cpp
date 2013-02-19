#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListMaterialRecDlg.h"

 

CListMaterialRecDlg::CListMaterialRecDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListMaterialRecDlg::IDD, pParent)
{

}

CListMaterialRecDlg::~CListMaterialRecDlg()
{
}

void CListMaterialRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListMaterialRecDlg, CReportPageDlg)
END_MESSAGE_MAP()
