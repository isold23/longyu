#pragma once
#include "mthelp.h"
#include "Muxing.h" 
 
class CMediaFileWriter
{
public:
	CMediaFileWriter(void);
	~CMediaFileWriter(void);

	int GetAudioFrameSize(void);
	BOOL IsRunning(void);

	BOOL Begin(LPCTSTR pcszFilePath,CSize size,int vBitrate,int vFps,int aSampleRate,int aBitrate);
	BOOL WriteVideo(LPCVOID data);
	BOOL WriteAudio(LPCVOID data,int len);
	BOOL End();

private:
	Muxing m_muxing;
	DWORD m_dwTickStart;

	CCriticalSection m_cs;
};

