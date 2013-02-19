#include "stdafx.h"
#include "RenderStatic.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif

CRenderStatic::CRenderStatic(void)
{
}

CRenderStatic::~CRenderStatic(void)
{
}


BEGIN_MESSAGE_MAP(CRenderStatic, CStatic)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CRenderStatic::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType,cx,cy);

	CWnd *pChild = GetWindow(GW_CHILD);
	if (pChild != NULL)
		pChild->MoveWindow(0,0,cx,cy);
}


BOOL CRenderStatic::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == FILETER_MESSAGE)
		GetParent()->SendMessage(FILETER_MESSAGE,pMsg->wParam,pMsg->lParam);

	return CStatic::PreTranslateMessage(pMsg);
}
