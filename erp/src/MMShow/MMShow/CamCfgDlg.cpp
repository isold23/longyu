#include "stdafx.h"
#include "Resource.h"
#include "CamCfgDlg.h"
#include "ArrayAdaptor.h"
#include "Cfg.h"
#include "Devices.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CCamCfgDlg::CCamCfgDlg(CWnd* pParent /*=NULL*/)
	: CCfgChildDlg(CCamCfgDlg::IDD,pParent)
{
}

CCamCfgDlg::~CCamCfgDlg(void)
{
}

void CCamCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CCfgChildDlg::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_CB_CAM,m_cbCam);
	DDX_Control(pDX,IDC_CB_CAM2,m_cbCam1);
	DDX_Control(pDX,IDC_CB_CAM3,m_cbCam2);
	DDX_Control(pDX, IDC_CB_SIZE, m_cbCaptureSize);
}

BOOL CCamCfgDlg::OnInitDialog(void)
{
	CCfgChildDlg::OnInitDialog();

	m_cbCaptureSize.AddString(_T("设备默认"));
	m_cbCaptureSize.SetCurSel(0);

	const CStringArray &devices = CDevices::GetVideoDevices(TRUE);
	const CStringArray &names = CDevices::GetVideoDeviceNames(TRUE);
	
	INT_PTR i=0;
	INT_PTR nCamCount = devices.GetCount();
	
	for (; i<nCamCount; ++i)
	{
		m_cbCam.AddString(names[i]);
		m_cbCam1.AddString(names[i]);
		m_cbCam2.AddString(names[i]);
	}

	if (gcfg.GetCam0().IsEmpty())
	{
		m_cbCam.SetCurSel(-1);
		m_cbCam1.SetCurSel(-1);
		m_cbCam2.SetCurSel(-1);	
	}
	else
	{
		m_cbCam.SetCurSel(FindIndex(devices,gcfg.GetCam0()));
		m_cbCam1.SetCurSel(FindIndex(devices,gcfg.GetCam1()));
		m_cbCam2.SetCurSel(FindIndex(devices,gcfg.GetCam2()));
	}
	return TRUE; 
}

BEGIN_MESSAGE_MAP(CCamCfgDlg, CCfgChildDlg)
END_MESSAGE_MAP()
 


BOOL CCamCfgDlg::SaveCfg(CString &strTip)
{
	int nIndex = m_cbCam.GetCurSel();
	int nIndex1 = m_cbCam1.GetCurSel();
	int nIndex2 = m_cbCam2.GetCurSel();

	if (nIndex<0 || nIndex1<0 || nIndex2<0)
	{
		strTip = _T("采集卡未正确设置");
		return FALSE;
	}
	else
	{
		const CStringArray &devices = CDevices::GetVideoDevices(TRUE);
		gcfg.SetCam0(devices[nIndex]);
		gcfg.SetCam1(devices[nIndex1]);
		gcfg.SetCam2(devices[nIndex2]);
		return TRUE;
	}
}

BOOL CCamCfgDlg::CancelCfg(CString &strTip)
{
	return SaveCfg(strTip);
}
