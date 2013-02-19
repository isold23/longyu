// WatchColorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CWatchColorDlg 对话框
class CWatchColorDlg : public CDialog
{
// 构造
public:
	CWatchColorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WATCHCOLOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_StaticColorView;
public:
	CStatic m_StaticAd;
public:
	CEdit m_EditRGB;
public:
	CString m_StrCopyRight;
public:
	CStatic m_StaticCopyRight;
};
