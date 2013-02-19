#include "StdAfx.h"
#include "Devices.h"
#include <DShow.h>
#include <qedit.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CStringArray CDevices::m_mics;

CStringArray CDevices::m_videInputDevices;
CStringArray CDevices::m_videInputDeviceNames;

CStringArray CDevices::m_videOutputDevices;
CStringArray CDevices::m_videOutputDeviceNames;

static BOOL GetAllWaveInMicDevice(CStringArray &mics)
{
	WAVEINCAPS caps;
	for (UINT i=0,cnt=waveInGetNumDevs(); i<cnt; ++i)
	{
		memset(&caps,0,sizeof(WAVEINCAPS));
	 	if (waveInGetDevCaps(i,&caps,sizeof(WAVEINCAPSA)) == MMSYSERR_NOERROR)
			mics.Add(caps.szPname);
	}
	return !!mics.GetCount();
}


static HRESULT GetAllVideoDevices(CStringArray &devices,CStringArray &names,BOOL bInput)
{
	USES_CONVERSION;

	HRESULT hr;
	CComPtr <ICreateDevEnum> pDevEnum;
	hr = pDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum,NULL,CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
		return hr;

	CComPtr<IEnumMoniker> pClassEnum;
	REFCLSID guid = bInput ? CLSID_VideoInputDeviceCategory : CLSID_TransmitCategory;
	hr = pDevEnum->CreateClassEnumerator(guid,&pClassEnum,0);
	if (FAILED(hr))
		return hr;

	if (pClassEnum == NULL)
		return E_FAIL;

	ULONG cFetched;
	CComPtr<IMoniker> pMoniker;
	CComPtr<IMalloc> pMalloc;
	CoGetMalloc(1,&pMalloc);
	while (SUCCEEDED(pClassEnum->Next (1, &pMoniker, &cFetched)))
	{
		if (pMoniker == NULL)
			break;

		//CComPtr<IBaseFilter> pSrc;	
		//hr = pMoniker->BindToObject(NULL,NULL,IID_IBaseFilter, (void**)&pSrc);
		//if (FAILED(hr)) return hr;

		LPOLESTR pszDisplayName;
		hr = pMoniker->GetDisplayName(NULL,NULL,&pszDisplayName);
		if (FAILED(hr)) return hr;
		devices.Add(W2CT(pszDisplayName));
		pMalloc->Free(pszDisplayName);

		CComPtr<IPropertyBag> pBag;
		hr = pMoniker->BindToStorage(0,0,IID_IPropertyBag, (void**)&pBag);
		if (FAILED(hr)) return hr;

		CComVariant varFriendName;
		pBag->Read(L"FriendlyName", &varFriendName, NULL);
		names.Add(varFriendName);

		pMoniker = NULL;
	}
	return E_FAIL;
}



HRESULT CDevices::FindVideoDevice(IBaseFilter **ppSrcFilter,LPCTSTR pcszDeviceName,BOOL bInput)
{
	USES_CONVERSION;

	HRESULT hr;
	CComPtr <ICreateDevEnum> pDevEnum;
	hr = pDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if (FAILED(hr))
		return hr;

	CComPtr<IEnumMoniker> pClassEnum;
	REFCLSID guid = (bInput ? CLSID_VideoInputDeviceCategory : CLSID_TransmitCategory);
	hr = pDevEnum->CreateClassEnumerator(guid,&pClassEnum,0);
	if (FAILED(hr))
		return hr;

	if (pClassEnum == NULL)
		return E_FAIL;

	ULONG cFetched;
	CComPtr<IMoniker> pMoniker;
	CComPtr<IMalloc> pMalloc;
	CoGetMalloc(1,&pMalloc);
	while (SUCCEEDED(pClassEnum->Next (1, &pMoniker, &cFetched)))
	{
		if (pMoniker == NULL)
			break;

		CComPtr<IBaseFilter> pSrc;	
		if (SUCCEEDED(pMoniker->BindToObject(NULL,NULL,IID_IBaseFilter, (void**)&pSrc)))
		{
			if (pcszDeviceName == NULL)
			{
				*ppSrcFilter = pSrc.Detach();
				return S_OK;
			}
			else 
			{
				LPOLESTR pszDisplayName;
				hr = pMoniker->GetDisplayName(NULL,NULL,&pszDisplayName);

				LPCWSTR pcwStr = T2CW(pcszDeviceName);
				if (wcscmp(pszDisplayName,pcwStr) == 0)
				{
					*ppSrcFilter = pSrc.Detach();
					return S_OK;
				}
				pMalloc->Free(pszDisplayName);
			}
		}

		pMoniker = NULL;
	}

	return E_FAIL;
}


BOOL CDevices::Load(void)
{
	BOOL bRet = GetAllWaveInMicDevice(m_mics);
	bRet = GetAllVideoDevices(m_videInputDevices,m_videInputDeviceNames,TRUE) && bRet;
	bRet = GetAllVideoDevices(m_videOutputDevices,m_videOutputDeviceNames,FALSE) && bRet;
	return bRet;
}
