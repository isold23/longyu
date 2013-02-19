#pragma once
#include "../UI/UIControl.h"

// CUserList 对话框

class CUserList : public CDialog
{
	DECLARE_DYNAMIC(CUserList)

public:
	CUserList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserList();

// 对话框数据
	enum { IDD = IDD_DIALOG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CBaseTree* mpTreeCtrl;
public:
	void Initialize();
	void AddUser(void* pDate);
	void DelUser(__int64 ai64UserID);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
private:
	bool mbTrackLeaveMsg;
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
