#pragma once
#include <afxmt.h>
#include "ArrayAdaptor.h"
#include "VideoRender.h"

class CCardWriter
{
public:
	CCardWriter(void);
	~CCardWriter(void);

	BOOL Start(int nCurrent,CSize,int nFps);
	BOOL Start(const CString &strCurrent,CSize size,int nFps);
	
	BOOL Stop(void);

	BOOL SetCurrentCard(int nIndex);

	BOOL WriteVideo(const void *buffer);

private:
	CVideoRender *m_pCurrentCard;
	CArrayAdaptor<CVideoRender*> m_cards;
	
	CCriticalSection m_cs;

};
