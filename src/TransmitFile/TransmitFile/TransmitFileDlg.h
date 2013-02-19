// TransmitFileDlg.h : 头文件
//

#pragma once
#include <strstream>
#include <string>

// CTransmitFileDlg 对话框
class CTransmitFileDlg : public CDialog
{
// 构造
public:
	CTransmitFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TRANSMITFILE_DIALOG };

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
	afx_msg void OnBnClickedBtnRecvFile();
public:
	afx_msg void OnBnClickedBtnSendFile();
public:
	afx_msg void OnBnClickedBtnClose();
public:
	afx_msg void OnBnClickedBtnFilePath();
public:
	CString m_strFilePath;
public:
	CString m_strBuddyIp;
public:
	short m_sBuddyPort;
public:
	CString m_strSelfInternetIp;
public:
	CString m_strSelfLocalIp;
public:
	short m_sSelfLocalPort;
public:
	short m_sSelfInternetPort;
public:
	CString m_strBuddyNatType;
public:
	CString m_strSelfNatType;
public:
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	afx_msg BOOL OnDeviceChange(UINT nEventType,DWORD_PTR dwData );
};
