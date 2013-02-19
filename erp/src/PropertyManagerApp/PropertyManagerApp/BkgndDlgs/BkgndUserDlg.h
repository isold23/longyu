#pragma once
#include "../ReportCtrl.h"
#include "../ReportPageDlg.h" 
#include "afxwin.h"

class CBkgndUserDlg : public CReportPageDlg
{
	DECLARE_MESSAGE_MAP()

	enum GroupColIndex { GId, GName, GIntro, GOpId, GOpName };
	enum AdminColIndex { AGrade,AName,AOp,AGroup,AUser,AIntro };
public:
	enum { IDD = IDD_BKGND_USER };

public:
	CBkgndUserDlg(CWnd* pParent = NULL);   
	virtual ~CBkgndUserDlg(void);


protected:
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);     
 
	afx_msg void OnUserItemButtonClick(NMHDR * pNotifyStruct, LRESULT *pResult); 
	afx_msg void OnUserItemValueChanged(NMHDR * pNotifyStruct, LRESULT *pResult);

	void InitUserList(void); 
	void FillUserListRecord(void);

	void InitGroupList(void); 
	void FillGroupListRecord(void);
	CXTPReportRecord* NewGroupRecord(tagGroupDesc *pGroup);
	CXTPReportRecord* BuildGoupListRecord(tagGroupDesc *pGroup);
 

	CEdit m_editPwd;
	CReportCtrl m_listUser;

	CReportCtrl m_listGroup;
 
};
