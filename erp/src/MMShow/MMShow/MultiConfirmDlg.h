#pragma once


// CMultiConfirmDlg 对话框

class CMultiConfirmDlg : public CDialog
{
	DECLARE_DYNAMIC(CMultiConfirmDlg)

public:
	CMultiConfirmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMultiConfirmDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
