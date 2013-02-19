
/***************************************************************************************************************************
版本声明：	北京新浪信息技术有限责任公司
文件名：	MediaInfo.cpp
创建人：	张亚伟
创建日期：	2007-02-07
版本号：	1.00.000
说明：		音视频数据包实现
*****************************************************************************************************************************/
#include "StandardSerialize.h"
#include "MediaInfo.h"

/*********************************************************************************************/
//麦的音频配置信息
/*********************************************************************************************/
int STRU_AUDIO_CONFIG::Serialize(CStandardSerialize & aoStandardSerialize)
{

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mlSamplesPerSec);
		aoStandardSerialize.Serialize(mwKBitsPerSec);
		aoStandardSerialize.Serialize(mbyChannels);
		aoStandardSerialize.Serialize(mbyBitsPerSample);
		return 1;
}

/*********************************************************************************************/
//麦的视频配置信息
/*********************************************************************************************/
int STRU_VIDEO_CONFIG::Serialize(CStandardSerialize & aoStandardSerialize)
{	

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mbySizeType);
		aoStandardSerialize.Serialize(mdwBandWidth);
		aoStandardSerialize.Serialize(mbyFramePerSecond);
		return 1;
}

//*/
/*********************************************************************************************/
//发言人的视频信息
/*********************************************************************************************/
int STRU_VIDEO_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mbyFramePerSecond);

		aoStandardSerialize.Serialize(mwFrameWidth);
		aoStandardSerialize.Serialize(mwFrameHeight);
		aoStandardSerialize.Serialize(mwBitCount);
		aoStandardSerialize.Serialize(mulChannelID);
		return 1;

}

/*********************************************************************************************/
//发言人的视频信息
/*********************************************************************************************/
int STRU_AUDIO_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mlSamplesPerSec);
		aoStandardSerialize.Serialize(mwKBitsPerSec);
		aoStandardSerialize.Serialize(mbyChannels);
		aoStandardSerialize.Serialize(mbyBitsPerSample);
		aoStandardSerialize.Serialize(mulChannelID);
		return 1;
}
