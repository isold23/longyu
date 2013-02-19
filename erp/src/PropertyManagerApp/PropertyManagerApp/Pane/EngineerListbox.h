#pragma once

class CPictureCtrl;

class CEngineerListbox : public CListBox
{
	DECLARE_MESSAGE_MAP()
public:
	CEngineerListbox(void);
	virtual ~CEngineerListbox(void);

	void SetBindWnd(CPictureCtrl *pPicCtrl);

protected:
	CPictureCtrl *m_pPicCtrl;
};

inline void CEngineerListbox::SetBindWnd(CPictureCtrl *pPicCtrl) {
	m_pPicCtrl = pPicCtrl;
}


