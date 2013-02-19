/****************************************************************************************************************************
版本声明：	北京新浪信息技术有限责任公司
文件名：	MediaInfo.h
创建人：	张亚伟
创建日期：	2007-02-06
版本号：	1.00.000
说明：		音视频数据包定义
*****************************************************************************************************************************/
#ifndef _MEDIA_INFO_H_
#define _MEDIA_INFO_H_

#include "StandardSerialize.h"

/*********************************************************************************************/
//麦的音频配置信息
/*********************************************************************************************/
struct	STRU_AUDIO_CONFIG
{
	uint8_t	mbyCodecType;				//使用的编解码类型
	int	mlSamplesPerSec;   				//采样频率
	//(8000/11025/12000/16000/22050/32000/44100(Hz))
	uint16_t    mwKBitsPerSec;        		//输出带宽(kbps)
	uint8_t    mbyChannels;				//声音通道数(1为单声道,2为立体声)
	uint8_t    mbyBitsPerSample;   		//采样大小(位)

	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//麦的视频配置信息
/*********************************************************************************************/
struct STRU_VIDEO_CONFIG
{
	uint8_t	mbyCodecType;				//视频编码类型
	uint8_t	mbySizeType;				//视频大小类型
	unsigned int	mdwBandWidth;				//视频占用带宽（单位kbits）
	uint8_t	mbyFramePerSecond;			//视频帧率（0为动态调整，1－15为实际设置帧率）	

	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//发言人的视频信息
/*********************************************************************************************/
class STRU_VIDEO_INFO
{
public:
	uint8_t	mbyCodecType;				//视频编码类型
	uint8_t	mbyFramePerSecond;			//视频帧率（0为动态调整，1－15为实际设置帧率）

	uint16_t	mwFrameWidth;				//图像宽度
	uint16_t	mwFrameHeight;				//图像高度
	uint16_t	mwBitCount;					//位图颜色深度
	unsigned int	mulChannelID;				//视频通道ID

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_VIDEO_INFO(){}
	~STRU_VIDEO_INFO(){}
	STRU_VIDEO_INFO(STRU_VIDEO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mbyFramePerSecond = info.mbyFramePerSecond;
			mwFrameWidth = info.mwFrameWidth;
			mwFrameHeight = info.mwFrameHeight;
			mwBitCount = info.mwBitCount;
			mulChannelID = info.mulChannelID;
		}
	}

	STRU_VIDEO_INFO& operator=(const STRU_VIDEO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mbyFramePerSecond = info.mbyFramePerSecond;
			mwFrameWidth = info.mwFrameWidth;
			mwFrameHeight = info.mwFrameHeight;
			mwBitCount = info.mwBitCount;
			mulChannelID = info.mulChannelID;
		}
		return *this;
	}
};

/*********************************************************************************************/
//发言人的视频信息
/*********************************************************************************************/
class STRU_AUDIO_INFO
{
public:
	uint8_t	mbyCodecType;				//使用的编解码类型
	int	mlSamplesPerSec;   				//采样频率
	//(8000/11025/12000/16000/22050/32000/44100(Hz))
	uint16_t    mwKBitsPerSec;        		//输出带宽(kbps)
	uint8_t    mbyChannels;				//声音通道数(1为单声道,2为立体声)
	uint8_t    mbyBitsPerSample;   		//采样大小(位)
	unsigned int	mulChannelID;				//音频通道ID

	STRU_AUDIO_INFO(){}
	~STRU_AUDIO_INFO(){}
	STRU_AUDIO_INFO(STRU_AUDIO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mlSamplesPerSec = info.mlSamplesPerSec;
			mwKBitsPerSec = info.mwKBitsPerSec;
			mbyChannels = info.mbyChannels;
			mbyBitsPerSample = info.mbyBitsPerSample;
			mulChannelID = info.mulChannelID;
		}
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_AUDIO_INFO& operator=(const STRU_AUDIO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mlSamplesPerSec = info.mlSamplesPerSec;
			mwKBitsPerSec = info.mwKBitsPerSec;
			mbyChannels = info.mbyChannels;
			mbyBitsPerSample = info.mbyBitsPerSample;
			mulChannelID = info.mulChannelID;
		}
		return *this;
	}
};
#endif //_MEDIA_INFO_H_
