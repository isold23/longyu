#pragma once

#define def_vBitsPerPixel 32
#define def_vBytesPerPixel (def_vBitsPerPixel/8)

//#define def_voBitrate		(512*1000)
//#define def_voFps			25

#define def_ffmpegPixFormat PIX_FMT_RGB32
#define def_ffmpegMaxPlans 4

#define def_dxMediaSubType MEDIASUBTYPE_RGB32

#define def_gplusPixFormat PixelFormat32bppRGB


//#define def_aoBitrate		(64*1000)
//#define def_aoSampleRate	44100
#define def_aoChannels		2
#define def_aoBitPerSample	16
#define def_aoBytePerSampel	(def_aoBitPerSample/8)

#define def_ffmpegAudioFomrat AV_SAMPLE_FMT_S16

#define def_dxTexFmt D3DFMT_X8R8G8B8
#define def_dxRenderTargetWidth 500
#define def_dxRenderTargetHeight 420
#define def_dxRenderTexWidth 2048
#define def_dxRenderTexHeight 2048
#define def_gpRenderTextureWidth 1920
#define def_gpRenderTextureHeight 1080
