#include "stdafx.h"
#include "GdiplusHelper.h"
#pragma comment(lib,"gdiplus.lib")

CGdiplusInit::CGdiplusInit(void) 
{
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;

	Gdiplus::GdiplusStartup(&m_lGdiPlusToken,&input,&output);
}

CGdiplusInit::~CGdiplusInit(void) 
{
	Gdiplus::GdiplusShutdown (m_lGdiPlusToken);
}

