#pragma once
#include "MapWnd/MapWnd.h"
#include "ListDlgs/ListDlg.h"
#include "Pane/NavigatorBar.h"
#include "PictureCtrl.h"
#include "BkgndDlgs/BkgndDlg.h"

class CPropertyManagerAppDoc;


class CPropertyManagerAppView : public CXTPResizeFormView
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CPropertyManagerAppView)

	CPropertyManagerAppView(void); 

public: 
	enum {MAP,LIST,ENGINEER,BKGND};

public:
	CPropertyManagerAppDoc* GetDocument(void) const; 
	virtual ~CPropertyManagerAppView(void);
 
	CWnd* GetActiveChild(void);
	void SetActiveChild(CWnd *pChild);


	CMapWnd& GetMapWnd(void);
	CListDlg& GetListDlg(void);
	CPictureCtrl& GetPicCtrl(void);
	CBkgndDlg& GetBkgndDlg(void);
	
	afx_msg void OnMapToolbarCommand(UINT nCmd);
private: 

	virtual BOOL OnInitDialog(void);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	CWnd *m_pActiveChild;

	CMapWnd m_mapWnd;
	CListDlg m_listDlg;
	CPictureCtrl m_picCtrl;
	CBkgndDlg m_bkgndDlg;
};

inline CWnd* CPropertyManagerAppView::GetActiveChild(void) {
	return m_pActiveChild;
}

inline CMapWnd& CPropertyManagerAppView::GetMapWnd(void) {
	return m_mapWnd;
}

inline CListDlg& CPropertyManagerAppView::GetListDlg(void) {
	return m_listDlg;
}

inline CPictureCtrl& CPropertyManagerAppView::GetPicCtrl(void) {
	return m_picCtrl;
}

inline 	CBkgndDlg& CPropertyManagerAppView::GetBkgndDlg(void) {
	return m_bkgndDlg;
}
