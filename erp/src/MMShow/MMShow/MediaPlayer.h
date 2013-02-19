#pragma once

class CStaticBuffer;
class MediaPlayerImpl;
class CMediaPlayer
{
public:
	enum EMovieMode { MOVIE_NOTOPENED,MOVIE_OPENED,MOVIE_PLAYING,MOVIE_STOPPED,MOVIE_PAUSED};

public:
	CMediaPlayer(void);
	~CMediaPlayer(void);

	void SetRenderWnd(HWND hWnd);
	
	BOOL OpenMovie(const CString &strFilePath);
	void CloseMovie(void);

	BOOL PlayMovie(void);
	BOOL PauseMovie(void);
	BOOL StopMovie(void);

 	BOOL CanMovieFrameStep(void);
	BOOL FrameStepMovie(void);

	DOUBLE GetDuration(void);
	DOUBLE GetCurrentPosition(void);
	EMovieMode StatusMovie(void);

	BOOL SeekToPercent(DOUBLE &rtSeekBy);
	BOOL SeekOffset(DOUBLE &rtSeekBy);
	BOOL SeekToPosition(DOUBLE rt,BOOL bFlushData);

	BOOL GetVolume(long &vol);
	BOOL SetVolume(long vol);

	BOOL IsMute(void) const;
	BOOL Mute(BOOL bMute);

	const CString &GetFilePath(void) const;
	void RepositionVideoWnd(void);

	BOOL SampleRef(BOOL bRef);
	DWORD GetSampleTick(void) const;
	BOOL GetSample(CStaticBuffer &buf,CSize &sizeOfSample);

private:
	MediaPlayerImpl *m_pImpl;
};
