#include "stdafx.h"
#include "Resource.h"
#include "RecordCfgDlg.h"
#include "FolderDialog.h"
#include "Cfg.h"
#include "Devices.h"
#include "ArrayAdaptor.h"
#include "FileHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CRecordCfgDlg::CRecordCfgDlg(CWnd* pParent /*=NULL*/)
	: CCfgChildDlg(CRecordCfgDlg::IDD, pParent)
{

}

CRecordCfgDlg::~CRecordCfgDlg()
{
}

void CRecordCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CCfgChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_FORMAT, m_cbFormat);
	DDX_Control(pDX, IDC_EDIT_FOLDER, m_editFolder);
	DDX_Control(pDX, IDC_CB_VIDEO_BITRATE, m_cbVideoBitrate);
	DDX_Control(pDX, IDC_CB_AUDIO_BITRATE, m_cbAudioBitrate);
	DDX_Control(pDX, IDC_CB_AUDIO_SAMPLE_RATE, m_cbAudioSampleRate);
	DDX_Control(pDX, IDC_CB_DEF_AUDIO_INPUT, m_cbAudioInput);
}


BEGIN_MESSAGE_MAP(CRecordCfgDlg, CCfgChildDlg)
	ON_BN_CLICKED(IDC_BTN_SELECT, &CRecordCfgDlg::OnBnClickedBtnSelect)
END_MESSAGE_MAP()



void Printbps(CString&,double);
BOOL CRecordCfgDlg::OnInitDialog(void)
{
	CCfgChildDlg::OnInitDialog();

	INT_PTR i; CString str;
	for (i=0; i<gsys.RecFormats().GetCount(); ++i)
		m_cbFormat.AddString(gsys.RecFormats()[i]);
	m_cbFormat.SetCurSel(gcfg.GetRecOutputFmt());

	m_editFolder.SetWindowText(gcfg.GetRecOutputPath());

	for (i=0; i<gsys.VideoBitrates().GetCount(); ++i)
	{
		Printbps(str,gsys.VideoBitrates()[i]);
		m_cbVideoBitrate.AddString(str);
	}
	m_cbVideoBitrate.SetCurSel(gcfg.GetRecVideoBitrate());

	for (i=0; i<gsys.AudioSampleRates().GetCount(); ++i)
	{
		str.Format(_T("%d"),gsys.AudioSampleRates()[i]);
		m_cbAudioSampleRate.AddString(str);
	}
	m_cbAudioSampleRate.SetCurSel(gcfg.GetRecAudioSampleRate());

	for (i=0; i<gsys.AudioBitrates().GetCount(); ++i)
	{
		str.Format(_T("%d Kbps"),gsys.AudioBitrates()[i]/1000);
		m_cbAudioBitrate.AddString(str);
	}
	m_cbAudioBitrate.SetCurSel(gcfg.GetRecAudioBitrate());

	for (i=0; i<CDevices::GetMics().GetCount(); ++i)
		m_cbAudioInput.AddString(CDevices::GetMics()[i]);
	i = FindIndex(CDevices::GetMics(),gcfg.GetRecAudoInput());
	m_cbAudioInput.SetCurSel(i<0 ? 0:i);

	return FALSE;
}

void CRecordCfgDlg::OnBnClickedBtnSelect(void)
{
	CFolderDialog dlg;
	if (dlg.DoModal(GetSafeHwnd()) == IDOK)
		m_editFolder.SetWindowText(dlg.GetPathName());
}

BOOL CRecordCfgDlg::SaveCfg(CString &strTip)
{
	CString str;
	m_editFolder.GetWindowText(str);
	if (!str.IsEmpty() && !Fh::IsDirectoryExist(str))
	{
		strTip = _T("录制默认输出目录不存在");
		return FALSE;
	}
	else
	{
		if (m_cbFormat.GetCurSel() < 0)
		{
			strTip = _T("录制格式未正确选择");
			return FALSE;
		}
		if (!str.IsEmpty() && !Fh::IsSlash(str[str.GetLength()-1]))
			str.AppendChar(_T('\\'));
		gcfg.SetRecOutputPath(str);
		gcfg.SetRecOutputFmt(m_cbFormat.GetCurSel());
		gcfg.SetRecVideoBitrate(m_cbVideoBitrate.GetCurSel());
		gcfg.SetRecAudioBitrate(m_cbAudioBitrate.GetCurSel());
		gcfg.SetRecAudioSampleRate(m_cbAudioSampleRate.GetCurSel());

		int nIndex = m_cbAudioInput.GetCurSel();
		if (nIndex >= 0)
			gcfg.SetRecAudoInput(CDevices::GetMics()[m_cbAudioInput.GetCurSel()]);
		return TRUE;
	}
}

BOOL CRecordCfgDlg::CancelCfg(CString &strTip)
{
	return TRUE;
}
