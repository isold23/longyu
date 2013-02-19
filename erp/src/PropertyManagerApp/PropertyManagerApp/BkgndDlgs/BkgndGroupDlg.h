#pragma once

#include "../ReportCtrl.h"
#include "../ReportPageDlg.h"
struct tagOpDesc;
struct tagGroupDesc;

class CBkgndGroupDlg : public CReportPageDlg
{
	DECLARE_MESSAGE_MAP()
   
	enum GroupColIndex { GName, GIntro, GModify, GDelete }; 
	enum RecType { RecTop,RecNormal,RecOpsTop,RecOpsNormal,RecOpTop,RecOpNormal,RecChildRecs };

public:
	enum { IDD = IDD_BKGND_GROUP };

public:
	CBkgndGroupDlg(CWnd* pParent = NULL);  
	virtual ~CBkgndGroupDlg(void);

protected:
	afx_msg void OnGroupItemButtonClick(NMHDR * pNotifyStruct, LRESULT *pResult); 
	afx_msg void OnGroupItemValueChanged(NMHDR * pNotifyStruct, LRESULT *pResult);

	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);   

	void InitGroupList(void); 
	void FillGroupListRecord(void);

	CXTPReportRecord* NewGroupRecord(tagGroupDesc *pGroup,BOOL bTop);
	CXTPReportRecord* NewRecordsRecord(tagGroupDesc *pGroup,BOOL bTop);
	CXTPReportRecord* NewOpsRecord(tagGroupDesc *pGroup,BOOL bTop);
	CXTPReportRecord* NewOpRecord(tagOpDesc *pOp,BOOL bTop);
	CXTPReportRecord* BuildGoupListRecord(tagGroupDesc *pGroup,BOOL bTop);
	void SetRecordObject(CXTPReportRecord *pRec,int nRecType,void *pObject);
	int GetRecordObject(CXTPReportRecord *pRec,tagGroupDesc *&pGroup,tagOpDesc *&pOp);


 
	void ClearRecordText(CXTPReportRecord *pRec);
	void GetRecordText(CXTPReportRecord *pRec,CString &strName, CString &strIntro);
 
	

	CReportCtrl m_listGroup;
  
};
