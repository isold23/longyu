#include "stdafx.h"
#include "UIControl.h"

#include "../UCChatRoom.h"

//---------------------------------------------------------------------------
extern CUCChatRoomApp theApp; 

CUIObject::CUIObject(HWND ahParent, int aiLeft, int aiTop, int aiwidth, int aiHeight)
{
	mhParent = ahParent;
	miLeft = aiLeft;
	miTop = aiTop;
	miWidth = aiwidth;
	miHeight = aiHeight;
	mbVisible = true;
	mbEnable = true;
	mbChecked = false;

	mclCaptionColor = RGB(0,0,0);
	mbBold = false;
	mbUnderLine = false;

	mstrctchType = StretchBoth;

	SetRect(&mrcClient, aiTop, aiTop, aiLeft + aiwidth, aiTop + aiHeight);
}

void CUIObject::SetVisible(bool abValue)
{
	if (mbVisible != abValue)
	{
		mbVisible = abValue;
		if(mbVisible)
			InvalidateRect(mhParent, &mrcClient, FALSE);
	}
}

void CUIObject::SetChecked(bool abValue)
{
	if (mbChecked != abValue)
	{
		mbChecked = abValue;
		if(mbVisible)
			InvalidateRect(mhParent, &mrcClient, FALSE);
	}
}

void CUIObject::SetEnable(bool abValue)
{
	if (mbEnable != abValue)
	{
		mbEnable = abValue;
		if(mbVisible)
			InvalidateRect(mhParent, &mrcClient, FALSE);
	}
}

void CUIObject::SetBold(bool abValue)
{
	if (mbBold != abValue)
	{
		mbBold = abValue;
		if(mbVisible)
			InvalidateRect(mhParent, &mrcClient, FALSE);
	}
}

void CUIObject::SetUnderLine(bool abValue)
{
	if (mbUnderLine != abValue)
	{
		mbUnderLine = abValue;
		if(mbVisible)
			InvalidateRect(mhParent, &mrcClient, FALSE);
	}
}

void CUIObject::Paint(HDC ahdc)
{
	if(mbVisible)
	{
		DrawBack(ahdc);
		DrawCaption(ahdc);
	}
}

void CUIObject::SetBackImage(Image* pImage)
{
	_ASSERT(pImage);
	if(pImage == mpImage)
		return;

	if(mpImage != NULL)
	{
		theApp.mpImageManager->ReleaseImage(mpImage);	
	}

	mpImage = pImage;
}

void  CUIObject::DrawBack(HDC ahdc)
{
	if(mpImage)
	{
		//mpImage->DrawEx(ahdc, miLeft, miTop, miWidth, miHeight, 0, 0, mpImage->GetSrcWidth(), mpImage->GetSrcHeight());
	}
}

void  CUIObject::DrawCaption(HDC ahdc)
{
	if(!mstrCaption.IsEmpty())
	{
		DrawText(ahdc, mstrCaption.GetBuffer(), mstrCaption.GetLength(), &mrcClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

//---------------------------------------------CUCScrollBar-----------------------------------------
CUCScrollBar::CUCScrollBar(HWND hParent, IView* pView)
{
	mbVisible = false;
	mhParent = hParent;
	mpView = pView;
	mbTrackMouseDown = false;
	mbUpMouseDown = false;
	mbDownMouseDown = false;
	mbMidMouseDown = false;
	mbTrackMouseOver = false;
	mbUpMouseOver = false;
	mbDownMouseOver = false;
	miTotalHeight = 0;
	miViewHeight = 0;
	muiTimer = 0;
	miArrowH = 17;
	mpImage = NULL;
	theApp.mpImageManager->AddImage(theApp.mpRoomData->mstrAppPath + L"skin\\scroll_v.png", &mpImage);
	miScrollStep = 5;
	miTrackTop = 0;
	miTrackLength = 0;
	mwDragTime = 0;
	miViewRelaPos = 0;
}

CUCScrollBar::~CUCScrollBar()
{
	if(mpImage)
	{
		if(theApp.mpImageManager)
			theApp.mpImageManager->ReleaseImage(mpImage);
		mpImage = NULL;
	}
}

void CUCScrollBar::SetRect(int aiLeft, int aiTop, int aiWidth, int aiHeight)
{
	::SetRect(&mrcClient, aiLeft, aiTop, aiLeft + aiWidth, aiTop + aiHeight);
	::SetRect(&mrcTop, aiLeft, aiTop, aiLeft + aiWidth, aiTop+miArrowH);
	::SetRect(&mrcBottom, aiLeft, aiTop + aiHeight - miArrowH, aiLeft + aiWidth, aiTop + aiHeight);
	::SetRect(&mrcMid, aiLeft, mrcTop.bottom, aiLeft + aiWidth, mrcBottom.top);
	::SetRect(&mrcTrack, aiLeft, aiTop+miArrowH, aiLeft + aiWidth, 0);
	int liTempVH = miViewHeight;
	miViewHeight = aiHeight;
	CalcScrollBar();
}

bool CUCScrollBar::GetVisible()
{
	return mbVisible;
}

void CUCScrollBar::Paint(HDC hdc)
{
	if(mbVisible && mpImage)
	{
		Graphics graphics(hdc);
		//绘制向上箭头
		if(mbUpMouseDown)
		{
			Rect lrcdest(mrcTop.left, mrcTop.top, mrcTop.right - mrcTop.left, mrcTop.bottom - mrcTop.top);
			graphics.DrawImage(mpImage, lrcdest, 17*2, 0, 17, 17, UnitPixel);
		}
		else if(mbUpMouseOver)
		{
			Rect lrcdest(mrcTop.left, mrcTop.top, mrcTop.right - mrcTop.left, mrcTop.bottom - mrcTop.top);
			graphics.DrawImage(mpImage, lrcdest, 17, 0, 17, 17, UnitPixel);
		}
		else
		{
			Rect lrcdest(mrcTop.left, mrcTop.top, mrcTop.right - mrcTop.left, mrcTop.bottom - mrcTop.top);
			graphics.DrawImage(mpImage, lrcdest, 0, 0, 17, 17, UnitPixel);
		}

		//绘制中间背景
		if(mbMidMouseDown)
		{
			Rect lrcdest(mrcMid.left, mrcMid.top, mrcMid.right - mrcMid.left, mrcMid.bottom - mrcMid.top);
			graphics.DrawImage(mpImage, lrcdest, 17*2, 17*2, 17, 16, UnitPixel);
		}
		else
		{
			Rect lrcdest(mrcMid.left, mrcMid.top, mrcMid.right - mrcMid.left, mrcMid.bottom - mrcMid.top);
			graphics.DrawImage(mpImage, lrcdest, 0, 17*2, 17, 16, UnitPixel);
		}

		//绘制滑块
		if(mbTrackMouseDown)
		{
			if(miTrackLength <= 17)
			{
				Rect lrcdest(mrcTrack.left, mrcTrack.top, mrcTrack.right - mrcTrack.left, mrcTrack.bottom - mrcTrack.top);
				graphics.DrawImage(mpImage, lrcdest, 17*2, 17*3, 17, 17, UnitPixel);
			}
			else
			{
				Rect lrcdest(mrcTrack.left, mrcTrack.top, mrcTrack.right - mrcTrack.left, 5);
				graphics.DrawImage(mpImage, lrcdest, 17*2, 17*3, 17, 5, UnitPixel);

				lrcdest = Rect(mrcTrack.left, mrcTrack.top+5, mrcTrack.right - mrcTrack.left, mrcTrack.bottom - mrcTrack.top - 10);
				graphics.DrawImage(mpImage, lrcdest, 17*2, 17*3+5, 17, 5, UnitPixel);
				
				lrcdest = Rect(mrcTrack.left, mrcTrack.bottom - 5, mrcTrack.right - mrcTrack.left, 5);
				graphics.DrawImage(mpImage, lrcdest, 17*2, 17*3+12, 17, 5, UnitPixel);
			}
			
		}
		else if(mbTrackMouseOver)
		{
			if(miTrackLength <= 17)
			{
				Rect lrcdest(mrcTrack.left, mrcTrack.top, mrcTrack.right - mrcTrack.left, mrcTrack.bottom - mrcTrack.top);
				graphics.DrawImage(mpImage, lrcdest, 17, 17*3, 17, 17, UnitPixel);
			}
			else
			{
				Rect lrcdest(mrcTrack.left, mrcTrack.top, mrcTrack.right - mrcTrack.left, 5);
				graphics.DrawImage(mpImage, lrcdest, 17, 17*3, 17, 5, UnitPixel);

				lrcdest = Rect(mrcTrack.left, mrcTrack.top+5, mrcTrack.right - mrcTrack.left, mrcTrack.bottom - mrcTrack.top - 10);
				graphics.DrawImage(mpImage, lrcdest, 17, 17*3+5, 17, 5, UnitPixel);

				lrcdest = Rect(mrcTrack.left, mrcTrack.bottom - 5, mrcTrack.right - mrcTrack.left, 5);
				graphics.DrawImage(mpImage, lrcdest, 17, 17*3+12, 17, 5, UnitPixel);
			}
		}
		else
		{
			if(miTrackLength <= 17)
			{
				Rect lrcdest(mrcTrack.left, mrcTrack.top, mrcTrack.right - mrcTrack.left, mrcTrack.bottom - mrcTrack.top);
				graphics.DrawImage(mpImage, lrcdest, 0, 17*3, 17, 17, UnitPixel);
			}
			else
			{
				Rect lrcdest(mrcTrack.left, mrcTrack.top, mrcTrack.right - mrcTrack.left, 5);
				graphics.DrawImage(mpImage, lrcdest, 0, 17*3, 17, 5, UnitPixel);

				lrcdest = Rect(mrcTrack.left, mrcTrack.top+5, mrcTrack.right - mrcTrack.left, mrcTrack.bottom - mrcTrack.top - 10);
				graphics.DrawImage(mpImage, lrcdest, 0, 17*3+5, 17, 5, UnitPixel);

				lrcdest = Rect(mrcTrack.left, mrcTrack.bottom - 5, mrcTrack.right - mrcTrack.left, 5);
				graphics.DrawImage(mpImage, lrcdest, 0, 17*3+12, 17, 5, UnitPixel);
			}
		}

		//绘制向下箭头
		if(mbDownMouseDown)
		{
			Rect lrcdest(mrcBottom.left, mrcBottom.top, mrcBottom.right - mrcBottom.left, mrcBottom.bottom - mrcBottom.top);
			graphics.DrawImage(mpImage, lrcdest, 17*2, 17, 17, 17, UnitPixel);
		}
		else if(mbDownMouseOver)
		{
			Rect lrcdest(mrcBottom.left, mrcBottom.top, mrcBottom.right - mrcBottom.left, mrcBottom.bottom - mrcBottom.top);
			graphics.DrawImage(mpImage, lrcdest, 17, 17, 17, 17, UnitPixel);
		}
		else
		{
			Rect lrcdest(mrcBottom.left, mrcBottom.top, mrcBottom.right - mrcBottom.left, mrcBottom.bottom - mrcBottom.top);
			graphics.DrawImage(mpImage, lrcdest, 0, 17, 17, 17, UnitPixel);
		}
	}
}

void CUCScrollBar::SetTotalHeight(int aiValue)
{
	if(miTotalHeight != aiValue)
	{
		miTotalHeight = aiValue;
		CalcScrollBar();
	}
}

void CUCScrollBar::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;
	if(mbVisible)
	{
		if(mbTrackMouseDown)
		{
			DWORD tmptime = 10;
			DWORD tmpcont = GetTickCount();
			if (miViewHeight > 115 && miViewHeight <= 400)
				tmptime = 20;
			else if(miViewHeight > 400)
				tmptime = 40;
			if (abs(tmpcont - mwDragTime) > tmptime)
			{
				Scroll(pt.y - miPreMousePosY);
				miPreMousePosY = pt.y;
			}			
			return;
		}

		if(PtInRect(&mrcClient, pt))
		{
			bool needPaint = false;
			if(mbTrackMouseOver || mbUpMouseOver || mbDownMouseOver)
			{
				mbTrackMouseOver = false;
				mbUpMouseOver = false;
				mbDownMouseOver = false;
				needPaint = true;
			}
			

			if(PtInRect(&mrcTop, pt))
			{
				if(mbUpMouseDown)
					return;
				
				mbUpMouseOver = true;
				RePaint();
				return;
			}
			else if(PtInRect(&mrcBottom, pt))
			{
				if(mbDownMouseDown)
					return;

				mbDownMouseOver = true;
				RePaint();
				return;
			}
			else if(PtInRect(&mrcTrack, pt))
			{
				mbTrackMouseOver = true;
				RePaint();
				return;
			}

			if(needPaint)
				RePaint();
		}
		else if(mbUpMouseDown || mbMidMouseDown || mbDownMouseDown ||
					mbTrackMouseOver || mbUpMouseOver || mbDownMouseOver)
		{
			//mbTrackMouseDown = false;
			mbUpMouseDown = false;
			mbDownMouseDown = false;
			mbMidMouseDown = false;

			mbTrackMouseOver = false;
			mbUpMouseOver = false;
			mbDownMouseOver = false;

			if(muiTimer != 0)
			{
				KillTimer(mhParent, muiTimer);
				muiTimer = 0;
			}	

			RePaint();
		}	
	}
	else
	{
		if(muiTimer != 0)
		{
			KillTimer(mhParent, muiTimer);
			muiTimer = 0;
		}	
	}
}

void CUCScrollBar::OnMouseLeave()
{
	if(mbUpMouseDown || mbMidMouseDown || mbDownMouseDown || mbTrackMouseDown
		|| mbTrackMouseOver || mbUpMouseOver || mbDownMouseOver)
	{
		mbUpMouseDown = false;
		mbDownMouseDown = false;
		mbMidMouseDown = false;
		mbTrackMouseDown = false;

		mbTrackMouseOver = false;
		mbUpMouseOver = false;
		mbDownMouseOver = false;

		if(muiTimer != 0)
		{
			KillTimer(mhParent, muiTimer);
			muiTimer = 0;
		}	

		RePaint();
	}
}

void CUCScrollBar::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(mbVisible)
	{
		Scroll(zDelta>0?(-miScrollStep):miScrollStep);
	}
}

void CUCScrollBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;
	if(mbVisible && PtInRect(&mrcClient, pt))
	{
		if(PtInRect(&mrcTop, pt))
		{
			Scroll(-miScrollStep);
			mbUpMouseDown = true;
		}
		else if(PtInRect(&mrcBottom, pt))
		{
			Scroll(miScrollStep);
			mbDownMouseDown = true;
		}
		else if(PtInRect(&mrcTrack, pt))
		{
			mbTrackMouseDown = true;	
			miPreMousePosY = pt.y;
		}
		else
		{
			mbMidMouseDown = true;
			miPreMousePosY = pt.y;
		}	
		if(!mbTrackMouseDown)
		{
			muiTimer = SetTimer(mhParent, 1000, 50, NULL);
		}
	}	
}

void CUCScrollBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(mbUpMouseDown || mbMidMouseDown || mbDownMouseDown || mbTrackMouseDown)
	{
		mbUpMouseDown = false;
		mbDownMouseDown = false;
		mbMidMouseDown = false;
		mbTrackMouseDown = false;
		if(muiTimer != 0)
		{
			KillTimer(mhParent, muiTimer);
			muiTimer = 0;
		}

		RePaint();
	}
}

void CUCScrollBar::OnTimer(UINT_PTR nIDEvent)
{
	if(muiTimer == nIDEvent)
	{
		if(mbVisible)
		{
			if (mbUpMouseDown)
			{
				Scroll(-miScrollStep);
			}
			else if (mbDownMouseDown)
			{
				Scroll(miScrollStep);
			}
			else if (mbMidMouseDown)
			{	
				//注意 当滑块移动到鼠标位置时 时钟应停下
				if(miTrackTop + miArrowH > miPreMousePosY)
				{
					Scroll(-miScrollStep*3);
				}
				else 
				{
					Scroll(miScrollStep*3);
				}
				if(miPreMousePosY > miTrackTop + miArrowH && miPreMousePosY < miTrackTop + miTrackLength + miArrowH)
				{
					KillTimer(mhParent, nIDEvent);
					muiTimer = 0;
				}
			}
		}
		else
		{
			KillTimer(mhParent, nIDEvent);
			muiTimer = 0;
		}
	}
}

void CUCScrollBar::RePaint()
{
	InvalidateRect(mhParent, &mrcClient, FALSE);
}

void CUCScrollBar::Scroll(int aiValue)
{
	int liTemp = miTrackTop + aiValue;
	//mpView->OnVScroll((liTemp - miTrackTop)*(miTotalHeight - miViewHeight)/(miViewHeight-2*miArrowH-miTrackLength));
	if(liTemp < 0)
		liTemp = 0;
	else if(liTemp > (miViewHeight - miTrackLength - 2*miArrowH))
	{
		liTemp  = miViewHeight - miTrackLength - 2*miArrowH;
	}

	if(liTemp != miTrackTop)
	{
		mrcTrack.top += liTemp - miTrackTop;
		mrcTrack.bottom = mrcTrack.top + miTrackLength;
		miTrackTop = liTemp;
		miViewRelaPos = miTrackTop*miTotalHeight/(miViewHeight-2*miArrowH);
		mpView->OnVScroll(miViewRelaPos);
	}
}

void CUCScrollBar::CalcScrollBar()
{
	if(miTotalHeight > miViewHeight)
	{

		miTrackLength = int(float(miViewHeight*(miViewHeight - 2*miArrowH))/float(miTotalHeight));
		if(mbVisible && miTrackTop != 0)
		{
			if(miViewRelaPos > miTotalHeight - miViewHeight)
			{
				miViewRelaPos = miTotalHeight - miViewHeight;
				mpView->OnVScroll(miViewRelaPos);
			}
			miTrackTop = (miViewHeight - 2*miArrowH)*miViewRelaPos/miTotalHeight;	
		}
		mbVisible = true;
		mrcTrack.top = miTrackTop + miArrowH;
		mrcTrack.bottom = mrcTrack.top + miTrackLength;
		RePaint();
	}
	else if(mbVisible)
	{
		mbVisible = false;
		miViewRelaPos = 0;
		miTrackTop = 0;
		miTrackLength = 0;
		RePaint();
	}
}

CTreeNode::CTreeNode()
{
	mpPeerImage = NULL;
	mpHeadImage = NULL;
}
CTreeNode::~CTreeNode()
{
	if(mpPeerImage)
	{
		theApp.mpImageManager->ReleaseImageEx(mpPeerImage);
		mpPeerImage = NULL;
	}
	if(mpHeadImage)
	{
		theApp.mpImageManager->ReleaseImage(mpHeadImage);
		mpPeerImage = NULL;
	}
}

class FindUser
{
public:
	FindUser(__int64 ai64UserID):mi64UserID(ai64UserID){}
	bool operator()(const CTreeNode* pNode)
	{
		return ((PSTRU_USER_INFO)pNode->mpData)->mi64UserID == mi64UserID;
	}
private:
	__int64 mi64UserID;
};

class FindPosNode
{
public:
	FindPosNode(POINT point):m_point(point){}
	bool operator()(const CTreeNode* pNode)
	{
		return PtInRect(&pNode->mrcClient, m_point);
	}
private:
	POINT m_point;
};

 bool SortProc(CTreeNode* elem1, CTreeNode* elem2)
 {
 	if(elem1 == elem2)
 		return true;

	PSTRU_USER_INFO pUser1 = PSTRU_USER_INFO(elem1->mpData);
 	PSTRU_USER_INFO pUser2 = PSTRU_USER_INFO(elem2->mpData);

	int result;
	result = pUser2->miPeerLevel - pUser1->miPeerLevel;
	if(result == 0)
	{
		result = pUser2->miSeller - pUser1->miSeller;
		if(result == 0)
		{
			result = pUser2->mbyPower - pUser1->mbyPower;
			if (result == 0)
			{
				result = pUser2->miShowStarLevel - pUser1->miShowStarLevel;
				if(result == 0)
				{
					result = pUser1->mi64UserID - pUser2->mi64UserID;
				}
			}
		}
	}
	return result < 0;
 }


//-----------------------------------------CBaseTree---------------------------------------
CBaseTree::CBaseTree(HWND hParent)
		:m_VScrollBar(hParent, this)
{
	mhParent = hParent;
	mbVisible = true;
	mbSort = true;
	mpImageState = NULL;

	miViewRelaPos = 0;
	miTotalHeight = 0;
	miItemHeight = 36;
	miSelUserID = 0;
	mbSeaching = false;

	m_pNodeList = &m_AllList;
}

CBaseTree::~CBaseTree()
{
	ClearAllItems();
}

void CBaseTree::OnVScroll(int aiValue)
{
	if(miViewRelaPos != aiValue)
	{
		miViewRelaPos = aiValue;
		SetItemRect();
		RePaint();
	}
}

void CBaseTree::SetRect(int aiLeft, int aiTop, int aiWidth, int aiHeight)
{
	::SetRect(&mrcClient, aiLeft, aiTop, aiLeft + aiWidth, aiTop + aiHeight);
	m_VScrollBar.SetRect(aiLeft + aiWidth - 17, aiTop, 17, aiHeight);
}

void CBaseTree::SetVisible(bool abValue)
{
	if(mbVisible != abValue)
	{
		mbVisible = abValue;
		RePaint();
	}
}

void CBaseTree::Paint(HDC hdc)
{
	if (mbVisible)
	{
		list<CTreeNode*>::iterator iter = m_pNodeList->begin();
		for (; iter != m_pNodeList->end(); iter++)
		{
			DrawItem(hdc, *iter);
		}

		m_VScrollBar.Paint(hdc);
	}
}

void CBaseTree::OnMouseMove(UINT nFlags, CPoint point)
{
	m_VScrollBar.OnMouseMove(nFlags, point);
}

void CBaseTree::OnMouseLeave()
{
	m_VScrollBar.OnMouseLeave();
}

void CBaseTree::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	if(mbVisible && PtInRect(&mrcClient, point))
	{
		m_VScrollBar.OnMouseWheel(nFlags, zDelta, pt);
	}
}

void CBaseTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_VScrollBar.OnLButtonDown(nFlags, point);
}

void CBaseTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(mbVisible)
	{
		m_VScrollBar.OnLButtonUp(nFlags, point);

		CTreeNode* pNode = NULL;
		if(FindPositionNode(pNode, point))
		{
			miSelUserID = PSTRU_USER_INFO(pNode->mpData)->mi64UserID;
			RePaint();
			::PostMessage(mhParent, WM_LCLICK_ITEM, WPARAM(pNode->mpData), 0);
		}
	}
}

void CBaseTree::OnRButtonUp(UINT nFlags, CPoint point)
{
	//m_VScrollBar.OnLButtonUp(nFlags, point);
	if(mbVisible)
	{
		CTreeNode* pNode = NULL;
		if(FindPositionNode(pNode, point))
		{
			miSelUserID = PSTRU_USER_INFO(pNode->mpData)->mi64UserID;
			RePaint();
			::PostMessage(mhParent, WM_RCLICK_ITEM, WPARAM(pNode->mpData), 0);
		}
	}
}

void CBaseTree::OnTimer(UINT_PTR nIDEvent)
{
	m_VScrollBar.OnTimer(nIDEvent);
}

void CBaseTree::InsertItem(CTreeNode* pNode)
{
	_ASSERT(pNode);
	
	int liCount = m_AllList.size();
	int liTop = liCount*miItemHeight - miViewRelaPos;
	::SetRect(&pNode->mrcClient, mrcClient.left, mrcClient.top + liTop, mrcClient.right - mrcClient.left, mrcClient.top + liTop + miItemHeight);

	PSTRU_USER_INFO pUser = PSTRU_USER_INFO(pNode->mpData);
	if(pUser->miPeerLevel > 0)
	{
		CString lstr;
		lstr.Format(L"\\skin\\peer_%d.gif", pUser->miPeerLevel);
		lstr = theApp.mpRoomData->mstrAppPath + lstr;
		if(theApp.mpImageManager->AddImageEx(lstr.GetBuffer(), &pNode->mpPeerImage))
		{
			pNode->mpPeerImage->SetVisible(false);
			pNode->mpPeerImage->SetParent(mhParent);
			pNode->mpPeerImage->SetPos(pNode->mrcClient.left, pNode->mrcClient.top + 2);
		}			
	}
	CString strPhoto;
	strPhoto.Format(L"face\\%d.bmp", pUser->mwPhotoNum);
	strPhoto = theApp.mpRoomData->mstrAppPath + strPhoto;
	if(!theApp.mpImageManager->AddImage(strPhoto.GetBuffer(), &pNode->mpHeadImage))
	{
		strPhoto = theApp.mpRoomData->mstrAppPath + L"face\\0.bmp";	
		theApp.mpImageManager->AddImage(strPhoto.GetBuffer(), &pNode->mpHeadImage);
	}	

	m_AllList.push_back(pNode);
	miTotalHeight = m_pNodeList->size()*miItemHeight;
	m_VScrollBar.SetTotalHeight(miTotalHeight);


	if(mbSort)
	{
		Sort();
	}
	RePaint();	
}

void CBaseTree::DeleteItem(__int64 aiUserID)
{
	list<CTreeNode*> ::iterator iter = find_if(m_AllList.begin(), m_AllList.end(), FindUser(aiUserID));
	if(iter != m_AllList.end())
	{
		CTreeNode* pNode = *iter;
		if(pNode->mrcClient.bottom > mrcClient.top && pNode->mrcClient.top < mrcClient.bottom)
		{

		}
		delete *iter;
		iter = m_AllList.erase(iter);
		if(mbSeaching)
		{
			m_SearchList.remove(*iter);
		}
		
		SetItemRect();		

		miTotalHeight = m_pNodeList->size()*miItemHeight;
		m_VScrollBar.SetTotalHeight(miTotalHeight);
	}

	if(miSelUserID == aiUserID)
	{
		miSelUserID = 0;
	}
}

void CBaseTree::ClearAllItems()
{
	list<CTreeNode*>::iterator iter = m_AllList.begin();
	for (; iter != m_AllList.end(); iter++)
	{
		delete *iter;
	}
	m_AllList.clear();
	m_SearchList.clear();

	miTotalHeight = 0;
	miViewRelaPos = 0;
	m_VScrollBar.SetTotalHeight(0);

	RePaint();
}

void CBaseTree::Search(const wchar_t* pKeyWords)
{
	if(wcslen(pKeyWords) != 0)
	{
		SetSearchState(true);
		m_SearchList.clear();

		list<CTreeNode*>::iterator iter = m_AllList.begin();
		for (; iter != m_AllList.end(); iter++)
		{
			PSTRU_USER_INFO pUser = PSTRU_USER_INFO((*iter)->mpData);
			if (KeyInItem(pUser, pKeyWords))
			{
				m_SearchList.push_back((*iter));
			}
			else if((*iter)->mpPeerImage != NULL)
			{
				(*iter)->mpPeerImage->SetVisible(false);
			}
		}
	}
	SetSearchState(false);
}

void CBaseTree::DrawItem(HDC hdc, CTreeNode* pNode)
{
	//可见
	if(pNode->mrcClient.bottom > mrcClient.top && pNode->mrcClient.top < mrcClient.bottom)
	{
		Graphics graphics(hdc);

		if(pNode->mpPeerImage != NULL)
		{
			pNode->mpPeerImage->SetVisible(true);
			pNode->mpPeerImage->Draw(hdc);
		}
		PSTRU_USER_INFO pUser = PSTRU_USER_INFO(pNode->mpData);
		
		//选中状态
		if(pUser->mi64UserID == miSelUserID)
		{
			HBRUSH hbr = CreateSolidBrush(RGB(255,245,222));
			FillRect(hdc, &pNode->mrcClient, hbr);
			DeleteObject(hbr);
		}
		//设置文字颜色
		if(pUser->miPeerLevel > 0 || pUser->miShowStarLevel > 0)
		{
			SetTextColor(hdc, RGB(255,0,0));
		}
		else if(pUser->GetUserStatus(CONST_USER_STATUS_HIDDE))
		{
			SetTextColor(hdc, RGB(112,177,235));
		}
		else 
		{
			SetTextColor(hdc, RGB(0x1F,0x6E,0xB1));
		}
		//画头像
		if(pNode->mpHeadImage)
		{
			Rect rcHead(pNode->mrcClient.left+16, pNode->mrcClient.top+4,28,28);
			graphics.DrawImage(pNode->mpHeadImage, rcHead, 0, 0, pNode->mpHeadImage->GetWidth(), pNode->mpHeadImage->GetHeight(), UnitPixel);
		}

		SetBkMode(hdc, TRANSPARENT);
		//画昵称
		RECT rcNick;
		::SetRect(&rcNick, pNode->mrcClient.left+46, pNode->mrcClient.top, pNode->mrcClient.left+181, pNode->mrcClient.top + miItemHeight/2);
		DrawText(hdc, pUser->macNickName.GetBuffer(), pUser->macNickName.GetLength(), &rcNick, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_WORD_ELLIPSIS);
		
		//画ID
		CString lstrID;
		lstrID.Format(_T("%I64d"), pUser->mi64UserID);
		RECT rcID;
		::SetRect(&rcID, pNode->mrcClient.left+46, pNode->mrcClient.top + miItemHeight/2, pNode->mrcClient.left+181, pNode->mrcClient.top + miItemHeight);
		DrawText(hdc, lstrID.GetBuffer(), lstrID.GetLength(), &rcID, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_WORD_ELLIPSIS);

		//秀星标志
		if(pUser->miPeerLevel == 0 && pUser->miShowStarLevel > 0)
		{
			int liIndex = 5 + pUser->miShowStarLevel;
			if(mpImageState)
			{
				Rect rcTemp(pNode->mrcClient.left, pNode->mrcClient.top + 2,16,16);
				graphics.DrawImage(mpImageState, rcTemp, 16*liIndex, 0, 16, 16, UnitPixel);
			}
		}
		//官方销售
		if(pUser->miSeller > 0)
		{
			if(mpImageState)
			{
				Rect rcTemp(pNode->mrcClient.left, pNode->mrcClient.top + 18,16,16);
				graphics.DrawImage(mpImageState, rcTemp, 16*12, 0, 16, 16, UnitPixel);
			}
		}
		//管理员
		if(pUser->mbyPower >= DEF_LEVEL_TEMP)
		{
			int liIndex = -1;
			switch(pUser->mbyPower)
			{
			case DEF_LEVEL_TEMP:
				liIndex = 0;
				break;
			case DEF_LEVEL_MANAGER:
				liIndex = 1;
				break;
			case DEF_LEVEL_ROOM_OWENER:
				liIndex = 2;
				break;
			case DEF_LEVEL_TITLE:
				liIndex = 3;
				break;
			case DEF_LEVEL_PATROL:
				liIndex = 4;
				break;
			case DEF_LEVEL_SUPER:
				liIndex = 5;
				break;
			default:
				break;
			}
			if(liIndex != -1)
			{
				if(mpImageState)
				{
					Rect rcTemp(pNode->mrcClient.left+132, pNode->mrcClient.top + 18,16,16);
					graphics.DrawImage(mpImageState, rcTemp, 16*liIndex, 0, 16, 16, UnitPixel);
				}	
			}
		}

		//周星 
		if(pUser->miWeekStar > 0)
		{
			int liIndex = 12 + pUser->miWeekStar;
			if(mpImageState)
			{
				Rect rcTemp(pNode->mrcClient.left+114, pNode->mrcClient.top + 18,16,16);
				graphics.DrawImage(mpImageState, rcTemp, 16*liIndex, 0, 16, 16, UnitPixel);
			}
		}
		//被禁言
		else if(pUser->GetUserStatus(CONST_USER_STATUS_FORBIDTALK))
		{

		}
		//关注
		else if(pUser->GetUserStatus(CONST_USER_STATUS_ATTENTION))
		{

		}
		//拒绝聊天信息
		else if(pUser->GetUserStatus(CONST_USER_STATUS_REFUSECHAT))
		{

		}
		//发言
		else if(pUser->mbyVoiceState == STRU_USRE_INFO::SPEAKING)
		{

		}
		//对聊
		else if(pUser->mbyVoiceState == STRU_USRE_INFO::PRIVATETALK)
		{

		}
		//有摄像头
		else if(pUser->GetUserStatus(CONST_USER_STATUS_HAVEVIDEO))
		{

		}
	}
	else
	{	
		if(pNode->mpPeerImage != NULL)
		{
			pNode->mpPeerImage->SetVisible(false);
		}
	}
}

void CBaseTree::Sort()
{
	if(mbSort)
	{
		m_AllList.sort(SortProc);
		SetItemRect();
	}
}

void CBaseTree::SetItemRect()
{
	int liTop = - miViewRelaPos;
	list<CTreeNode*>::iterator iter = m_pNodeList->begin();
	for (; iter != m_pNodeList->end(); iter++)
	{
		::SetRect(&(*iter)->mrcClient, mrcClient.left, liTop, mrcClient.right, liTop+miItemHeight);
		if((*iter)->mpPeerImage)
			(*iter)->mpPeerImage->SetTop(liTop+2);
		liTop += miItemHeight;
	}
}

void CBaseTree::RePaint()
{
	InvalidateRect(mhParent, &mrcClient, FALSE);
}

void CBaseTree::SetSearchState(bool abValue)
{
	if(mbSeaching != abValue)
	{
		mbSeaching = abValue;
		if(mbSeaching)
			m_pNodeList = &m_SearchList;
		else
			m_pNodeList = &m_AllList;
	}
}

bool CBaseTree::KeyInItem(const PSTRU_USER_INFO pUser, const wchar_t* pKey)
{
	CString lstrID;
	lstrID.Format(L"%I64d", pUser->mi64UserID);
	return pUser->macNickName.Find(pKey) != -1 || lstrID.Find(pKey) != -1;
	return true;
}

bool CBaseTree::FindPositionNode(CTreeNode*& pNode, CPoint point)
{
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;
	RECT lrcView = mrcClient;
	if(m_VScrollBar.GetVisible())
	{
		lrcView.right -= 17;
	}
	if( PtInRect(&lrcView, point))
	{
		list<CTreeNode*> ::iterator iter = find_if(m_pNodeList->begin(), m_pNodeList->end(), FindPosNode(pt));
		if(iter != m_pNodeList->end())
		{
			pNode = *iter;
			return true;
		}
	}
	return false;
}