#pragma once

class CSysDefault
{
public:
	CSysDefault(void);
	~CSysDefault(void);

	BOOL Ajusted(void) const;
	BOOL Load(void);
	
	CString GetPath(void) const;
	
	BOOL ButtonShowTip(void) const;

	const CString& PicPath(void) const;
	const CString& CfgPath(void) const;
	
	const CStringArray& RecFormats(void) const;

	const CUIntArray& AudioBitrates(void) const;
	const CUIntArray& AudioSampleRates(void) const;

	const CUIntArray& VideoFpses(void) const;
	const CUIntArray& VideoBitrates(void) const;
	const CArray<CSize,CSize>& VideoOutputSizes(void) const; 

private:
	BOOL m_bAdjusted;

	BOOL m_bButtonShowTip;

	CString m_strCfgPath;
	CString m_strPicPath;

	CStringArray m_recFormats;

	CUIntArray m_aBitrates;
	CUIntArray m_aSampleRates;


	CUIntArray m_vFpses;
	CUIntArray m_vBitrates;	
	CArray<CSize,CSize> m_vOutputSizes;
};

inline BOOL CSysDefault::Ajusted(void) const {
	return m_bAdjusted;
}

inline 	BOOL CSysDefault::ButtonShowTip(void) const {
	return m_bButtonShowTip;
}

inline const CString& CSysDefault::CfgPath(void) const {
	return m_strCfgPath;
}
inline 	const CString& CSysDefault::PicPath(void) const {
	return m_strPicPath;
}

inline const CStringArray& CSysDefault::RecFormats(void) const {
	return m_recFormats;
}

inline const CUIntArray& CSysDefault::AudioSampleRates(void) const {
	return m_aSampleRates;
}
 
inline const CUIntArray& CSysDefault::AudioBitrates(void) const {
	return m_aBitrates;
}

inline const CUIntArray& CSysDefault::VideoFpses(void) const {
	return m_vFpses;
}

inline const CUIntArray& CSysDefault::VideoBitrates(void) const {
	return m_vBitrates;
}

inline const CArray<CSize,CSize>& CSysDefault::VideoOutputSizes(void) const {
	return m_vOutputSizes;
} 


extern CSysDefault gsys;