#pragma once
 
class CReportCtrl;

class CReportPrinter : public CXTPFrameWnd
{ 
public:
	CReportPrinter(void);
	~CReportPrinter(void);

	void DoPrint(CReportCtrl *pSrcCtrl,CXTPReportViewPrintOptions *pOptions=NULL); 

	void OnPrintEnd(void);
private:   

	void PrepareFrame(void); 
	void FillData(CReportCtrl *pSrcCtrl);
	
	CReportCtrl *m_pSrcCtrl;
	CXTPReportView *m_pView;
};