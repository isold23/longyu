#pragma once

#include "Muxing.h" 
#include <afxmt.h>

class CMediaWriter
{
public:
	enum  
	{
		DefvoBitrate = Muxing::def_voBitrate,
		DefvoFrameWidth = Muxing::def_voFrameWidth,
		DefvoFrameHeight = Muxing::def_voFrameHeight,
		DefvoFps = Muxing::def_voFps
	};
	enum 
	{
		DefaoBitrate = Muxing::def_aoBitrate,
		DefaoSampleRate = Muxing::def_aoSampleRate,
		DefaoChannels = Muxing::def_aoChannels,
		DefaoBitPerSample =  Muxing::def_aoBitPerSample
	};

public:
	CMediaWriter(void);
	~CMediaWriter(void);

	int GetAudioFrameSize(void);
	BOOL IsRunning(void);

	BOOL Begin(LPCTSTR pcszFilePath);
	BOOL WriteVideo(Bitmap *pBitmap,const RectF &rcSource);
	BOOL WriteAudio(LPCVOID data,int len);
	BOOL End();

private:
	Muxing m_muxing;
	DWORD m_dwTickStart;

	CCriticalSection m_cs;
};

