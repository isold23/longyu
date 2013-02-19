#include "stdafx.h"
#include "MediaFileWriter.h"
#include "DrawHelper.h"
#include "MediaFormatDef.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMediaFileWriter::CMediaFileWriter(void)
{

}

CMediaFileWriter::~CMediaFileWriter(void)
{

}



BOOL CMediaFileWriter::Begin(LPCTSTR pcszFilePath,CSize size,int vBitrate,int vFps,int aSampleRate,int aBitrate)
{
	USES_CONVERSION;
	CGuard g(m_cs);
	if (m_muxing.running())
		return FALSE;

	m_dwTickStart = GetTickCount();
	return m_muxing.prepare(T2A(pcszFilePath),size,vBitrate,vFps,aSampleRate,aBitrate);
}

 

BOOL CMediaFileWriter::WriteVideo(LPCVOID data)
{//return TRUE;
	CGuard g(m_cs);
	if (!m_muxing.running())
		return FALSE;

	unsigned long tick = GetTickCount() - m_dwTickStart;
	m_muxing.writeVideoFrame(tick,data);
	return TRUE;
}

BOOL CMediaFileWriter::WriteAudio(LPCVOID data,int len)
{		//return TRUE;
	CGuard g(m_cs);
	if (!m_muxing.running())
		return FALSE;

	unsigned long tick = GetTickCount() - m_dwTickStart;
	m_muxing.writeAudioFrame(tick,(unsigned char*)data,len);
	return TRUE;
}

BOOL CMediaFileWriter::End(void)
{
	CGuard g(m_cs);
	if (!m_muxing.running())
		return FALSE;
	return m_muxing.end();
}

BOOL CMediaFileWriter::IsRunning(void) 
{
	return m_muxing.running();
}

int CMediaFileWriter::GetAudioFrameSize(void) 
{
	CGuard g(m_cs);
	return m_muxing.audioFrameSize();
}
