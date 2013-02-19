#pragma once
class CXmlNode;

class CHistoryCtrl : public CComboBox
{
	DECLARE_MESSAGE_MAP()

public:
	CHistoryCtrl(LPCTSTR pcszTagName);
	virtual ~CHistoryCtrl(void);

	void Add(const CString &strText);

	BOOL Load(CXmlNode &node);
	BOOL Save(CXmlNode &node);

	LPCTSTR GetTagName(void) const;

private:
	afx_msg void OnSelChange(void);
	
	LPCTSTR m_pcszTagName;
};

inline LPCTSTR CHistoryCtrl::GetTagName(void) const {
	return m_pcszTagName;
}


