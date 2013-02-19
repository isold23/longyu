#include "stdafx.h"
#include "MediaWriter.h"
#include "DrawHelper.h"

class CGuard
{
public:
	CGuard(CCriticalSection &cs)
		:m_cs(cs) {
		m_cs.Lock();
	}

	~CGuard(void) {
		m_cs.Unlock();
	}

private:
	CCriticalSection &m_cs;
};


CMediaWriter::CMediaWriter(void)
{

}

CMediaWriter::~CMediaWriter(void)
{

}



BOOL CMediaWriter::Begin(LPCTSTR pcszFilePath)
{
	USES_CONVERSION;
	CGuard g(m_cs);
	if (m_muxing.running())
		return FALSE;

	Muxing::Context ctx;
	strncpy(ctx.ofile,T2CA(pcszFilePath),sizeof(ctx.ofile));
	m_dwTickStart = GetTickCount();
	return m_muxing.prepare(ctx);
}

static inline int vfmt(PixelFormat fmt)
{
	switch (fmt)
	{
	case PixelFormat24bppRGB:
		return Muxing::rgb24;
	case PixelFormat32bppRGB:
	case PixelFormat32bppARGB:
	case PixelFormat32bppPARGB:
		return Muxing::rgb32;
	default:
		ASSERT(false);
		return 0;
	}
}

BOOL CMediaWriter::WriteVideo(Bitmap *pBitmap,const RectF &rcSource)
{
	TcCode();
	CGuard g(m_cs);
	if (!m_muxing.running())
		return FALSE;

	BitmapData data;
	PixelFormat fmt = pBitmap->GetPixelFormat();
	Rect rc((int)rcSource.X,(int)rcSource.Y,(int)rcSource.Width,(int)rcSource.Height);

	unsigned long tick = GetTickCount() - m_dwTickStart;
	Muxing::VFrameContext vfc;
	vfc.fmt = vfmt(fmt);
	vfc.w = pBitmap->GetWidth();
	vfc.h = pBitmap->GetHeight();
	vfc.x = rc.X;
	vfc.y = rc.Y;
	vfc.cx = rc.Width;
	vfc.cy = rc.Height;

	pBitmap->LockBits(&rc,ImageLockModeRead,fmt,&data);
	vfc.stride = data.Stride;
	m_muxing.writeVideoFrame(tick,vfc,data.Scan0);
	pBitmap->UnlockBits(&data);
	return TRUE;
}

BOOL CMediaWriter::WriteAudio(LPCVOID data,int len)
{		
	TcCode();
	CGuard g(m_cs);
	if (!m_muxing.running())
		return FALSE;

	unsigned long tick = GetTickCount() - m_dwTickStart;
	m_muxing.writeAudioFrame(tick,(unsigned char*)data,len);
	return TRUE;
}

BOOL CMediaWriter::End(void)
{	
	TcCode();
	CGuard g(m_cs);
	if (!m_muxing.running())
		return FALSE;
	return m_muxing.end();
}

BOOL CMediaWriter::IsRunning(void) 
{
	CGuard g(m_cs);
	return m_muxing.running();
}

int CMediaWriter::GetAudioFrameSize(void) 
{
	CGuard g(m_cs);
	return m_muxing.audioFrameSize();
}
