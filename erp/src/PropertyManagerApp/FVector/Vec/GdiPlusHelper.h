#pragma once
#include <GdiPlus.h>

class CGdiplusInit
{
public:
	CGdiplusInit(void);
	~CGdiplusInit(void);

private:
	ULONG_PTR m_lGdiPlusToken;
};

 