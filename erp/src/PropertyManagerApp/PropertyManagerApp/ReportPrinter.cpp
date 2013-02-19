#include "StdAfx.h"
#include "resource.h" 
#include "ReportPrinter.h"
#include "ReportCtrl.h"


extern CImageList g_ReportCtrlImagelist;

class CReportPrinterView : public CXTPReportView
{
	DECLARE_DYNCREATE(CReportPrinterView)

	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
	{
		CXTPReportView::OnEndPrinting(pDC,pInfo);
		((CReportPrinter*)GetParentFrame())->OnPrintEnd();
	}

	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo)
	{
		if (CXTPReportView::OnPreparePrinting(pInfo))
			return TRUE; 

		((CReportPrinter*)GetParentFrame())->OnPrintEnd();
		return FALSE;
	}
};

IMPLEMENT_DYNCREATE(CReportPrinterView,CXTPReportView)

  
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CReportPrinter::CReportPrinter(void)
	:m_pView(NULL),m_pSrcCtrl(NULL)
{
}

CReportPrinter::~CReportPrinter(void)
{
}

 
 
void CReportPrinter::PrepareFrame(void)
{ 
	ASSERT(m_pSrcCtrl == NULL);

	CCreateContext contextT;
	contextT.m_pLastView       = NULL;
	contextT.m_pCurrentFrame   = NULL;
	contextT.m_pNewDocTemplate = NULL;
	contextT.m_pCurrentDoc     = NULL;
	contextT.m_pNewViewClass   = RUNTIME_CLASS(CReportPrinterView);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE;
	LoadFrame(IDR_EMPTY, dwStyle, 0, &contextT);
	InitialUpdateFrame(NULL, FALSE);
	m_pView = (CXTPReportView*)GetActiveView();
	m_pView->GetReportCtrl().SetImageList(&g_ReportCtrlImagelist);
}

void CReportPrinter::FillData(CReportCtrl *pSrcCtrl)
{
	m_pSrcCtrl = pSrcCtrl;

	CXTPReportControl &dst = m_pView->GetReportCtrl();
	dst.ResetContent(FALSE);
	dst.GetColumns()->Clear();
	dst.AllowEdit(FALSE);

	if (pSrcCtrl == NULL)
		return;
 
	dst.SetGridStyle(FALSE,pSrcCtrl->GetGridStyle(FALSE));
	dst.SetGridStyle(TRUE,pSrcCtrl->GetGridStyle(TRUE));
	dst.GetPaintManager()->SetColumnStyle(pSrcCtrl->GetPaintManager()->GetColumnStyle());

	int i = 0;
	int cnt = pSrcCtrl->GetColumns()->GetCount();
	for (; i<cnt; ++i)
	{
		CXTPReportColumn *s = pSrcCtrl->GetColumns()->GetAt(i);
		CXTPReportColumn *d = new CXTPReportColumn(s->GetIndex(),s->GetCaption(),s->GetWidth(),
				s->IsAutoSize(),s->GetIconID(),s->IsSortable(),s->IsVisible());

		d->SetAlignment(s->GetAlignment());
		d->SetHeaderAlignment(s->GetHeaderAlignment());

		d->AllowRemove(FALSE);
		d->SetAllowDrag(FALSE);
		dst.AddColumn(d); 
	}

	for (i=0,cnt=pSrcCtrl->GetRows()->GetCount(); i<cnt; ++i)
	{
		CXTPReportRecord *s = pSrcCtrl->GetRows()->GetAt(i)->GetRecord();
		CXTPReportRecord  *d = new CXTPReportRecord();

		for (int j=0,cntj=s->GetItemCount(); j<cntj; ++j)
		{
			CXTPReportRecordItem *si = s->GetItem(j);
			CXTPReportRecordItem *di = new CXTPReportRecordItem();
			di->SetCaption(si->GetCaption(NULL));
			di->HasCheckbox(si->GetHasCheckbox());
			di->SetChecked(si->IsChecked());
			for (int k=0,cntk=si->GetItemControls()->GetSize(); k<cntk; ++k)
			{
				CXTPReportRecordItemControl *ic = si->GetItemControls()->GetAt(k);
				CXTPReportRecordItemControl *dc = di->GetItemControls()->AddControl(ic->GetType());
				dc->SetIconIndex(PBS_NORMAL,ic->GetIconIndex(PBS_NORMAL));
				dc->SetIconIndex(PBS_PRESSED,ic->GetIconIndex(PBS_PRESSED));
				dc->SetSize(ic->GetSize());
			}

			d->AddItem(di);
		}

		dst.AddRecord(d);
	}

	dst.Populate();

}
 
void CReportPrinter::DoPrint(CReportCtrl *pSrcCtrl,CXTPReportViewPrintOptions *pOptions)
{  
	if (GetSafeHwnd() == NULL)
		PrepareFrame();

	FillData(pSrcCtrl);

	if (pSrcCtrl == NULL)
		return;

	if (pOptions != NULL)
		m_pView->GetPrintOptions()->Set(pOptions);
	m_pView->SendMessage(WM_COMMAND,ID_FILE_PRINT);
}

void CReportPrinter::OnPrintEnd(void)
{
	ASSERT(m_pSrcCtrl != NULL);
	m_pSrcCtrl->OnPrintEnd();
}