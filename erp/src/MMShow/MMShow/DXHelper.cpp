#include "StdAfx.h"
#include "DXHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void RemoveGraphFromRot(DWORD pdwRegister)
{
	CComPtr<IRunningObjectTable> pROT;
	if (SUCCEEDED(GetRunningObjectTable(0, &pROT)))
		pROT->Revoke(pdwRegister);
}

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister)
{
	USES_CONVERSION;

	CComPtr<IRunningObjectTable> pROT;
	if (FAILED(GetRunningObjectTable(0, &pROT)))
		return E_FAIL;

	TCHAR str[128];
	wsprintf(str,_T("FilterGraph %08x pid %08x"),(DWORD_PTR)pUnkGraph,GetCurrentProcessId());

	CComPtr<IMoniker> pMoniker;
	HRESULT hr = CreateItemMoniker(L"!", T2CW(str), &pMoniker);
	if (FAILED(hr))
		return hr;
	
	DWORD dwTmpRegister;
	if (pdwRegister == NULL)
		pdwRegister = &dwTmpRegister;
	return pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE,pUnkGraph,pMoniker, pdwRegister);
}

HRESULT FindPin(IBaseFilter *pFilter, PIN_DIRECTION pinDir, IPin **ppPin)
{
	CComPtr<IPin> pPin;
	CComPtr<IEnumPins> pEnum;

	pFilter->EnumPins(&pEnum);
	while(pEnum->Next(1, &pPin, 0) == S_OK)
	{
		PIN_DIRECTION dir;
		pPin->QueryDirection(&dir);
		if (dir == pinDir)
		{
			*ppPin = pPin.Detach();
			return S_OK;
		}
		pPin = NULL;
	}
	return E_FAIL;  
}

BOOL RenderFilter(IGraphBuilder *pGraph,IBaseFilter *pFilter)
{
	CComPtr<IPin> pPin;
	CComPtr<IEnumPins> pEnum;
	pFilter->EnumPins(&pEnum);
	while(pEnum->Next(1, &pPin, 0) == S_OK)
	{
		PIN_DIRECTION dir;
		pPin->QueryDirection(&dir);
		if (dir == PINDIR_OUTPUT)
		{
			CComPtr<IPin> pNextPin;
			pPin->ConnectedTo(&pNextPin);
			if (pNextPin == NULL)
			{
				pGraph->Render(pPin);
				return TRUE;
			}
		}
		pPin = NULL;
	}
	return FALSE;
}
/*	_________________				|	_________________			__________________			
	|				|---->pin		|	|				|			|				 |---->pin				
	| source filter |				|	| source filter |----pin--->| splitter filter|		
	|ooooooooooooooo|---->pin		|	|ooooooooooooooo|			|oooooooooooooooo|---->pin				
									|						
*/
BOOL RenderSourceFilter(IGraphBuilder *pGraph,IBaseFilter *pSrcFilter,IPin *pSrcPin)
{
	if (RenderFilter(pGraph,pSrcFilter))
		return TRUE;
	
	CComPtr<IPin> pNextPin;
	if (FAILED(pSrcPin->ConnectedTo(&pNextPin)))
		return E_FAIL;

	PIN_INFO pinInfo;
	if (FAILED(pNextPin->QueryPinInfo(&pinInfo)))
		return E_FAIL;

	if (pinInfo.pFilter == NULL)
		return FALSE;

	CComPtr<IBaseFilter> pnFilter;
	pnFilter.Attach(pinInfo.pFilter);

	return RenderFilter(pGraph,pnFilter);
}

HRESULT ConnectFilters(IGraphBuilder *pGraph,IBaseFilter *pFirst,
	IBaseFilter *pSecond,IPin **ppFirstPin,IPin **ppSecondPin)
{

	CComPtr<IPin> pSecondPin;
	HRESULT hr = FindPin(pSecond,PINDIR_INPUT,&pSecondPin);
	if (FAILED(hr)) return hr;
	
	CComPtr<IPin> pFirstPin;
	CComPtr<IEnumPins> pEnum;
	pFirst->EnumPins(&pEnum);
	while(pEnum->Next(1, &pFirstPin, 0) == S_OK)
	{
		PIN_DIRECTION pinDir;
		pFirstPin->QueryDirection(&pinDir);
		if (pinDir==PINDIR_OUTPUT && SUCCEEDED(pGraph->Connect(pFirstPin, pSecondPin)))
		{
			if (ppFirstPin != NULL)
				*ppFirstPin = pFirstPin.Detach();
			if (ppSecondPin != NULL)
				*ppSecondPin = pSecondPin.Detach();
			return S_OK;
		}
		pFirstPin = NULL;
	}
	return E_FAIL;
}
