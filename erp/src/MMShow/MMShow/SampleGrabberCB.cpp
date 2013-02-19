#include "StdAfx.h"
#include "SampleGrabberCB.h"
#include "MediaFormatDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSampleGrabberCB::CSampleGrabberCB(void)
	:m_bSample(FALSE)
{
}

CSampleGrabberCB::~CSampleGrabberCB(void)
{
}

ULONG STDMETHODCALLTYPE CSampleGrabberCB::AddRef(void) { return 2; }
ULONG STDMETHODCALLTYPE CSampleGrabberCB::Release(void) { return 1; }
HRESULT STDMETHODCALLTYPE CSampleGrabberCB::QueryInterface(REFIID riid, void ** ppv)
{
	if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
	{
		*ppv = (void*)static_cast<ISampleGrabberCB*>(this);
		return S_OK;
	} 
	return E_NOINTERFACE;
}
HRESULT STDMETHODCALLTYPE CSampleGrabberCB::SampleCB(double SampleTime,IMediaSample *pSample)
{
	return S_OK;
}
HRESULT STDMETHODCALLTYPE CSampleGrabberCB::BufferCB(double dblSampleTime, BYTE *pBuffer,long lBufferSize)
{
	if (m_bSample)
	{
		m_dwSampleTick = GetTickCount();
		m_sample.Set(pBuffer,lBufferSize);
	}
	return S_OK;
}

BOOL CSampleGrabberCB::GetSample(CStaticBuffer &buf,CSize &sizeOfSample)
{
	ASSERT(m_bSample);

	LPBYTE  pSample = m_sample.Ptr() ;
	if (pSample == NULL)
		return FALSE;

	sizeOfSample.cx = m_vih.bmiHeader.biWidth;
	sizeOfSample.cy = m_vih.bmiHeader.biHeight;
	
	buf.Set(m_sample.Ptr(),m_sample.Size());

	return TRUE;
}

