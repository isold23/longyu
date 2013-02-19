#pragma once

class CUser
{
public:
	CUser(void);
	~CUser(void);


	int GetId(void) const;
	const CString& GetName(void) const;
	void SetId(int nUserId,const CString &strName);
 
	int GetGroupId(void) const;
	const CString& GetGroupName(void) const;
	const CString& GetGroupIntro(void) const;

	void SetUserInfo(int nGroupId, CString strGroupName, CString strGroupIntro);
 

private:
	int m_nUserId;
	CString m_strName;

	int m_nGroupId;
	CString m_strGroupName;
	CString m_strGroupIntro;
};

extern CUser g_user;


inline int CUser::GetId(void) const {
	ASSERT(m_nUserId >= 0);
	return m_nUserId;
}

inline const CString& CUser::GetName(void) const {
	return m_strName;
}

inline void CUser::SetId(int nUserId,const CString &strName) {
	ASSERT(m_nUserId < 0);
	m_nUserId = nUserId;
	m_strName = strName;
}

 
inline int CUser::GetGroupId(void) const {
	return m_nGroupId;
}

inline const CString& CUser::GetGroupName(void) const {
	return m_strGroupName;
}

inline const CString& CUser::GetGroupIntro(void) const {
	return m_strGroupIntro;
}

inline void CUser::SetUserInfo(int nGroupId, CString strGroupName, CString strGroupIntro) {
	m_nGroupId = nGroupId;
	m_strGroupName = strGroupName;
	m_strGroupIntro = strGroupIntro;
}