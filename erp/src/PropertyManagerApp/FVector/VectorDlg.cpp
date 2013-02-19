// VectorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Vector.h"
#include "VectorDlg.h"

#define DOC_EXTENSION _T("xml")
#define DOC_EXTFILTER _T("VEC文件(*.xml)|*.xml|所有文件(*.*)|*.*||")

 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VECWND_ID 0x994

CVectorDlg::CVectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVectorDlg::IDD, pParent)
{ 
}

void CVectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_CHKOUTLINE,m_chkOutline);
	DDX_Control(pDX,IDC_CBOUTLINESTYLE,m_cbOutlineStyle);
	DDX_Control(pDX,IDC_CBOUTLINEWIDTH,m_cbOutlineWidth);
	DDX_Control(pDX,IDC_BTNOUTLINECOLOR,m_cpOutlineColor);
	DDX_Control(pDX,IDC_CHKFILL,m_chkFill);
	DDX_Control(pDX,IDC_EDITCUSTOMDATA,m_editCustomData);
	DDX_Control(pDX,IDC_BTNFILLCOLOR,m_cpFillColor);
	DDX_Control(pDX,IDC_BTNBKCOLOR,m_cpBkColor);
	DDX_Control(pDX, IDC_EDITDESC, m_editDesc);
}

BEGIN_MESSAGE_MAP(CVectorDlg, CDialog) 
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_RESET,ID_GAUGE,&CVectorDlg::OnOPCommand) 
	ON_COMMAND(ID_ERASE,&CVectorDlg::OnEraseElem)
	ON_COMMAND(ID_TOPMOST,&CVectorDlg::OnSetTopmost)
	ON_COMMAND(ID_DOWNMOST,&CVectorDlg::OnSetDownmost)
	ON_COMMAND(ID_CLONE,&CVectorDlg::OnClone)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_LOAD,&CVectorDlg::OnLoad)
	ON_COMMAND(ID_SAVE,&CVectorDlg::OnSave)
	ON_COMMAND(ID_ABOUT,&CVectorDlg::OnAbout)
	ON_COMMAND(ID_ADD,&CVectorDlg::OnAdd)
	ON_COMMAND(ID_REMOVE,&CVectorDlg::OnRemove)
	ON_COMMAND(ID_CAPTURE,&CVectorDlg::OnCapture)
	ON_COMMAND(ID_BKGNDIMG,&CVectorDlg::OnBkgndImage)
	ON_COMMAND_RANGE(ID_ZOOMIN,ID_ZOOMORG,&CVectorDlg::OnZoom)
	ON_NOTIFY(VWN_SELCHANGE,VECWND_ID,&CVectorDlg::OnVecWndSelChange)
	ON_NOTIFY(VWN_HOVERCHANGE,VECWND_ID,&CVectorDlg::OnVecWndHoverChange)
	ON_CONTROL(CBN_SELCHANGE,IDC_CBOUTLINESTYLE,&CVectorDlg::OnCBOutlineStyle) 
	ON_CONTROL(CBN_SELCHANGE,IDC_CBOUTLINEWIDTH,&CVectorDlg::OnCBOutlineWidth)
	ON_MESSAGE(CPN_SELENDOK,&CVectorDlg::OnCPSelChang) 
	ON_BN_CLICKED(IDC_CHKOUTLINE, &CVectorDlg::OnBnClickedChkoutline)
	ON_BN_CLICKED(IDC_CHKFILL, &CVectorDlg::OnBnClickedChkfill)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnToolTipText) 
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnToolTipText) 
END_MESSAGE_MAP()



void CVectorDlg::OnLoad(void)
{
	CFileDialog dlg(TRUE,DOC_EXTENSION,NULL,OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, DOC_EXTFILTER);
	if (dlg.DoModal() == IDOK)
	{
		if (!m_wndVec.Load(dlg.GetPathName()))
			MessageBox(_T("加载失败!"),_T("提示信息"),MB_ICONERROR);
		else
			m_editDesc.SetWindowText(m_wndVec.GetDesc());
	}
}


void CVectorDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[MAX_PATH];
	DragQueryFile(hDropInfo,0,szFileName,_countof(szFileName));

	if (!m_wndVec.Load(szFileName))
		MessageBox(_T("加载失败!"),_T("提示信息"),MB_ICONERROR);

	DragFinish(hDropInfo);
}

void CVectorDlg::OnSave(void)
{
	CFileDialog dlg(FALSE,DOC_EXTENSION,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, DOC_EXTFILTER);
	if (dlg.DoModal() == IDOK)
	{	
		CElem *pElem = m_wndVec.GetSelectedElem();
		if (pElem != NULL)
		{
			CString strDesc;
			m_editDesc.GetWindowText(strDesc);
			pElem->SetDesc(strDesc);
		}
		
		if (!m_wndVec.Save(dlg.GetPathName()))
			MessageBox(_T("保存失败!"),_T("提示信息"),MB_ICONERROR);
	}
}


void CVectorDlg::OnBkgndImage(void)
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_wndVec.SetBkgndImage(dlg.GetPathName());
	}
}
 

void CVectorDlg::OnOPCommand(UINT uCmd)
{
	m_wndVec.SetOPType(uCmd - ID_RESET);
}

void CVectorDlg::OnEraseElem(void)
{
	m_wndVec.RemoveSelected();
}

void CVectorDlg::OnSetTopmost(void)
{
	m_wndVec.SetSelectTopmost();
}

void CVectorDlg::OnSetDownmost(void)
{
	m_wndVec.SetSelectDownmost();
}

void CVectorDlg::OnCapture(void)
{
	if (m_wndCapture.m_hWnd == NULL)
		m_wndCapture.Create();
	
	m_wndCapture.Show();
}

void CVectorDlg::OnAdd(void)
{

}

void CVectorDlg::OnRemove(void)
{

}

void CVectorDlg::OnClone(void)
{
	m_wndVec.CloneSelectedElem();
}

void CVectorDlg::OnZoom(UINT uCmd)
{
	const REAL Scale = 0.9f;
	const REAL fScaleOut = Scale;
	const REAL fScaleIn = 1.0f/Scale;
	switch (uCmd)
	{
	case ID_ZOOMIN:
		m_wndVec.Zoom(fScaleIn,fScaleIn);
		break;
	case ID_ZOOMOUT:
		m_wndVec.Zoom(fScaleOut,fScaleOut);
		break;
	case ID_ZOOMORG:
		m_wndVec.SetScale(CSizeF(1.0f,1.0f));
		break;
	case ID_ZOOMXIN:
		m_wndVec.Zoom(fScaleIn,1.0f);
		break;
	case ID_ZOOMXOUT:
		m_wndVec.Zoom(fScaleOut,1.0f);
		break;
	case ID_ZOOMYIN:
		m_wndVec.Zoom(1.0f,fScaleIn);
		break;
	case ID_ZOOMYOUT:
		m_wndVec.Zoom(1.0f,fScaleOut);
		break;
	case ID_ZOOMXFIT:
	case ID_ZOOMYFIT:
	case ID_ZOOMFIT:
		{
			CRectF rc;
			m_wndVec.GetElemsBoudsRect(rc);
			if (!rc.IsRectEmpty())
			{
				CRect rect;
				m_wndVec.GetWindowRect(rect);
				rect.OffsetRect(-rect.TopLeft());

				switch (uCmd)
				{
				case ID_ZOOMFIT:
					m_wndVec.Zoom(rect.right/rc.right,rect.bottom/rc.bottom);
					break;
				case ID_ZOOMXFIT:
					m_wndVec.Zoom(rect.right/rc.right,rect.right/rc.right);
					break;
				case ID_ZOOMYFIT:
					m_wndVec.Zoom(rect.bottom/rc.bottom,rect.bottom/rc.bottom);
					break;
				}
			}
		}
		break;
	}
}

void CVectorDlg::OnAbout(void)
{
	CDialog dlg(IDD_ABOUTBOX);
	dlg.DoModal();
}
 

void  CVectorDlg::OnCBOutlineStyle(void)
{ 
	CElem *pElem = m_wndVec.GetSelectedElem();
	ASSERT(pElem != NULL);

	int nType = pElem->GetType();
	switch (nType)
	{
	case CElem::Line:
	case CElem::Bezier:
	case CElem::Arc:
	case CElem::FreeLine: 
		{ 
			COutlined *e = static_cast<COutlined*>(pElem);
			e->SetDasHStyle(m_cbOutlineStyle.GetStyle());
		}
		break;
	case CElem::Poly:
	case CElem::Rectangle:
	case CElem::RoundRect:
	case CElem::Ellipse:
	case CElem::Chord:
	case CElem::Pie:
	case CElem::Region:
		{
			CFilled *e = static_cast<CFilled*>(pElem);
			e->SetDasHStyle(m_cbOutlineStyle.GetStyle());
		}
		break;
	default:
		ASSERT(FALSE);
	}

}

void  CVectorDlg::OnCBOutlineWidth(void)
{
	CElem *pElem = m_wndVec.GetSelectedElem();
	ASSERT(pElem != NULL);

	int nType = pElem->GetType();
	switch (nType)
	{
	case CElem::Line:
	case CElem::Bezier:
	case CElem::Arc:
	case CElem::FreeLine:
		{ 
			COutlined *e = static_cast<COutlined*>(pElem);
			e->SetOutlineWidth(m_cbOutlineWidth.GetWidth());
		}
		break;
	case CElem::Poly:
	case CElem::Rectangle:
	case CElem::RoundRect:
	case CElem::Ellipse:
	case CElem::Chord:
	case CElem::Pie:
	case CElem::Region:
		{
			CFilled *e = static_cast<CFilled*>(pElem);
			e->SetOutlineWidth(m_cbOutlineWidth.GetWidth());
		}
		break;
	default:
		ASSERT(FALSE);
	}
}

LRESULT  CVectorDlg::OnCPSelChang(WPARAM wParam,LPARAM lParam)
{
	COLORREF clr = (COLORREF)wParam;
	UINT uCtrlId = (UINT)lParam;

	if (uCtrlId == IDC_BTNBKCOLOR)
	{
		m_wndVec.SetBkColor(clr);
		return 0;
	}

	CElem *pElem = m_wndVec.GetSelectedElem();
	ASSERT(pElem != NULL);

	int nType = pElem->GetType();
	switch (nType)
	{
	case CElem::Line:
	case CElem::Bezier:
	case CElem::Arc:
	case CElem::FreeLine:
		{ 
			COutlined *e = static_cast<COutlined*>(pElem);
			ASSERT(uCtrlId == IDC_BTNOUTLINECOLOR);
			e->SetOutlineColor(clr);
		}
		break;
	case CElem::Poly:
	case CElem::Rectangle:
	case CElem::RoundRect:
	case CElem::Ellipse:
	case CElem::Chord:
	case CElem::Pie:
	case CElem::Region:
		{
			CFilled *e = static_cast<CFilled*>(pElem);
			if (uCtrlId == IDC_BTNOUTLINECOLOR)
				e->SetOutlineColor(clr);
			else
				e->SetFillColor(clr);
		}
		break;
	default:
		ASSERT(FALSE);
	}

	return 0;
}

BOOL CVectorDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CVectorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	EnableToolTips(TRUE);
	m_tip.Create(this);
	m_tip.Activate(TRUE);
	m_tip.SetDelayTime(2000,0);
	
	CRect rcQ;
	CRect rect;
	m_tb.Create(this);
	m_tb.LoadToolBar(IDR_TBMAIN);
	m_tb.SetBarStyle(CBRS_ALIGN_TOP|CBRS_TOOLTIPS|CBRS_FLYBY);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
 	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0,reposQuery,rect);
	 
	CRect rc;
	GetClientRect(rc); 
	rc.top = rect.top;

	m_editDesc.GetClientRect(rect);
	rc.left = rect.right + 10;

	m_wndVec.Create(WS_CHILD|WS_VISIBLE,rc,this,VECWND_ID);

	m_cbOutlineStyle.Init();
	m_cbOutlineWidth.Init();
	m_cpBkColor.SetColor(m_wndVec.GetBkColor());

	NMOBJECTNOTIFY nmn;
	nmn.pObject = NULL;
	LRESULT lResult;
	OnVecWndSelChange((NMHDR*)&nmn,&lResult);

	m_wndVec.SetBkgndImage(_T("Pic/Bkgnd.jpg"));

	CCommandLineInfo infoCmd;
	AfxGetApp()->ParseCommandLine(infoCmd);
	if (infoCmd.m_nShellCommand == CCommandLineInfo::FileOpen)
	{
		if (!m_wndVec.Load(infoCmd.m_strFileName))
			MessageBox(_T("加载失败!"),_T("提示信息"),MB_ICONERROR);
	}

	m_tip.AddTool(&m_wndVec,_T(""));

	ShowWindow(SW_MAXIMIZE);
	return TRUE; 
}

void CVectorDlg::OnSize(UINT nType, int cx, int cy)
{
	if (m_tb.GetSafeHwnd() != NULL)
	{
		CRect rc;
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0,reposQuery,rc);

		CRect rect;
		m_editDesc.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right += 10;
		m_wndVec.MoveWindow(rect.right,rc.top,cx-rect.right,rc.Height());
	}	
	CDialog::OnSize(nType,cx,cy);
}

 

 
 

void CVectorDlg::OnBnClickedChkoutline()
{
	BOOL bOutline = (m_chkOutline.GetCheck() == BST_CHECKED);

	CElem *pElem = m_wndVec.GetSelectedElem();
	ASSERT(pElem != NULL);

	int nType = pElem->GetType();
	switch (nType)
	{
	case CElem::Poly:
	case CElem::Rectangle:
	case CElem::RoundRect:
	case CElem::Ellipse:
	case CElem::Chord:
	case CElem::Pie:
	case CElem::Region:
		{
			CFilled *e = static_cast<CFilled*>(pElem);
			e->SetOutline(bOutline);	
		}
		break;
	default:
		ASSERT(FALSE);
	}
}

void CVectorDlg::OnBnClickedChkfill()
{ 
	BOOL bFill = (m_chkFill.GetCheck() == BST_CHECKED);
	m_cpFillColor.EnableWindow(bFill);


	CElem *pElem = m_wndVec.GetSelectedElem();
	ASSERT(pElem != NULL);

	int nType = pElem->GetType();
	switch (nType)
	{
	case CElem::Poly:
	case CElem::Rectangle:
	case CElem::RoundRect:
	case CElem::Ellipse:
	case CElem::Chord:
	case CElem::Pie:
	case CElem::Region:
		{
			CFilled *e = static_cast<CFilled*>(pElem);
			e->SetFill(bFill);	
		}
		break;
	default:
		ASSERT(FALSE);
	} 
}

	
void CVectorDlg::OnVecWndHoverChange(NMHDR *pNM, LRESULT *pResult)
{
	CElem *pElem = m_wndVec.GetHoverElem();
	if (pElem !=  NULL)
		m_tip.UpdateTipText(pElem->GetDesc(),&m_wndVec);
	m_tip.Activate(pElem != NULL);
}

void CVectorDlg::OnVecWndSelChange(NMHDR *pNM, LRESULT *pResult)
{
	CElem *pOldElem = (CElem*)((NMOBJECTNOTIFY*)pNM)->pObject;
	
	CString strDesc;

	TCHAR szTemp[64];
	m_editCustomData.GetWindowText(szTemp,sizeof(szTemp));
	DWORD_PTR dwCustomData = (DWORD_PTR)_ttoi64(szTemp);


	m_editDesc.GetWindowText(strDesc);
 
	if (pOldElem != NULL)
	{
		pOldElem->SetDesc(strDesc);
		pOldElem->SetCustomData(dwCustomData);
	}
	else 
	{
		m_wndVec.SetDesc(strDesc);
		m_wndVec.SetCustomData(dwCustomData);
	}

	CElem *pElem = m_wndVec.GetSelectedElem();
	if (pElem == NULL)
	{
		m_chkOutline.EnableWindow(FALSE);
		m_cbOutlineStyle.EnableWindow(FALSE);
		m_cbOutlineWidth.EnableWindow(FALSE);
		m_cpOutlineColor.EnableWindow(FALSE);
		m_chkFill.EnableWindow(FALSE);
		m_cpFillColor.EnableWindow(FALSE);
		m_editDesc.SetWindowText(m_wndVec.GetDesc());
		m_editCustomData.SetWindowText(_ui64tot(m_wndVec.GetCustomData(),szTemp,10));
	}
	else
	{	 
		m_editDesc.SetWindowText(pElem->GetDesc());
		m_editCustomData.SetWindowText(_ui64tot(pElem->GetCustomData(),szTemp,10));

		int nType = pElem->GetType();
		switch (nType)
		{
		case CElem::Line:
		case CElem::Bezier:
		case CElem::Arc:
		case CElem::FreeLine:
			{ 
				COutlined *e = static_cast<COutlined*>(pElem);
				m_chkOutline.EnableWindow(FALSE);
				m_cbOutlineStyle.EnableWindow(TRUE);
				m_cbOutlineStyle.SetStyle(e->GetDashStyle());
				m_cbOutlineWidth.EnableWindow(TRUE);
				m_cbOutlineWidth.SetWidth(e->GetOutlineWidth());
				m_cpOutlineColor.EnableWindow(TRUE);
				m_cpOutlineColor.SetColor(e->GetOutlineColor());
				m_chkFill.EnableWindow(FALSE);
				m_cpFillColor.EnableWindow(FALSE);
			}
			break;
		case CElem::Poly:
		case CElem::Rectangle:
		case CElem::RoundRect:
		case CElem::Ellipse:
		case CElem::Chord:
		case CElem::Pie:
		case CElem::Region:
			{
				CFilled *e = static_cast<CFilled*>(pElem);
				m_chkOutline.EnableWindow(TRUE);
				m_chkOutline.SetCheck(e->IsOutline() ? BST_CHECKED:BST_UNCHECKED);
				m_cbOutlineStyle.EnableWindow(e->IsOutline());
				m_cbOutlineWidth.EnableWindow(e->IsOutline());
				m_cpOutlineColor.EnableWindow(e->IsOutline());	
				if (e->IsOutline())
				{	
					m_cbOutlineStyle.SetStyle(e->GetDashStyle());
					m_cbOutlineWidth.SetWidth(e->GetOutlineWidth());
					m_cpOutlineColor.SetColor(e->GetOutlineColor());
				}
				m_chkFill.EnableWindow(TRUE);
				m_chkFill.SetCheck(e->IsFill() ? BST_CHECKED:BST_UNCHECKED);
				m_cpFillColor.EnableWindow(e->IsFill());
				if (e->IsFill())
					m_cpFillColor.SetColor(e->GetFillColor());
			}
			break;
		default:
			break;
		}
	}
}

BOOL CVectorDlg::OnToolTipText(UINT /*nID*/,NMHDR *pNMHDR,LRESULT *pResult) 
{ 
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW); 
	if (GetRoutingFrame() != NULL) 
		return FALSE; 

	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR; 
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR; 
	
	CString strTipText;
	UINT nID = (UINT)pNMHDR->idFrom; 

	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) || 
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
		nID = ::GetDlgCtrlID((HWND)(UINT_PTR)nID); 

	if (nID != 0)
	{ 
		strTipText.LoadString(nID);

		USES_CONVERSION;
		if (pNMHDR->code == TTN_NEEDTEXTA) 
			lstrcpyA(pTTTA->szText, T2CA(strTipText)); 
		else 
			lstrcpyW(pTTTW->szText, T2CW(strTipText)); 

		*pResult = 0; 
		return TRUE; 
	} 

	return FALSE;
} 