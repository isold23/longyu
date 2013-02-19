#pragma once

class CCustomDraw
{
public:
	CCustomDraw();
};

class CUIObject
{
	enum StretcType{NOStretch, StretctH, StretcV, StretchBoth};
public:
	CUIObject(HWND ahParent, int aiLeft, int aiTop, int aiwidth, int aiHeight);
	virtual ~CUIObject(){}
	bool IsVisible(){return mbVisible;}
	bool IsChecked(){return mbChecked;}
	bool IsEnable(){return mbEnable;}
	void SetVisible(bool abValue);
	void SetChecked(bool abValue);
	void SetEnable(bool abValue);
	void SetBold(bool abValue);
	void SetUnderLine(bool abValue);
	void Paint(HDC ahdc);
	void SetBackImage(Image* pImage);
private:
	void DrawBack(HDC ahdc);
	void DrawCaption(HDC ahdc);
private:
	HWND mhParent;
	bool mbChecked;
	bool mbVisible;
	bool mbEnable;
	bool mbMouseOver;
	Image* mpImage;
	CString mstrCaption;

	int  miLeft;
	int  miTop;
	int  miWidth;
	int  miHeight;
	RECT mrcClient;

	COLORREF mclCaptionColor;
	bool mbBold;
	bool mbUnderLine;

	StretcType mstrctchType;
};

interface IView
{
	virtual void OnVScroll(int aiValue) = 0; 
};

class CUCScrollBar
{
public:
	CUCScrollBar(HWND hParent, IView* pView);
	virtual ~CUCScrollBar();
	void SetRect(int aiLeft, int aiTop, int aiWidth, int aiHeight);
	bool GetVisible();
	void Paint(HDC hdc);
	void SetTotalHeight(int aiValue);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMouseLeave();
	void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnTimer(UINT_PTR nIDEvent);
private:
	void RePaint();
	void Scroll(int aiValue);
	void CalcScrollBar();
private:
	RECT mrcClient;
	RECT mrcTop;
	RECT mrcBottom;
	RECT mrcTrack;
	RECT mrcMid;
	bool mbVisible;
	bool mbTrackMouseDown;
	bool mbUpMouseDown;
	bool mbDownMouseDown;
	bool mbMidMouseDown;
	bool mbTrackMouseOver;
	bool mbUpMouseOver;
	bool mbDownMouseOver;
	int miTotalHeight;		//所有Item高度和
	int miViewRelaPos;		//相对起始位置 
	int miViewHeight;		//控件可见高度
	int miTrackTop;			//滑块顶部位置
	int miTrackLength;      //滑块高度
	int miPreMousePosY;
	int miScrollStep;       //滚动步长 
	int miArrowH;
	Image* mpImage;
	IView* mpView;
	HWND mhParent;
	UINT_PTR muiTimer;
	DWORD mwDragTime;
};

//template<class T>
class CTreeNode
{
public:
	CTreeNode();
	~CTreeNode();
	RECT mrcClient;
	IImageEx* mpPeerImage;
	Image* mpHeadImage;
	void* mpData;
};

#define WM_LCLICK_ITEM WM_USER+116
#define WM_RCLICK_ITEM WM_USER+117

class CBaseTree:public IView
{
public:
	CBaseTree(HWND hParent);
	virtual ~CBaseTree();
	virtual void OnVScroll(int aiValue); 
	void SetRect(int aiLeft, int aiTop, int aiWidth, int aiHeight);
	void SetVisible(bool abValue);
	void Paint(HDC hdc);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMouseLeave();
	void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnTimer(UINT_PTR nIDEvent);
	void InsertItem(CTreeNode* pNode);
	void DeleteItem(__int64 aiUserID);
	void ClearAllItems();
	void Search(const wchar_t* pKeyWords);
private:
	void DrawItem(HDC hdc, CTreeNode* pNode);
	void Sort();
	void SetItemRect();
	void RePaint();
	void SetSearchState(bool abValue);
	bool KeyInItem(const PSTRU_USER_INFO pUser, const wchar_t* pKey);
	bool FindPositionNode(CTreeNode*& pNode, CPoint point);
private:
	bool mbSort;
	RECT mrcClient;
	bool mbVisible;
	int miItemHeight;
	HWND mhParent;
	COLORREF mclBackColor;
	CUCScrollBar m_VScrollBar;
	list<CTreeNode*>* m_pNodeList;
	list<CTreeNode*> m_SearchList;
	list<CTreeNode*> m_AllList;
	int miViewRelaPos;		//相对起始位置
	int miTotalHeight;		//所有Item累计高度
	Image* mpImageState;	//状态图
	__int64 miSelUserID;
	bool mbSeaching;	    //搜索过滤中
};

class CBaseForm:public CDialog
{
public:
	CBaseForm(CWnd* pParent = NULL);   // 标准构造函数
	CBaseForm(UINT anIDTemplate,
		CWnd* apParentWnd = NULL );
	virtual ~CBaseForm();

};