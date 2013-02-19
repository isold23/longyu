#pragma once

class CVolumeSetter
{
public:
	static UINT WM_VOLUME_CHANGED;
public:
	CVolumeSetter(void);
	~CVolumeSetter(void);

	BOOL OK(void) const;

	BOOL IsMute(void);
	BOOL Mute(BOOL bMute = TRUE);
	
	DWORD GetVolMetric(void);
	DWORD GetMinVol(void);
	DWORD GetMaxVol(void);
	DWORD GetCurVol(void);
	BOOL SetCurVol(DWORD dwValue );

	BOOL Init(HWND hWnd);
	void Free(void);

	BOOL IsMuteControl(DWORD dwId) const;
	BOOL IsVolControl(DWORD dwId) const;

private:
	BOOL Init(void);
  
	UINT m_nMixerID;
	DWORD_PTR m_dwMixerHandle;

	DWORD m_dwLineID;
	DWORD m_dwVolumeControlID;
	DWORD m_dwMuteControlID;
	int  m_nChannelCount;
 
 
	DWORD m_dwMinimalVolume;
	DWORD m_dwMaximalVolume;
	DWORD m_dwVolumeStep;

};

inline BOOL CVolumeSetter::OK(void) const {
	return m_dwMixerHandle;
}

inline BOOL CVolumeSetter::IsMuteControl(DWORD dwId) const {
	return dwId == m_dwMuteControlID;
}

inline BOOL CVolumeSetter::IsVolControl(DWORD dwId) const {
	return dwId == m_dwVolumeControlID;
}
