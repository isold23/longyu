#pragma once

class COptions
{
public:
	COptions(void);
	~COptions(void);

	BOOL Load(void);
	BOOL Save(void);

	const CString& GetDBAddr(void) const;
	void SetDBAddr(const CString &strAddr);

	CString GetDBConnString(LPCTSTR pcszDBAddr) const;

private:
	BOOL m_bModified;
	CString m_strDBAddr;
};

extern COptions g_ops;

inline const CString& COptions::GetDBAddr(void) const {
	return m_strDBAddr;
}

inline void COptions::SetDBAddr(const CString &strAddr) {
	if (m_strDBAddr != strAddr) {
		m_bModified = TRUE;
		m_strDBAddr = strAddr;
	}
}
