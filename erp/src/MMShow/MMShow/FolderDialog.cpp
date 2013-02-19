#include "StdAfx.h"
#include "FolderDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFolderDialog::CFolderDialog(void)
{
}

CFolderDialog::~CFolderDialog(void)
{
}


INT_PTR CFolderDialog::DoModal(HWND hWnd)
{
	BROWSEINFO bi;
	memset(&bi,0,sizeof(BROWSEINFO));
	bi.lpszTitle = _T("ÇëÑ¡ÔñÄ¿Â¼");
	bi.hwndOwner = hWnd;
	bi.ulFlags = BIF_RETURNONLYFSDIRS|BIF_DONTGOBELOWDOMAIN; 

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
		return IDCANCEL;

	CComPtr<IMalloc> pMalloc;
	SHGetMalloc(&pMalloc);
	TCHAR szPath[MAX_PATH];

	BOOL bRet = SHGetPathFromIDList(pidl,szPath);
	pMalloc->Free(pidl);
	if (bRet)
		m_strPath = szPath;
	return (bRet ? IDOK : IDCANCEL);
}
