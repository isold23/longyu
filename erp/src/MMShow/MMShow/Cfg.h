#pragma once
#include "XProp.h"
#include "SysDefault.h"


class CCfg
{
public:
	enum {CamCount = 3};

public:
	CCfg(void);
	~CCfg(void);

	BOOL Load(void);
	BOOL Save(void);
	
	XModifiedFlag()

	// Camare settings
	XStrProp(Cam0);
	XStrProp(Cam1);
	XStrProp(Cam2);
	//XSizeProp(CamSize);
 
	// Output settings
	// 0:Preview 1:Live
	XUintProp(OutputVideoInput);
	// "0","1","dev name"
	XStrProp(OutputVideoOutput);
	XUintProp(OutputVideoSize);
	XUintProp(OutputVideoFps); 

	// Record settings
	XUintProp(RecOutputFmt);
	XStrProp(RecOutputPath);
	XUintProp(RecVideoBitrate);
	XUintProp(RecAudioBitrate);
	XUintProp(RecAudioSampleRate); 
	XStrProp(RecAudoInput);

	// Ui settings  (op and preview)
	XBoolProp(UiOpTransparentGauge);
	XBoolProp(UiOpShowGauge);
	XBoolProp(UiOpAutoSaveHistory);
	// According tab pages
	XUintProp(UiOpDefaut);
	XUintProp(UiPreviewDefault);
	XBoolProp(UiPreviewShowCursor);
	XBoolProp(UiPreviewOpen);

	// three ones
	XUintProp(UiLiveDefault);

};

 

extern CCfg gcfg;