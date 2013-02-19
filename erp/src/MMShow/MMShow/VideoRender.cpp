#include "StdAfx.h"
#include "VideoRender.h"
#include "Devices.h"
#include <streams.h>
#include "MediaFormatDef.h"
#include "DXHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class VideoRenderImpl :
	public CBaseFilter,
	public CBaseOutputPin
{
public:
	VideoRenderImpl(void);
	~VideoRenderImpl(void);

	HRESULT Open(HWND hWnd,CSize size,int nFps);
	HRESULT Open(LPCTSTR pcszCardName,CSize size,int nFps);
	HRESULT Close(void);

	BOOL IsOpened(void) const;
	HRESULT Write(LPCVOID buffer);

	int GetMediaFps(void) const;
	CSize GetMediaSize(void) const;
	HWND GetTargetWnd(void) const;
	LPCTSTR GetTargeDevice(void) const;

private:
	// IUnknown
	STDMETHODIMP_(ULONG) Release(void);

	// CBaseOutputPin
	virtual HRESULT CheckMediaType(const CMediaType *pMediaType);
	virtual HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
	virtual HRESULT GetMediaType(CMediaType *pMediaType);
	virtual HRESULT DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties);
	virtual HRESULT DecideAllocator(IMemInputPin * pPin, IMemAllocator ** pAlloc);

	// CBaseFilter
	virtual int GetPinCount(void);
	virtual CBasePin* GetPin(int n);

	void InitMedia(CSize size,int nFps);

	HRESULT Open(IBaseFilter *pRender);
	void ReleaseInterfaces(void);

	CCritSec m_csFilter;

	HWND m_hTargetWnd;
	LPCTSTR m_pcszTargetDevice;

	CMediaType m_mediaType;
	CComPtr<IGraphBuilder> m_pFilterGraph;
	CComQIPtr<IMediaControl> m_pMediaControl;
};


static const LPCTSTR Name_ThisRender = _T("ThisCardRenderZZ");
static const GUID Guid_ThisRender = 
	{ 0xd6109838, 0x9bae, 0x457a, { 0x9f, 0x44, 0x36, 0xa9, 0x2c, 0x2a, 0xf6, 0xb9 } };

static const LPCWSTR Name_ThisPin = L"ThisCardRenderPinZZ";
static  TCHAR TName_ThisPin[] = _T("ThisCardRenderPinZZ");
 

VideoRenderImpl::VideoRenderImpl(void)
	:CBaseFilter(Name_ThisRender,NULL,&m_csFilter,Guid_ThisRender),
	 CBaseOutputPin(TName_ThisPin,this,&m_csFilter,NULL,Name_ThisPin)
{
	m_mediaType.SetType(&MEDIATYPE_Video);
	m_mediaType.SetSubtype(&def_dxMediaSubType);
	m_mediaType.SetFormatType(&FORMAT_VideoInfo);
	m_mediaType.SetTemporalCompression(FALSE);

	VIDEOINFOHEADER vih;
	memset(&vih,0,sizeof(VIDEOINFOHEADER));
	vih.AvgTimePerFrame = 0;//UNITS/def_voFps;
	//vih.dwBitRate = def_vBytePerFrame;
	vih.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	vih.bmiHeader.biBitCount = def_vBitsPerPixel;
	//vih.bmiHeader.biWidth = def_voFrameWidth;
	//vih.bmiHeader.biHeight = def_voFrameHeight;
	vih.bmiHeader.biPlanes = 1;
	//vih.bmiHeader.biSizeImage = def_vBytePerFrame;
	m_mediaType.SetFormat((BYTE*)&vih,sizeof(VIDEOINFOHEADER));

	m_hTargetWnd = NULL;
	m_pcszTargetDevice = NULL;
}

VideoRenderImpl::~VideoRenderImpl(void)
{
	Close();

	CBaseFilter::m_cRef = 0;
	CBaseOutputPin::m_cRef = 0;
}
	// IUnknown
/*
	*------------***************************------------*
		  *--------------*CBaseOutputPin*------------*
	*------------***************************------------*
*/	

STDMETHODIMP_(ULONG) VideoRenderImpl::Release(void) 
{
	return 1;
};
/*
	*------------***************************------------*
		  *--------------*CBaseOutputPin*------------*
	*------------***************************------------*
*/	
HRESULT VideoRenderImpl::CheckMediaType(const CMediaType *pMediaType)
{
	CAutoLock cAutoLock(&m_csFilter);

	CheckPointer(pMediaType, E_POINTER);

	if(pMediaType->majortype != m_mediaType.majortype)
		return E_INVALIDARG;

	if(pMediaType->subtype != m_mediaType.subtype)
		return E_INVALIDARG;

	//if(pMediaType->formattype != s_mediaType.formattype)
	//	return E_INVALIDARG; 
	return S_OK;
}

HRESULT VideoRenderImpl::GetMediaType(CMediaType *pMediaType)
{
	CAutoLock cAutoLock(&m_csFilter);

	*pMediaType = m_mediaType;
	return S_OK;
}

HRESULT VideoRenderImpl::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	if (iPosition<0) 
		return E_INVALIDARG;
 
	if (iPosition>0) 
		return VFW_S_NO_MORE_ITEMS;

	return GetMediaType(pMediaType);
}



HRESULT VideoRenderImpl::DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
{
	CheckPointer(pAlloc,E_POINTER);
	CheckPointer(pProperties,E_POINTER);

	CAutoLock cAutoLock(&m_csFilter);

	VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER*)m_mediaType.Format();
	pProperties->cBuffers = 1;
	pProperties->cbBuffer = pvi->bmiHeader.biSizeImage;

	ALLOCATOR_PROPERTIES Actual;
	HRESULT hr = pAlloc->SetProperties(pProperties,&Actual);
	if(FAILED(hr)) return hr;

	if(Actual.cbBuffer < pProperties->cbBuffer)
		return E_FAIL;

	ASSERT(Actual.cBuffers == 1);
	return S_OK;
}

#define FAILED_RET_ALLOC(hr,x) if (FAILED(hr=(x))) { return hr;}
HRESULT VideoRenderImpl::DecideAllocator(IMemInputPin * pPin, IMemAllocator **pAlloc)
{
	CComPtr<IMemAllocator> spAlloc;

	ALLOCATOR_PROPERTIES prop;
	ZeroMemory(&prop, sizeof(prop));

	pPin->GetAllocatorRequirements(&prop);
	if (prop.cbAlign == 0) 
		prop.cbAlign = 1;
	
	HRESULT hr;
	FAILED_RET_ALLOC(hr,InitAllocator(&spAlloc));
	FAILED_RET_ALLOC(hr,DecideBufferSize(spAlloc, &prop));
	FAILED_RET_ALLOC(hr,pPin->NotifyAllocator(spAlloc, FALSE));

	*pAlloc = spAlloc.Detach();
	return S_OK;
}

/*
	*------------***************************------------*
		  *--------------*CBaseFilter*------------*
	*------------***************************------------*
*/	
int VideoRenderImpl::GetPinCount(void)
{
	CAutoLock cAutoLock(&m_csFilter);
	return 1;
}

CBasePin* VideoRenderImpl::GetPin(int n)
{
	CAutoLock cAutoLock(&m_csFilter);
	return (n == 0 ? this : NULL);
}

/*
	*------------***************************------------*
		  *--------------*VideoRenderImpl*------------*
	*------------***************************------------*
*/	

void VideoRenderImpl::ReleaseInterfaces(void)
{
	if (m_pFilterGraph != NULL)
		m_pFilterGraph.Release();
	if (m_pMediaControl != NULL)
		m_pMediaControl.Release();
}

void VideoRenderImpl::InitMedia(CSize size,int nFps)
{
	VIDEOINFOHEADER *vih = (VIDEOINFOHEADER*)m_mediaType.Format();
	vih->dwBitRate = size.cx*size.cy*def_vBytesPerPixel;
	vih->bmiHeader.biWidth = size.cx;
	vih->bmiHeader.biHeight = size.cy;
	vih->bmiHeader.biSizeImage = vih->dwBitRate;
	vih->AvgTimePerFrame = UNITS/nFps;
}


inline int VideoRenderImpl::GetMediaFps(void) const 
{
	VIDEOINFOHEADER *vih = (VIDEOINFOHEADER*)m_mediaType.Format();
	return UNITS/vih->AvgTimePerFrame;
}

inline CSize VideoRenderImpl::GetMediaSize(void) const
{
	VIDEOINFOHEADER *vih = (VIDEOINFOHEADER*)m_mediaType.Format();
	
	CSize size;
	size.cx = vih->bmiHeader.biWidth;
	size.cy = vih->bmiHeader.biHeight;
	return size;
}

inline HWND VideoRenderImpl::GetTargetWnd(void) const
{
	return m_hTargetWnd;
}

inline LPCTSTR VideoRenderImpl::GetTargeDevice(void) const
{
	return m_pcszTargetDevice;
}



#define FAILED_RET_OPEN(hr,x) if (FAILED(hr=(x))) { ReleaseInterfaces(); return hr;}
HRESULT VideoRenderImpl::Open(HWND hWnd,CSize size,int nFps)
{
	InitMedia(size,nFps);

	HRESULT hr;
	CComQIPtr<IBaseFilter> pRender;
	FAILED_RET_OPEN(hr,pRender.CoCreateInstance(CLSID_VideoRenderer));

	FAILED_RET_OPEN(hr,Open(pRender));

	CComQIPtr<IVideoWindow> pVw = pRender;
	if (pVw == NULL)
		FAILED_RET_OPEN(hr,E_FAIL);

	if (hWnd != NULL)
	{
		FAILED_RET_OPEN(hr,pVw->put_Owner((OAHWND)hWnd));
		FAILED_RET_OPEN(hr,pVw->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN));

		CRect rc;
		::GetClientRect(hWnd,&rc);
		FAILED_RET_OPEN(hr,pVw->SetWindowPosition(0,0,rc.right,rc.bottom));
		FAILED_RET_OPEN(hr,pVw->put_Visible(OATRUE));
	}

	m_pMediaControl = m_pFilterGraph;
	FAILED_RET_OPEN(hr,m_pMediaControl->Run());

	m_hTargetWnd = hWnd;
	return S_OK;
}

HRESULT VideoRenderImpl::Open(LPCTSTR pcszCardName,CSize size,int nFps)
{	
	InitMedia(size,nFps);

	CComPtr<IBaseFilter> pCardFilter;

	CDevices::FindVideoDevice(&pCardFilter,pcszCardName,FALSE);
	if (pCardFilter == NULL)
		return E_FAIL;

	HRESULT hr;
	FAILED_RET_OPEN(hr,Open(pCardFilter));
	
	CComQIPtr<IMediaControl> pMediaControl = m_pFilterGraph;
	FAILED_RET_OPEN(hr,pMediaControl->Run());
	
	m_pcszTargetDevice = pcszCardName;
	return S_OK;
}

HRESULT VideoRenderImpl::Open(IBaseFilter *pRender)
{
	HRESULT hr;

	FAILED_RET_OPEN(hr,m_pFilterGraph.CoCreateInstance(CLSID_FilterGraph));
	FAILED_RET_OPEN(hr,m_pFilterGraph->AddFilter(this,Name_ThisRender));

	CComPtr<IPin> pRenderPin;
	FAILED_RET_OPEN(hr,::FindPin(pRender,PINDIR_INPUT,&pRenderPin));

	FAILED_RET_OPEN(hr,m_pFilterGraph->AddFilter(pRender,L"Dest Render"));

	FAILED_RET_OPEN(hr,m_pFilterGraph->Connect(this,pRenderPin));

	return S_OK;
}

#define FAILED_RET_WRITE(hr,x) if (FAILED(hr=(x))) { return hr;}
HRESULT VideoRenderImpl::Write(LPCVOID buffer)
{
	CAutoLock cAutoLock(&m_csFilter);

	if (!IsOpened())
		return E_FAIL;

	BYTE *pData;
	CComPtr<IMediaSample> pSample;

	HRESULT hr;
	FAILED_RET_WRITE(hr,GetDeliveryBuffer(&pSample,NULL,NULL,0));

	FAILED_RET_WRITE(hr,pSample->GetPointer(&pData));

	CSize size = GetMediaSize();
	int nFrameSize = size.cx*size.cy*def_vBytesPerPixel;
	memcpy(pData,buffer,nFrameSize);
 
	FAILED_RET_WRITE(hr,pSample->SetActualDataLength(nFrameSize));
	FAILED_RET_WRITE(hr,pSample->SetSyncPoint(FALSE));
	FAILED_RET_WRITE(hr,Deliver(pSample));

	return S_OK;
}

BOOL VideoRenderImpl::IsOpened(void) const
{
	return (m_pFilterGraph != NULL);
}

HRESULT VideoRenderImpl::Close(void)
{
	if (IsOpened())
	{
		m_pMediaControl->StopWhenReady();
		ReleaseInterfaces();
	}
	return TRUE;
}

CVideoRender::CVideoRender(void)
	:m_pImpl(NULL)
{
}

CVideoRender::~CVideoRender(void)
{
	if (m_pImpl != NULL)
		delete m_pImpl;
}

HRESULT CVideoRender::Open(HWND hWnd,CSize size,int nFps)
{
	if (m_pImpl != NULL)
	{
		ASSERT(m_pImpl->GetTargetWnd() == hWnd);
		if (m_pImpl->GetMediaSize()!=size || m_pImpl->GetMediaFps()!=nFps)
		{
			delete m_pImpl;
			m_pImpl = NULL;
		}
	}

	if (m_pImpl != NULL)
		return S_OK;
	
	m_pImpl = new VideoRenderImpl();
	return m_pImpl->Open(hWnd,size,nFps);
	
}

HRESULT CVideoRender::Open(LPCTSTR pcszCardName,CSize size,int nFps)
{
	if (m_pImpl != NULL)
	{
		ASSERT(m_pImpl->GetTargeDevice() == pcszCardName);
		if (m_pImpl->GetMediaSize()!=size || m_pImpl->GetMediaFps()!=nFps)
		{
			delete m_pImpl;
			m_pImpl = NULL;
		}
	}
	if (m_pImpl != NULL)
		return S_OK;
	
	m_pImpl = new VideoRenderImpl();
	HRESULT hr = m_pImpl->Open(pcszCardName,size,nFps);
	if (FAILED(hr))
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
	return hr;
}

HRESULT CVideoRender::Close(void)
{
	if (m_pImpl == NULL)
		return E_FAIL;
		
	delete m_pImpl;
	m_pImpl = NULL;
	return S_OK;
}

BOOL CVideoRender::IsOpened(void) const
{
	return (m_pImpl != NULL);
}

HRESULT CVideoRender::Write(LPCVOID buffer)
{
	return m_pImpl->Write(buffer);
}
