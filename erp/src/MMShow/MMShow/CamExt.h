#pragma once

#include "ArrayAdaptor.h"
#include "SimpleBuffer.h"


class CCamExt;
class CamExtImpl;

class CCamSampleListener
{
public:
	virtual void OnSample(CCamExt *pCamExt){};
};

class CCamExt 
{
public:
	CCamExt(LPCTSTR pcszCamName=NULL,LPCTSTR pcszDisplayName=NULL);
	~CCamExt(void);

	void SetCapture(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify);
	void SetPreview(HWND hWnd,CCamSampleListener *pListener,BOOL bNotify);

	BOOL Start(void);
	BOOL Stop(void);

	LPCTSTR GetName(void) const;
	LPCTSTR GetDisplayName(void) const;

	BOOL SampleRef(BOOL bRef);
	DWORD GetSampleTick(void) const;
	BOOL GetSample(CStaticBuffer &buf,CSize &sizeOfSample);

private:
	CamExtImpl *m_pImpl;
};