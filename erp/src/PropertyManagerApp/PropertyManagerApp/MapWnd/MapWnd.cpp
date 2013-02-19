#include "stdafx.h"
#include "MapWnd.h"
#include "../resource.h"


CMapWnd::CMapWnd(void)
{

}

CMapWnd::~CMapWnd(void)
{

}

BEGIN_MESSAGE_MAP(CMapWnd,CVecWnd)
	ON_NOTIFY_REFLECT(VWN_HOVERCHANGE,&CMapWnd::OnHoverChange)
	ON_COMMAND_RANGE(IDS_BUILDING,IDS_OTHER,&CMapWnd::OnSelTickChange)
END_MESSAGE_MAP()

void CMapWnd::OnHoverChange(NMHDR *pNM, LRESULT *pResult)
{
	if (m_tip.GetSafeHwnd() == NULL)
	{
		EnableToolTips(TRUE);
		m_tip.Create(this);
		m_tip.Activate(TRUE);
		m_tip.SetDelayTime(2000,0);
		m_tip.AddTool(this,_T(""));
	}

	CElem *pElem = GetHoverElem();
	if (pElem !=  NULL)
		m_tip.UpdateTipText(pElem->GetDesc(),this);
	m_tip.Activate(pElem != NULL);

	*pResult = FALSE;
}

void CMapWnd::OnSelTickChange(UINT nCmd)
{
	int nCustomData =  -1;
	switch (nCmd)
	{
	case IDS_WAY: 
		nCustomData = 0; 
		break;

	case IDS_GREEN:
		nCustomData = 1;
		break;

	case IDS_ELECTRONIC:
		nCustomData = 2;
		break;

	case IDS_WATER:
		nCustomData = 3;
		break;

	case IDS_WARM:
		nCustomData = 4;
		break;

	case IDS_OTHER:
		//nCustomData = 5;
		//break;

	default:
		SetTicked(FALSE); 
		return;
	};

	for (UINT i=0; i<GetElemCount(); ++i)
	{
		CElem *pElem = GetElemByIndex(i);
		pElem->SetTicked(pElem->GetCustomData() == nCustomData);
	}
	SetTicked(TRUE);
}

BOOL CMapWnd::PreTranslateMessage(MSG* pMsg)
{
	if (m_tip.GetSafeHwnd() != NULL)
		m_tip.RelayEvent(pMsg);
	return CVecWnd::PreTranslateMessage(pMsg);
}
