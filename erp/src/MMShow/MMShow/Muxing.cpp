#include "stdafx.h"
#include <afxmt.h>
#include "muxing.h"


#include "MediaFormatDef.h"




extern "C"
{
 
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

 
#pragma comment(lib,"libgcc.a")
#pragma comment(lib,"libbz2.a") 
#pragma comment(lib,"libmingwex.a")
#pragma comment(lib,"libz.a")

#pragma comment(lib,"libavcodec.a")
#pragma comment(lib,"libswscale.a")
#pragma comment(lib,"libavutil.a")
#pragma comment(lib,"libavformat.a")

}


/*
	*------------***************************------------*
		  *--------------*Muxing*------------*
	*------------***************************------------*
*/

struct muxing_global_init { 
	muxing_global_init(void) { 
		av_register_all();
	}
} muxing_global_init_x;


#define DEF_VOPIX_FORMAT PIX_FMT_YUV420P

static inline int64_t streamTime(unsigned long tick,AVStream *st)
{
	return ((int64_t)tick*st->time_base.den)/(1000*st->time_base.num); 
}


Muxing::Muxing(void)
{
	memset(this,0,sizeof(Muxing));
}

Muxing::~Muxing(void)
{
	if (oc_ != NULL)
		end();
}



int Muxing::audioFrameSize(void) const 
{
	AVCodecContext *c = aStream_->codec;
	return c->frame_size*def_aoBytePerSampel*c->channels;
}


bool Muxing::addAudioStream(AVFormatContext *oc,int aSampleRate,int aBitrate)
{
	CodecID codecId = oc->oformat->audio_codec;
	AVCodec *codec = avcodec_find_encoder(codecId);
	if (!codec) 
		return false;

	aStream_ = avformat_new_stream(oc, codec);
	if (aStream_ == NULL) 
		return false;

	aStream_->id = 1;

	AVCodecContext *c = aStream_->codec;
	c->codec = codec;
	c->codec_id = codecId;
	c->sample_fmt  = def_ffmpegAudioFomrat;
	c->sample_rate = aSampleRate;
	c->bit_rate    = aBitrate;
	c->bit_rate_tolerance = c->bit_rate*50;
	c->channels    = def_aoChannels;

	if (oc->oformat->flags & AVFMT_GLOBALHEADER)
		c->flags |= CODEC_FLAG_GLOBAL_HEADER;
	return true;
}
 
bool Muxing::openAudio(void)
{
	return (avcodec_open2(aStream_->codec, NULL, NULL) >= 0); 
}

bool Muxing::writeAudioFrame(unsigned long tick,unsigned char *buffer,int len)
{
	AVPacket pkt = { 0 }; 
	AVFrame *frame = avcodec_alloc_frame();

	av_init_packet(&pkt);
	AVCodecContext *c = aStream_->codec;

	frame->nb_samples = c->frame_size;
	
	avcodec_fill_audio_frame(frame,c->channels,c->sample_fmt,(uint8_t*)buffer,len,1);

	int got_packet;
	avcodec_encode_audio2(c, &pkt, frame, &got_packet);
	if (!got_packet) 
	{
		av_free(frame);
		return false;
	}
	pkt.stream_index = aStream_->index;
	return (av_interleaved_write_frame(oc_, &pkt) >= 0);
}

void Muxing::closeAudio(void)
{

} 

bool Muxing::addVideoStream(AVFormatContext *oc,CSize vSize,int vBitrate,int vFps)
{
	CodecID codecId = oc->oformat->video_codec;
	AVCodec *codec = avcodec_find_encoder(codecId);
	if (!codec)
		return false;

	vStream_ = avformat_new_stream(oc, codec);
	if (!vStream_)
		return false;

	AVCodecContext *c = vStream_->codec;
	avcodec_get_context_defaults3(c, codec);
	
	c->codec = codec;
	c->codec_id = codecId;
	c->bit_rate = vBitrate;
	c->bit_rate_tolerance = c->bit_rate*50;
	c->width    = vSize.cx;
	c->height   = vSize.cy;
	c->time_base.den = vFps;
	c->time_base.num = 1;
	c->gop_size      = 12; 
	c->pix_fmt       = DEF_VOPIX_FORMAT;
	if (c->codec_id == CODEC_ID_MPEG2VIDEO) {
		c->max_b_frames = 2;
	}
	if (c->codec_id == CODEC_ID_MPEG1VIDEO)
		c->mb_decision = 2;

	if (oc->oformat->flags & AVFMT_GLOBALHEADER)
		c->flags |= CODEC_FLAG_GLOBAL_HEADER;

	return true;
}
static int s_srcEncSliceOffset = 0; 
static int s_srcEncStride[def_ffmpegMaxPlans] = {0,0,0,0};
static const unsigned char* s_srcEncSlice[def_ffmpegMaxPlans] = {0};
 
bool Muxing::openVideo(void)
{
	AVCodecContext *c = vStream_->codec;
	if (avcodec_open2(c, NULL, NULL) < 0)
		return false;

	vCvt_.opic = avcodec_alloc_frame();
	avpicture_alloc((AVPicture*)vCvt_.opic,DEF_VOPIX_FORMAT,c->width,c->height);

	vCvt_.obufferSize = 10*1024*1024;
	vCvt_.obuffer = (unsigned char*)av_malloc(vCvt_.obufferSize);
 	
	vCvt_.ctx = sws_getContext(c->width,c->height,def_ffmpegPixFormat,c->width,
		c->height,c->pix_fmt,SWS_POINT, NULL, NULL, NULL);

	s_srcEncStride[0] = -c->width*def_vBytesPerPixel;
	s_srcEncSliceOffset = c->width*(c->height-1)*def_vBytesPerPixel;
	return true;
} 

bool Muxing::writeVideoFrame(unsigned long tick,const void *buffer)
{
	AVCodecContext *c = vStream_->codec;

	s_srcEncSlice[0] = (const unsigned char*)buffer+s_srcEncSliceOffset;
	sws_scale(vCvt_.ctx, s_srcEncSlice, s_srcEncStride,0,c->height, vCvt_.opic->data, vCvt_.opic->linesize);

	int out = avcodec_encode_video(c,vCvt_.obuffer,vCvt_.obufferSize,vCvt_.opic); 
	if (out < 0) 
		return false;
	if (out == 0)
	{
		vCvt_.opic->pts++;
		return true;
	}

	AVPacket pkt;
	av_init_packet(&pkt);

	if (c->coded_frame->pts != AV_NOPTS_VALUE)
		pkt.pts = streamTime(tick,vStream_);					
	if (c->coded_frame->key_frame)
		pkt.flags |= AV_PKT_FLAG_KEY;

	pkt.stream_index = vStream_->index;
	pkt.data         = vCvt_.obuffer;
	pkt.size         = out;

	if (av_interleaved_write_frame(oc_,&pkt) < 0)
		return false;

	vCvt_.opic->pts++;
	return true;
}

void Muxing::closeVideo(void)
{
	if (vStream_ != NULL)
	{
		avcodec_close(vStream_->codec);
		
		av_free(vCvt_.obuffer);
		
		avpicture_free((AVPicture*)vCvt_.opic);
		av_free(vCvt_.opic);

		sws_freeContext(vCvt_.ctx);

		memset(&vCvt_,0,sizeof(VSwsContext));
 	}
}

 
 
bool Muxing::prepare(const char *ofile,CSize vSize,int vBitrate,int vFps,int aSampleRate,int aBitrate)
{ 
	AVFormatContext *oc;
	avformat_alloc_output_context2(&oc, NULL, NULL, ofile);
	if (oc == NULL) 
		return false;

	AVOutputFormat *fmt = oc->oformat;
	if (fmt->flags & AVFMT_NOFILE) {
		avformat_free_context(oc);
		return false;
	}



	/*if (fmt->video_codec = CODEC_ID_MPEG1VIDEO) */
	{
		addVideoStream(oc,vSize,vBitrate,vFps);
		openVideo();
	}

	/*if (fmt->audio_codec = CODEC_ID_MP2)*/
	if (aSampleRate != 0)
	{
		addAudioStream(oc,aSampleRate,aBitrate);
		openAudio();
	}

	av_dump_format(oc, 0, ofile, 1);

	bool ret = !avio_open(&oc->pb, ofile, AVIO_FLAG_WRITE) && !avformat_write_header(oc, NULL); 
	if (ret)
	{
		vCvt_.opic->pts = 0;
		oc_ = oc;
	}
	else 
	{
		avformat_free_context(oc);
		cleanup(oc);
	}
	return ret;
}

bool Muxing::cleanup(AVFormatContext *oc)
{
	closeVideo();
	closeAudio();

	aStream_ = NULL;
	vStream_ = NULL;

	for (unsigned i = 0; i < oc->nb_streams; i++) {
		av_freep(&oc->streams[i]->codec);
		av_freep(&oc->streams[i]);
	}

	if (!(oc->oformat->flags & AVFMT_NOFILE))
		avio_close(oc->pb);

	av_free(oc);

	return true;
}


bool Muxing::end(void)
{
	av_write_trailer(oc_);
	cleanup(oc_);
	oc_ = NULL;
	return true;
}
 


/*
	*------------***************************------------*
		  *--------------*scaleImage*------------*
	*------------***************************------------*
*/
class SwsContextCache : public CCriticalSection 
{
public:
	SwsContextCache(void) 
	{
		memset(this,0,sizeof(this));
	}
	~SwsContextCache(void) 
	{
		if (ctx_ != NULL)
			sws_freeContext(ctx_);
	}


	SwsContext* ctx(int cxSrc,int cySrc,int cxDst,int cyDst) 
	{
		if (cxSrc!=cxSrc_ || cySrc!=cySrc_ || cxDst!=cxDst_ || cySrc!=cyDst_) 
		{
			if (ctx_ != NULL)
				sws_freeContext(ctx_);
			ctx_ = sws_getContext(cxSrc,cySrc,def_ffmpegPixFormat,cxDst,cyDst,
				def_ffmpegPixFormat,SWS_FAST_BILINEAR, NULL, NULL, NULL);
			cxSrc_ = cxSrc; cySrc_ = cySrc; cxDst_ = cxDst; cyDst_ = cyDst;
		}
		return ctx_;
	}

	int s_srcStride[def_ffmpegMaxPlans];
	int s_dstStride[def_ffmpegMaxPlans];
	unsigned char* s_srcSlice[def_ffmpegMaxPlans];
	unsigned char* s_dstSlice[def_ffmpegMaxPlans];

private:
	int cxSrc_,cySrc_;
	int cxDst_,cyDst_;
	SwsContext *ctx_;
};

/*
	*------------***************************------------*
		  *--------------*scaleImage*------------*
	*------------***************************------------*
*/	
void scaleImage(int cxSrc,int cySrc,int cxDst,int cyDst,const void *src,int stride,void *dst)
{
	static SwsContextCache s_scc;
 
	s_scc.Lock();

	s_scc.s_srcStride[0] = stride;
	s_scc.s_dstStride[0] = cxDst*def_vBytesPerPixel;
	s_scc.s_dstSlice[0] = (unsigned char*)dst;
	s_scc.s_srcSlice[0] = (unsigned char*)src+ (stride>0 ? 0: (1-cySrc)*stride);

	SwsContext* sc = s_scc.ctx(cxSrc,cySrc,cxDst,cyDst);
	sws_scale(sc,s_scc.s_srcSlice,s_scc.s_srcStride,0,cySrc,s_scc.s_dstSlice,s_scc.s_dstStride);

	s_scc.Unlock();
}

