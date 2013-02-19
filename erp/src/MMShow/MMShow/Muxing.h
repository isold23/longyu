#pragma once 

struct AVFrame;
struct AVStream;
struct AVFormatContext;

struct SwsContext;

 
class Muxing
{
public:
	Muxing(void);
	~Muxing(void);

	int audioFrameSize(void) const;
	bool running(void) const;

	bool prepare(const char *ofile,CSize vSize,int vBitrate,int vFps,int aSampleRate,int aBitrate);	
	bool end(void);

	bool writeVideoFrame(unsigned long tick,const void *buffer);
	bool writeAudioFrame(unsigned long tick,unsigned char *buffer,int len);

private:
	bool cleanup(AVFormatContext *oc);

	bool addVideoStream(AVFormatContext *oc,CSize vSize,int vBitrate,int vFps);
	bool addAudioStream(AVFormatContext *oc,int aSampleRate,int aBitrate);

	bool openAudio(void);
	void closeAudio(void);

	bool openVideo(void);
	void closeVideo(void);

	AVStream *aStream_;

	AVStream *vStream_;

	AVFormatContext *oc_;

	struct VSwsContext {
		SwsContext *ctx;
		
		AVFrame *opic;

		unsigned char *obuffer;
		int obufferSize;

	} vCvt_;
};

inline bool Muxing::running(void) const {
	return (oc_ != 0);
}
