#include "stdafx.h"
#include "Resource.h"
#include "LiveSrcDlg.h"
#include "OutputDlg.h"
#include "Cfg.h" 
#include "MediaFormatDef.h"

CLiveSrcDlg::CLiveSrcDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CLiveSrcDlg::IDD, pParent),
	  m_pOutputDlg(NULL),m_pRefOutputDlg(NULL)
{
}


CLiveSrcDlg::~CLiveSrcDlg(void)
{
}

void CLiveSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_STC_BIG,m_stcBig);
	DDX_Control(pDX,IDC_STC_SMALL,m_stcSmall);
	DDX_Control(pDX,IDC_STC_SMALL2,m_stcSmall2);
}


BEGIN_MESSAGE_MAP(CLiveSrcDlg, CResizableDialog)
	ON_WM_SIZE()
	ON_MESSAGE(CLiveSrcChildDlg::WM_WANNABIG,&CLiveSrcDlg::OnWannaBig)
END_MESSAGE_MAP()

BOOL CLiveSrcDlg::OnInitDialog(void)
{
	CResizableDialog::OnInitDialog();

	AddAnchor(m_stcSmall,TOP_LEFT,CSize(33,50));
	AddAnchor(m_stcSmall2,CSize(0,50),CSize(33,100));
	AddAnchor(m_stcBig,CSize(33,0),BOTTOM_RIGHT);

	x_dlg0.Create(CLiveSrcChildDlg::IDD,this);
	x_dlg0.ShowWindow(SW_SHOW);
	x_dlg0.AttachTo(&m_stcBig);
	m_pBig = &x_dlg0;
	x_dlg0.SetCam(this,TRUE,gcams.GetCam(gcfg.GetUiLiveDefault()));

	UINT camIndexes[3] = {0,1,2};
	int index = FindIndex(camIndexes,_countof(camIndexes),gcfg.GetUiLiveDefault());
	std::swap(camIndexes[index],camIndexes[2]);

	x_dlg1.Create(CLiveSrcChildDlg::IDD,this);
	x_dlg1.ShowWindow(SW_SHOW);
	x_dlg1.AttachTo(&m_stcSmall);
	x_dlg1.SetCam(NULL,FALSE,gcams.GetCam(camIndexes[0]));
	
	x_dlg2.Create(CLiveSrcChildDlg::IDD,this);
	x_dlg2.ShowWindow(SW_SHOW);
	x_dlg2.AttachTo(&m_stcSmall2);
	x_dlg2.SetCam(NULL,FALSE,gcams.GetCam(camIndexes[1]));

	return FALSE;
}


CLiveSrcChildDlg* CLiveSrcDlg::GetAttached(CStatic &stc)
{
	return (CLiveSrcChildDlg*)GetWindowLongPtr(stc,GWLP_USERDATA);
}


void CLiveSrcDlg::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType,cx,cy);
	
	if (x_dlg0.GetSafeHwnd() != NULL)
	{
		x_dlg0.FollowAttach();
		x_dlg1.FollowAttach();
		x_dlg2.FollowAttach();
	}
}

LRESULT CLiveSrcDlg::OnWannaBig(WPARAM wParam,LPARAM lParam)
{
	CLiveSrcChildDlg *pDlg = (CLiveSrcChildDlg*)wParam;	
	if (m_pBig == pDlg)
	{
		m_pRefOutputDlg->ChangeSrcTo(FALSE);
	}
	else
	{
		CWnd *pBigAttachTo = m_pBig->GetAttachTo();
		m_pBig->AttachTo(pDlg->GetAttachTo());
		if (m_pOutputDlg != NULL)
		{
			m_pBig->SetCam(NULL,FALSE);
			m_pBig->SampleRef(FALSE);
		}
	
		pDlg->AttachTo(pBigAttachTo);
		
		m_pBig = pDlg;
		
		if (m_pOutputDlg != NULL)
		{
			m_pBig->SetCam(this,TRUE);
			m_pBig->SampleRef(TRUE);
		}
	}
	return 0;
}


void CLiveSrcDlg::OnSample(CCamExt *pCamExt)
{
	if (m_pOutputDlg != NULL)
	{
		CGuard g(m_cs);
		if (m_pOutputDlg != NULL)
		{
			CStaticBuffer buf;
			CSize sizeFull;
			pCamExt->GetSample(buf,sizeFull);
			m_pOutputDlg->RenderVideo(buf.Ptr(),sizeFull,sizeFull.cx*def_vBytesPerPixel);
		}
	}
}

void CLiveSrcDlg::SetOutput(COutputDlg *pOutputDlg) 
{
	CGuard g(m_cs);
	if (m_pOutputDlg != pOutputDlg)
	{
		if (m_pOutputDlg != NULL)
			m_pBig->SampleRef(FALSE);

		m_pOutputDlg = pOutputDlg;
		if (m_pOutputDlg == NULL)
			m_pBig->SetCam(NULL,FALSE);
		else
			m_pBig->SetCam(this,TRUE);

		if (m_pOutputDlg != NULL)
			m_pBig->SampleRef(TRUE);
	}
}

void CLiveSrcDlg::SampleRef(BOOL bRef)
{
	if (m_pOutputDlg != NULL)
		m_pBig->SampleRef(bRef);
}