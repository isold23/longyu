#include "StdAfx.h"
#include "Cams.h"
#include "Cfg.h"
#include "Devices.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCams gcams;

CCams::CCams(void)
{
}

CCams::~CCams(void)
{
	Free();
}

BOOL CCams::Init(void)
{
	const CStringArray &devices = CDevices::GetVideoDevices(TRUE);
	const CStringArray &names = CDevices::GetVideoDeviceNames(TRUE);

	int nCam0Index = FindIndex(devices,gcfg.GetCam0());
	int nCam1Index = FindIndex(devices,gcfg.GetCam1());
	int nCam2Index = FindIndex(devices,gcfg.GetCam2());

	if (nCam0Index<0 || nCam1Index<0 || nCam2Index<0)
		return FALSE;

	m_cams.Add(new CCamExt(gcfg.GetCam0(),names[nCam0Index]));
	m_cams.Add(new CCamExt(gcfg.GetCam1(),names[nCam1Index]));
	m_cams.Add(new CCamExt(gcfg.GetCam2(),names[nCam2Index]));
	
	return TRUE;
}


BOOL CCams::Free(void)
{
	for (int i=0; i<m_cams.GetCount(); ++i)
	{
		m_cams[i]->Stop();
		delete m_cams[i];
	}
	m_cams.RemoveAll();
	return TRUE;
}

BOOL CCams::Start(void)
{
	BOOL bRet = m_cams[0]->Start();
	bRet = m_cams[1]->Start() && bRet;
	bRet = m_cams[2]->Start() && bRet;
	return bRet;
}

BOOL CCams::Stop(void)
{
	return m_cams[0]->Stop() && m_cams[1]->Stop() && m_cams[2]->Stop();
}
