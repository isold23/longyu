#pragma once

struct IBaseFilter;

class CDevices
{
	CDevices(void);
	~CDevices(void);

public:
	static BOOL Load(void);

	static const CStringArray& GetMics(void);
	static const CStringArray& GetVideoDevices(BOOL bInput);
	static const CStringArray& GetVideoDeviceNames(BOOL bInput);
	
	static HRESULT FindVideoDevice(IBaseFilter **ppSrcFilter,LPCTSTR pcszDeviceName,BOOL bInput);

private:
	static CStringArray m_mics;

	static CStringArray m_videInputDevices;
	static CStringArray m_videInputDeviceNames;

	static CStringArray m_videOutputDevices;
	static CStringArray m_videOutputDeviceNames;
};


inline const CStringArray& CDevices::GetMics(void) {
	return m_mics;
}

inline const CStringArray& CDevices::GetVideoDevices(BOOL bInput) {
	return bInput ? m_videInputDevices : m_videOutputDevices;
}

inline const CStringArray& CDevices::GetVideoDeviceNames(BOOL bInput) {
	return bInput ? m_videInputDeviceNames : m_videOutputDeviceNames;
}

