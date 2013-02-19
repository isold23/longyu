#include "stdafx.h"
#include "Resource.h"
#include "DShowSrcDlg.h"
#include "Cfg.h"
#include "Cams.h"
#include "DrawHelper.h"
#include "MediaFormatDef.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDShowSrcDlg::CDShowSrcDlg(CWnd* pParent /*=NULL*/)
	: CVideoSrcBaseDialog(CDShowSrcDlg::IDD, pParent)
{
	m_bSampleRef = FALSE;
	m_pcszName = (_T("ÊÓÆµÁ÷"));
}

CDShowSrcDlg::~CDShowSrcDlg()
{
}

void CDShowSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CVideoSrcBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_CB_CAM,m_cbCam);
	DDX_Control(pDX,IDC_STC_CONTENT,m_stcCams[0]);
	DDX_Control(pDX,IDC_STC_CONTENT2,m_stcCams[1]);
	DDX_Control(pDX,IDC_STC_CONTENT3,m_stcCams[2]);
}


BEGIN_MESSAGE_MAP(CDShowSrcDlg, CVideoSrcBaseDialog)
	ON_CBN_SELCHANGE(IDC_CB_CAM,OnCbCamSelChange)
END_MESSAGE_MAP()


BOOL CDShowSrcDlg::OnInitDialog(void)
{
	CVideoSrcBaseDialog::OnInitDialog();
	AddAnchor(IDC_CB_CAM,TOP_LEFT,TOP_RIGHT);
	
	CWnd *pStcGauge = GetDlgItem(IDC_STC_GAUGE);
	AddAnchor(pStcGauge->GetSafeHwnd(),TOP_LEFT,BOTTOM_RIGHT);
	m_gaugeWnd.Create(pStcGauge,gcfg.GetUiOpTransparentGauge(),this);
 
	for (int i=0; i<_countof(m_stcCams); ++i)
		AddAnchor(m_stcCams[i],TOP_LEFT,BOTTOM_RIGHT);

	m_cbCam.AddString(gcams.GetCam(0)->GetDisplayName());
	m_cbCam.AddString(gcams.GetCam(1)->GetDisplayName());
	m_cbCam.AddString(gcams.GetCam(2)->GetDisplayName());

	gcams.GetCam(0)->SetCapture(m_stcCams[0],this,FALSE);
	gcams.GetCam(1)->SetCapture(m_stcCams[1],NULL,FALSE);
	gcams.GetCam(2)->SetCapture(m_stcCams[2],NULL,FALSE);

	m_nCurSel = 0;
	m_cbCam.SetCurSel(m_nCurSel);
	return TRUE;
}	

void CDShowSrcDlg::OnCbCamSelChange(void)
{
	for (int i=0; i<_countof(m_stcCams); ++i)
	{
		gcams.GetCam(i)->SetCapture(m_stcCams[0],NULL,FALSE);
		m_stcCams[i].ShowWindow(SW_HIDE);
	}

	if (m_bSampleRef)
		gcams.GetCam(m_nCurSel)->SampleRef(FALSE);
	
	m_nCurSel = m_cbCam.GetCurSel();
	gcams.GetCam(m_nCurSel)->SetCapture(m_stcCams[0],NULL,FALSE);
	m_stcCams[m_nCurSel].ShowWindow(SW_SHOW);
	m_stcCams[m_nCurSel].BringWindowToTop();
	
	if (m_bSampleRef)
		gcams.GetCam(m_nCurSel)->SampleRef(TRUE);
}


DWORD CDShowSrcDlg::GetSampleTick(void)
{
	return max(m_gaugeWnd.GetSampleTick(),gcams.GetCam(m_nCurSel)->GetSampleTick());
}

BOOL CDShowSrcDlg::GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample)
{
	CCamExt *pCamExt = gcams.GetCam(m_nCurSel);

	if (!pCamExt->GetSample(buf,sizeFull))
		return FALSE;

	rcSample = CRect(0,0,sizeFull.cx,sizeFull.cy);
	m_gaugeWnd.CalcViewRect(rcSample);

	int nHeight = rcSample.Height();
	rcSample.bottom = sizeFull.cy - rcSample.top;
	rcSample.top = rcSample.bottom - nHeight;

	nStride = sizeFull.cx*def_vBytesPerPixel;
	buf.Set(buf.Ptr()+(rcSample.left+rcSample.top*sizeFull.cx)*def_vBytesPerPixel,nStride*nHeight);

	return TRUE;
}

void CDShowSrcDlg::SampleRef(BOOL bRef)
{
	ASSERT(m_bSampleRef == !bRef);
	m_bSampleRef = bRef;
	gcams.GetCam(m_nCurSel)->SampleRef(bRef);
}