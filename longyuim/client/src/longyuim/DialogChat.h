#pragma once


// CDialogChat dialog

class CDialogChat : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogChat)

public:
	CDialogChat(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogChat();

// Dialog Data
	enum { IDD = IDD_DIALOG_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
