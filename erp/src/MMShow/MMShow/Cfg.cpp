#include "StdAfx.h"
#include "Cfg.h"
#include "FileHelper.h"
#include "XMLDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCfg gcfg;

CCfg::CCfg(void)
{
	m_OutputVideoInput = 0;
	m_OutputVideoSize = 0;
	m_OutputVideoFps = 0; 

	// Record settings
	m_RecOutputFmt = 0;
	m_RecVideoBitrate = 0;
	m_RecAudioBitrate = 0;
	m_RecAudioSampleRate = 0; 

	// Ui settings  (op and preview)
	m_UiOpTransparentGauge = FALSE;
	m_UiOpShowGauge = TRUE;
	m_UiOpAutoSaveHistory = FALSE;
	m_UiOpDefaut = 0;
	m_UiPreviewDefault = 0;
	m_UiPreviewShowCursor = TRUE;
	m_UiPreviewOpen = TRUE;
	m_UiLiveDefault = 0;
}

CCfg::~CCfg(void)
{
}

BOOL CCfg::Load(void)
{
	m_bModified = FALSE;

	CXmlDoc doc;
	if (!doc.Load(gsys.CfgPath()))
		return TRUE;

	CXmlNode root = doc.Root;
	if (root.Name != _T("XStudio"))
		return FALSE;

	CXmlNode node = root.GetFirstChild(_T("Cam"));
	if (!node.IsNull())
	{
		m_Cam0 = node.GetStringAttrib(_T("Cam0"));
		m_Cam1 = node.GetStringAttrib(_T("Cam1"));
		m_Cam2 = node.GetStringAttrib(_T("Cam2"));
		//m_CamSize.cx = node.GetIntAttrib(_T("CamCX"));
		//m_CamSize.cy = node.GetIntAttrib(_T("CamCY"));
	}

	node = root.GetFirstChild(_T("Output"));
	if (!node.IsNull())
	{
		m_OutputVideoInput =  node.GetUIntAttrib(_T("VideoInput"));
		m_OutputVideoOutput = node.GetStringAttrib(_T("VideoOutput")); 
		m_OutputVideoSize = node.GetUIntAttrib(_T("VideoSize"));
		m_OutputVideoFps = node.GetUIntAttrib(_T("VideoFps"));
	}

	node = root.GetFirstChild(_T("Rec"));
	if (!node.IsNull())
	{
		m_RecOutputFmt = node.GetUIntAttrib(_T("OutputFmt"));
		m_RecOutputPath = node.GetStringAttrib(_T("OutputPath"));
		m_RecVideoBitrate = node.GetUIntAttrib(_T("VideoBitrate"));
		m_RecAudioBitrate = node.GetUIntAttrib(_T("AudioBitrate"));
		m_RecAudioSampleRate = node.GetUIntAttrib(_T("AudioSampleRate"));
		m_RecAudoInput = node.GetStringAttrib(_T("AudioInput"));
	}

	node = root.GetFirstChild(_T("Ui"));
	if (!node.IsNull())
	{
		m_UiOpTransparentGauge = node.GetBoolAttrib(_T("OpTransparentGauge"));
		m_UiOpShowGauge = node.GetBoolAttrib(_T("OpShowGauge")); 
		m_UiOpAutoSaveHistory = node.GetBoolAttrib(_T("OpAutoSaveHistory")); 
		m_UiOpDefaut = node.GetUIntAttrib(_T("OpDefaut")); 
		m_UiPreviewDefault = node.GetUIntAttrib(_T("PreviewDefault")); 
		m_UiPreviewShowCursor = node.GetBoolAttrib(_T("PreviewShowCursor")); 
		m_UiPreviewOpen = node.GetBoolAttrib(_T("PreviewOpen")); 
		m_UiLiveDefault = node.GetUIntAttrib(_T("LiveDefault")); 
	}

	if (gsys.Ajusted())
	{
		SetRecOutputFmt(0);
		SetRecAudioBitrate(0);
		SetRecAudioSampleRate(0);
		SetRecVideoBitrate(0);
		SetOutputVideoFps(0);
		SetOutputVideoSize(0);
		
	}
	return TRUE;
}

BOOL CCfg::Save(void)
{
	CXmlDoc doc;
	doc.SetText(_T("<XStudio />"));
	CXmlNode root = doc.Root;
	
	CXmlNode node = root.AppendChild(_T("Cam"));
	node.SetAttrib(_T("Cam0"),m_Cam0);
	node.SetAttrib(_T("Cam1"),m_Cam1);
	node.SetAttrib(_T("Cam2"),m_Cam2);
	//node.SetAttrib(_T("CamCX"),m_CamSize.cx);
	//node.SetAttrib(_T("CamCY"),m_CamSize.cy);

	node = root.AppendChild(_T("Output"));
	node.SetAttrib(_T("VideoInput"),m_OutputVideoInput);
	node.SetAttrib(_T("VideoOutput"),m_OutputVideoOutput); 
	node.SetAttrib(_T("VideoSize"),m_OutputVideoSize);
	node.SetAttrib(_T("VideoFps"),m_OutputVideoFps);

	node = root.AppendChild(_T("Rec"));
	node.SetAttrib(_T("OutputFmt"),m_RecOutputFmt);
	node.SetAttrib(_T("OutputPath"),m_RecOutputPath);
	node.SetAttrib(_T("AudioBitrate"),m_RecAudioBitrate);
	node.SetAttrib(_T("AudioSampleRate"),m_RecAudioSampleRate); 
	node.SetAttrib(_T("VideoBitrate"),m_RecVideoBitrate); 
	node.SetAttrib(_T("AudioInput"),m_RecAudoInput); 

	node = root.AppendChild(_T("Ui"));
	node.SetAttrib(_T("OpTransparentGauge"),m_UiOpTransparentGauge); 
	node.SetAttrib(_T("OpShowGauge"),m_UiOpShowGauge); 
	node.SetAttrib(_T("OpAutoSaveHistory"),m_UiOpAutoSaveHistory); 
	node.SetAttrib(_T("OpDefaut"),m_UiOpDefaut); 
	node.SetAttrib(_T("PreviewDefault"),m_UiPreviewDefault); 
	node.SetAttrib(_T("PreviewShowCursor"),m_UiPreviewShowCursor); 
	node.SetAttrib(_T("PreviewOpen"),m_UiPreviewOpen); 
	node.SetAttrib(_T("LiveDefault"),m_UiLiveDefault); 

	return doc.Save(gsys.CfgPath());
}
