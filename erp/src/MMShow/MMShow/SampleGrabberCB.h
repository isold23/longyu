#pragma once

#include <qedit.h>
#include <DShow.h>
#include "SimpleBuffer.h"


class CSampleGrabberCB  : public ISampleGrabberCB
{
public:
	CSampleGrabberCB(void);
	~CSampleGrabberCB(void);

	BOOL SampleRef(BOOL bRef);
	
	const VIDEOINFOHEADER& GetVideoFormat(void) const;
	DWORD GetSampleTick(void) const;

	BOOL GetSample(CStaticBuffer &buf,CSize &sizeOfSample);
protected:
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppv);
	virtual HRESULT STDMETHODCALLTYPE SampleCB(double SampleTime,IMediaSample *pSample);
	virtual HRESULT STDMETHODCALLTYPE BufferCB(double dblSampleTime, BYTE *pBuffer,long lBufferSize);

	BOOL m_bSample;
	VIDEOINFOHEADER m_vih;
	DWORD m_dwSampleTick;
	CDynBuffer m_sample;
};


inline const VIDEOINFOHEADER& CSampleGrabberCB::GetVideoFormat(void) const {
	return m_vih;
}

inline DWORD CSampleGrabberCB::GetSampleTick(void) const {
	return m_dwSampleTick;
}

inline BOOL CSampleGrabberCB::SampleRef(BOOL bRef) {
	return (bRef ? ++m_bSample : --m_bSample);
}