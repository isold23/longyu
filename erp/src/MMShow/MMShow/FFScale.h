#pragma once

//Scale算法
enum SwsAlogrithm
{
	SWS_SA_FAST_BILINEAR    = 0x1,
	SWS_SA_BILINEAR            = 0x2,
	SWS_SA_BICUBIC            = 0x4,
	SWS_SA_X                = 0x8,
	SWS_SA_POINT            = 0x10,
	SWS_SA_AREA                = 0x20,
	SWS_SA_BICUBLIN            = 0x40,
	SWS_SA_GAUSS            = 0x80,
	SWS_SA_SINC                = 0x100,
	SWS_SA_LANCZOS            = 0x200,
	SWS_SA_SPLINE            = 0x400,
};

//视频图像格式
enum PicFormat
{
	SWS_PF_NONE            = PIX_FMT_NONE,
	SWS_PF_YUV420P        = PIX_FMT_YUV420P,
	SWS_PF_RGB24        = PIX_FMT_RGB24,
	SWS_PF_BGR24        = PIX_FMT_BGR24,
	SWS_PF_ARGB            = PIX_FMT_ARGB,
	SWS_PF_RGBA            = PIX_FMT_RGBA,
	SWS_PF_ABGR            = PIX_FMT_ABGR,
	SWS_PF_BGRA            = PIX_FMT_BGRA,
};


class CFFScale
{
public:
	CFFScale(void);
	~CFFScale(void);

	//设置输入输出图片属性以及Scale算法
	void SetAttribute(PicFormat srcFormat, PicFormat dstFormat, SwsAlogrithm enAlogrithm = SWS_SA_FAST_BILINEAR);

	//Scale
	BOOL Scale(
		byte *pSrc, int nSrcW, int nSrcH, int nSrcPicth,
		byte *pDst, int nDstW, int nDstH, int nDstPicth
		);

private:

	//初始化
	BOOL Init();

	//反初始化
	void DeInit();

	SwsContext*    m_pSwsContext;        //SWS对象
	PicFormat m_srcFormat;            //源像素格式
	PicFormat m_dstFormat;            //目标像素格式
	SwsAlogrithm m_enAlogrithm;        //Resize算法

	int m_nSrcW, m_nSrcH;            //源图像宽高
	int m_nSrcPicth;                //源图像第一行数据的长度
	int m_nSrcSlice[4];                //源图像各分量数据起始地址偏移
	int m_nSrcStride[4];            //源图像各分量一行数据的长度

	int m_nDstW, m_nDstH;            //目标图像宽高
	int m_nDstPicth;                //目标图像第一行数据的长度
	int m_nDstSlice[4];                //目标图像各分量数据起始地址偏移
	int m_nDstStride[4];            //目标图像各分量一行数据的长度

};