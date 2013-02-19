#include "stdafx.h"
#include "../PropertyManagerApp.h"
#include "../ObjectDesc.h"
#include "../User.h"
#include "BkgndUserDlg.h"


CBkgndUserDlg::CBkgndUserDlg(CWnd* pParent /*=NULL*/)
	: CReportPageDlg(CBkgndUserDlg::IDD, pParent)
{

}

CBkgndUserDlg::~CBkgndUserDlg()
{
}

void CBkgndUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CReportPageDlg::DoDataExchange(pDX);
 
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
	DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
}


BEGIN_MESSAGE_MAP(CBkgndUserDlg, CReportPageDlg)
	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED,IDC_LIST_USER,&CBkgndUserDlg::OnUserItemValueChanged)
	ON_NOTIFY(XTP_NM_REPORT_ITEMBUTTONCLICK, IDC_LIST_USER, &CBkgndUserDlg::OnUserItemButtonClick)
END_MESSAGE_MAP()



BOOL CBkgndUserDlg::OnInitDialog()
{
	CReportPageDlg::OnInitDialog();

	InitUserList();
	InitGroupList();
 
	return TRUE;  
}

 
static CReportCtrl::ColInfo UserListCols[] = {
	{ _T("帐户"),	100,		FALSE,	TRUE,	_T("UserName"),		FALSE,	FALSE,	CReportCtrl::FmtIdStr		}, 
	{ _T("组名"),	100,		FALSE,	FALSE,	_T("GroupName"),	FALSE,	TRUE,	CReportCtrl::FmtNon			},
	{ NULL,			0,			FALSE,	FALSE,	_T("UserId"),		FALSE,	FALSE,	CReportCtrl::FmtIdOnly		}
};

void CBkgndUserDlg::InitUserList(void)
{
	CXTPResizePoint resizeBottomRight(2/3.0f,1.0f);
	SetResize(IDC_STC_PWD,resizeBottomRight,resizeBottomRight);
	SetResize(IDC_EDIT_PWD,resizeBottomRight,resizeBottomRight);
	 
	SetResize(IDC_LIST_USER,XTP_ANCHOR_TOPLEFT,resizeBottomRight);
	SetResize(IDC_STC_USER,XTP_ANCHOR_TOPLEFT,resizeBottomRight);

	m_listUser.Initialize(UserListCols,_countof(UserListCols),CReportCtrl::OpDelete|CReportCtrl::OpModify|CReportCtrl::OpAdd);

	FillUserListRecord();
}

void FillUserRecordGroupId(FieldsPtr &fields,CXTPReportRecord *pRec)
{
	int nGroupId = fields->Item[_T("UserGroup")]->Value;
	pRec->GetItem(0)->SetItemData(nGroupId);
	pRec->GetItem(1)->SetItemData(nGroupId);
}

void CBkgndUserDlg::FillUserListRecord(void)
{ 
	CXTPReportColumn *pCol = m_listUser.GetColumns()->GetAt(1);
	pCol->SetEditable(TRUE);

	if (!g_group.Childs.IsEmpty())
	{
		CArray<tagGroupDesc*,tagGroupDesc*> groups;
		g_group.Childs[0]->ToGroups(groups);

		CXTPReportRecordItemEditOptions *pEditOptions = pCol->GetEditOptions();
		pEditOptions->m_bConstraintEdit = TRUE;
		pEditOptions->AddComboButton(TRUE);
		for (INT_PTR i=0; i<groups.GetCount(); ++i)
			pEditOptions->AddConstraint(groups[i]->Name,groups[i]->Id);
	} 

	_RecordsetPtr rst;
	CString ErrDesc;
	if (g_sp.RRGetUsers(rst,g_user.GetId(),ErrDesc) >= 0) 
		m_listUser.FillRecordset(rst,FillUserRecordGroupId);

 
}
 
static CReportCtrl::ColInfo GroupListCols[] = { 
	{ _T("组名"),		60,		FALSE,	TRUE,		},
	{ _T("描述"),		160,	FALSE,	FALSE,		}
};

void CBkgndUserDlg::InitGroupList(void)
{ 
	CXTPResizePoint resizeTopLeft(2/3.0f,0.0f); 
	SetResize(IDC_STC_GROUP,resizeTopLeft,XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_LIST_GROUP,resizeTopLeft,XTP_ANCHOR_BOTTOMRIGHT);
	
	m_listGroup.AllowEdit(FALSE);
	m_listGroup.Initialize(GroupListCols,_countof(GroupListCols));
	m_listGroup.SetTreeIndent(25);
	m_listGroup.GetReportHeader()->AllowColumnRemove(FALSE); 
	m_listGroup.GetColumns()->GetAt(0)->SetTreeColumn(TRUE);

	FillGroupListRecord();
}
 
CXTPReportRecord* CBkgndUserDlg::NewGroupRecord(tagGroupDesc *pGroup)
{
	CXTPReportRecord *pRec = new CXTPReportRecord();
	// Name
	CXTPReportRecordItem *pItem = new CXTPReportRecordItem();
	pItem->SetCaption(pGroup->Name); 
	pItem->SetIconIndex(CReportCtrl::IndexManager); 
	pRec->AddItem(pItem); 

	// Intro
	pItem = new CXTPReportRecordItem();
 	pItem->SetCaption(pGroup->Intro);
	pRec->AddItem(pItem);
 
	pRec->SetBookmark(_variant_t(pGroup->Id));
	return pRec;
}

CXTPReportRecord* CBkgndUserDlg::BuildGoupListRecord(tagGroupDesc *pGroup)
{
	CXTPReportRecord *pRec = NewGroupRecord(pGroup); 
	for (INT_PTR j=0; j<pGroup->Childs.GetCount(); ++j)
		pRec->GetChilds()->Add(BuildGoupListRecord(pGroup->Childs[j]));
	return pRec;
}

void CBkgndUserDlg::FillGroupListRecord(void)
{
	m_listGroup.ResetContent(FALSE);
	m_listGroup.AddRecord(BuildGoupListRecord(g_group.Childs[0]));
	m_listGroup.Populate();	
	m_listGroup.ExpandAll(TRUE);
}
 
void CBkgndUserDlg::OnUserItemButtonClick(NMHDR * pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	CXTPReportRecordItem *pItem = pItemNotify->pItem;
	CXTPReportRecord *pRec = pItemNotify->pRow->GetRecord();
	BOOL bDelete = m_listUser.IsDeleteOpCol(pItem);

	int nRet = 0;
	CString strErrDesc;

	if (m_listUser.IsAddOpRecord(pRec))
	{
		if (bDelete)
		{
			pRec->GetItem(0)->SetCaption(_T(""));
			pRec->GetItem(1)->SetCaption(_T(""));
			pRec->GetItem(0)->SetItemData(0);
		}
		else
		{
			CString strPwd;
			m_editPwd.GetWindowText(strPwd);
			if (strPwd.Trim().IsEmpty())
			{
				nRet = -1;
				strErrDesc = _T("请设置初始密码");
			}
			else
			{
				int nGroupId = pRec->GetItem(1)->GetItemData();
				nRet = g_sp.RVAddUser(g_user.GetId(),pRec->GetItem(0)->GetCaption(NULL),strPwd,nGroupId,strErrDesc);
				if (nRet >= 0)
				{
					CXTPReportRecord *pRec = m_listUser.TransferAddRecord();
					SetRecId(pRec,nRet);
					pRec->GetItem(0)->SetItemData(nGroupId);
				}
			}
		}
	}
	else
	{
		int nOpedId = RecId(pRec);
		if (bDelete)
		{
			nRet = g_sp.RVDelUser(g_user.GetId(),nOpedId,strErrDesc);
			if (nRet >= 0)
			{
				pRec->Delete();
				m_listUser.Populate();
			}
		}
		else
		{
			CString strPwd;
			int nOldGroupId = pRec->GetItem(0)->GetItemData();
			int nNewGroupId = pRec->GetItem(1)->GetItemData();
			if (nOldGroupId == nNewGroupId)
			{
				m_editPwd.GetWindowText(strPwd);
				if (strPwd.Trim().IsEmpty())
				{
					nRet = -1;
					strErrDesc = _T("请设置初始密码");
				}  
			}
			if (nRet >= 0)
				nRet = g_sp.RVUpdateGroupUser(g_user.GetId(),nOpedId,nNewGroupId,strPwd,strErrDesc);
			if (nRet >= 0 && strPwd.IsEmpty())
				pRec->GetItem(0)->SetItemData(nNewGroupId);
			 
		}
	}

	if (nRet < 0)
		m_listGroup.AlertError(strErrDesc);
}

void CBkgndUserDlg::OnUserItemValueChanged(NMHDR * pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	CXTPReportRecordItem *pItem = pItemNotify->pItem;
	CXTPReportRecord *pRec = pItemNotify->pRow->GetRecord();

	ASSERT(m_listUser.GetInplaceList()->GetSafeHwnd() != NULL);
	CXTPReportInplaceList *pList = m_listUser.GetInplaceList();
 
	CString strCaption;
	int nListCurSel = pList->GetCurSel();
	pList->GetText(nListCurSel,strCaption);
	pItem->SetCaption(strCaption);
	
	CXTPReportColumn *pCol = m_listUser.GetColumns()->GetAt(1);
	CXTPReportRecordItemConstraints *pConstrants = pCol->GetEditOptions()->GetConstraints();
	pItem->SetItemData(pConstrants->GetAt(nListCurSel)->m_dwData);
}
