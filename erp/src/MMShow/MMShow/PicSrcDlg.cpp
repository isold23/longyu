#include "stdafx.h"
#include "Resource.h"
#include "PicSrcDlg.h"
#include "DrawHelper.h"
#include "FileHelper.h"
#include "MediaFormatDef.h"
#include <GdiPlus.h>
#include "Cfg.h"
#include "FileHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



IMPLEMENT_DYNAMIC(CPicSrcDlg, CVideoSrcBaseDialog)

CPicSrcDlg::CPicSrcDlg(CWnd* pParent /*=NULL*/)
	: CVideoSrcBaseDialog(CPicSrcDlg::IDD, pParent),
	  m_cbHistory(_T("PicHistory"))
{
	m_pcszName = _T("图像");
}

CPicSrcDlg::~CPicSrcDlg(void)
{
}

void CPicSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CVideoSrcBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_HISTORY, m_cbHistory);
	DDX_Control(pDX, IDC_BTN_SELECT_FILE, m_btnOpen);
}
 

BEGIN_MESSAGE_MAP(CPicSrcDlg, CVideoSrcBaseDialog)
	ON_COMMAND(IDC_CB_HISTORY,&CPicSrcDlg::OnCBHistorySelChange)
	ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CPicSrcDlg::OnBnClickedBtnSelectFile)
END_MESSAGE_MAP()

 
BOOL CPicSrcDlg::OnInitDialog(void)
{
	CVideoSrcBaseDialog::OnInitDialog();
	
	Fh::Cder cder(gsys.PicPath());
	CWindowRect rc(GetDlgItem(IDC_STC_CONTENT));
	ScreenToClient(rc);
	m_pictureCtrl.Create(WS_CHILD|WS_VISIBLE,rc,this,1096); 

	AddAnchor(m_cbHistory,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_BTN_SELECT_FILE,TOP_RIGHT);
	AddAnchor(m_pictureCtrl,TOP_LEFT,BOTTOM_RIGHT);

	m_gaugeWnd.Create(&m_pictureCtrl,gcfg.GetUiOpTransparentGauge());
	m_cbHistory.SetFocus();

	m_btnOpen.SetImageFile(_T("OpenFile.png"));
	m_btnOpen.SetTip(_T("打开文件"));

	return TRUE;
}

LPCTSTR ALL_IMAGE_FILTER = _T(\
"所有图片文件|*.bmp;*.jpg;*.jpeg;*.jfif;*.png;*.tif;*.tiff;*.png;|\
位图文件(*.bmp)|*.bmp;|JPEG(*.jpg;*.jpeg;*.jfif)|*.jpg;*.jpeg;*.jfif;|GIF(*.png)|*.png;|\
TIFF(*.tif;*.tiff)|*.tif;*.tiff;|PNG(*.png)|*.png;|所有文件|*||"
);

void CPicSrcDlg::OnBnClickedBtnSelectFile()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ENABLESIZING,ALL_IMAGE_FILTER);
	if (dlg.DoModal() == IDOK)
		Show(dlg.GetPathName());
}

void CPicSrcDlg::Show(const CString &strFilePath)
{
	if (m_pictureCtrl.Show(strFilePath))
	{
		int nIndex = m_cbHistory.FindString(-1,strFilePath);
		if (nIndex < 0)
			m_cbHistory.InsertString(0,strFilePath);
		m_cbHistory.SetWindowText(strFilePath);
	}
	else
	{
		CString str ;
		str.Format(_T("打开图片文件 \"%s\" 失败,请确认图片文件格式正确"),Fh::GetFileName(strFilePath));
		MessageBox(str,_T("提示信息"),MB_ICONINFORMATION);
	}
}

void CPicSrcDlg::OnCBHistorySelChange(void)
{
	CString str;
	int nIndex = m_cbHistory.GetCurSel();
	m_cbHistory.GetLBText(nIndex,str); 
 	Show(str);
}

void CPicSrcDlg::OnOK(void)
{
	CString str;
	m_cbHistory.GetWindowText(str);
	str.Trim();
	if (!str.IsEmpty())
		Show(str);
}

CString CPicSrcDlg::GetDesc(void)
{
	return m_pictureCtrl.GetFilePath();
}

DWORD CPicSrcDlg::GetSampleTick(void) 
{
	return max(m_gaugeWnd.GetSampleTick(),m_pictureCtrl.GetSampleTick());
}


BOOL CPicSrcDlg::GetSample(CStaticBuffer &buf,int &nStride,CSize &sizeFull,CRect &rcSample)
{
	Gdiplus::Bitmap* pBitmap = m_pictureCtrl.GetBitmap();
	if (pBitmap == NULL)
		return FALSE;

	sizeFull = CSize(pBitmap->GetWidth(),pBitmap->GetHeight());	

	rcSample = CRect(0,0,sizeFull.cx,sizeFull.cy);
	m_gaugeWnd.CalcViewRect(rcSample);

	buf.Set(sizeFull.cx*rcSample.Height()*def_vBytesPerPixel);

	Gdiplus::BitmapData bitmapData;
	bitmapData.Width = rcSample.Width();
	bitmapData.Height = rcSample.Height();
	bitmapData.PixelFormat = def_gplusPixFormat;
	bitmapData.Stride = bitmapData.Width*def_vBytesPerPixel;
	bitmapData.Scan0 = buf.Ptr();
	bitmapData.Reserved = 0;

	Gdiplus::Rect rcLock(rcSample.left,rcSample.top,bitmapData.Width,bitmapData.Height);
	pBitmap->LockBits(&rcLock,Gdiplus::ImageLockModeRead|Gdiplus::ImageLockModeUserInputBuf,
		def_gplusPixFormat,&bitmapData);
	pBitmap->UnlockBits(&bitmapData);
	nStride = -bitmapData.Stride; 

	return TRUE;
}
