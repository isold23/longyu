#pragma once 
#include "MapListbox.h"
#include "ListPane.h"
#include "EngineerListbox.h"
#include "BkgndTreeCtrl.h"

class CVecWnd;
class CListDlg;
class CBkgndDlg;
class CPictureCtrl;
class CPropertyManagerAppView;

class CNavigatorBar : public CXTPShortcutBar
{
	DECLARE_MESSAGE_MAP()

public:
	CNavigatorBar(void);
	~CNavigatorBar(void);

	void SetBindWnd(CMapWnd *pMapWnd,CListDlg *pListDlg, CBkgndDlg *pBkgndDlg,CPictureCtrl *pPicCtrl);

	int GetActiveChild(void);
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID);

	BOOL BeforeClose(void); 
private:  

	CMapListbox m_mapListbox;
	CXTPShortcutBarPane m_mapListboxPane;

	CListPane m_listPane;
	CXTPShortcutBarPane m_listTreeCtrlPane;

	CEngineerListbox m_engineerListbox;
	CXTPShortcutBarPane m_engineerListboxPane;

	CBkgndTreeCtrl m_bkgndTreeCtrl;
	CXTPShortcutBarPane m_bkgndListboxPane;

	CImageList m_imageList;

};
 

class CNavigatorBarSplitter : public CXTPSplitterWndEx
{
	static const int MIN_WIDTH = 32;

	void TrackColumnSize(int x, int col);
};