#pragma once

class AudioCaptureImpl;
class CAudioCapture
{
public:
	class Callback
	{
	public:
		virtual void onAudioData(LPCVOID data,int len) = 0;
	};


public:
	CAudioCapture(Callback *cb);
	~CAudioCapture(void);

	BOOL ok(void) const;
	BOOL init(int channels,int bitsPerSample,int samplesPerSec,int blockSize,LPCTSTR deviceName=NULL);
	void free(void);

private:
	AudioCaptureImpl *m_pImpl;
};
