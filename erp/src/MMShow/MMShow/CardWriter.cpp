#include "StdAfx.h"
#include "CardWriter.h"
#include "Devices.h"
#include "VideoRender.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCardWriter::CCardWriter(void)
	:m_pCurrentCard(NULL)
{
}

CCardWriter::~CCardWriter(void)
{
}

BOOL CCardWriter::Start(int nCurrent,CSize size,int nFps)
{
	const CStringArray &devices = CDevices::GetVideoDevices(FALSE);

	for (INT_PTR i=0; i<devices.GetCount(); ++i)
	{
		CVideoRender *pCardRender = new CVideoRender();
		if (SUCCEEDED(pCardRender->Open(devices.GetAt(i),size,nFps)))
			m_cards.Add(pCardRender);
	}
	SetCurrentCard(nCurrent);
	return TRUE;
}

BOOL CCardWriter::Start(const CString &strCurrent,CSize size,int nFps)
{
	const CStringArray &devices = CDevices::GetVideoDevices(FALSE);

	for (INT_PTR i=0; i<devices.GetCount(); ++i)
	{
		CVideoRender *pCardRender = new CVideoRender();
		if (SUCCEEDED(pCardRender->Open(devices.GetAt(i),size,nFps)))
			m_cards.Add(pCardRender);
	}

	SetCurrentCard(FindIndex(devices,strCurrent));
	return TRUE;
}

BOOL CCardWriter::SetCurrentCard(int nIndex)
{
	if (nIndex>=0 && nIndex<m_cards.GetCount())
		m_pCurrentCard = m_cards[nIndex];
	else
		m_pCurrentCard = NULL;
	return TRUE;
}

BOOL CCardWriter::Stop(void)
{
	for (int i=0; i<m_cards.GetCount(); ++i)
	{
		m_cards[i]->Close();
		delete m_cards[i];
	}
	m_cards.RemoveAll();
	return TRUE;
}

BOOL CCardWriter::WriteVideo(const void *buffer)
{	
	return (m_pCurrentCard==NULL ? FALSE: m_pCurrentCard->Write(buffer));
}
