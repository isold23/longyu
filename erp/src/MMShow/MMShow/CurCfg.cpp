#include "stdafx.h"
#include "MMShow.h" 
#include "CurCfg.h"
#include "Devices.h"
#include "cfg.h"
#include "ArrayAdaptor.h"

CCurCfg* CCurCfg::s_pInst = NULL;

CCurCfg::CCurCfg(CWnd *pParentWnd)
	: CDialog(CCurCfg::IDD, pParentWnd)
{
	m_vFps = gcfg.GetOutputVideoFps();
	m_vSize = gcfg.GetOutputVideoSize();
	m_vBitrate = gcfg.GetRecVideoBitrate();
	m_aBitrate = gcfg.GetRecAudioBitrate();
	m_aSampleRate = gcfg.GetRecAudioSampleRate();
	m_aInput = FindIndex(CDevices::GetMics(),gcfg.GetRecAudoInput());
	if (m_aInput == -1)
		m_aInput = 0;

	ASSERT(s_pInst == NULL);
	s_pInst = this;

}

CCurCfg::~CCurCfg(void)
{
}

void CCurCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_FPS, m_cbVFps);
	DDX_Control(pDX, IDC_CB_VIDEO_SIZE, m_cbVSize);
	DDX_Control(pDX, IDC_CB_VIDEO_BITRATE, m_cbVBitrate);
	DDX_Control(pDX, IDC_CB_AUDIO_BITRATE, m_cbABitrate);
	DDX_Control(pDX, IDC_CB_AUDIO_SAMPLE_RATE, m_cbASampleRate);
	DDX_Control(pDX, IDC_CB_DEF_AUDIO_INPUT, m_cbAInput);
	DDX_Control(pDX, IDC_CHK_DEFAULT, m_chkSaveAsDefault);
}


BEGIN_MESSAGE_MAP(CCurCfg, CDialog)
	ON_WM_ACTIVATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CCurCfg::OnActivate(UINT nState,CWnd* pWndOther,BOOL bMinimized)
{
	if (nState == WA_INACTIVE)
		ShowWindow(SW_HIDE);
}

UINT CCurCfg::UiToMem(void)
{
	UINT flag = 0;

	UINT nNewVal = m_cbABitrate.GetCurSel();
	if (m_aBitrate != nNewVal)
	{
		m_aBitrate = nNewVal;
		flag |= ABitrateF;
	}

	nNewVal = m_cbASampleRate.GetCurSel();
	if (m_aSampleRate != nNewVal)
	{
		m_aSampleRate = nNewVal;
		flag |= ASampleRateF;
	}

	nNewVal = m_cbAInput.GetCurSel();
	if (m_aInput != nNewVal)
	{
		m_aInput = nNewVal;
		flag |= AInputF;
	}

	nNewVal = m_cbVFps.GetCurSel();
	if (m_vFps != nNewVal)
	{
		m_vFps = nNewVal;
		flag |= VFpsF;
	}

	nNewVal = m_cbVBitrate.GetCurSel(); 
	if (m_vBitrate != nNewVal)
	{
		m_vBitrate = nNewVal;
		flag |= VBitrateF;
	}

	nNewVal = m_cbVSize.GetCurSel();
	if (m_vSize != nNewVal)
	{
		m_vSize = nNewVal;
		flag |= VSizeF;
	}

	return flag;
}

void CCurCfg::MemToUi(void)
{
	m_cbABitrate.SetCurSel(m_aBitrate);
	m_cbASampleRate.SetCurSel(m_aSampleRate);
	m_cbAInput.SetCurSel(m_aInput);

	m_cbVFps.SetCurSel(m_vFps);
	m_cbVSize.SetCurSel(m_vSize);
	m_cbVBitrate.SetCurSel(m_vBitrate);
}

 
void Printbps(CString&,double);
BOOL CCurCfg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	INT_PTR i; CString str;
	
	for (i=0; i<gsys.VideoFpses().GetCount(); ++i)
	{
		str.Format(_T("%d"),gsys.VideoFpses()[i]);
		m_cbVFps.AddString(str);
	}

	for (i=0; i<gsys.VideoOutputSizes().GetCount(); ++i)
	{
		str.Format(_T("%d x %d"),gsys.VideoOutputSizes()[i]);
		m_cbVSize.AddString(str);
	}
	
	for (i=0; i<gsys.VideoBitrates().GetCount(); ++i)
	{
		Printbps(str,gsys.VideoBitrates()[i]);
		m_cbVBitrate.AddString(str);
	}

	for (i=0; i<gsys.AudioBitrates().GetCount(); ++i)
	{
		str.Format(_T("%d Kbps"),gsys.AudioBitrates()[i]/1000);
		m_cbABitrate.AddString(str);
	}

	for (i=0; i<gsys.AudioSampleRates().GetCount(); ++i)
	{
		str.Format(_T("%d"),gsys.AudioSampleRates()[i]);
		m_cbASampleRate.AddString(str);
	}
 
	for (i=0; i<CDevices::GetMics().GetCount(); ++i)
		m_cbAInput.AddString(CDevices::GetMics()[i]);

	m_chkSaveAsDefault.SetCheck(BST_CHECKED);

	MemToUi();
	return FALSE;
}

void CCurCfg::OnOK(void)
{
	UINT flag = UiToMem();
	if (flag != 0)
	{
		if (m_chkSaveAsDefault.GetCheck() == BST_CHECKED)
		{
			if (m_aInput >= 0)
				gcfg.SetRecAudoInput(CDevices::GetMics()[m_aInput]);
			gcfg.SetRecAudioSampleRate(m_aBitrate);
			gcfg.SetRecAudioSampleRate(m_aSampleRate);

			gcfg.SetOutputVideoFps(m_vFps);
			gcfg.SetRecVideoBitrate(m_vBitrate);
			gcfg.SetOutputVideoSize(m_vSize);

		}
		GetParent()->PostMessage(WM_CFG_FINISHIED,flag);
	}
	ShowWindow(SW_HIDE);

}

void CCurCfg::OnCancel(void)
{
	ShowWindow(SW_HIDE);
}

void CCurCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags,point);
}

UINT CCurCfg::ABitrate(void) 
{
	return gsys.AudioBitrates()[s_pInst->m_aBitrate];
}

UINT CCurCfg::ASampleRate(void) 
{
	return gsys.AudioSampleRates()[s_pInst->m_aSampleRate];
}

static CString EmptyString;
const CString& CCurCfg::AInput(void) 
{
	if (CDevices::GetMics().IsEmpty() || s_pInst->m_aInput<0)
		return EmptyString;
	return CDevices::GetMics()[s_pInst->m_aInput];
}

CSize CCurCfg::VSize(void) 
{
	return gsys.VideoOutputSizes()[s_pInst->m_vSize];
}

UINT CCurCfg::VFps(void) 
{
	return gsys.VideoFpses()[s_pInst->m_vFps];
}

UINT CCurCfg::VBitrate(void) 
{
	return gsys.VideoBitrates()[s_pInst->m_vBitrate];
}
