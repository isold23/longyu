#include "stdafx.h"
#include "AudioCapture.h"
#include <MMSystem.h>

#pragma comment(lib,"Winmm.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class AudioCaptureImpl
{
	class Buffer
	{
		static const int BlockCount = 100;

		class Block 
		{
		public:
			Block(void) {
				memset(this,0,sizeof(Block));
			}

			~Block(void) {
				if (mData != NULL)
					delete[] mData;
			}

			void alloc(int size) {
				if (mData != NULL)
					delete[] mData;

				mData = new char[size];
				mHdr.dwLoops = 1;
				mHdr.lpData = mData;
				mHdr.dwBufferLength = size;
				mHdr.dwFlags = WHDR_BEGINLOOP|WHDR_ENDLOOP;
			}

			WAVEHDR& hdr(void) {
				return mHdr;
			}

			char* data(void) {
				return mData;
			}

		public:
			WAVEHDR mHdr;
			char *mData;
		};

	public:
		Buffer(void);
		~Buffer(void);

		int blockCount(void) const;
		LPWAVEHDR block(int index); 
		void setBlockDataSize(int size);

	private:
		int mBlockDataSize;
		Block mBlocks[BlockCount];
	};

public:
	AudioCaptureImpl(CAudioCapture::Callback *cb);
	~AudioCaptureImpl(void);

	BOOL ok(void) const;
	BOOL init(int channels,int bitsPerSample,int samplesPerSec,int blockSize,LPCTSTR deviceName=NULL);
	void free(void);

private:
	static void CALLBACK waveInProc(HWAVEIN,UINT,DWORD,DWORD,DWORD);
	void onData(LPCVOID data,int len);

	HWAVEIN mWaveIn; 
	Buffer *mBuffer;
	CAudioCapture::Callback *mCallback;


};

inline BOOL AudioCaptureImpl::ok(void) const {
	return (mWaveIn != NULL);
}

inline void AudioCaptureImpl::onData(LPCVOID data,int len) {
	mCallback->onAudioData(data,len);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
AudioCaptureImpl::Buffer::Buffer(void)
	:mBlockDataSize(0)
{
}

AudioCaptureImpl::Buffer::~Buffer(void)
{
}


int AudioCaptureImpl::Buffer::blockCount(void) const
{
	return BlockCount;
}

LPWAVEHDR AudioCaptureImpl::Buffer::block(int index)
{
	return &mBlocks[index].hdr();
}

void AudioCaptureImpl::Buffer::setBlockDataSize(int size)
{
	if (mBlockDataSize != size)
		for (int i=0; i<BlockCount; ++i)
			mBlocks[i].alloc(size);
	mBlockDataSize = size;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
AudioCaptureImpl::AudioCaptureImpl(CAudioCapture::Callback *cb)
	:mWaveIn(NULL),
	 mCallback(cb),
	 mBuffer(NULL)
{
}

AudioCaptureImpl::~AudioCaptureImpl(void)
{
	if (ok())
		free();
}



void CALLBACK AudioCaptureImpl::waveInProc(HWAVEIN hwi,UINT msg,DWORD userData,DWORD param1,DWORD param2)
{
	AudioCaptureImpl *ac = (AudioCaptureImpl*)(DWORD_PTR)userData;

	switch (msg)
	{
	case WIM_DATA:
		{
			LPWAVEHDR hdr = (LPWAVEHDR)(DWORD_PTR)param1;

			if (hdr->dwFlags&WHDR_DONE && ac->ok())
			{
				ac->onData(hdr->lpData,hdr->dwBytesRecorded);
				if (ac->ok())
				{
					waveInUnprepareHeader(hwi,hdr,sizeof(WAVEHDR));
					if (ac->ok())
					{
						waveInPrepareHeader(hwi,hdr,sizeof(WAVEHDR));
						waveInAddBuffer(hwi,hdr,sizeof(WAVEHDR));
					}
				}
			}
		}
		break;
	case WIM_OPEN:
	case WIM_CLOSE:
		break;
	}
}

BOOL getDeviceId(LPCTSTR deviceName,UINT &deviceId)
{
	if (deviceName == NULL)
	{
		deviceId = WAVE_MAPPER;
		return TRUE;
	}

	WAVEINCAPS caps;
	for (int i=0,cnt=waveInGetNumDevs(); i<cnt; ++i)
	{
		memset(&caps,0,sizeof(WAVEINCAPS));
		waveInGetDevCaps(i,&caps,sizeof(WAVEINCAPSA));
		if (waveInGetDevCaps(i,&caps,sizeof(WAVEINCAPSA)) == MMSYSERR_NOERROR
			&& _tcscmp(deviceName,caps.szPname) == 0)
		{
			deviceId = i;
			return TRUE;
		}
	}

	//deviceId = 0;
	return TRUE;
}

BOOL AudioCaptureImpl::init(int channels,int bitsPerSample,int samplesPerSec,int blockSize,LPCTSTR deviceName)
{
	if (ok()) return FALSE;

	WAVEFORMATEX wfx;
	memset(&wfx,0,sizeof(WAVEFORMATEX));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = channels;
	wfx.nSamplesPerSec = samplesPerSec;
	wfx.wBitsPerSample = bitsPerSample;
	wfx.nBlockAlign = channels*(bitsPerSample/8);
	wfx.nAvgBytesPerSec = samplesPerSec*wfx.nBlockAlign;

	UINT deviceId;
	if (!getDeviceId(deviceName,deviceId))
		return FALSE;

	if (waveInOpen(&mWaveIn,deviceId,&wfx,(DWORD_PTR)waveInProc,
		(DWORD_PTR)this,CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
		return FALSE;

	if (waveInStart(mWaveIn) != MMSYSERR_NOERROR)
	{
		waveInClose(mWaveIn);
		mWaveIn = NULL;
		return FALSE;
	} 


	mBuffer = new Buffer();
	mBuffer->setBlockDataSize(blockSize);

	for (int i=0,cnt=mBuffer->blockCount(); i<cnt; ++i)
	{
		LPWAVEHDR hdr = mBuffer->block(i);
		waveInPrepareHeader(mWaveIn,hdr,sizeof(WAVEHDR));
		waveInAddBuffer(mWaveIn,hdr,sizeof(WAVEHDR));
	}

	return TRUE;
}

void AudioCaptureImpl::free(void)
{
	if (ok())
	{
		HWAVEIN waveIn = mWaveIn;
		mWaveIn = NULL;
	
		waveInStop(mWaveIn);
		waveInReset(waveIn);
		waveInClose(waveIn);

		delete mBuffer;
		mBuffer = NULL;
	}
}

CAudioCapture::CAudioCapture(CAudioCapture::Callback *cb)
{
	m_pImpl = new AudioCaptureImpl(cb);
}

CAudioCapture::~CAudioCapture(void)
{
	delete m_pImpl;
}

BOOL CAudioCapture::ok(void) const
{
	return m_pImpl->ok();
}

BOOL CAudioCapture::init(int channels,int bitsPerSample,int samplesPerSec,int blockSize,LPCTSTR deviceName)
{
	return m_pImpl->init(channels,bitsPerSample,samplesPerSec,blockSize,deviceName);
}

void CAudioCapture::free(void)
{
	m_pImpl->free();
}
