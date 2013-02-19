#pragma once   


class CWindowRender
{
public:
	CWindowRender(void);
	~CWindowRender(void);

	HRESULT Start(HWND targetWnd);

	BOOL IsStarted(void) const;
	void Stop(void);

	HRESULT Render(HWND *renderWnds=NULL,int cnt=0);

	HRESULT Fill(LPCVOID buf,CSize size,int stride);

private:
	void *m_pImpl;
};