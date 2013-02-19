#pragma once
#include "CamExt.h"

class CCams
{
public:
	CCams(void);
	~CCams(void);

	BOOL Init(void);
	BOOL Free(void);

	BOOL Start(void);
	BOOL Stop(void);

	int GetCamCount(void) const;
	CCamExt* GetCam(int nIndex);

private:
	CArrayAdaptor<CCamExt*> m_cams;
};

inline int CCams::GetCamCount(void) const {
	return m_cams.GetCount();
}

inline CCamExt* CCams::GetCam(int nIndex) {
	return m_cams[nIndex];
}


extern CCams gcams;