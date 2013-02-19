// downloadfileDlg.h : 头文件
//

#pragma once
#include "download/HttpDownload.h"

// CdownloadfileDlg 对话框
class CdownloadfileDlg : public CDialog
{
// 构造
public:
	CdownloadfileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DOWNLOADFILE_DIALOG };

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
	afx_msg void OnBnClickedBtnDownload();
public:
	CString m_strUrl;
public:
	CString m_strLocal;
public:
	afx_msg void OnBnClickedButton2();
public:
	CString m_strProxyIp;
public:
	CString m_strProxyPort;
public:
	CString m_strProxyPassword;
public:
	CString m_strProxyUserName;
public:
	afx_msg void OnBnClickedButton1();
public:
	CString m_strUploadFileName;
public:
	afx_msg void OnBnClickedBtnUpload();
};
