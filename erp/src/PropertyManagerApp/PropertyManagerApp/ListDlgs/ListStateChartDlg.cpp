#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "ListStateChartDlg.h"

 

CListStateChartDlg::CListStateChartDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CListStateChartDlg::IDD, pParent)
{

}

CListStateChartDlg::~CListStateChartDlg()
{
}

void CListStateChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListStateChartDlg, CReportPageDlg)
END_MESSAGE_MAP()
