#pragma once

class CFolderDialog
{
public:
	CFolderDialog(void);
	~CFolderDialog(void);

	INT_PTR DoModal(HWND hWnd);

	const CString& GetPathName(void) const;
private:
	CString m_strPath;
};

inline const CString& CFolderDialog::GetPathName(void) const {
	return m_strPath;
}
