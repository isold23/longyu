#include "StdAfx.h"
#include "MediaPlayer.h"
#include "SampleGrabberCB.h"
#include "DrawHelper.h"
#include "DXHelper.h"
#include "MediaFormatDef.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class MediaPlayerImpl : public CSampleGrabberCB
{
public:
	MediaPlayerImpl(void);
	~MediaPlayerImpl(void);

	void SetRenderWnd(HWND hWnd);

	BOOL OpenMovie(const CString &strFilePath);
	void CloseMovie(void);

	BOOL PlayMovie(void);
	BOOL PauseMovie(void);
	BOOL StopMovie(void);

	BOOL CanMovieFrameStep(void);
	BOOL FrameStepMovie(void);

	REFTIME GetDuration(void);
	REFTIME GetCurrentPosition(void);
	CMediaPlayer::EMovieMode StatusMovie(void);

	BOOL SeekToPercent(REFTIME &rtSeekBy);
	BOOL SeekOffset(REFTIME &rtSeekBy);
	BOOL SeekToPosition(REFTIME rt,BOOL bFlushData);

	BOOL GetVolume(long &vol);
	BOOL SetVolume(long vol);

	BOOL IsMute(void) const;
	BOOL Mute(BOOL bMute);

	const CString &GetFilePath(void) const;
	void RepositionVideoWnd(void);

private: 
	HRESULT AddSampleGrabber(IBaseFilter *pSrcFilter/*,IBaseFilter *pRenderFilter*/);

	CMediaPlayer::EMovieMode  m_Mode;
	GUID  m_TimeFormat;

	CComQIPtr<IFilterGraph> m_pFitlerGraph;
	CComQIPtr<IGraphBuilder> m_pGraphBuilder;
	CComQIPtr<IMediaControl> m_pMediaControl;
	CComQIPtr<IMediaSeeking> m_pMediaSeeking;
	CComQIPtr<IMediaEvent> m_pMediaEvent;
	CComQIPtr<IBasicAudio> m_pBasicAudio;


	CComPtr<ISampleGrabber> m_pSampleGrabber;

	HWND m_hRenderWnd;
	CString m_strFilePath;

	DWORD m_dwSampleTick;

	long m_volumeMute;
};

inline const CString& MediaPlayerImpl::GetFilePath(void) const {
	return m_strFilePath;
}

inline void MediaPlayerImpl::SetRenderWnd(HWND hWnd) {
	m_hRenderWnd = hWnd;
} 

inline BOOL MediaPlayerImpl::IsMute(void) const {
	return (m_volumeMute != LONG_MAX);
}

/*
	*------------***************************------------*
		  *--------------*MediaPlayerImpl*------------*
	*------------***************************------------*
*/	
MediaPlayerImpl::MediaPlayerImpl(void) 
{
	m_volumeMute = LONG_MAX;
	m_hRenderWnd = NULL;
	m_Mode = CMediaPlayer::MOVIE_NOTOPENED;
	m_TimeFormat = TIME_FORMAT_MEDIA_TIME;
	memset(&m_vih,0,sizeof(VIDEOINFOHEADER));
}

MediaPlayerImpl::~MediaPlayerImpl(void)
{
}
  


#define FAILED_RET(x) if (FAILED(x)) { CloseMovie(); return FALSE;}
#define FALSE_RET(x) if ((x)) { CloseMovie(); return FALSE;}

BOOL MediaPlayerImpl::OpenMovie(const CString &strFilePath)
{
	USES_CONVERSION;
	
	FAILED_RET(m_pFitlerGraph.CoCreateInstance(CLSID_FilterGraph));

	m_Mode = CMediaPlayer::MOVIE_OPENED;

	m_pGraphBuilder = m_pFitlerGraph;
	FALSE_RET(m_pGraphBuilder == NULL);

	CComPtr<IBaseFilter> pSrcFilter;
	FAILED_RET(m_pGraphBuilder->AddSourceFilter(T2CW(strFilePath),L"Source",&pSrcFilter));

	FAILED_RET(m_pSampleGrabber.CoCreateInstance(CLSID_SampleGrabber));
	CComQIPtr<IBaseFilter> pGrabFilter = m_pSampleGrabber;
	FALSE_RET(pGrabFilter == NULL);
	FAILED_RET(m_pFitlerGraph->AddFilter(pGrabFilter,L"SampleGrabber"));


	AM_MEDIA_TYPE mt;
	memset(&mt,0,sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = def_dxMediaSubType;
	m_pSampleGrabber->SetMediaType(&mt);
	m_pSampleGrabber->SetBufferSamples( FALSE );
	m_pSampleGrabber->SetOneShot(FALSE);
	m_pSampleGrabber->SetCallback(this,1);

	CComPtr<IPin> pSrcPin;
	FAILED_RET(ConnectFilters(m_pGraphBuilder,pSrcFilter,pGrabFilter,&pSrcPin));
	m_pGraphBuilder->Render(pSrcPin);
	
	CComPtr<IPin> pGrabPin;
	FindPin(pGrabFilter,PINDIR_OUTPUT,&pGrabPin);
	m_pGraphBuilder->Render(pGrabPin);
	RenderSourceFilter(m_pGraphBuilder,pSrcFilter,pSrcPin);


	memset(&mt,0,sizeof(AM_MEDIA_TYPE));
	m_pSampleGrabber->GetConnectedMediaType(&mt);
	memcpy(&m_vih,mt.pbFormat,sizeof(VIDEOINFOHEADER));
	if (mt.cbFormat != 0)
		CoTaskMemFree((PVOID)mt.pbFormat);
	if (mt.pUnk != NULL)
		mt.pUnk->Release();


	m_pMediaControl = m_pFitlerGraph;
	FALSE_RET(m_pMediaControl == NULL);

	m_pMediaEvent = m_pFitlerGraph;
	m_pBasicAudio = m_pFitlerGraph;
	m_pMediaSeeking = m_pFitlerGraph;


	if (IsMute())
		m_pBasicAudio->put_Volume(-10000);

	CComQIPtr<IVideoWindow> pWnd = m_pFitlerGraph;
	pWnd->put_Owner((OAHWND)m_hRenderWnd);
	pWnd->put_WindowStyle(WS_CHILD);
	RepositionVideoWnd();

	m_strFilePath = strFilePath;
	return TRUE;
}

void MediaPlayerImpl::RepositionVideoWnd(void)
{
	if (m_pFitlerGraph!=NULL && m_hRenderWnd!=NULL)
	{
		CComQIPtr<IVideoWindow> pWnd = m_pFitlerGraph;

		CClientRect rc(m_hRenderWnd);
		pWnd->SetWindowPosition(rc.left,rc.top,rc.right,rc.bottom); 
	}
}



void MediaPlayerImpl::CloseMovie(void)
{
	m_dwSampleTick = 0;

	m_Mode = CMediaPlayer::MOVIE_NOTOPENED;
  	
	if (m_pFitlerGraph != NULL)
		m_pFitlerGraph.Release();
	if (m_pMediaControl != NULL)
		m_pMediaControl.Release();
	if (m_pMediaSeeking != NULL)
		m_pMediaSeeking.Release();
	if (m_pMediaEvent != NULL)
		m_pMediaEvent.Release(); 
	if (m_pBasicAudio != NULL)
		m_pBasicAudio.Release();
	if (m_pSampleGrabber != NULL)
		m_pSampleGrabber.Release(); 
	if (m_pGraphBuilder != NULL)
		m_pGraphBuilder.Release();
}
 

  

BOOL MediaPlayerImpl::PlayMovie(void)
{
	REFTIME rt, rtAbs, rtDur;
	HRESULT hr=S_OK;

	rt = GetCurrentPosition();
	rtDur = GetDuration();

	rtAbs = rt - rtDur;
	if(rtAbs < (REFTIME)0)
	{
		rtAbs = -rtAbs;
	}

	if(rtAbs < (REFTIME)1)
	{
		SeekToPosition((REFTIME)0,FALSE);
	}

	m_Mode = CMediaPlayer::MOVIE_PLAYING;
	hr = m_pMediaControl->Run();
	return TRUE;
}

BOOL MediaPlayerImpl::PauseMovie(void)
{
	m_Mode = CMediaPlayer::MOVIE_PAUSED;

	HRESULT hr = m_pMediaControl->Pause();
	return TRUE;
}

BOOL MediaPlayerImpl::StopMovie(void)
{
	m_Mode = CMediaPlayer::MOVIE_STOPPED;
	HRESULT hr = m_pMediaControl->StopWhenReady();
	return TRUE;
}
 
CMediaPlayer::EMovieMode MediaPlayerImpl::StatusMovie(void)
{
	if(m_pMediaControl)
	{
		FILTER_STATE    fs;
		HRESULT         hr;

		hr = m_pMediaControl->GetState(100, (OAFilterState *)&fs);
		if(hr == VFW_S_STATE_INTERMEDIATE)
			return m_Mode;

		switch(fs)
		{
		case State_Stopped:
			m_Mode = CMediaPlayer::MOVIE_STOPPED;
			break;

		case State_Paused:
			m_Mode = CMediaPlayer::MOVIE_PAUSED;
			break;

		case State_Running:
			m_Mode = CMediaPlayer::MOVIE_PLAYING;
			break;
		}
	}

	return m_Mode;
}

BOOL MediaPlayerImpl::CanMovieFrameStep(void)
{
	IVideoFrameStep* lpFS;
	HRESULT hr;

	hr = m_pFitlerGraph->QueryInterface(__uuidof(IVideoFrameStep), (LPVOID *)&lpFS);
	if(SUCCEEDED(hr))
	{
		hr = lpFS->CanStep(0L, NULL);
		lpFS->Release();
	}

	return SUCCEEDED(hr);
}
 
BOOL MediaPlayerImpl::FrameStepMovie(void)
{
	if (m_pFitlerGraph == NULL)
		return FALSE;

	IVideoFrameStep* lpFS;
	HRESULT hr;

	hr = m_pFitlerGraph->QueryInterface(__uuidof(IVideoFrameStep), (LPVOID *)&lpFS);
	if(SUCCEEDED(hr))
	{
		hr = lpFS->Step(1, NULL);
		lpFS->Release();
	}

	return SUCCEEDED(hr);
}





REFTIME MediaPlayerImpl::GetDuration(void)
{
	HRESULT hr;
	LONGLONG Duration;

	if(m_TimeFormat != TIME_FORMAT_MEDIA_TIME)
	{
		hr = m_pMediaSeeking->GetDuration(&Duration);
		if(SUCCEEDED(hr))
		{
			return double(Duration);
		}
	}
	else if(m_pMediaSeeking != NULL)
	{
		hr = m_pMediaSeeking->GetDuration(&Duration);
		if(SUCCEEDED(hr))
		{
			return double(Duration) / UNITS;
		}
	}

	return 0;
}

REFTIME MediaPlayerImpl::GetCurrentPosition(void)
{
	REFTIME rt = (REFTIME) 0;
	HRESULT hr;
	LONGLONG Position;

	if(m_TimeFormat != TIME_FORMAT_MEDIA_TIME)
	{
		hr = m_pMediaSeeking->GetPositions(&Position, NULL);
		if(SUCCEEDED(hr))
		{
			return double(Position);
		}
	}
	else if(m_pMediaSeeking != NULL)
	{
		hr = m_pMediaSeeking->GetPositions(&Position, NULL);
		if(SUCCEEDED(hr))
		{
			return double(Position) / UNITS;
		}
	}

	return rt;
}

BOOL MediaPlayerImpl::SeekToPercent(REFTIME &rtSeekBy)
{
	if (rtSeekBy <0.0 || rtSeekBy>=1.0f)
		return FALSE;

	rtSeekBy *= GetDuration();
	return SeekToPosition(rtSeekBy,TRUE);	
}

BOOL MediaPlayerImpl::SeekOffset(REFTIME &rtSeekBy)
{
	REFTIME rtDur = GetDuration();
	rtSeekBy += GetCurrentPosition();
	rtSeekBy = max(0, min(rtSeekBy,rtSeekBy));
	return SeekToPosition(rtSeekBy,TRUE);
}

BOOL MediaPlayerImpl::SeekToPosition(REFTIME rt,BOOL bFlushData)
{
	HRESULT hr;
	LONGLONG llTime = (LONGLONG)(m_TimeFormat == TIME_FORMAT_MEDIA_TIME ? rt * double(UNITS) : rt );

	if(m_pMediaSeeking != NULL)
	{
		FILTER_STATE fs;
		hr = m_pMediaControl->GetState(100, (OAFilterState *)&fs);

		hr = m_pMediaSeeking->SetPositions(&llTime, AM_SEEKING_AbsolutePositioning, NULL, 0);

		if(fs == State_Stopped && bFlushData)
		{
			hr = m_pMediaControl->Pause();
			hr = m_pMediaControl->GetState(INFINITE, (OAFilterState *)&fs);
			hr = m_pMediaControl->StopWhenReady();
		}

		if(SUCCEEDED(hr))
			return TRUE;
	}

	return FALSE;
}


 

BOOL MediaPlayerImpl::GetVolume(long &vol)
{
	return FALSE;
}

BOOL MediaPlayerImpl::SetVolume(long vol)
{
	if (m_pBasicAudio == NULL)
		return FALSE;

	vol = (long)(2000.0*log(pow(10.0,-80.0)+vol/100.0));
	return SUCCEEDED(m_pBasicAudio->put_Volume(vol));
}

BOOL MediaPlayerImpl::Mute(BOOL bMute)
{
	if (m_pBasicAudio == NULL)
		return FALSE;

	if (!bMute) // unmute
	{
		if (!IsMute())
			return FALSE;

		if (FAILED(m_pBasicAudio->put_Volume(m_volumeMute)))
			return FALSE;
		m_volumeMute = LONG_MAX;
		return TRUE;
	}
	else	// mute
	{
		if (IsMute())
			return FALSE;		 
		return SUCCEEDED(m_pBasicAudio->get_Volume(&m_volumeMute)) &&
			SUCCEEDED(m_pBasicAudio->put_Volume(-10000));
	}
}


CMediaPlayer::CMediaPlayer(void)
{
	m_pImpl = new MediaPlayerImpl();
}

CMediaPlayer::~CMediaPlayer(void)
{
	delete m_pImpl;
}

void CMediaPlayer::SetRenderWnd(HWND hWnd)
{
	m_pImpl->SetRenderWnd(hWnd);
}

BOOL CMediaPlayer::OpenMovie(const CString &strFilePath)
{
	return m_pImpl->OpenMovie(strFilePath);
}

void CMediaPlayer::CloseMovie(void)
{
	m_pImpl->CloseMovie();
}

BOOL CMediaPlayer::PlayMovie(void)
{
	return m_pImpl->PlayMovie();
}

BOOL CMediaPlayer::PauseMovie(void)
{
	return m_pImpl->PauseMovie();
}

BOOL CMediaPlayer::StopMovie(void)
{
	return m_pImpl->StopMovie();
}

BOOL CMediaPlayer::CanMovieFrameStep(void)
{
	return m_pImpl->CanMovieFrameStep();
}

BOOL CMediaPlayer::FrameStepMovie(void)
{
	return m_pImpl->FrameStepMovie();
}

REFTIME CMediaPlayer::GetDuration(void)
{
	return m_pImpl->GetDuration();
}

REFTIME CMediaPlayer::GetCurrentPosition(void)
{
	return m_pImpl->GetCurrentPosition();
}

CMediaPlayer::EMovieMode CMediaPlayer::StatusMovie(void)
{
	return m_pImpl->StatusMovie();
}

BOOL CMediaPlayer::SeekToPercent(REFTIME &rtSeekBy)
{
	return m_pImpl->SeekOffset(rtSeekBy);
}

BOOL CMediaPlayer::SeekOffset(REFTIME &rtSeekBy)
{
	return m_pImpl->SeekOffset(rtSeekBy);
}

BOOL CMediaPlayer::SeekToPosition(REFTIME rt,BOOL bFlushData)
{
	return m_pImpl->SeekToPosition(rt,bFlushData);
}

BOOL CMediaPlayer::GetVolume(long &vol)
{
	return m_pImpl->GetVolume(vol);
}

BOOL CMediaPlayer::SetVolume(long vol)
{
	return m_pImpl->SetVolume(vol);
}


BOOL CMediaPlayer::IsMute(void) const
{
	return m_pImpl->IsMute();
}

BOOL CMediaPlayer::Mute(BOOL bMute)
{
	return m_pImpl->Mute(bMute);
}


const CString& CMediaPlayer::GetFilePath(void) const
{
	return m_pImpl->GetFilePath();
}

void CMediaPlayer::RepositionVideoWnd(void)
{
	return m_pImpl->RepositionVideoWnd();
}

DWORD CMediaPlayer::GetSampleTick(void) const
{
	return m_pImpl->GetSampleTick();
}

BOOL CMediaPlayer::GetSample(CStaticBuffer &buf,CSize &sizeOfSample)
{
	return m_pImpl->GetSample(buf,sizeOfSample);
}

BOOL CMediaPlayer::SampleRef(BOOL bRef)
{
	return m_pImpl->SampleRef(bRef);
}