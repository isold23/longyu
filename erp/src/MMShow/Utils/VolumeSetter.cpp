#include "StdAfx.h"
#include <MMSystem.h>
#include "VolumeSetter.h"

UINT CVolumeSetter::WM_VOLUME_CHANGED = MM_MIXM_CONTROL_CHANGE;


CVolumeSetter::CVolumeSetter(void)
	: m_nMixerID(0),
	  m_dwMixerHandle(0),
	  m_dwMinimalVolume(-1),
	  m_dwMaximalVolume(-1)
{
}

CVolumeSetter::~CVolumeSetter()
{
	Free();
}

BOOL CVolumeSetter::Init(HWND hWnd)
{
	if (!mixerGetNumDevs())
		return FALSE;

	MMRESULT mmResult = mixerGetID(NULL,&m_nMixerID,MIXER_OBJECTF_MIXER);
	if (mmResult != MMSYSERR_NOERROR)
		return FALSE;
	
	mmResult = mixerOpen((LPHMIXER)&m_dwMixerHandle, m_nMixerID, (DWORD)hWnd, 0L, CALLBACK_WINDOW);
	if (mmResult != MMSYSERR_NOERROR)
		return FALSE;

	if (Init())
		return TRUE;

	Free();
	return FALSE;
}

void CVolumeSetter::Free(void)
{
	if (m_dwMixerHandle != 0)
	{
		mixerClose((HMIXER)m_dwMixerHandle);
		m_dwMixerHandle = 0;
	}
}
  
BOOL CVolumeSetter::Init(void)
{
	MMRESULT mmResult;
	MIXERLINE mixerLine;
	memset(&mixerLine, 0, sizeof(MIXERLINE));
	mixerLine.cbStruct = sizeof(MIXERLINE);
	mixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	mmResult = mixerGetLineInfo((HMIXEROBJ)m_dwMixerHandle, &mixerLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
	if (mmResult != MMSYSERR_NOERROR)
		return FALSE;

	MIXERCONTROL Control;
	memset(&Control, 0, sizeof(MIXERCONTROL));
	Control.cbStruct = sizeof(MIXERCONTROL);

	MIXERLINECONTROLS LineControls;
	memset(&LineControls, 0, sizeof(MIXERLINECONTROLS));
	LineControls.cbStruct = sizeof(MIXERLINECONTROLS);

	LineControls.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	LineControls.dwLineID = mixerLine.dwLineID;
	LineControls.cControls = 1;
	LineControls.cbmxctrl = sizeof(MIXERCONTROL);
	LineControls.pamxctrl = &Control;
	mmResult = mixerGetLineControls((HMIXEROBJ)m_dwMixerHandle, &LineControls, MIXER_GETLINECONTROLSF_ONEBYTYPE);

	m_nChannelCount = mixerLine.cChannels;
	m_dwLineID = LineControls.dwLineID;
	m_dwVolumeControlID = Control.dwControlID;
	m_dwMinimalVolume = Control.Bounds.dwMinimum;
	m_dwMaximalVolume = Control.Bounds.dwMaximum;
	m_dwVolumeStep = Control.Metrics.cSteps;

	LineControls.dwControlType = MIXERCONTROL_CONTROLTYPE_MUTE;
	mmResult = mixerGetLineControls((HMIXEROBJ)m_dwMixerHandle, &LineControls, MIXER_GETLINECONTROLSF_ONEBYTYPE);
	m_dwMuteControlID = Control.dwControlID;

	return TRUE;
}
	
BOOL CVolumeSetter::IsMute(void)
{
	if (m_dwMixerHandle == 0)
		return FALSE;

	MIXERCONTROLDETAILS_UNSIGNED aDetail;
	MIXERCONTROLDETAILS ControlDetails;
	memset(&ControlDetails, 0, sizeof(MIXERCONTROLDETAILS));
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_dwMuteControlID;
	ControlDetails.cChannels = 1;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = &aDetail;


	if (mixerGetControlDetails((HMIXEROBJ)m_dwMixerHandle,&ControlDetails,MIXER_GETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return FALSE;

	return aDetail.dwValue;
}

BOOL CVolumeSetter::Mute(BOOL bMute)
{
	if (m_dwMixerHandle == 0)
		return FALSE;

	MIXERCONTROLDETAILS_UNSIGNED aDetail;
	aDetail.dwValue = bMute;

	MIXERCONTROLDETAILS ControlDetails;
	memset(&ControlDetails, 0, sizeof(MIXERCONTROLDETAILS));
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_dwMuteControlID;
	ControlDetails.cChannels = 1;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = &aDetail;

	return (mixerSetControlDetails((HMIXEROBJ)m_dwMixerHandle,&ControlDetails,MIXER_GETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR);
}
 
DWORD CVolumeSetter::GetVolMetric(void)
{
	if (m_dwMixerHandle == 0)
		return -1;
	return m_dwVolumeStep;
}

DWORD CVolumeSetter::GetMinVol(void)
{
	if (m_dwMixerHandle == 0)
		return -1;
	return m_dwMinimalVolume;
}

DWORD CVolumeSetter::GetMaxVol(void)
{
	if (m_dwMixerHandle == 0)
		return -1;
	return m_dwMaximalVolume;
}

DWORD CVolumeSetter::GetCurVol(void)
{
	if (m_dwMixerHandle == 0)
		return -1;

	MIXERCONTROLDETAILS_UNSIGNED aDetail;
	MIXERCONTROLDETAILS ControlDetails;
	memset(&ControlDetails, 0, sizeof(MIXERCONTROLDETAILS));
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_dwVolumeControlID;
	ControlDetails.cChannels = 1;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = &aDetail;
	MMRESULT mmResult = mixerGetControlDetails((HMIXEROBJ)m_dwMixerHandle, &ControlDetails, MIXER_GETCONTROLDETAILSF_VALUE);
	if (mmResult != MMSYSERR_NOERROR)
		return -1;
	
	return aDetail.dwValue;
}

BOOL CVolumeSetter::SetCurVol(DWORD dwValue)
{
	if ((m_dwMixerHandle == 0) || (dwValue<m_dwMinimalVolume) || (dwValue>m_dwMaximalVolume))
		return FALSE;

	MIXERCONTROLDETAILS_UNSIGNED aDetail;
	aDetail.dwValue = dwValue;
	
	MIXERCONTROLDETAILS ControlDetails;
	memset(&ControlDetails, 0, sizeof(MIXERCONTROLDETAILS));
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_dwVolumeControlID;
	ControlDetails.cChannels = 1;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = &aDetail;
	
	return (mixerSetControlDetails((HMIXEROBJ)m_dwMixerHandle, &ControlDetails, MIXER_SETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR);
} 