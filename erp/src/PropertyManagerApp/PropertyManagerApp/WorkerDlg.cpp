#include "stdafx.h"
#include "PropertyManagerApp.h"
#include "WorkerDlg.h"

CWorkerDlg::CWorker::CWorker(void)
	:m_hTread(NULL)
{
}

CWorkerDlg::CWorker::~CWorker(void)
{
}

void CWorkerDlg::CWorker::Start(CWorkerDlg *pDlg)
{
	m_pDlg = pDlg;
	DWORD dwThreadId;
	m_hTread = ::CreateThread(NULL,0,ThreadProc,this,0,&dwThreadId);
}
 

DWORD WINAPI CWorkerDlg::CWorker::ThreadProc( LPVOID pParam)
{
	CWorker *pWorker = (CWorkerDlg::CWorker*)pParam;
	DWORD ret = pWorker->Run();
	pWorker->m_pDlg->WorkerDone();
	return ret;
}
 

CWorkerDlg::CWorkerDlg(CWnd* pParent)
	: CXTPResizeDialog(CWorkerDlg::IDD, pParent),
	  m_pWorker(NULL),m_pcszText(NULL),m_bShow(TRUE)
{

}

CWorkerDlg::~CWorkerDlg(void)
{
}

void CWorkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_TITLE, m_stcText);
	DDX_Control(pDX, IDC_PROGRESS, m_processCtrl);
}


BEGIN_MESSAGE_MAP(CWorkerDlg, CXTPResizeDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CWorkerDlg::OnInitDialog(void)
{
	CXTPResizeDialog::OnInitDialog();


	SetResize(IDC_STC_TITLE,XTP_ANCHOR_MIDDLELEFT,XTP_ANCHOR_MIDDLERIGHT);
	SetResize(IDC_PROGRESS,XTP_ANCHOR_MIDDLELEFT,XTP_ANCHOR_MIDDLERIGHT);
	
	ASSERT(m_pWorker!=NULL || m_bShow);
	m_processCtrl.SetMarquee(TRUE,50);

	if (!m_bShow)
	{
		if (m_pcszText != NULL)
			m_stcText.SetWindowText(m_pcszText);
		m_pWorker->Start(this);
		if (m_nTimeout != -1)
			m_nTimerId = SetTimer(TIMER_ID,m_nTimeout,NULL);

		ModifyStyle(0,WS_POPUP,0);
	}
	return FALSE;
}

void CWorkerDlg::ShowWorker(CWorker *pWorker,LPCTSTR pcszText,int nTimeout)
{
	m_pWorker = pWorker; 
	m_nTimeout = nTimeout;
	m_pcszText = pcszText;

	m_stcText.SetWindowText(m_pcszText);
	m_pWorker->Start(this);
	if (m_nTimeout != -1)
		m_nTimerId = SetTimer(TIMER_ID,m_nTimeout,NULL);
	 
}

INT_PTR CWorkerDlg::DoWorker(CWorker *pWorker,LPCTSTR pcszText,int nTimeout) 
{
	m_pWorker = pWorker; 
	m_nTimeout = nTimeout;
	m_pcszText = pcszText;

	m_bShow = FALSE;
	return DoModal();
}




void CWorkerDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(m_nTimerId);
	if (!m_bShow)
		EndDialog(IDCANCEL);
	CXTPResizeDialog::OnTimer(nIDEvent);
}

void CWorkerDlg::WorkerDone(void)
{
	if (!m_bShow && GetSafeHwnd()!= NULL)
		PostMessage(WM_COMMAND,IDOK);
}

void CWorkerDlg::OnOK(void)
{

}

void CWorkerDlg::OnCancel(void)
{

}
