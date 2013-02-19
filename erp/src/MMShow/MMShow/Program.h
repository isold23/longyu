#pragma once 
#include "ArrayAdaptor.h"
#include "XProp.h"

class VideoProperty
{
	friend class CProgram;
	friend class ProgramProperties;
	VideoProperty(void);

	XModifiedFlag()

	XUintProp(VideoOutputWidth);
	XUintProp(VideoOutputHeight);
	XUintProp(HorizontalBlackMagicSafeZone);
	XUintProp(VerticalBlackMagicSafeZone);
	XBoolProp(UseWatermark);
	XStrProp(TopLeftWatermarkBitmapFileName);
	XUintProp(TopLeftWatermarkLeftPosition);
	XUintProp(TopLeftWatermarkTopPosition);
	XBoolProp(UseTopLeftWatermarkTransparencyColour);
	XClrProp(TopLeftWatermarkTransparencyColour); 
	XStrProp(TopRightWatermarkBitmapFileName); 
	XUintProp(TopRightWatermarkRightPosition);
	XUintProp( TopRightWatermarkTopPosition);
	XBoolProp(UseTopRightWatermarkTransparencyColour);
	XClrProp(TopRightWatermarkTransparencyColour);
	XStrProp(BottomLeftWatermarkBitmapFileName); 
	XUintProp(BottomLeftWatermarkLeftPosition);
	XUintProp(BottomLeftWatermarkBottomPosition);
	XBoolProp( UseBottomLeftWatermarkTransparencyColour);
	XClrProp(BottomLeftWatermarkTransparencyColour);
	XStrProp(BottomRightWatermarkBitmapFileName);
	XUintProp(BottomRightWatermarkRightPosition);
	XUintProp(BottomRightWatermarkBottomPosition);
	XBoolProp(UseBottomRightWatermarkTransparencyColour);
	XClrProp(BottomRightWatermarkTransparencyColour);
	XBoolProp(CatchWebHtmlPopups);
};

class ContentLink
{
	friend class CProgram;

	ContentLink(void);

	XModifiedFlag()

	XStrProp(Type);
	XStrProp(Name);
	XStrProp(Description);
	XUintProp(Zoom);
	XUintProp(HorizontalScrollBarPosition);
	XUintProp(VerticalScrollBarPosition);
	XUintProp(CaptureRectLeft);
	XUintProp(CaptureRectTop);
	XUintProp(CaptureRectWidth);
	XUintProp(CaptureRectHeight);
	XUintProp(Volume);
	XBoolProp(Active);
	XBoolProp(ShowMouseCursor);
	XBoolProp(UseWatermark);
	XStrProp(BottomLeftWatermarkBitmapFileName);
	XUintProp(BottomLeftWatermarkLeftPosition);
	XUintProp(BottomLeftWatermarkBottomPosition);
	XBoolProp(UseBottomLeftWatermarkTransparencyColour);
	XClrProp(BottomLeftWatermarkTransparencyColour);
	XStrProp(FilePath);
	XUintProp(StartPosition);
	XUintProp(EndPosition);
};


class ProgramProperties
{
	friend class CProgram;
	ProgramProperties(void);

	XModifiedFlag()

	XStrProp(Name);
	XStrProp(Description);
	XStrProp(CreatedBy);
	
	VideoProperty VideoProp;

private:
	COleDateTime m_CreationTime;
	COleDateTime m_LastUpdatedTime;
};


class CProgram
{
public:
	typedef CArrayAdaptor<ContentLink*> ContentLinks;
	
	CProgram(void);
	~CProgram(void);

	BOOL Load(const CString &strFilePath);	
	BOOL Save(void);
	BOOL SaveAs(const CString &strFilePath);

	BOOL IsLoaded(void) const;

	BOOL MoveUp(int nIndex);
	BOOL MoveUp(ContentLink *cl);
	
	BOOL MoveDown(int nIndex);
	BOOL MoveDown(ContentLink *cl);

	BOOL Remove(int nIndex);
	BOOL Remove(ContentLink *cl);

	ContentLink* AddContentLink(const CString &strName,const CString &strPath,
		const CString &strDesc,BOOL bWebPage);

	const CString& GetFilePath(void) const;
//////////////////////////////////////////////////////////////////////////
	void ResetContent(void);
	int IndexOf(ContentLink *cl);

	bool IsModified(void) const;


	CString Version;
	ProgramProperties ProgramProp;
	ContentLinks Contents;

private:
	void ClearModifiedFlag(void);

	CString m_strFilePath;
};

inline BOOL CProgram::IsLoaded(void) const {
	return !m_strFilePath.IsEmpty();
}

inline const CString& CProgram::GetFilePath(void) const {
	return m_strFilePath;
}