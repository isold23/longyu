 
#include "stdafx.h"
#include "Resource.h"
#include "OutputCfgDlg.h"
#include "Devices.h"
#include "ArrayAdaptor.h"
#include "Cfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void Printbps(CString &str,double v)
{
	double k = v/1024.00;
	double m = k/1024;

	if (m >= 1.0)
	{
		if (m == (int)m)
			str.Format(_T("%d Mbps"),(int)m);
		else
			str.Format(_T("%0.1f Mbps"),m);
	}
	else
	{
		if (k == (int)k)
			str.Format(_T("%d Kbps"),(int)k);
		else
			str.Format(_T("%0.1f Kbps"),k);
	}
}

int VideoOutputIndex(const CString &str)
{
	const CStringArray &devices =  CDevices::GetVideoDevices(FALSE);
	const CStringArray &names = CDevices::GetVideoDeviceNames(FALSE);

	if (str.IsEmpty() || str==_T("0"))
		return 0;

	if (str == _T("1"))
		return 1;

	INT_PTR nIndex = FindIndex(devices,str);
	if (nIndex < 0)  
		return nIndex;
	return (nIndex<0 ? 0 : nIndex+2);
}

CString VideoOutputString(int nIndex)
{
	const CStringArray &devices =  CDevices::GetVideoDevices(FALSE);
	const CStringArray &names = CDevices::GetVideoDeviceNames(FALSE);

	switch (nIndex)
	{
	case 0:
		return _T("0");
	case 1:
		return _T("1");
	default:
		return devices[nIndex-2];
	}
}

COutputCfgDlg::COutputCfgDlg(CWnd* pParent /*=NULL*/)
	: CCfgChildDlg(COutputCfgDlg::IDD, pParent)
{

}

COutputCfgDlg::~COutputCfgDlg()
{
}

void COutputCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CCfgChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_FPS, m_cbDefVideFps);
	DDX_Control(pDX, IDC_CB_VIDEO_SIZE, m_cbDefVideoSize);
	DDX_Control(pDX, IDC_CB_DEF_VIDEO_INPUT, m_cbDefVideoInput);
	DDX_Control(pDX, IDC_CB_DEF_VIDEO_OUTPUT, m_cbDefVideoOutput);
}


BEGIN_MESSAGE_MAP(COutputCfgDlg, CCfgChildDlg)
END_MESSAGE_MAP()

int VideoOutputIndex(const CString&);
BOOL COutputCfgDlg::OnInitDialog(void)
{
	CCfgChildDlg::OnInitDialog();

	m_cbDefVideoInput.AddString(_T("Ô¤ÀÀ"));
	m_cbDefVideoInput.AddString(_T("Ö±²¥"));
	m_cbDefVideoInput.SetCurSel(gcfg.GetOutputVideoInput());


	m_cbDefVideoOutput.AddString(_T("Í£Ö¹Êä³ö..."));
	m_cbDefVideoOutput.AddString(_T("Ô¤ÀÀÊä³ö..."));
	
	INT_PTR i; CString str;
	const CStringArray &devices =  CDevices::GetVideoDevices(FALSE);
	const CStringArray &names = CDevices::GetVideoDeviceNames(FALSE);
	for (i=0; i<names.GetCount(); ++i)
		m_cbDefVideoOutput.AddString(names[i]);
	m_cbDefVideoOutput.SetCurSel(VideoOutputIndex(gcfg.GetOutputVideoOutput())); 

	for (i=0; i<gsys.VideoFpses().GetCount(); ++i)
	{
		str.Format(_T("%d"),gsys.VideoFpses()[i]);
		m_cbDefVideFps.AddString(str);
	}
	m_cbDefVideFps.SetCurSel(gcfg.GetOutputVideoFps());

	for (i=0; i<gsys.VideoOutputSizes().GetCount(); ++i)
	{
		str.Format(_T("%d x %d"),gsys.VideoOutputSizes()[i]);
		m_cbDefVideoSize.AddString(str);
	}
	m_cbDefVideoSize.SetCurSel(gcfg.GetOutputVideoSize());

	return FALSE;
}


BOOL COutputCfgDlg::SaveCfg(CString &strTip)
{
	gcfg.SetOutputVideoInput(m_cbDefVideoInput.GetCurSel());

	gcfg.SetOutputVideoOutput(VideoOutputString(m_cbDefVideoOutput.GetCurSel()));

	gcfg.SetOutputVideoSize(m_cbDefVideoSize.GetCurSel());
	gcfg.SetOutputVideoFps(m_cbDefVideFps.GetCurSel());
	return TRUE;
}
 