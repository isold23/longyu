#include "stdafx.h"
#include "WindowRender.h"
#include <comdef.h>
#include <d3d9.h>
#include <GdiPlus.h>
#include "MediaFormatDef.h"

 
#pragma comment(lib,"d3d9.lib")

 
class Direct3D9
{
public:
	static IDirect3D9* Inst(void)
	{
		static IDirect3D9Ptr inst(Direct3DCreate9(D3D_SDK_VERSION));
		return inst;
	}
};


//////////////////////////////////////////////////////////////////////////
/////																 /////
//////////////////////////////////////////////////////////////////////////
class DxWindowRenderImpl 
{
public:
	struct CustomVertex
	{ 
		enum {Fvf = D3DFVF_XYZRHW|D3DFVF_TEX1};
		enum {PrimitiveType = D3DPT_TRIANGLESTRIP,VertexCount = 4,PrimitiveCount = 2};
		enum {VerticesBytes = VertexCount*sizeof(float)*6};

		float x, y, z, rhw;    
		float u,v;
	};

	friend void InitD3dpp(D3DPRESENT_PARAMETERS&,HWND);
public:

	DxWindowRenderImpl(void);
	~DxWindowRenderImpl(void);

	HRESULT Start(HWND targetWnd);

	BOOL IsStarted(void) const;
	void Stop(void);

	HRESULT Render(HWND *renderWnds,int cnt);

	HRESULT Fill(LPCVOID buf,CSize size,int stride);

protected:  
	void InitD3dpp(D3DPRESENT_PARAMETERS &d3dpp,HWND targetWnd);

	HRESULT InitResource(void);
	void InitVertices(void);

	HRESULT SetVertices(CSize sizeOfSrc);

	HRESULT Test(void);
	HRESULT Reset(void);

	IDirect3DDevice9Ptr device_;
	IDirect3DTexture9Ptr texture_;

	CSize sizeOfFilled_;

	HWND targetWnd_;
	IDirect3DVertexBuffer9Ptr vertexBuffer_;
	CustomVertex vertices_[CustomVertex::VertexCount];
};

 
//////////////////////////////////////////////////////////////////////////
/////																 /////
//////////////////////////////////////////////////////////////////////////

#define FAILED_RET_VIDEO_RENDER(x)  do{if (FAILED(hr=x)) return hr;} while(0)

DxWindowRenderImpl::DxWindowRenderImpl(void)
{ 
	sizeOfFilled_.cx = sizeOfFilled_.cy = 0;
}

DxWindowRenderImpl::~DxWindowRenderImpl(void)
{
	if (IsStarted())
		Stop(); 
}

void DxWindowRenderImpl::InitD3dpp(D3DPRESENT_PARAMETERS &d3dpp,HWND targetWnd)
{
	memset(&d3dpp,0,sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.hDeviceWindow = targetWnd;
	d3dpp.BackBufferWidth = def_dxRenderTargetWidth;
	d3dpp.BackBufferHeight = def_dxRenderTargetHeight; 
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; 
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
}


HRESULT DxWindowRenderImpl::Start(HWND targetWnd)
{
	InitVertices();

	D3DPRESENT_PARAMETERS d3dpp;
	InitD3dpp(d3dpp,targetWnd);
	targetWnd_ = targetWnd;

	
	HRESULT hr;
	FAILED_RET_VIDEO_RENDER(Direct3D9::Inst()->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
		NULL,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &device_));

	return InitResource();
}
   
void DxWindowRenderImpl::InitVertices(void)
{
	vertices_[0].x = 0.0f;
	vertices_[0].y = 0.0f;
	vertices_[0].z = 0.5f;
	vertices_[0].rhw = 1.0f;
	vertices_[0].u = 0.0f;

	vertices_[1].y = 0.0f;
	vertices_[1].z = 0.5f;
	vertices_[1].rhw = 1.0f;

	vertices_[2].x = 0.0f; 
	vertices_[2].z = 0.5f;
	vertices_[2].rhw = 1.0f;
	vertices_[2].u = 0.0f;
	vertices_[2].v = 0.0f;

	vertices_[3].z = 0.5f;
	vertices_[3].rhw = 1.0f;
	vertices_[3].v = 0.0f; 

	vertices_[1].x = (float)def_dxRenderTargetWidth; 
	vertices_[2].y = (float)def_dxRenderTargetHeight; 
	vertices_[3].x = (float)def_dxRenderTargetWidth;
	vertices_[3].y = (float)def_dxRenderTargetHeight;
}

HRESULT DxWindowRenderImpl::InitResource(void)
{
	HRESULT hr;

	FAILED_RET_VIDEO_RENDER(device_->CreateTexture(def_dxRenderTexWidth,def_dxRenderTexHeight,1,
		D3DUSAGE_DYNAMIC,def_dxTexFmt,D3DPOOL_DEFAULT,&texture_,NULL));

	FAILED_RET_VIDEO_RENDER(device_->CreateVertexBuffer(sizeof(vertices_),D3DUSAGE_WRITEONLY,CustomVertex::Fvf,
		D3DPOOL_MANAGED,&vertexBuffer_,NULL));

	return S_OK;
}

void DxWindowRenderImpl::Stop(void)
{  
	texture_ = NULL;
	device_ = NULL;
}

BOOL DxWindowRenderImpl::IsStarted(void) const
{
	return (device_ != NULL);
}


HRESULT DxWindowRenderImpl::Render(HWND *renderWnds,int cnt)
{
	if (cnt == 0) 
	{
		renderWnds = &targetWnd_;
		cnt = 1;
	}

	HRESULT hr;
	FAILED_RET_VIDEO_RENDER(Test());
 
	FAILED_RET_VIDEO_RENDER(device_->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0f,0));
	FAILED_RET_VIDEO_RENDER(device_->BeginScene());
	FAILED_RET_VIDEO_RENDER(device_->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR));
	FAILED_RET_VIDEO_RENDER(device_->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR));
	FAILED_RET_VIDEO_RENDER(device_->SetTexture(0,texture_));
	FAILED_RET_VIDEO_RENDER(device_->SetStreamSource( 0, vertexBuffer_,0,sizeof(CustomVertex)));
	FAILED_RET_VIDEO_RENDER(device_->SetFVF(CustomVertex::Fvf));
	FAILED_RET_VIDEO_RENDER(device_->DrawPrimitive((D3DPRIMITIVETYPE)CustomVertex::PrimitiveType, 0,CustomVertex::PrimitiveCount));
	FAILED_RET_VIDEO_RENDER(device_->SetTexture(0,0));	
	FAILED_RET_VIDEO_RENDER(device_->EndScene());
	
	for (int i=0; i<cnt; ++i)
		FAILED_RET_VIDEO_RENDER(device_->Present(NULL,NULL,renderWnds[i],NULL));
	
	return S_OK;
}
  

HRESULT DxWindowRenderImpl::Test(void)
{
	if (!IsStarted())
		return E_FAIL;

	HRESULT hr = device_->TestCooperativeLevel();
	if (hr == D3DERR_DEVICELOST) 
		return hr;

	if (hr == D3DERR_DEVICENOTRESET)
		return Reset();

	return hr;
}

 
HRESULT DxWindowRenderImpl::Reset(void)
{
	texture_ = NULL;
	vertexBuffer_ = NULL;
	sizeOfFilled_.cx = sizeOfFilled_.cy = 0;

	D3DPRESENT_PARAMETERS d3dpp;
	InitD3dpp(d3dpp,targetWnd_);

	HRESULT hr;
	FAILED_RET_VIDEO_RENDER(device_->Reset(&d3dpp));
	return InitResource();
}


HRESULT DxWindowRenderImpl::Fill(LPCVOID buf,CSize size,int stride)
{
	const char *src = (const char*)buf;
	if (stride < 0)
		src += stride*(1-size.cy);

	HRESULT hr;
	D3DLOCKED_RECT lockRect;
	
	int lineSize = size.cx*def_vBytesPerPixel;
	FAILED_RET_VIDEO_RENDER(texture_->LockRect(0,&lockRect,NULL,D3DLOCK_DISCARD));

	char *dest = (char*)lockRect.pBits;
	for (int i=0; i<size.cy; ++i)
	{
		memcpy(dest,src,lineSize);
		src += stride;
		dest += lockRect.Pitch;
	}

	FAILED_RET_VIDEO_RENDER(texture_->UnlockRect(0));
	return SetVertices(size);
}

HRESULT DxWindowRenderImpl::SetVertices(CSize sizeOfSrc)
{
	if (sizeOfFilled_.cx==sizeOfSrc.cx && sizeOfFilled_.cy==sizeOfSrc.cy)
	{
		return S_OK;
	}
	else
	{
		sizeOfFilled_ = sizeOfSrc;

		float u = (float)sizeOfSrc.cx/(float)def_dxRenderTexWidth;
		float v = (float)sizeOfSrc.cy/(float)def_dxRenderTexHeight;

		vertices_[0].v = vertices_[1].v = v;
		vertices_[1].u = vertices_[3].u = u;

		HRESULT hr;
		void *buf = NULL;
		FAILED_RET_VIDEO_RENDER(vertexBuffer_->Lock(0,CustomVertex::VerticesBytes,&buf,0));
		memcpy(buf,vertices_,CustomVertex::VerticesBytes);
		return vertexBuffer_->Unlock();
	}
}


//////////////////////////////////////////////////////////////////////////
/////																 /////
//////////////////////////////////////////////////////////////////////////
class GpWindowRenderImpl
{
public:
	GpWindowRenderImpl(void);
	~GpWindowRenderImpl(void);
	HRESULT Start(HWND targetWnd);
	BOOL IsStarted(void) const;
	void Stop(void);
	HRESULT Render(HWND *renderWnds=NULL,int cnt=0);
	HRESULT Fill(LPCVOID buf,CSize size,int stride);
private:
	HWND targetWnd_;
	CSize sizeOfFilled_;
	Gdiplus::Bitmap *texture_;
};
GpWindowRenderImpl::GpWindowRenderImpl(void)
	:targetWnd_(NULL),texture_(NULL)
{
}
GpWindowRenderImpl::~GpWindowRenderImpl(void)
{
	if (IsStarted())
		Stop();
}
HRESULT GpWindowRenderImpl::Start(HWND targetWnd)
{
	targetWnd_ = targetWnd;
	texture_ = new Gdiplus::Bitmap(def_gpRenderTextureWidth,def_gpRenderTextureHeight,def_gplusPixFormat);
	return S_OK;
}
BOOL GpWindowRenderImpl::IsStarted(void) const
{
	return (texture_ != NULL);
}
void GpWindowRenderImpl::Stop(void)
{
	delete texture_;
	texture_ = NULL;
	targetWnd_ = NULL;
}
HRESULT GpWindowRenderImpl::Render(HWND *renderWnds,int cnt)
{ 
	if (cnt == 0) 
	{
		renderWnds = &targetWnd_;
		cnt = 1;
	}
	for (int i=0; i<cnt; ++i)
	{
		RECT rc;
		::GetClientRect(renderWnds[i],&rc);
		HDC hDC = ::GetDC(renderWnds[i]);
		{
			Gdiplus::Graphics g(hDC);
			g.DrawImage(texture_,Gdiplus::RectF(0,0,rc.right,rc.bottom),0,0,sizeOfFilled_.cx,sizeOfFilled_.cy,Gdiplus::UnitPixel);
		}
		::ReleaseDC(renderWnds[i],hDC);
	}
	return S_OK;
}
HRESULT GpWindowRenderImpl::Fill(LPCVOID buf,CSize size,int stride)
{
	sizeOfFilled_ = size;
	Gdiplus::Rect rc(0,0,def_gpRenderTextureWidth,def_gpRenderTextureHeight);
	const char *src = (const char*)buf;
	stride = -stride;
	if (stride < 0) 
		src += stride*(1-size.cy);
	Gdiplus::BitmapData bd; 
	int lineSize = size.cx*def_vBytesPerPixel;
	texture_->LockBits(&rc,Gdiplus::ImageLockModeWrite,def_gplusPixFormat,&bd);
	char *dest = (char*)bd.Scan0;
	for (int i=0; i<size.cy; ++i)
	{
		memcpy(dest,src,lineSize);
		src += stride;
		dest += bd.Stride;
	}
	return -texture_->UnlockBits(&bd);
}
#if 1
	typedef DxWindowRenderImpl WindowRenderImpl;
#else
	typedef GpWindowRenderImpl WindowRenderImpl;
#endif
CWindowRender::CWindowRender(void)
{
	m_pImpl = new WindowRenderImpl();
}

CWindowRender::~CWindowRender(void)
{
	delete (WindowRenderImpl*)m_pImpl;
}

HRESULT CWindowRender::Start(HWND targetWnd)
{
	return ((WindowRenderImpl*)m_pImpl)->Start(targetWnd);
}

BOOL CWindowRender::IsStarted(void) const
{
	return ((WindowRenderImpl*)m_pImpl)->IsStarted();
}

void CWindowRender::Stop(void)
{
	((WindowRenderImpl*)m_pImpl)->Stop();
}

HRESULT CWindowRender::Render(HWND renderWnds[],int cnt)
{
	return ((WindowRenderImpl*)m_pImpl)->Render(renderWnds,cnt);
}

HRESULT CWindowRender::Fill(LPCVOID buf,CSize size,int stride)
{
	return ((WindowRenderImpl*)m_pImpl)->Fill(buf,size,stride);
}
