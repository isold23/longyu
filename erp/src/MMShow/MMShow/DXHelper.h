#pragma once
#include <streams.h>

void RemoveGraphFromRot(DWORD pdwRegister);
HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);

HRESULT FindPin(IBaseFilter *pFilter, PIN_DIRECTION pinDir, IPin **ppPin);
BOOL RenderFilter(IGraphBuilder *pGraph,IBaseFilter *pFilter);
BOOL RenderSourceFilter(IGraphBuilder *pGraph,IBaseFilter *pSrcFilter,IPin *pSrcPin);
HRESULT ConnectFilters(IGraphBuilder *pGraph,IBaseFilter *pFirst,IBaseFilter *pSecond,
					  IPin **ppFirstPin=NULL,IPin **ppSecondPin=NULL);