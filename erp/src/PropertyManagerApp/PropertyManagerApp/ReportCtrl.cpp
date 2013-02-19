#include "StdAfx.h"
#include "ReportCtrl.h"
#include "resource.h"
#include "DrawHelper.h"
#include "ReportPrinter.h"

CImageList g_ReportCtrlImagelist;
 

const CReportCtrl::ColInfo CReportCtrl::s_EditCols[] = { 
	{ _T("提交"),		CReportCtrl::OpColWidth,		TRUE,	FALSE },	
	{ _T("重置"),		CReportCtrl::OpColWidth,		TRUE,	FALSE },	
	{ _T("删除"),		CReportCtrl::OpColWidth,		TRUE,	FALSE },
};


CReportCtrl::CReportCtrl(void)
{

	if (g_ReportCtrlImagelist.GetSafeHandle() == NULL)
	{
		g_ReportCtrlImagelist.Create(16,16,ILC_MASK|ILC_COLOR32,5,1);
		g_ReportCtrlImagelist.Add(AfxGetApp()->LoadIcon(IDI_OK));
		g_ReportCtrlImagelist.Add(AfxGetApp()->LoadIcon(IDI_RESET));
		g_ReportCtrlImagelist.Add(AfxGetApp()->LoadIcon(IDI_DEL));
		g_ReportCtrlImagelist.Add(AfxGetApp()->LoadIcon(IDI_ADD));
		g_ReportCtrlImagelist.Add(AfxGetApp()->LoadIcon(IDI_MANAGERS));
		g_ReportCtrlImagelist.Add(AfxGetApp()->LoadIcon(IDI_OPS));
	}

	SetImageList(&g_ReportCtrlImagelist);
	m_pSubmitOpCol = NULL;
	m_pDeleteOpCol = NULL;
	m_pResetOpCol = NULL;
	m_pAddOpRecord = NULL;
	m_cols = NULL;
	m_nColCount = 0;
	m_pPrinter = NULL;
 
}

CReportCtrl::~CReportCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CReportCtrl,CXTPReportControl)
	ON_NOTIFY_REFLECT_EX(XTP_NM_REPORT_VALUECHANGED, &CReportCtrl::OnValueChanged)
	ON_NOTIFY_REFLECT_EX(XTP_NM_REPORT_ITEMBUTTONCLICK, &CReportCtrl::OnItemButtonClick)
END_MESSAGE_MAP()
  
void CReportCtrl::AlertError(LPCTSTR pcszText,int nErrCode)  
{
	CString str;
	if (nErrCode != 0)
	{
		str.Format(_T("%s  错误码:%d"),pcszText,nErrCode); 
		pcszText = str;
	}
	MessageBox(pcszText,_T("错误提示"),MB_ICONSTOP); 
} 

void CReportCtrl::DoPrint(void)
{ 
	if (m_pPrinter == NULL)
	{
		m_pPrinter = new CReportPrinter();
		m_pPrinter->DoPrint(this);
	}
}


void CReportCtrl::OnPrintEnd(void)
{
	ASSERT(m_pPrinter != NULL);
	m_pPrinter->DestroyWindow();
	m_pPrinter = NULL;
}

  

CXTPReportRecordItem* CReportCtrl::NewButtonItem(int nIcon)
{
	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	CXTPReportRecordItemControl* pButton = pItem->GetItemControls()->AddControl(xtpItemControlTypeButton); 
	pButton->SetAlignment(xtpItemControlLeft);
	pButton->SetIconIndex(PBS_NORMAL, nIcon);
	pButton->SetIconIndex(PBS_PRESSED,nIcon);
	pButton->SetSize(CSize(OpColWidth, 0));
	pItem->SetEditable(TRUE);
	return pItem;
}

void CReportCtrl::Initialize(const CReportCtrl::ColInfo cols[], int nColCount, UINT nOpFlag)
{
	m_nOpFlag = nOpFlag;
	m_cols = cols;
	m_nColCount = nColCount;

	AllowEdit(nOpFlag != 0);
	SetGridStyle(FALSE,xtpReportGridSolid);
	GetPaintManager()->SetColumnStyle(xtpReportColumnResource);
	GetPaintManager()->m_strNoItems.Empty();

	for (int i=0; i<nColCount; ++i)
	{
		const ColInfo &c = cols[i];
		if (c.fmt != FmtIdOnly)
		{
			CXTPReportColumn *pCol = new CXTPReportColumn(GetColumns()->GetCount(),c.caption,c.width,
			!c.fixed,XTP_REPORT_NOICON,c.sortable);
			pCol->AllowRemove(FALSE);
			pCol->SetAllowDrag(FALSE);
			AddColumn(pCol);
		}
	}

	if (nOpFlag & OpModify)
		m_pSubmitOpCol = AddOpCol(IndexModify);
	if (nOpFlag & OpReset)
		m_pResetOpCol = AddOpCol(IndexReset);
	if (nOpFlag & OpDelete)
		m_pDeleteOpCol = AddOpCol(IndexDelete);
 

}

CXTPReportColumn* CReportCtrl::AddOpCol(int i)
{ 
	const ColInfo &c = s_EditCols[i];
	CXTPReportColumn *pCol = new CXTPReportColumn(GetColumns()->GetCount(),c.caption,c.width,FALSE,XTP_REPORT_NOICON,FALSE);
	pCol->AllowRemove(FALSE);
	pCol->SetAllowDrag(FALSE);
	AddColumn(pCol);
	return pCol;
}

CXTPReportRecordItem* CReportCtrl::RecordItemFromCol(const ColInfo &c,const _variant_t &v)
{
	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	pItem->SetEditable(c.editable);
	if (!c.check)
	{
		pItem->SetCaption(CString(v));
	}
	else
	{
		pItem->HasCheckbox(c.check); 
		pItem->SetChecked((bool)v);
	}
	return pItem;
}

void CReportCtrl::PutRecordAux(CXTPReportRecord *pRec)
{
	if (m_nOpFlag & OpId)
		CopyRecId(pRec);
	if (m_nOpFlag & OpModify)
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexModify));
	if (m_nOpFlag & OpReset)
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexReset));
	if (m_nOpFlag & OpDelete)
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexDelete));
}
 
void CReportCtrl::PutAddRecordAux(void)
{
	//if (m_nOpFlag & OpModify)
		m_pAddOpRecord->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexAdd));
	//if (m_nOpFlag & OpReset)
		m_pAddOpRecord->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexReset));
	//if (m_nOpFlag & OpDelete)
	//	m_pAddOpRecord->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexReset));
}

 
void CReportCtrl::FillRecordset(_RecordsetPtr &rst,FillRecordAux funcAux)
{ 
	if (rst != NULL)
		while (!rst->adoEOF)
		{
			FieldsPtr fields = rst->Fields;
			CXTPReportRecord *pRec = new CXTPReportRecord();
			for (int i=0; i<m_nColCount; ++i)
			{
				if (m_cols[i].fmt ==FmtIdOnly)
					pRec->SetBookmark(fields->Item[m_cols[i].field]->Value);
				else
					pRec->AddItem(RecordItemFromCol(m_cols[i],fields->Item[m_cols[i].field]->Value));

			}

			PutRecordAux(pRec);
			if (funcAux != NULL)
				funcAux(fields,pRec);

			AddRecord(pRec);
			rst->MoveNext();
		}

	if (m_nOpFlag & OpAdd)
	{
		m_pAddOpRecord = new CXTPReportRecord();
		for (int i=0; i<m_nColCount; ++i)
		{
			const ColInfo &col= m_cols[i];
			
			if (m_cols[i].fmt != FmtIdOnly)
			{
				CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
				pItem->HasCheckbox(col.check);
				m_pAddOpRecord->AddItem(pItem); 
			}
		}

		PutAddRecordAux();
		AddRecord(m_pAddOpRecord);
	}

	Populate();
}
 
void CReportCtrl::ClearAddRecord(void)
{
	ASSERT(m_pAddOpRecord != NULL);

	for (int i=0; i<m_nColCount; ++i)
	{
		if (m_cols[i].check)
			m_pAddOpRecord->GetItem(i)->SetChecked(FALSE);
		else
			m_pAddOpRecord->GetItem(i)->SetCaption(_T(""));
	}
}



BOOL CReportCtrl::OnValueChanged(NMHDR* pNotifyStruct, LRESULT *pResult)
{
 
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	CXTPReportRecordItem *pItem = pItemNotify->pItem;

	CString str;
	if (GetInplaceList()->GetSafeHwnd() != NULL)
		return FALSE;
	else
		GetInplaceEdit()->GetWindowText(str);

	
	str.Trim();
	switch (m_cols[pItem->GetIndex()].fmt)
	{
	case FmtStr:
		pItem->SetCaption(str);
		break;

	case FmtId:
		{
			int nId = _ttoi(str);
			if (nId > 0)
			{
				pItem->SetCaption(CNumericString(nId));
			}
			else
			{
				AlertError(_T("请填入正确的数值"));
				return TRUE;
			}
		}
		break;

	case FmtIdStr:
		if (!str.IsEmpty())
		{
			pItem->SetCaption(str);
		}
		else
		{
			AlertError(_T("字段不能为空,请重新输入"));
			return TRUE;
		} 
		break;
	}
	return TRUE;
}

BOOL CReportCtrl::OnItemButtonClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	if(!(pItemNotify->pRow && pItemNotify->pItem && pItemNotify->pItemControl))
		return TRUE;

	if (!(m_nOpFlag&OpModify))
		return FALSE;

	CXTPReportRecord *pRec = pItemNotify->pRow->GetRecord();
	if (IsAddOpRecord(pRec) && IsDeleteOpCol(pItemNotify->pItem))
	{
		ClearAddRecord();
		return TRUE;
	}

	return FALSE;
}

CXTPReportRecord* CReportCtrl::TransferAddRecord(void)
{
	ASSERT (m_pAddOpRecord != NULL);

	CXTPReportRecord *pRec = new CXTPReportRecord();
	for (int i=0; i<m_nColCount; ++i)
	{
		const ColInfo &col = m_cols[i];
		if (col.fmt != FmtIdOnly)
		{
			CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
			if (!col.check)
			{
				pItem->SetCaption(m_pAddOpRecord->GetItem(i)->GetCaption(NULL));
			}
			else
			{
				pItem->SetEditable(col.editable);
				pItem->HasCheckbox(col.check); 
				pItem->SetChecked(m_pAddOpRecord->GetItem(i)->IsChecked());
			}
			pRec->AddItem(pItem);
		}
	}

	PutRecordAux(pRec);

	GetRecords()->InsertAt(m_pAddOpRecord->GetIndex(),pRec);
	ClearAddRecord();
	
	Populate();

	return pRec;
 
}


void CReportCtrl::DeleteRecord(CXTPReportRecord *pRec)
{
	GetRecords()->RemoveRecord(pRec);
	Populate();
}

void CReportCtrl::RemoveEditOptions(CXTPReportRecordItem *pItem,DWORD_PTR dwData)
{
	CXTPReportRecordItemEditOptions *pEditOptions = pItem->GetEditOptions(NULL);
	ASSERT(pEditOptions != NULL);

	CXTPReportRecordItemConstraints *pConstraints = pEditOptions->GetConstraints();
	ASSERT(pConstraints != NULL);

	CXTPReportRecordItemConstraint *pConstraint = pEditOptions->FindConstraint(dwData);
	ASSERT (pConstraint != NULL);

	CDWordArray dwDatas;
	CStringArray strConstraints;

	for (int i=0; i<pConstraints->GetCount(); ++i)
	{
		CXTPReportRecordItemConstraint *pConstraint = pConstraints->GetAt(i);
		if (pConstraint->m_dwData != dwData)
		{
			dwDatas.Add(pConstraint->m_dwData);
			strConstraints.Add(pConstraint->m_strConstraint);
		}
	}

	pConstraints->RemoveAll();
	for (int i=0; i<dwDatas.GetCount(); ++i)
		pEditOptions->AddConstraint(strConstraints[i],dwDatas[i]);
}
