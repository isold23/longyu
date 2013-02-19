#include "StdAfx.h"
#include "CamExt.h" 
#include "SampleGrabberCB.h"
#include "Devices.h"
#include "DXHelper.h"
#include "MediaFormatDef.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif

class CamExtImpl : public CSampleGrabberCB
{
public:

private:
	enum {CaptureListener,PreviewListener,ListernerCount};
	struct ListenerInfo
	{
		HWND hWnd;
		CCamSampleListener *pListener;
		BOOL bNotify;
		CComQIPtr<IBaseFilter> pRender;
	};

public:
	CamExtImpl(CCamExt *pInst,LPCTSTR pcszCamName=NULL,LPCTSTR pcszDisplayName=NULL);
	virtual ~CamExtImpl(void);

	void SetCapture(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify);
	void SetPreview(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify);

	BOOL Start(void);
	BOOL Stop(void);

	LPCTSTR GetName(void) const;
	LPCTSTR GetDisplayName(void) const;

protected:
	HRESULT STDMETHODCALLTYPE BufferCB(double SampleTime,BYTE *pBuffer,long lBufferSize);

	HRESULT GetInterfaces(void);
	void ReleaseInterfaces(void);
	HRESULT CreateRender(ListenerInfo &li);
	HRESULT SetupRender(ListenerInfo &li);

	CComPtr<ICaptureGraphBuilder2> m_pCaptureGraphBuilder;
	CComPtr<IGraphBuilder> m_pFilterGraph;
	CComQIPtr<IMediaControl> m_pMediaControl; 
	CComPtr<ISampleGrabber> m_pSampleGrabber;
	CComPtr<IBaseFilter> m_pSrcCamFilter;

	CCamExt *m_pInst;
	LPCTSTR m_pcszCamName;
	LPCTSTR m_pcszCamDisplayName;

	ListenerInfo m_listeners[ListernerCount];
};

inline LPCTSTR CamExtImpl::GetName(void) const {
	return m_pcszCamName;
}

inline LPCTSTR CamExtImpl::GetDisplayName(void) const {
	return m_pcszCamDisplayName;
}


CamExtImpl::CamExtImpl(CCamExt *pInst,LPCTSTR pcszCamName,LPCTSTR pcszDisplayName)
	:m_pInst(pInst),
	 m_pcszCamName(pcszCamName),
	 m_pcszCamDisplayName(pcszDisplayName)
{
}

CamExtImpl::~CamExtImpl(void)
{
}


void CamExtImpl::SetCapture(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify)
{
	m_listeners[CaptureListener].hWnd = hWnd;
	m_listeners[CaptureListener].pListener = pListener;
	m_listeners[CaptureListener].bNotify = bNotify;
}

void CamExtImpl::SetPreview(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify)
{
	m_listeners[PreviewListener].hWnd = hWnd;
	m_listeners[PreviewListener].pListener = pListener;
	m_listeners[PreviewListener].bNotify = bNotify;
}


#define FAILED_RET(x) if (FAILED((x))) {ReleaseInterfaces(); return FALSE;}
#define FAILED_RET_HR(hr,x) if (FAILED(hr=(x))) {return hr;}

BOOL CamExtImpl::Start(void)
{
	ASSERT(m_pCaptureGraphBuilder == NULL);

	FAILED_RET(CDevices::FindVideoDevice(&m_pSrcCamFilter,m_pcszCamName,TRUE));

	FAILED_RET(GetInterfaces());

	FAILED_RET(m_pCaptureGraphBuilder->SetFiltergraph(m_pFilterGraph));

	FAILED_RET(m_pFilterGraph->AddFilter(m_pSrcCamFilter, L"Video Capture"));

	FAILED_RET(m_pSampleGrabber.CoCreateInstance(CLSID_SampleGrabber));

	//VIDEOINFOHEADER  vih;
	//memset(&vih,0,sizeof(vih));
	//vih.bmiHeader.biWidth = Muxing::def_voFrameWidth;
	//vih.bmiHeader.biHeight = Muxing::def_voFrameHeight;
	//vih.AvgTimePerFrame = UNITS/Muxing::def_voFps;

	AM_MEDIA_TYPE mt; 
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = def_dxMediaSubType;
/*	mt.pbFormat = (BYTE*)&vih;
	mt.cbFormat = sizeof(VIDEOINFOHEADER)*/;
	FAILED_RET(m_pSampleGrabber->SetMediaType(&mt));

	//CComPtr<IAMStreamConfig> pConfig;
	//FAILED_RET(m_pCaptureGraphBuilder->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,
	//	pSrcCamFilter,IID_IAMStreamConfig,(void**)&pConfig));  
	//FAILED_RET(pConfig->SetFormat(&mt));

	CComQIPtr<IBaseFilter> pSgf = m_pSampleGrabber;
	FAILED_RET(m_pFilterGraph->AddFilter(pSgf,L"Grabber"));

 

	FAILED_RET(CreateRender(m_listeners[CaptureListener]));
	FAILED_RET(m_pCaptureGraphBuilder->RenderStream (&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,
		m_pSrcCamFilter,pSgf, m_listeners[CaptureListener].pRender));
	FAILED_RET(SetupRender(m_listeners[CaptureListener]));

	FAILED_RET(CreateRender(m_listeners[PreviewListener]));
	FAILED_RET(m_pCaptureGraphBuilder->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
		m_pSrcCamFilter,NULL, m_listeners[PreviewListener].pRender));
	FAILED_RET(SetupRender(m_listeners[PreviewListener]));

	m_pSampleGrabber->SetBufferSamples(FALSE);
	m_pSampleGrabber->SetOneShot(FALSE);
	m_pSampleGrabber->SetCallback(this,1);

	memset(&mt,0,sizeof(AM_MEDIA_TYPE));
	m_pSampleGrabber->GetConnectedMediaType(&mt);
	memcpy(&m_vih,mt.pbFormat,sizeof(VIDEOINFOHEADER));
	if (mt.cbFormat != 0)
		CoTaskMemFree((PVOID)mt.pbFormat);
	if (mt.pUnk != NULL)
		mt.pUnk->Release();

	FAILED_RET(m_pMediaControl->Run());

	AddGraphToRot(m_pFilterGraph,NULL);
	return TRUE;
}

BOOL CamExtImpl::Stop(void)
{
	if (m_pMediaControl != NULL)
		m_pMediaControl->StopWhenReady();
  
	ReleaseInterfaces();
	
	m_dwSampleTick = 0;

	return TRUE;
}


HRESULT CamExtImpl::GetInterfaces(void)
{
	HRESULT hr;
	FAILED_RET_HR(hr,m_pFilterGraph.CoCreateInstance(CLSID_FilterGraph));
	FAILED_RET_HR(hr,m_pCaptureGraphBuilder.CoCreateInstance(CLSID_CaptureGraphBuilder2));

	m_pMediaControl = m_pFilterGraph;
	return hr;
}

void CamExtImpl::ReleaseInterfaces(void)
{
	m_pCaptureGraphBuilder.Detach();
	m_pFilterGraph.Detach();
	m_pMediaControl.Detach(); 
	m_pSampleGrabber.Detach();
	m_pSrcCamFilter.Detach();
	m_listeners[CaptureListener].pRender.Release();
	m_listeners[PreviewListener].pRender.Release();
}



HRESULT CamExtImpl::CreateRender(ListenerInfo &li)
{
	HRESULT hr;
	FAILED_RET_HR(hr,li.pRender.CoCreateInstance(CLSID_VideoMixingRenderer9));
	FAILED_RET_HR(hr,m_pFilterGraph->AddFilter(li.pRender,L"Other Render"));
	return S_OK;
}


HRESULT CamExtImpl::SetupRender(ListenerInfo &li)
{
	CComQIPtr<IVideoWindow> pVw = li.pRender;
	if (pVw == NULL)
		return E_FAIL;

	HRESULT hr;
	FAILED_RET_HR(hr,pVw->put_Owner((OAHWND)li.hWnd));
	FAILED_RET_HR(hr,pVw->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN));

	CRect rc;
	::GetClientRect(li.hWnd,&rc);
	FAILED_RET_HR(hr,pVw->SetWindowPosition(0,0,rc.right,rc.bottom));
	FAILED_RET_HR(hr,pVw->put_Visible(OATRUE));
 
	return S_OK;
}

 

HRESULT STDMETHODCALLTYPE CamExtImpl::BufferCB(double SampleTime,BYTE *pBuffer,long lBufferSize)
{
	if (m_bSample)
	{
		CSampleGrabberCB::BufferCB(SampleTime,pBuffer,lBufferSize);

		ListenerInfo &liCapture = m_listeners[CaptureListener];
		if (liCapture.pListener!=NULL && liCapture.bNotify)
			liCapture.pListener->OnSample(m_pInst);

		ListenerInfo &liPreview = m_listeners[PreviewListener];
		if (liPreview.pListener!=NULL && liPreview.bNotify)
			liPreview.pListener->OnSample(m_pInst);
	}
	return S_OK;
}

CCamExt::CCamExt(LPCTSTR pcszCamName,LPCTSTR pcszDisplayName)
{
	m_pImpl = new CamExtImpl(this,pcszCamName,pcszDisplayName);
}

CCamExt::~CCamExt(void)
{
	delete m_pImpl;
}

void CCamExt::SetCapture(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify)
{
	m_pImpl->SetCapture(hWnd,pListener,bNotify);
}

void CCamExt::SetPreview(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify)
{
	m_pImpl->SetPreview(hWnd,pListener,bNotify);
}

BOOL CCamExt::Start(void)
{
	return m_pImpl->Start();
}

BOOL CCamExt::Stop(void)
{
	return m_pImpl->Stop();
}

LPCTSTR CCamExt::GetName(void) const
{
	return m_pImpl->GetName();
}

LPCTSTR CCamExt::GetDisplayName(void) const
{
	return m_pImpl->GetDisplayName();
}

DWORD CCamExt::GetSampleTick(void) const
{
	return m_pImpl->GetSampleTick();
}

BOOL CCamExt::GetSample(CStaticBuffer &buf,CSize &sizeOfSample)
{
	return m_pImpl->GetSample(buf,sizeOfSample);
}

BOOL CCamExt::SampleRef(BOOL bRef)
{
	return m_pImpl->SampleRef(bRef);
}