#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "../User.h"
#include "../ObjectDesc.h"
#include "BkgndGroupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CXTPReportRecord* CBkgndGroupDlg::NewGroupRecord(tagGroupDesc *pGroup,BOOL bTop)
{
	CXTPReportRecord *pRec = new CXTPReportRecord();
	// Name
	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	pItem->SetCaption(pGroup->Name); 
	pItem->SetIconIndex(CReportCtrl::IndexManager); 
	pItem->SetEditable(!bTop);
	pRec->AddItem(pItem); 

	// Intro
	pItem = new CXTPReportRecordItem();
	pItem->SetEditable(!bTop);
	pItem->SetCaption(pGroup->Intro);
	pRec->AddItem(pItem);

	if (!bTop)
	{
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexModify));
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexDelete));
	}


	SetRecordObject(pRec,bTop ? RecTop : RecNormal,pGroup);
	return pRec;
}

CXTPReportRecord* CBkgndGroupDlg::NewRecordsRecord(tagGroupDesc *pGroup,BOOL bTop)
{
	CXTPReportRecord *pRec = new CXTPReportRecord();


	// Caption
	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	pItem->SetIconIndex(CReportCtrl::IndexManager); 
	pItem->SetItemData(RecChildRecs);
	pRec->AddItem(pItem); 

	// Intro
	pRec->AddItem(new CXTPReportRecordItem()); 

	pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexAdd));
	pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexReset));

	SetRecordObject(pRec,RecChildRecs,pGroup);

	return pRec;
}

CXTPReportRecord* CBkgndGroupDlg::NewOpsRecord(tagGroupDesc *pGroup,BOOL bTop)
{
	CXTPReportRecord *pRec = new CXTPReportRecord();

	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	pItem->SetIconIndex(CReportCtrl::IndexOp); 
	pItem->SetEditable(!bTop);

	if (!bTop)
	{ 
		CXTPReportRecordItemEditOptions *pEditOptions = pItem->GetEditOptions(NULL);
		tagGroupDesc *pParent = pGroup->pParent;
		for (INT_PTR i=0; i<pParent->Ops.GetCount(); ++i)
		{
			INT_PTR j=0;
			for (; j<pGroup->Ops.GetCount(); ++j)
			{
				if (pParent->Ops[i].Id == pGroup->Ops[j].Id)
					break;
			}

			if (j == pGroup->Ops.GetCount())
				pEditOptions->AddConstraint(pParent->Ops[i].Name,(DWORD_PTR)&pParent->Ops[i]);

		}
		pEditOptions->m_bAllowEdit = FALSE;
		pEditOptions->AddComboButton(TRUE);
	}

	pItem->SetCaption(_T(""));
	pRec->AddItem(pItem);

	if (!bTop)
	{
		pItem = new CXTPReportRecordItem();
		pItem->SetItemData(0);
		pItem->SetEditable(FALSE);
		pRec->AddItem(pItem);

		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexAdd));
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexReset));
	}

	SetRecordObject(pRec,bTop ? RecOpsTop : RecOpsNormal,pGroup);

	return pRec;
}


CXTPReportRecord* CBkgndGroupDlg::NewOpRecord(tagOpDesc *pOp,BOOL bTop)
{
	CXTPReportRecord *pRec = new CXTPReportRecord();

	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	pItem->SetIconIndex(CReportCtrl::IndexOp); 
	pItem->SetEditable(FALSE); 
	pItem->SetCaption(pOp->Name); 
	pRec->AddItem(pItem);


	pItem = new CXTPReportRecordItem();
	pItem->SetCaption(pOp->Intro);
	pItem->SetEditable(FALSE);
	pRec->AddItem(pItem);

	pRec->AddItem(new CXTPReportRecordItem())->SetEditable(FALSE);

	if (!bTop)
		pRec->AddItem(CReportCtrl::NewButtonItem(CReportCtrl::IndexDelete));

	SetRecordObject(pRec,bTop ? RecOpTop : RecOpNormal,pOp);
	return pRec;
}

CXTPReportRecord* CBkgndGroupDlg::BuildGoupListRecord(tagGroupDesc *pGroup,BOOL bTop)
{
	CXTPReportRecord *pRec = NewGroupRecord(pGroup,bTop);
	CXTPReportRecord *ops = NewOpsRecord(pGroup,bTop);

	for (INT_PTR i=0; i<pGroup->Ops.GetCount(); ++i)
	{
		tagOpDesc *pOp = &pGroup->Ops[i];
		ops->GetChilds()->Add(NewOpRecord(pOp,bTop));
	}
	pRec->GetChilds()->Add(ops);

	CXTPReportRecord *recs = NewRecordsRecord(pGroup,bTop);	 
	for (INT_PTR j=0; j<pGroup->Childs.GetCount(); ++j)
		recs->GetChilds()->Add(BuildGoupListRecord(pGroup->Childs[j],FALSE));
	pRec->GetChilds()->Add(recs);

	return pRec;
}

inline void CBkgndGroupDlg::SetRecordObject(CXTPReportRecord *pRec,int nRecType,void *pObject)
{
	pRec->SetBookmark(_variant_t((ULONGLONG)pObject));
	pRec->GetItem(0)->SetItemData(nRecType);
}

inline int CBkgndGroupDlg::GetRecordObject(CXTPReportRecord *pRec,tagGroupDesc *&pGroup,tagOpDesc *&pOp)
{ 	
	CXTPReportRecordItem *pItem =  pRec->GetItem(0);
	int nRecType = pItem->GetItemData();
	switch (nRecType)
	{
	case RecOpTop:
	case RecOpNormal:
		pOp = (tagOpDesc*)(DWORD_PTR)pRec->GetBookmark().ullVal;
		pGroup = NULL;
		break;
	default:
		pGroup = (tagGroupDesc*)(DWORD_PTR)pRec->GetBookmark().ullVal;
		pOp = NULL;
		break;
	}

	return nRecType;
}

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

 
 
CBkgndGroupDlg::CBkgndGroupDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CBkgndGroupDlg::IDD, pParent)
{

}

CBkgndGroupDlg::~CBkgndGroupDlg()
{
}

void CBkgndGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup); 
}


BEGIN_MESSAGE_MAP(CBkgndGroupDlg, CReportPageDlg)
		ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED,IDC_LIST_GROUP,&CBkgndGroupDlg::OnGroupItemValueChanged)
		ON_NOTIFY(XTP_NM_REPORT_ITEMBUTTONCLICK, IDC_LIST_GROUP, &CBkgndGroupDlg::OnGroupItemButtonClick)
END_MESSAGE_MAP()


BOOL CBkgndGroupDlg::OnInitDialog(void)
{
	CReportPageDlg::OnInitDialog();

	InitGroupList(); 

	return TRUE;  
 
}


static CReportCtrl::ColInfo GroupListCols[] = { 
			{ _T("×éÃû"),			160,	FALSE,	FALSE,		_T(""),		FALSE,	TRUE,	CReportCtrl::FmtIdStr	},
			{ _T("ÃèÊö"),			160,	FALSE,	FALSE,		_T(""),		FALSE,	TRUE,	CReportCtrl::FmtStr		},
		};

void CBkgndGroupDlg::InitGroupList(void)
{
	SetResize(IDC_LIST_GROUP,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_STC_GROUP,XTP_ANCHOR_TOPLEFT,XTP_ANCHOR_BOTTOMRIGHT);
 


	m_listGroup.SetTreeIndent(5);
	m_listGroup.GetReportHeader()->AllowColumnRemove(FALSE);
	m_listGroup.Initialize(GroupListCols,_countof(GroupListCols),CReportCtrl::OpExceptReset);
	m_listGroup.GetColumns()->GetAt(0)->SetTreeColumn(TRUE);
 

	FillGroupListRecord();

} 

void CBkgndGroupDlg::FillGroupListRecord(void)
{
	m_listGroup.ResetContent(FALSE);

	CString strErrDesc;

	if (g_group.FromUserId(g_user.GetId(),strErrDesc) >= 0)
	{
		m_listGroup.AddRecord(BuildGoupListRecord(g_group.Childs[0],TRUE));
		m_listGroup.Populate();	
		m_listGroup.ExpandAll(TRUE);
	}

}

void CBkgndGroupDlg::OnGroupItemValueChanged(NMHDR * pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	CXTPReportRecordItem *pItem = pItemNotify->pItem;
	CXTPReportRecord *pRec = pItemNotify->pRow->GetRecord();

	ASSERT(m_listGroup.GetInplaceList()->GetSafeHwnd() != NULL);
	CXTPReportInplaceList *pList = m_listGroup.GetInplaceList();
	
	tagOpDesc *pOp; tagGroupDesc *pGroup;
	ASSERT(GetRecordObject(pRec,pGroup,pOp) == RecOpsNormal);

	CString strCaption;
	int nListCurSel = pList->GetCurSel();
	pList->GetText(nListCurSel,strCaption);
	pItem->SetCaption(strCaption);

	pOp = (tagOpDesc*)pItem->GetEditOptions(NULL)->GetConstraints()->GetAt(nListCurSel)->m_dwData;
 
	CXTPReportRecordItem *pIntroItem = pRec->GetItem(1);
	pIntroItem->SetCaption(pOp->Intro);
	pIntroItem->SetItemData((DWORD_PTR)pOp);
}

void CBkgndGroupDlg::ClearRecordText(CXTPReportRecord *pRec)
{
	pRec->GetItem(0)->SetCaption(_T(""));
	pRec->GetItem(1)->SetCaption(_T(""));
	pRec->GetItem(1)->SetItemData(0);
}

void CBkgndGroupDlg::GetRecordText(CXTPReportRecord *pRec,CString &strName, CString &strIntro)
{
	strName = pRec->GetItem(0)->GetCaption(NULL);
	strIntro = pRec->GetItem(1)->GetCaption(NULL);
}

 
 
void CBkgndGroupDlg::OnGroupItemButtonClick(NMHDR * pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	CXTPReportRecordItem *pItem = pItemNotify->pItem;
	CXTPReportRecord *pRec = pItemNotify->pRow->GetRecord();

	int nRet = 0;
	CString strErrDesc;
	tagOpDesc *pOp; tagGroupDesc *pGroup;
	CString strName,strIntro;

	BOOL bDelete = (pItem->GetIndex() == GDelete);

	switch (GetRecordObject(pRec,pGroup,pOp))
	{
	case RecOpNormal:
		ASSERT(bDelete);
		nRet = g_sp.RVDelGroupOp(g_user.GetId(),pOp->Group->Id,pOp->Id,strErrDesc);
		break;

	case RecChildRecs:
		if (bDelete)
		{
			ClearRecordText(pRec);
		}
		else
		{			
			GetRecordText(pRec,strName,strIntro);
			nRet = g_sp.RVAddGroup(g_user.GetId(),pGroup->Id,strName,strIntro,strErrDesc);
		}
		break;

	case RecNormal:
		if (bDelete)
		{
			nRet = g_sp.RVDelGroup(g_user.GetId(),pGroup->Id,strErrDesc);
		}
		else
		{
			GetRecordText(pRec,strName,strIntro);
			nRet = g_sp.RVUpdateGroup(g_user.GetId(),pGroup->Id,strName,strIntro,strErrDesc);
		}
		break;

	case RecOpsNormal:
		if (bDelete)
		{
			ClearRecordText(pRec);
		}
		else
		{
			tagOpDesc *pOpToAdd = (tagOpDesc*)pRec->GetItem(1)->GetItemData();
			if (pOpToAdd != NULL)
				nRet = g_sp.RVAddGroupOp(g_user.GetId(),pGroup->Id,pOpToAdd->Id,strErrDesc);
		}
		break;

	default:
		return;
	}



	if (nRet < 0)
		m_listGroup.AlertError(strErrDesc);
	else
		FillGroupListRecord();
}

