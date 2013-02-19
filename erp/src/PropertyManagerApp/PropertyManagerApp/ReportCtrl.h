#pragma once
#include "Sql/sql.h"

class CReportPrinter;

class CReportCtrl : public CXTPReportControl
{ 
	DECLARE_MESSAGE_MAP()

public:
	enum { OpColWidth = 35 };
	
	enum { FmtNon, FmtId, FmtIdStr, FmtStr, FmtIdOnly };

	enum { IndexModify, IndexReset, IndexDelete, IndexAdd, IndexManager, IndexOp };
	enum { OpNone, OpModify=0x01, OpReset=0x02, OpDelete=0x04, OpAdd=0x08, OpId=0x10,
		OpExceptReset=OpModify|OpDelete|OpAdd,OpAll=OpExceptReset|OpReset };

	struct ColInfo 
	{ 
		LPCTSTR caption;
		UINT width; 
		BOOL fixed;
		BOOL sortable;  

		LPCTSTR field;
		BOOL check;
		BOOL editable;
		BYTE fmt;
	};

 	static const ColInfo s_EditCols[];

	typedef void (*FillRecordAux)(FieldsPtr &fields,CXTPReportRecord *pRec);
public:
	CReportCtrl(void);
	~CReportCtrl(void);
 
	void Initialize(const ColInfo cols[], int nColCount,UINT nOpFlag=OpNone);
	void FillRecordset(_RecordsetPtr &rst,FillRecordAux funcAux=NULL);
 

	void AlertError(LPCTSTR pcszText,int nErrCode=0);

	BOOL IsSubmitOpCol(CXTPReportColumn *pCol);
	BOOL IsSubmitOpCol(CXTPReportRecordItem *pCol);

	BOOL IsDeleteOpCol(CXTPReportColumn *pCol);
	BOOL IsDeleteOpCol(CXTPReportRecordItem *pCol);


	BOOL IsResetOpCol(CXTPReportColumn *pCol);
	BOOL IsResetOpCol(CXTPReportRecordItem *pCol);


	BOOL IsAddOpRecord(CXTPReportRecord *pCol);
	BOOL IsAddOpRecord(CXTPReportRecordItem *pCol);

	void ClearAddRecord(void);
	CXTPReportRecord* TransferAddRecord(void);

	void DeleteRecord(CXTPReportRecord *pRec);

	void DoPrint(void); 
	void ResetPrinter(void);
	void OnPrintEnd(void);


	static CXTPReportRecordItem* NewButtonItem(int nIcon);
	static void RemoveEditOptions(CXTPReportRecordItem *pItem,DWORD_PTR dwData);
protected:	
	afx_msg BOOL OnValueChanged(NMHDR* pNotifyStruct, LRESULT *pResult);
	afx_msg BOOL OnItemButtonClick(NMHDR *pNotifyStruct, LRESULT *pResult);

	CXTPReportColumn* AddOpCol(int i);


	void PutRecordAux(CXTPReportRecord *pRec);
	CXTPReportRecordItem* RecordItemFromCol(const ColInfo &c,const _variant_t &v);

	void PutAddRecordAux(void);

	CXTPReportColumn *m_pSubmitOpCol;
	CXTPReportColumn *m_pDeleteOpCol;
	CXTPReportColumn *m_pResetOpCol;
	CXTPReportRecord *m_pAddOpRecord;

	UINT m_nOpFlag;

	const ColInfo *m_cols;
	int m_nColCount;

	CReportPrinter *m_pPrinter;
};
 

inline void CReportCtrl::ResetPrinter(void) { m_pPrinter = NULL; }

 
inline BOOL CReportCtrl::IsSubmitOpCol(CXTPReportColumn *pCol) { ASSERT(pCol->GetControl()==this); return pCol == m_pSubmitOpCol; }
inline BOOL CReportCtrl::IsSubmitOpCol(CXTPReportRecordItem *pItem) { return pItem->GetIndex() == m_pSubmitOpCol->GetIndex(); }

inline BOOL CReportCtrl::IsDeleteOpCol(CXTPReportColumn *pCol) { ASSERT(pCol->GetControl()==this);  return pCol == m_pDeleteOpCol; }
inline BOOL CReportCtrl::IsDeleteOpCol(CXTPReportRecordItem *pItem) { return pItem->GetIndex() == m_pDeleteOpCol->GetIndex(); }


inline BOOL CReportCtrl::IsResetOpCol(CXTPReportColumn *pCol) { ASSERT(pCol->GetControl()==this);  return pCol == m_pResetOpCol; }
inline BOOL CReportCtrl::IsResetOpCol(CXTPReportRecordItem *pItem) { return pItem->GetIndex() == m_pResetOpCol->GetIndex(); }


inline BOOL CReportCtrl::IsAddOpRecord(CXTPReportRecord *pRec) {  return pRec == m_pAddOpRecord; }
inline BOOL CReportCtrl::IsAddOpRecord(CXTPReportRecordItem *pItem) { return pItem->GetRecord() == m_pAddOpRecord; }

inline int RecId(CXTPReportRecord *pRec) { return pRec->GetBookmark().intVal; } 
inline void SetRecId(CXTPReportRecord *pRec,int val) {  pRec->SetBookmark(_variant_t(val)); } 
inline void CopyRecId(CXTPReportRecord *pRec) { pRec->SetBookmark(_variant_t(_ttoi(pRec->GetItem(0)->GetCaption(NULL)))); }

inline CString StrRec(CXTPReportRecord *pRec,int nIndex) { return pRec->GetItem(nIndex)->GetCaption(NULL); }
inline int IntRec(CXTPReportRecord *pRec,int nIndex) { return _ttoi(StrRec(pRec,nIndex)); }
inline bool BoolRec(CXTPReportRecord *pRec,int nIndex) { return pRec->GetItem(nIndex)->IsChecked()==TRUE; }