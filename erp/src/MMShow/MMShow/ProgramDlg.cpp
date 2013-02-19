#include "stdafx.h"
#include "Resource.h"
#include "ProgramDlg.h"
#include "ProgramItemDlg.h"
#include "FileHelper.h"
#include "Cfg.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CProgramDlg::CProgramDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CProgramDlg::IDD, pParent)
{

}

CProgramDlg::~CProgramDlg()
{
}

void CProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DESC, m_editDesc);
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_listProgram);
	DDX_Control(pDX, IDC_STC_PROGRAM_NAME, m_stcProgramName);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_BTN_UP, m_btnUp);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BTN_PROP, m_btnProp);

}


BEGIN_MESSAGE_MAP(CProgramDlg, CResizableDialog)
	ON_WM_CTLCOLOR() 
	ON_BN_CLICKED(IDC_BTN_ADD, &CProgramDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CProgramDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_UP, &CProgramDlg::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DEL, &CProgramDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_PROP, &CProgramDlg::OnBnClickedBtnProp)
	ON_LBN_SELCHANGE(IDC_LIST_PROGRAM,&CProgramDlg::OnListProgramSelChange)
	ON_LBN_DBLCLK(IDC_LIST_PROGRAM,&CProgramDlg::OnListProgramDblClicked)
END_MESSAGE_MAP()

 
BOOL CProgramDlg::OnInitDialog(void)
{
	CResizableDialog::OnInitDialog();

	const int DescHeight = 35;

	AddAnchor(IDC_STATIC1,TOP_LEFT);
	AddAnchor(m_stcProgramName,TOP_LEFT,TOP_RIGHT);
	AddAnchor(m_editDesc,TOP_LEFT,CSize(100,DescHeight));

	AddAnchor(m_btnAdd,CSize(100,DescHeight));
	AddAnchor(m_btnDel,CSize(100,DescHeight));
	AddAnchor(m_btnUp,CSize(100,DescHeight));
	AddAnchor(m_btnDown,CSize(100,DescHeight));
	AddAnchor(m_btnProp,CSize(100,DescHeight));
	AddAnchor(m_listProgram,CSize(0,DescHeight),BOTTOM_RIGHT);

	m_fontDesc.CreatePointFont(160,_T("宋体"));
	m_editDesc.SetFont(&m_fontDesc);

	Fh::Cder cder(gsys.PicPath());

	m_fontList.CreatePointFont(120,_T("宋体"));
	m_listProgram.SetFont(&m_fontList);

	m_btnAdd.SetImageFile(_T("ProgramAdd.png"));
	m_btnAdd.SetTip(_T("添加"));

	m_btnDel.SetImageFile(_T("ProgramDelete.png"));
	m_btnDel.SetTip(_T("移除"));

	m_btnUp.SetImageFile(_T("ProgramUpward.png"));
	m_btnUp.SetTip(_T("下移"));

	m_btnDown.SetImageFile(_T("ProgramDownward.png"));
	m_btnDown.SetTip(_T("上移"));

	m_btnProp.SetImageFile(_T("ProgramPropset.png"));
	m_btnProp.SetTip(_T("属性"));


	return FALSE;
}


HBRUSH CProgramDlg::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() != IDC_EDIT_DESC)
		return hBrush;

	pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkMode(TRANSPARENT);
	return GetSysColorBrush(COLOR_WINDOW);
}


void CProgramDlg::OnListProgramSelChange(void)
{
	int nIndex = m_listProgram.GetCurSel();
	if (nIndex >= 0)
	{
		ContentLink *cl = (ContentLink*)m_listProgram.GetItemData(nIndex);
		m_editDesc.SetWindowText(cl->GetDescription());
	}
}

void CProgramDlg::RefreshProgram(void)
{
	m_editDesc.SetWindowText(m_program.ProgramProp.GetDescription());

	m_listProgram.ResetContent();
	for (int i=0; i<m_program.Contents.GetCount(); ++i)
	{
		ContentLink *cl = m_program.Contents[i];
		int nIndex = m_listProgram.AddString(cl->GetName());
		m_listProgram.SetItemData(nIndex,(DWORD_PTR)cl);
	}
}


LPCTSTR PROGRAM_EXT = _T(".xml");
LPCTSTR ALL_PROGRAM_FILTER = _T("节目单文件 (*.xml)|*.xml||");

void CProgramDlg::OpenProgramFile(void)
{
	if (QuitConfirm())
	{
		CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ENABLESIZING,ALL_PROGRAM_FILTER);
		if (dlg.DoModal() == IDOK)
		{
			CString strFilePath = dlg.GetPathName();
			if (m_program.Load(strFilePath))
			{
				RefreshProgram();
			}
			else
			{
				CString str ;
				str.Format(_T("打开节目单文件 \"%s\" 失败,请确认节目单文件格式正确"),Fh::GetFileName(strFilePath));
				MessageBox(str,_T("提示信息"),MB_ICONINFORMATION);
			}
		}
	}
}

void CProgramDlg::OnBnClickedBtnAdd(void)
{
	CProgramItemDlg dlg(_T("添加新项"));
	if (dlg.DoModal() == IDOK)
	{
		ContentLink *cl = m_program.AddContentLink(dlg.GetName(),
			dlg.GetPath(),dlg.GetDesc(),dlg.IsWebPage());
		int nIndex = m_listProgram.AddString(cl->GetName());
		m_listProgram.SetItemData(nIndex,(DWORD_PTR)cl);

		if (m_listProgram.GetCurSel() < 0)
		{
			m_listProgram.SetCurSel(nIndex);
			m_editDesc.SetWindowText(cl->GetDescription());
		}
	}
}

void CProgramDlg::OnBnClickedBtnDown(void)
{
	int nIndex = m_listProgram.GetCurSel();
	if (nIndex < 0)
	{
		MessageBox(_T("当前未选中项目，不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else if (!m_program.MoveDown(nIndex))
	{
		MessageBox(_T("当前项目不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else
	{
		CString str;
		m_listProgram.GetText(nIndex,str);
		DWORD_PTR dwData = m_listProgram.GetItemData(nIndex);		
		m_listProgram.DeleteString(nIndex);	

		nIndex = m_listProgram.InsertString(nIndex+1,str); 
		m_listProgram.SetItemData(nIndex,dwData);
		m_listProgram.SetCurSel(nIndex);
	}
}

void CProgramDlg::OnBnClickedBtnUp(void)
{
	int nIndex = m_listProgram.GetCurSel();
	if (nIndex < 0)
	{
		MessageBox(_T("当前未选中项目，不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else if (!m_program.MoveUp(nIndex))
	{
		MessageBox(_T("当前项目不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else
	{
		CString str;
		m_listProgram.GetText(nIndex,str);
		DWORD_PTR dwData = m_listProgram.GetItemData(nIndex);		
		m_listProgram.DeleteString(nIndex);	

		nIndex = m_listProgram.InsertString(nIndex-1,str); 
		m_listProgram.SetItemData(nIndex,dwData);
		m_listProgram.SetCurSel(nIndex);
	}
}

void CProgramDlg::OnBnClickedBtnDel(void)
{
	int nIndex = m_listProgram.GetCurSel();
	if (nIndex < 0)
	{
		MessageBox(_T("当前未选中项目，不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else if (!m_program.Remove(nIndex))
	{
		MessageBox(_T("当前项目不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else
	{
		m_listProgram.DeleteString(nIndex);
		if (nIndex == m_listProgram.GetCount())
			nIndex = max(nIndex-1,0);
		m_listProgram.SetCurSel(nIndex);
	}
}

void CProgramDlg::OnBnClickedBtnProp(void)
{
	int nIndex = m_listProgram.GetCurSel();
	if (nIndex < 0)
	{
		MessageBox(_T("当前未选中项目，不能进行该操作"),_T("提示信息"),MB_ICONINFORMATION);
	}
	else
	{
		CProgramItemDlg dlg(_T("项属性"));
		ContentLink *cl = (ContentLink*)m_listProgram.GetItemData(nIndex);

		dlg.SetName(cl->GetName());
		dlg.SetPath(cl->GetFilePath());
		dlg.SetDesc(cl->GetDescription());
		dlg.SetWebPage(cl->GetType() == _T("WebPage"));
		if (dlg.DoModal() == IDOK)
		{
			cl->SetName(dlg.GetName());
			cl->SetFilePath(dlg.GetPath());
			cl->SetDescription(dlg.GetDesc());
			cl->SetType((dlg.IsWebPage() ? _T("WebPage") : _T("VideoFile")));
		}
	}
}

void CProgramDlg::OnListProgramDblClicked(void)
{
	int nIndex = m_listProgram.GetCurSel();	
	if (nIndex >= 0)
		GetParent()->SendMessage(WM_OPEN_CONTENTLINK,m_listProgram.GetItemData(nIndex));
}

BOOL CProgramDlg::QuitConfirm(void)
{
	if (!m_program.IsModified())
		return TRUE;

	CString str;
	if (m_program.IsLoaded())
	{
		str.Format(_T("保存对 \"%s\" 的更改吗？"),m_program.GetFilePath());
		int nRet = MessageBox(str,_T("信息提示"),MB_YESNOCANCEL|MB_ICONQUESTION);
		if (nRet == IDNO)
			return TRUE;
		if (nRet == IDCANCEL)
			return FALSE;
		
		// if (nRet == IDYES)
		if (m_program.Save())
			return TRUE;
		
		str.Format(_T("保存节目单文件 \"%s\" 失败,请确认文件路径"),m_program.GetFilePath());
		MessageBox(str,_T("提示信息"),MB_ICONINFORMATION);
		return FALSE;
	}
	else
	{
		str.Format(_T("保存 新建节目单 么吗？"));
		int nRet = MessageBox(str,_T("信息提示"),MB_YESNOCANCEL|MB_ICONQUESTION);
		if (nRet == IDNO)
			return TRUE;
		if (nRet == IDCANCEL)
			return FALSE;
		
		//if (nRet == IDYES)	
		CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ENABLESIZING,ALL_PROGRAM_FILTER);
		if (dlg.DoModal() != IDOK)
			return FALSE;

		CString strFilePath = dlg.GetPathName();
		if (Fh::GetFileExt(strFilePath).CompareNoCase(PROGRAM_EXT+1))
			strFilePath += PROGRAM_EXT;
		if (m_program.SaveAs(strFilePath))
			return TRUE;
 
		str.Format(_T("保存节目单文件 \"%s\" 失败,请确认文件路径"),strFilePath);
		MessageBox(str,_T("提示信息"),MB_ICONINFORMATION);
		return FALSE;
	}
}

BOOL CProgramDlg::OpenNew(void)
{
	if (!QuitConfirm())
		return FALSE;
	
	m_program.ResetContent();
	RefreshProgram();
	return TRUE;
}

BOOL CProgramDlg::Reload(void)
{
	if (!m_program.IsModified())
		return TRUE;

	CString strPath = m_program.GetFilePath();

	CString str;
	if (m_program.IsLoaded())
		str.Format(_T("放弃对 \"%s\" 的修改么？"),strPath);
	else
		str.Format(_T("放弃对 新建节目单 的修改么？"),strPath);
	if(MessageBox(str,_T("信息提示"),MB_YESNO|MB_ICONQUESTION) == IDNO)
		return FALSE;

	if (strPath.IsEmpty())
		m_program.ResetContent();
	else
		m_program.Load(strPath);
	RefreshProgram();
	return TRUE;
}

BOOL CProgramDlg::ShowProp(void)
{
	return TRUE;
}

BOOL CProgramDlg::Save(void)
{
	if (!m_program.IsModified())
		return TRUE;

	if (m_program.IsLoaded())
		return m_program.Save();

	return SaveAs();
}

BOOL CProgramDlg::SaveAs(void)
{
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ENABLESIZING,ALL_PROGRAM_FILTER);
	if (dlg.DoModal() != IDOK)
		return FALSE;

	CString strFilePath = dlg.GetPathName();
	if (Fh::GetFileExt(strFilePath).CompareNoCase(PROGRAM_EXT+1))
		strFilePath += PROGRAM_EXT;

	if (m_program.SaveAs(strFilePath))
		return TRUE;

	CString str;
	str.Format(_T("保存节目单文件 \"%s\" 失败,请确认文件路径"),strFilePath);
	MessageBox(str,_T("提示信息"),MB_ICONINFORMATION);
	return FALSE;

}