#pragma once
#include "GaugeWnd.h"
#include "ResizableDialog.h"
#include "SimpleBuffer.h"


class CVideoSrcBaseDialog : public CResizableDialog
{
	DECLARE_MESSAGE_MAP()

public:
	CVideoSrcBaseDialog(void);
	CVideoSrcBaseDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	CVideoSrcBaseDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual ~CVideoSrcBaseDialog(void);

	virtual void SampleRef(BOOL bRef);

	LPCTSTR GetName(void) const;
	void RepositionChildren(void);

	BOOL IsGaugeVisible(void) const;
	void ShowGauge(BOOL bShow);
	
	virtual DWORD GetSampleTick(void);
	virtual BOOL GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample) = 0;

	virtual CWnd* GetDefaultCtrl(void);
	virtual void SetDrawCursor(BOOL bDraw);
	virtual CString GetDesc(void);

	virtual void OnGaugeChanged(void);
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	BOOL m_bVisible;
	LPCTSTR m_pcszName;
	CGaugeWnd m_gaugeWnd;
};

inline 	LPCTSTR CVideoSrcBaseDialog::GetName(void) const {
	return m_pcszName;
}

inline BOOL CVideoSrcBaseDialog::IsGaugeVisible(void) const {
	return m_gaugeWnd.IsManualVisible();
}

inline void CVideoSrcBaseDialog::ShowGauge(BOOL bShow) {
	if (m_gaugeWnd.GetSafeHwnd() != NULL)
		m_gaugeWnd.ShowManual(bShow);
}
