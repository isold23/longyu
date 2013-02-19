#pragma once

class VideoRenderImpl;

class CVideoRender
{
public:
	CVideoRender(void);
	~CVideoRender(void);

	HRESULT Open(HWND hWnd,CSize size,int nFps);
	HRESULT Open(LPCTSTR pcszCardName,CSize size,int nFps);
	HRESULT Close(void);

	BOOL IsOpened(void) const;
	HRESULT Write(LPCVOID buffer);

private:
	VideoRenderImpl *m_pImpl;
};
