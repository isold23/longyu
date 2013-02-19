#pragma once 
 
class CWorkerDlg : public CXTPResizeDialog
{ 
	DECLARE_MESSAGE_MAP()

	enum { TIMER_ID = 1000 };
public:
	enum { IDD = IDD_WORKER };

public:
	class CWorker
	{
	public:
		CWorker(void);
		~CWorker(void);

		void Start(CWorkerDlg *pDlg); 
		virtual DWORD Run(void) = 0;  
 

	private:
		static DWORD WINAPI ThreadProc( LPVOID pParam);
 
		CWorkerDlg *m_pDlg;
		HANDLE m_hTread;
	};

public:
	CWorkerDlg(CWnd* pParent = NULL);   
	virtual ~CWorkerDlg(void);
  
	void ShowWorker(CWorker *pWorker,LPCTSTR pcszText,int nTimeout=-1);
	INT_PTR DoWorker(CWorker *pWorker,LPCTSTR pcszText,int nTimeout=-1);

	void WorkerDone(void);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);   

	virtual void OnOK(void);
	virtual void OnCancel(void);

	afx_msg void OnTimer(UINT_PTR nIDEvent); 
 
	BOOL m_bShow;
	LPCTSTR m_pcszText;
	CWorker *m_pWorker;
	int m_nTimeout;

	int m_nTimerId;



	CStatic m_stcText;
	CXTPMarqueeCtrl m_processCtrl;
};
 