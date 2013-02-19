#include "StdAfx.h"
#include "SysDefault.h"
#include "URLCodec.h"
#include "XmlDoc.h"
#include "FileHelper.h"

#define SYS_DEFAULT_FILE_NAME _T("sys.xml")
#define CFG_FILE_NAME _T("cfg.xml")
#define IMAGES_FOLDER _T("Images")

CSysDefault gsys;

CSysDefault::CSysDefault(void)
{
	m_bButtonShowTip = INT_MIN;
}

CSysDefault::~CSysDefault(void)
{
}

CString CSysDefault::GetPath(void) const
{
	return Fh::ToAppDirectory(SYS_DEFAULT_FILE_NAME);
}


BOOL CSysDefault::Load(void)
{
	m_bAdjusted = FALSE;

	CXmlDoc doc;
	if (!doc.Load(GetPath()))
	{	
		m_bAdjusted = TRUE;
	}
	else
	{
		CXmlNode node = doc.Root;
		if (node.Name != _T("XStudioSysDefault"))
		{
			m_bAdjusted = TRUE;
		}
		else
		{
			m_strCfgPath = node.GetStringAttrib(_T("Cfg"));
			m_strPicPath = node.GetStringAttrib(_T("Images"));
			if (node.HasAttrib(_T("ButtonShowTip")))
				m_bButtonShowTip = node.GetBoolAttrib(_T("ButtonShowTip"));

			int i,cnt;
			CXmlNode n = node.GetFirstChild(_T("RecordFormats"));		
			for (i=0,cnt=n.GetChildCount(); i<cnt; ++i)
				m_recFormats.Add(n.GetChild(i).GetStringAttrib(_T("Val")));

			n = node.GetFirstChild(_T("AudioBitrates"));		
			for (i=0,cnt=n.GetChildCount(); i<cnt; ++i)
				m_aBitrates.Add(n.GetChild(i).GetUIntAttrib(_T("Val")));

			n = node.GetFirstChild(_T("AudioSampleRates"));		
			for (i=0,cnt=n.GetChildCount(); i<cnt; ++i)
				m_aSampleRates.Add(n.GetChild(i).GetUIntAttrib(_T("Val")));

			n = node.GetFirstChild(_T("VideoFpses"));		
			for (i=0,cnt=n.GetChildCount(); i<cnt; ++i)
				m_vFpses.Add(n.GetChild(i).GetUIntAttrib(_T("Val")));


			n = node.GetFirstChild(_T("VideoBitrates"));		
			for (i=0,cnt=n.GetChildCount(); i<cnt; ++i)
				m_vBitrates.Add(n.GetChild(i).GetUIntAttrib(_T("Val")));

			n = node.GetFirstChild(_T("OutputSizes"));		
			for (i=0,cnt=n.GetChildCount(); i<cnt; ++i)
			{
				CXmlNode nc = n.GetChild(i);
				m_vOutputSizes.Add(CSize(nc.GetUIntAttrib(_T("Width")),nc.GetUIntAttrib(_T("Height"))));
			}
		}
	}

	m_bAdjusted = (m_bButtonShowTip==INT_MIN || m_strCfgPath.IsEmpty() || m_strPicPath.IsEmpty() || m_recFormats.IsEmpty() || m_aSampleRates.IsEmpty() ||
		m_aBitrates.IsEmpty() || m_vFpses.IsEmpty() || m_vBitrates.IsEmpty() || m_vOutputSizes.IsEmpty());
	

	if (m_bAdjusted)
	{
		m_bButtonShowTip = TRUE;

		m_strCfgPath = CFG_FILE_NAME;
		m_strPicPath = IMAGES_FOLDER;

		m_recFormats.RemoveAll();
		m_recFormats.Add(_T(".mpg"));

		m_aSampleRates.RemoveAll();
		m_aSampleRates.Add(44100);

		m_aBitrates.RemoveAll();
		m_aBitrates.Add(64*1000);

		m_vFpses.RemoveAll();
		m_vFpses.Add(25);

		m_vBitrates.RemoveAll();
		m_vBitrates.Add(1024*1024);

		m_vOutputSizes.RemoveAll();
		m_vOutputSizes.Add(CSize(720,576));


		CXmlDoc doc;
		CXmlNode node = doc.CreateRoot(_T("XStudioSysDefault"));
		node.SetAttrib(_T("ButtonShowTip"),m_bButtonShowTip);
		node.SetAttrib(_T("Cfg"),m_strCfgPath);
		node.SetAttrib(_T("Images"),m_strPicPath);
		
		CXmlNode n = node.AppendChild(_T("RecordFormats"));
		INT_PTR i;
		for (i=0; i<m_recFormats.GetCount(); ++i)
			n.AppendChild(_T("Elem")).SetAttrib(_T("Val"),m_recFormats[i]);

		n = node.AppendChild(_T("AudioSampleRates"));
		for (i=0; i<m_aSampleRates.GetCount(); ++i)
			n.AppendChild(_T("Elem")).SetAttrib(_T("Val"),m_aSampleRates[i]);

		n = node.AppendChild(_T("AudioBitrates"));
		for (i=0; i<m_aBitrates.GetCount(); ++i)
			n.AppendChild(_T("Elem")).SetAttrib(_T("Val"),m_aBitrates[i]);
		
		n = node.AppendChild(_T("VideoFpses"));
		for (i=0; i<m_vFpses.GetCount(); ++i)
			n.AppendChild(_T("Elem")).SetAttrib(_T("Val"),m_vFpses[i]);

		n = node.AppendChild(_T("VideoBitrates"));
		for (i=0; i<m_vBitrates.GetCount(); ++i)
			n.AppendChild(_T("Elem")).SetAttrib(_T("Val"),m_vBitrates[i]);

		n = node.AppendChild(_T("OutputSizes"));
		for (i=0; i<m_vOutputSizes.GetCount(); ++i)
		{
			CXmlNode nc = n.AppendChild(_T("Elem"));
			nc.SetAttrib(_T("Width"),m_vOutputSizes[i].cx);
			nc.SetAttrib(_T("Height"),m_vOutputSizes[i].cy);
		}

		doc.Save(GetPath());
	}
	return TRUE;
}

