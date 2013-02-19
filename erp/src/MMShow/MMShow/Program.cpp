#include "StdAfx.h"
#include "Program.h"
#include "XmlDoc.h"
#include "URLCodec.h"
 
#define PROG_LOCAL static inline  


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ContentLink::ContentLink(void)
	:m_bModified(false)
{
}

VideoProperty::VideoProperty(void)
	:m_bModified(false)
{
}

ProgramProperties::ProgramProperties(void)
	:m_bModified(false)
{
}



CProgram::CProgram(void)
{
}

CProgram::~CProgram(void)
{
	ResetContent();
}


PROG_LOCAL UINT GetNodeInt(CXmlNode &node,const CString &name,UINT &ret)
{
	CXmlNode n = node.GetFirstChild(name);
	return ret = (n.IsNull() ? 0 : _ttoi(n.GetValue()));
}

PROG_LOCAL CString& GetNodeString(CXmlNode &node,const CString &name,CString &ret)
{
	return ret = node.GetFirstChild(name).GetValue();
}

PROG_LOCAL bool GetNodeBool(CXmlNode &node,const CString &name,bool &ret)
{
	return ret = (node.GetFirstChild(name).GetValue() == _T("True"));
}

PROG_LOCAL COleDateTime& GetNodeTime(CXmlNode &node,const CString &name,COleDateTime &ret)
{ 
	CXmlNode n = node.GetFirstChild(name);
	if (!n.IsNull())
	{
		UINT nTmp;
		ret.SetDateTime(GetNodeInt(n,_T("Year"),nTmp),
			GetNodeInt(n,_T("Month"),nTmp),
			GetNodeInt(n,_T("Day"),nTmp),
			GetNodeInt(n,_T("Hour"),nTmp),
			GetNodeInt(n,_T("Minute"),nTmp),
			GetNodeInt(n,_T("Second"),nTmp));
	} 
	return ret;
}

void CProgram::ResetContent(void)
{
	for (int i=0; i <Contents.GetCount(); ++i)
		delete Contents[i];
	Contents.RemoveAll();

	ProgramProp.m_Name.Empty();
	ProgramProp.m_Description.Empty();
	ProgramProp.m_CreatedBy.Empty();
	//ProgramProp.CreationTime = COleDateTime::GetCurrentTime();
	//ProgramProp.LastUpdatedTime = COleDateTime::GetCurrentTime();

	ProgramProp.VideoProp.m_VideoOutputWidth = 0;
	ProgramProp.VideoProp.m_VideoOutputHeight = 0;
	ProgramProp.VideoProp.m_HorizontalBlackMagicSafeZone = 0;
	ProgramProp.VideoProp.m_VerticalBlackMagicSafeZone = 0;
	ProgramProp.VideoProp.m_UseWatermark = false;
	ProgramProp.VideoProp.m_TopLeftWatermarkBitmapFileName.Empty();
	ProgramProp.VideoProp.m_TopLeftWatermarkLeftPosition = 0;
	ProgramProp.VideoProp.m_TopLeftWatermarkTopPosition = 0;
	ProgramProp.VideoProp.m_UseTopLeftWatermarkTransparencyColour = false;
	ProgramProp.VideoProp.m_TopLeftWatermarkTransparencyColour = 0; 
	ProgramProp.VideoProp.m_TopRightWatermarkBitmapFileName.Empty(); 
	ProgramProp.VideoProp.m_TopRightWatermarkRightPosition = 0;
	ProgramProp.VideoProp.m_TopRightWatermarkTopPosition = 0;
	ProgramProp.VideoProp.m_UseTopRightWatermarkTransparencyColour = false;
	ProgramProp.VideoProp.m_TopRightWatermarkTransparencyColour = 0;
	ProgramProp.VideoProp.m_BottomLeftWatermarkBitmapFileName.Empty(); 
	ProgramProp.VideoProp.m_BottomLeftWatermarkLeftPosition = 0;
	ProgramProp.VideoProp.m_BottomLeftWatermarkBottomPosition = 0;
	ProgramProp.VideoProp.m_UseBottomLeftWatermarkTransparencyColour = false;
	ProgramProp.VideoProp.m_BottomLeftWatermarkTransparencyColour = 0;
	ProgramProp.VideoProp.m_BottomRightWatermarkBitmapFileName.Empty();
	ProgramProp.VideoProp.m_BottomRightWatermarkRightPosition = 0;
	ProgramProp.VideoProp.m_BottomRightWatermarkBottomPosition = 0;
	ProgramProp.VideoProp.m_UseBottomRightWatermarkTransparencyColour = false;
	ProgramProp.VideoProp.m_BottomRightWatermarkTransparencyColour = 0;
	ProgramProp.VideoProp.m_CatchWebHtmlPopups = false;
						  
	ProgramProp.m_bModified = ProgramProp.VideoProp.m_bModified = false;

	m_strFilePath.Empty();
}

BOOL CProgram::Load(const CString &strFilePath)
{
	CXmlDoc doc;
	if (!doc.Load(strFilePath))
		return FALSE;

	ResetContent();

	CString str;
	CXmlNode root = doc.Root;

	GetNodeString(root,_T("Version"),Version);

	CXmlNode node = root.GetFirstChild(_T("ProgramProperties"));
	GetNodeString(node,_T("Name"),ProgramProp.m_Name);
	GetNodeString(node,_T("Description"),URLDecode(ProgramProp.m_Description));
	GetNodeString(node,_T("Description"),str);
	ProgramProp.m_Description = URLDecode(str);
	GetNodeString(node,_T("CreatedBy"),ProgramProp.m_CreatedBy);
	GetNodeTime(node,_T("CreationTime"),ProgramProp.m_CreationTime);
	GetNodeTime(node,_T("LastUpdatedTime"),ProgramProp.m_LastUpdatedTime);

	GetNodeInt(node,_T("VideoOutputWidth"),ProgramProp.VideoProp.m_VideoOutputWidth);
	GetNodeInt(node,_T("VideoOutputHeight"),ProgramProp.VideoProp.m_VideoOutputHeight);
	GetNodeInt(node,_T("HorizontalBlackMagicSafeZone"),ProgramProp.VideoProp.m_HorizontalBlackMagicSafeZone);
	GetNodeInt(node,_T("VerticalBlackMagicSafeZone"),ProgramProp.VideoProp.m_VerticalBlackMagicSafeZone);
	GetNodeBool(node,_T("UseWatermark"),ProgramProp.VideoProp.m_UseWatermark);
	GetNodeString(node,_T("TopLeftWatermarkBitmapFileName"),ProgramProp.VideoProp.m_TopLeftWatermarkBitmapFileName);
	GetNodeInt(node,_T("TopLeftWatermarkLeftPosition"),ProgramProp.VideoProp.m_TopLeftWatermarkLeftPosition);
	GetNodeInt(node,_T("TopLeftWatermarkTopPosition"),ProgramProp.VideoProp.m_TopLeftWatermarkTopPosition);
	GetNodeBool(node,_T("UseTopLeftWatermarkTransparencyColour"),ProgramProp.VideoProp.m_UseTopLeftWatermarkTransparencyColour);
	GetNodeInt(node,_T("TopLeftWatermarkTransparencyColour"),(UINT&)ProgramProp.VideoProp.m_TopLeftWatermarkTransparencyColour);
	GetNodeString(node,_T("TopRightWatermarkBitmapFileName"),ProgramProp.VideoProp.m_TopRightWatermarkBitmapFileName);
	GetNodeInt(node,_T("TopRightWatermarkRightPosition"),ProgramProp.VideoProp.m_TopRightWatermarkRightPosition);
	GetNodeInt(node,_T("TopRightWatermarkTopPosition"),ProgramProp.VideoProp.m_TopRightWatermarkTopPosition);
	GetNodeBool(node,_T("UseTopRightWatermarkTransparencyColour"),ProgramProp.VideoProp.m_UseTopRightWatermarkTransparencyColour);
	GetNodeInt(node,_T("TopRightWatermarkTransparencyColour"),(UINT&)ProgramProp.VideoProp.m_TopRightWatermarkTransparencyColour);
	GetNodeString(node,_T("BottomLeftWatermarkBitmapFileName"),ProgramProp.VideoProp.m_BottomLeftWatermarkBitmapFileName);
	GetNodeInt(node,_T("BottomLeftWatermarkLeftPosition"),ProgramProp.VideoProp.m_BottomLeftWatermarkLeftPosition);
	GetNodeInt(node,_T("BottomLeftWatermarkBottomPosition"),ProgramProp.VideoProp.m_BottomLeftWatermarkBottomPosition);
	GetNodeBool(node,_T("UseBottomLeftWatermarkTransparencyColour"),ProgramProp.VideoProp.m_UseBottomLeftWatermarkTransparencyColour);
	GetNodeInt(node,_T("BottomLeftWatermarkTransparencyColour"),(UINT&)ProgramProp.VideoProp.m_BottomLeftWatermarkTransparencyColour);
	GetNodeString(node,_T("BottomRightWatermarkBitmapFileName"),ProgramProp.VideoProp.m_BottomRightWatermarkBitmapFileName);
	GetNodeInt(node,_T("BottomRightWatermarkRightPosition"),ProgramProp.VideoProp.m_BottomRightWatermarkRightPosition);
	GetNodeInt(node,_T("BottomRightWatermarkBottomPosition"),ProgramProp.VideoProp.m_BottomRightWatermarkBottomPosition);
	GetNodeBool(node,_T("UseBottomRightWatermarkTransparencyColour"),ProgramProp.VideoProp.m_UseBottomRightWatermarkTransparencyColour);
	GetNodeInt(node,_T("BottomRightWatermarkTransparencyColour"),(UINT&)ProgramProp.VideoProp.m_BottomRightWatermarkTransparencyColour);
	GetNodeBool(node,_T("CatchWebHtmlPopups"),ProgramProp.VideoProp.m_CatchWebHtmlPopups);

	

	CXmlNode n;
	node = root.GetFirstChild(_T("ContentLinksList"));
	if (node.IsNull())
		return TRUE;

	for (int i=0,cnt=node.GetChildCount(); i<cnt; ++i)
	{

		n = node.GetChild(i);		
		if (n.GetName() != _T("ContentLink"))
			continue;

		ContentLink *cl = new ContentLink;;
		Contents.Add(cl);

		GetNodeString(n,_T("Type"),cl->m_Type);
		GetNodeString(n,_T("Name"),cl->m_Name);
		GetNodeString(n,_T("Description"),str);
		cl->m_Description = URLDecode(str);

		GetNodeInt(n,_T("Zoom"),cl->m_Zoom);
		GetNodeInt(n,_T("HorizontalScrollBarPosition"),cl->m_HorizontalScrollBarPosition);
		GetNodeInt(n,_T("VerticalScrollBarPosition"),cl->m_VerticalScrollBarPosition);

		GetNodeInt(n,_T("CaptureRectLeft"),cl->m_CaptureRectLeft);
		GetNodeInt(n,_T("CaptureRectTop"),cl->m_CaptureRectTop);
		GetNodeInt(n,_T("CaptureRectWidth"),cl->m_CaptureRectWidth);
		GetNodeInt(n,_T("CaptureRectHeight"),cl->m_CaptureRectHeight);

		GetNodeInt(n,_T("Volume"),cl->m_Volume);
		GetNodeBool(n,_T("Active"),cl->m_Active);
		GetNodeBool(n,_T("ShowMouseCursor"),cl->m_ShowMouseCursor);
		GetNodeBool(n,_T("UseWatermark"),cl->m_UseWatermark);
		GetNodeString(n,_T("BottomLeftWatermarkBitmapFileName"),cl->m_BottomLeftWatermarkBitmapFileName);

		GetNodeInt(n,_T("BottomLeftWatermarkLeftPosition"),cl->m_BottomLeftWatermarkLeftPosition);
		GetNodeInt(n,_T("BottomLeftWatermarkBottomPosition"),cl->m_BottomLeftWatermarkBottomPosition);
		GetNodeBool(n,_T("UseBottomLeftWatermarkTransparencyColour"),cl->m_UseBottomLeftWatermarkTransparencyColour);
		GetNodeInt(n,_T("BottomLeftWatermarkTransparencyColour"),(UINT&)cl->m_BottomLeftWatermarkTransparencyColour);
		GetNodeString(n,_T("FilePath"),cl->m_FilePath);
		GetNodeInt(n,_T("StartPosition"),cl->m_StartPosition);  
		GetNodeInt(n,_T("EndPosition"),cl->m_EndPosition);   
	}

	m_strFilePath = strFilePath;
	return TRUE;
}

BOOL CProgram::Save(void)
{
	return SaveAs(m_strFilePath);
}

PROG_LOCAL void AppendIntNode(CXmlNode &node,const CString &name,INT nValue)
{
	TCHAR sz[32];
	node.AppendChild(name).SetValue(_itot(nValue,sz,10));
}

PROG_LOCAL void AppendStringNode(CXmlNode &node,const CString &name,const CString &value)
{
	node.AppendChild(name).SetValue(value);
}

PROG_LOCAL void AppendBoolNode(CXmlNode &node,const CString &name,bool flag)
{
	AppendStringNode(node,name,flag ? _T("True") : _T("False"));
}

PROG_LOCAL void AppendTimeNode(CXmlNode &node,const CString &name,const COleDateTime &time)
{
	CXmlNode n = node.AppendChild(name);
	SYSTEMTIME t;
	time.GetAsSystemTime(t);
	AppendIntNode(n,_T("Year"),t.wYear);
	AppendIntNode(n,_T("Month"),t.wMonth);
	AppendIntNode(n,_T("Day"),t.wDay);
	AppendIntNode(n,_T("Hour"),t.wHour);
	AppendIntNode(n,_T("Minute"),t.wMinute);
	AppendIntNode(n,_T("Second"),t.wSecond);
}

BOOL CProgram::SaveAs(const CString &strFilePath)
{
	CXmlDoc doc;
	if (!doc.SetText(_T("<?xml version=\"1.0\" ?><!-- iPoint-media Go Live Studio's User Program Xml--><Program/>")))
		return FALSE;

	CXmlNode root = doc.Root;
	AppendStringNode(root,_T("Version"),Version);

	CXmlNode node = root.AppendChild(_T("ProgramProperties"));
	AppendStringNode(node,_T("Name"),ProgramProp.GetName());
	AppendStringNode(node,_T("Description"),URLEncode(ProgramProp.GetDescription()));
	AppendStringNode(node,_T("CreatedBy"),ProgramProp.GetCreatedBy());
	AppendTimeNode(node,_T("CreationTime"),ProgramProp.m_CreationTime);
	AppendTimeNode(node,_T("LastUpdatedTime"),ProgramProp.m_LastUpdatedTime);
	
	AppendIntNode(node,_T("VideoOutputWidth"),ProgramProp.VideoProp.GetVideoOutputWidth());
	AppendIntNode(node,_T("VideoOutputHeight"),ProgramProp.VideoProp.GetVideoOutputHeight());
	AppendIntNode(node,_T("HorizontalBlackMagicSafeZone"),ProgramProp.VideoProp.GetHorizontalBlackMagicSafeZone());
	AppendIntNode(node,_T("VerticalBlackMagicSafeZone"),ProgramProp.VideoProp.GetVerticalBlackMagicSafeZone());
	AppendBoolNode(node,_T("UseWatermark"),ProgramProp.VideoProp.GetUseWatermark());
	AppendStringNode(node,_T("TopLeftWatermarkBitmapFileName"),ProgramProp.VideoProp.GetTopLeftWatermarkBitmapFileName());
	AppendIntNode(node,_T("TopLeftWatermarkLeftPosition"),ProgramProp.VideoProp.GetTopLeftWatermarkLeftPosition());
	AppendIntNode(node,_T("TopLeftWatermarkTopPosition"),ProgramProp.VideoProp.GetTopLeftWatermarkTopPosition());
	AppendBoolNode(node,_T("UseTopLeftWatermarkTransparencyColour"),ProgramProp.VideoProp.GetUseTopLeftWatermarkTransparencyColour());
	AppendIntNode(node,_T("TopLeftWatermarkTransparencyColour"),ProgramProp.VideoProp.GetTopLeftWatermarkTransparencyColour());
	AppendStringNode(node,_T("TopRightWatermarkBitmapFileName"),ProgramProp.VideoProp.GetTopRightWatermarkBitmapFileName());
	AppendIntNode(node,_T("TopRightWatermarkRightPosition"),ProgramProp.VideoProp.GetTopRightWatermarkRightPosition());
	AppendIntNode(node,_T("TopRightWatermarkTopPosition"),ProgramProp.VideoProp.GetTopRightWatermarkTopPosition());
	AppendBoolNode(node,_T("UseTopRightWatermarkTransparencyColour"),ProgramProp.VideoProp.GetUseTopRightWatermarkTransparencyColour());
	AppendIntNode(node,_T("TopRightWatermarkTransparencyColour"),ProgramProp.VideoProp.GetTopRightWatermarkTransparencyColour());
	AppendStringNode(node,_T("BottomLeftWatermarkBitmapFileName"),ProgramProp.VideoProp.GetBottomLeftWatermarkBitmapFileName());
	AppendIntNode(node,_T("BottomLeftWatermarkLeftPosition"),ProgramProp.VideoProp.GetBottomLeftWatermarkLeftPosition());
	AppendIntNode(node,_T("BottomLeftWatermarkBottomPosition"),ProgramProp.VideoProp.GetBottomLeftWatermarkBottomPosition());
	AppendBoolNode(node,_T("UseBottomLeftWatermarkTransparencyColour"),ProgramProp.VideoProp.GetUseBottomLeftWatermarkTransparencyColour());
	AppendIntNode(node,_T("BottomLeftWatermarkTransparencyColour"),ProgramProp.VideoProp.GetBottomLeftWatermarkTransparencyColour());
	AppendStringNode(node,_T("BottomRightWatermarkBitmapFileName"),ProgramProp.VideoProp.GetBottomRightWatermarkBitmapFileName());
	AppendIntNode(node,_T("BottomRightWatermarkRightPosition"),ProgramProp.VideoProp.GetBottomRightWatermarkRightPosition());
	AppendIntNode(node,_T("BottomRightWatermarkBottomPosition"),ProgramProp.VideoProp.GetBottomRightWatermarkBottomPosition());
	AppendBoolNode(node,_T("UseBottomRightWatermarkTransparencyColour"),ProgramProp.VideoProp.GetUseBottomRightWatermarkTransparencyColour());
	AppendIntNode(node,_T("BottomRightWatermarkTransparencyColour"),ProgramProp.VideoProp.GetBottomRightWatermarkTransparencyColour());
	AppendBoolNode(node,_T("CatchWebHtmlPopups"),ProgramProp.VideoProp.GetCatchWebHtmlPopups());
 

	CXmlNode n;
	node = root.AppendChild(_T("ContentLinksList"));
	for (int i=0; i<Contents.GetCount(); ++i)
	{
		ContentLink *cl = Contents[i];

		n = node.AppendChild(_T("ContentLink"));
		
		AppendStringNode(n,_T("Type"),cl->GetType());
		AppendStringNode(n,_T("Name"),cl->GetName());
		AppendStringNode(n,_T("Description"),URLEncode(cl->GetDescription()));

		AppendIntNode(n,_T("Zoom"),cl->GetZoom());
		AppendIntNode(n,_T("HorizontalScrollBarPosition"),cl->GetHorizontalScrollBarPosition());
		AppendIntNode(n,_T("VerticalScrollBarPosition"),cl->GetVerticalScrollBarPosition());

		AppendIntNode(n,_T("CaptureRectLeft"),cl->GetCaptureRectLeft());
		AppendIntNode(n,_T("CaptureRectTop"),cl->GetCaptureRectTop());
		AppendIntNode(n,_T("CaptureRectWidth"),cl->GetCaptureRectWidth());
		AppendIntNode(n,_T("CaptureRectHeight"),cl->GetCaptureRectHeight());

		AppendIntNode(n,_T("Volume"),cl->GetVolume());
		AppendBoolNode(n,_T("Active"),cl->GetActive());
		AppendBoolNode(n,_T("ShowMouseCursor"),cl->GetShowMouseCursor());
		AppendBoolNode(n,_T("UseWatermark"),cl->GetUseWatermark());
		AppendStringNode(n,_T("BottomLeftWatermarkBitmapFileName"),cl->GetBottomLeftWatermarkBitmapFileName());

		AppendIntNode(n,_T("BottomLeftWatermarkLeftPosition"),cl->GetBottomLeftWatermarkLeftPosition());
		AppendIntNode(n,_T("BottomLeftWatermarkBottomPosition"),cl->GetBottomLeftWatermarkBottomPosition());
		AppendBoolNode(n,_T("UseBottomLeftWatermarkTransparencyColour"),cl->GetUseBottomLeftWatermarkTransparencyColour());
		AppendIntNode(n,_T("BottomLeftWatermarkTransparencyColour"),cl->GetBottomLeftWatermarkTransparencyColour());
		AppendStringNode(n,_T("FilePath"),cl->GetFilePath());
		AppendIntNode(n,_T("StartPosition"),cl->GetStartPosition());  
		AppendIntNode(n,_T("EndPosition"),cl->GetEndPosition());   
	}

	if (!doc.Save(strFilePath))
		return FALSE;

	ClearModifiedFlag();
	m_strFilePath = strFilePath;
	return TRUE;
}

void CProgram::ClearModifiedFlag(void)
{
	ProgramProp.m_bModified = false;
	ProgramProp.VideoProp.m_bModified = false;
	for (int i=0,cnt = Contents.GetCount(); i<cnt; ++i)
		Contents[i]->m_bModified = false;
}


int CProgram::IndexOf(ContentLink *cl)
{
	int i = 0;
	int cnt = Contents.GetCount();
	for (; i<cnt; ++i)
		if (cl == Contents[i])
			break;
	return (i==cnt ? -1 : i);
}

BOOL CProgram::MoveUp(int nIndex)
{
	if (nIndex <= 0)
		return FALSE;
	if (nIndex >= Contents.GetCount())
		return FALSE;

	ProgramProp.SetModified();
	std::swap(Contents[nIndex],Contents[nIndex-1]);
	return TRUE;
}

BOOL CProgram::MoveUp(ContentLink *cl)
{
	return MoveUp(IndexOf(cl));
}

BOOL CProgram::MoveDown(int nIndex)
{
	if (nIndex < 0)
		return FALSE;
	if (nIndex >= Contents.GetCount()-1)
		return FALSE;

	ProgramProp.SetModified();
	std::swap(Contents[nIndex],Contents[nIndex+1]);
	return TRUE;
}

BOOL CProgram::MoveDown(ContentLink *cl)
{
	return MoveDown(IndexOf(cl));
}

BOOL CProgram::Remove(int nIndex)
{
	if (nIndex < 0)
		return FALSE;
	if (nIndex >= Contents.GetCount())
		return FALSE;

	ProgramProp.SetModified();

	delete Contents[nIndex];
	Contents.RemoveAt(nIndex);
	return TRUE;
}

BOOL CProgram::Remove(ContentLink *cl)
{
	return Remove(IndexOf(cl));
}

ContentLink* CProgram::AddContentLink(const CString &strName,const CString &strPath,
				const CString &strDesc,BOOL bWebPage)
{
	ContentLink *cl = new ContentLink;
	cl->SetType((bWebPage ? _T("WebPage") : _T("VideoFile")));
	cl->SetName(strName);
	cl->SetFilePath(strPath);
	cl->SetDescription(strDesc);
	Contents.Add(cl);
	ProgramProp.SetModified();
	
	return cl;
}


bool CProgram::IsModified(void) const
{
	if (ProgramProp.IsModified())
		return true;

	for (int i=0,cnt=Contents.GetCount(); i<cnt; ++i)
		if (Contents[i]->IsModified())
			return true;

	return false;
}