#pragma once


class CLoginHistory
{
public:
	struct Record
	{
		CString User;
		CString Pwd;
		BOOL SavePwd;
	};

public:
	CLoginHistory(void);
	~CLoginHistory(void);

	BOOL Load(void);
	BOOL Save(void);

	void Clear(void);


	int GetAutoLogin(void) const;
	void Add(const CString &strUser,const CString &strPwd,BOOL bSavePwd,BOOL bAutoLogin);

	const Record& GetRecord(int i) const;
	int GetRecordCount(void) const;

private:
	CString m_strAutoLogin;
	CArray<Record,Record&> m_records;
};

extern CLoginHistory g_lhistory;



inline const CLoginHistory::Record& CLoginHistory::GetRecord(int i) const {
	return m_records[i];
}

inline int CLoginHistory::GetRecordCount(void) const {
	return m_records.GetCount();
}
