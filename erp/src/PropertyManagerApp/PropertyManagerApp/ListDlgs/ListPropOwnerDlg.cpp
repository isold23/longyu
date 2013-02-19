#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListPropOwnerDlg.h"
 

CListPropOwnerDlg::CListPropOwnerDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListPropOwnerDlg::IDD, pParent)
{

}

CListPropOwnerDlg::~CListPropOwnerDlg()
{
}

void CListPropOwnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListPropOwnerDlg, CReportPageDlg)
END_MESSAGE_MAP()
