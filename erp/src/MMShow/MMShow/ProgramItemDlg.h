#pragma once

class CProgramItemDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	enum { IDD = IDD_PPROGRAMITEM };

public:
	CProgramItemDlg(LPCTSTR pcszCaption,CWnd* pParent = NULL); 
	virtual ~CProgramItemDlg();

	BOOL IsWebPage(void) const;
	void SetWebPage(BOOL bWebPage);

	const CString& GetName(void) const;
	void SetName(const CString &strName);

	const CString& GetPath(void) const;
	void SetPath(const CString &strPath);

	const CString& GetDesc(void) const;
	void SetDesc(const CString &strDesc);

protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual void OnOK(void);

	afx_msg void OnChangeType(void);
	afx_msg void OnBnClickedBtnSelectFile(void);

	LPCTSTR m_pcszCaption;

	BOOL m_bWebPage;
	CString m_strName;
	CString m_strPath;
	CString m_strDesc;
};

inline BOOL CProgramItemDlg::IsWebPage(void) const {
	return m_bWebPage;
}

inline void CProgramItemDlg::SetWebPage(BOOL bWebPage) {
	m_bWebPage = bWebPage;
}

inline const CString& CProgramItemDlg::GetName(void) const {
	return m_strName;
}

inline void CProgramItemDlg::SetName(const CString &strName) {
	m_strName = strName;
}

inline const CString& CProgramItemDlg::GetPath(void) const {
	return m_strPath;
}

inline void CProgramItemDlg::SetPath(const CString &strPath) {
	m_strPath = strPath;
}

inline const CString& CProgramItemDlg::GetDesc(void) const {
	return m_strDesc;
}

inline void CProgramItemDlg::SetDesc(const CString &strDesc) {
	m_strDesc = strDesc;
}