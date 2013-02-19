
extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <windows.h>
#include <GdiPlus.h>
#include "ImageProcess.h"
#include "MediaFormatDef.h"


class SwsContextCache 
{
public:
	SwsContextCache(void) 
	{
		memset(this,0,sizeof(this));
		InitializeCriticalSection(&cs_);
	}
	~SwsContextCache(void) 
	{
		if (ctx_ != NULL)
			sws_freeContext(ctx_);
		DeleteCriticalSection(&cs_);
	}

	void lock(void) 
	{
		EnterCriticalSection(&cs_);
	}
	void unlock(void) 
	{
		LeaveCriticalSection(&cs_);
	}

	SwsContext* ctx(int cx,int cy) 
	{
		if (cx!=cx_ || cy!=cy_) 
		{
			if (ctx_ != NULL)
				sws_freeContext(ctx_);
			ctx_ = sws_getContext(cx,cy,def_ffmpegPixFormat,def_voFrameWidth,def_voFrameHeight,
				def_ffmpegPixFormat,SWS_FAST_BILINEAR, NULL, NULL, NULL);
			cx_ = cx; cy_ = cy;
		}
		return ctx_;
	}

	int s_srcStride[def_ffmpegMaxPlans];
	int s_dstStride[def_ffmpegMaxPlans];
	unsigned char* s_srcSlice[def_ffmpegMaxPlans];
	unsigned char* s_dstSlice[def_ffmpegMaxPlans];

private:
	int cx_,cy_;
	SwsContext *ctx_;
	CRITICAL_SECTION cs_;
};

void scaleImage(int cx,int cy,const void *src,int stride,void *dst)
{
	static SwsContextCache s_scc;
	
	s_scc.lock();
	
	s_scc.s_srcStride[0] = stride;
	s_scc.s_dstStride[0] = def_voBytePerLine;
	s_scc.s_dstSlice[0] = (unsigned char*)dst;
	s_scc.s_srcSlice[0] = (unsigned char*)src+ (stride>0 ? 0: (1-cy)*stride);

	SwsContext* sc = s_scc.ctx(cx,cy);
	sws_scale(sc,s_scc.s_srcSlice,s_scc.s_srcStride,0,cy,s_scc.s_dstSlice,s_scc.s_dstStride);

	s_scc.unlock();
}

 