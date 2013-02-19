#include "stdafx.h"
#include "Resource.h"
#include "OutputDlg.h"
#include "FileHelper.h"
#include "PreviewDlg.h"
#include "LiveSrcDlg.h"
#include "DrawHelper.h"
#include "cfg.h"
#include "MediaFormatDef.h"
#include "Devices.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum {OutputStop,OutputPreview,OutputCard};

COutputDlg::COutputDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(COutputDlg::IDD, pParent),
	  m_pPreviewDlg(NULL),
	  m_pLiveSrcDlg(NULL),
	  m_audioCapture(this),
	  s_curCfg(this),
	  m_chkRecord(FALSE),
	  m_rdLive(&m_rdPreview),
	  m_rdPreview(&m_rdLive)
{

}

COutputDlg::~COutputDlg()
{
	m_pOutputBuf = NULL;
	m_eventOutput.SetEvent();
	WaitForSingleObject(m_hOutputThread,INFINITE);
	::CloseHandle(m_hOutputThread);
}

void COutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_CB_VIDEO_OUTPUT,m_cbOutput);
	DDX_Control(pDX,IDC_STC_CONTENT,m_stcVideo);
	DDX_Control(pDX,IDC_BTN_SELECT_FILE, m_btnOpen);
	DDX_Control(pDX,IDC_BTN_RECORD,m_chkRecord);
	//DDX_Control(pDX,IDC_RD_DSHOW, m_rdLive);
	//DDX_Control(pDX,IDC_RD_PREVIEW,m_rdPreview);
	DDX_Control(pDX,IDC_EDIT_REC_PATH,m_editRecPath);
	DDX_Control(pDX,IDC_BTN_CFG,m_btnCfg);
}


BEGIN_MESSAGE_MAP(COutputDlg, CResizableDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_CB_VIDEO_OUTPUT,&COutputDlg::OnOutputSelChange)
	ON_BN_CLICKED(IDC_BTN_RECORD, &COutputDlg::OnBnClickedBtnRecord)
	ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &COutputDlg::OnBnClickedBtnSelRecFile)
	ON_BN_CLICKED(IDC_RD_PREVIEW,&COutputDlg::OnChangeSrc)
	ON_BN_CLICKED(IDC_RD_DSHOW,&COutputDlg::OnChangeSrc)
	ON_BN_CLICKED(IDC_BTN_CFG,&COutputDlg::OnOutputCfg)
	ON_MESSAGE(CCurCfg::WM_CFG_FINISHIED,&COutputDlg::OnOutputCfgFininshed) 
END_MESSAGE_MAP()

int VideoOutputIndex(const CString&);

BOOL COutputDlg::OnInitDialog(void)
{
	CResizableDialog::OnInitDialog();

	Fh::Cder cder(gsys.PicPath());

	m_btnOpen.SetImageFile(_T("OpenFile.png")); 
	m_btnOpen.SetTip(_T("选择文件"));

	m_chkRecord.SetImageFile(_T("Record.png"),_T("Recording.png"));
	m_chkRecord.SetTip(_T("开始录制"),_T("结束录制"));

	m_rdPreview.SetImageFile(_T("OutputDownOff.png"),_T("OutputDownOn.png"));
	m_rdPreview.SetTip(_T("预览输出"));

	m_rdLive.SetImageFile(_T("OutputRightOff.png"),_T("OutputRightOn.png"));
	m_rdLive.SetTip(_T("直播输出"));

	m_btnCfg.SetImageFile(_T("OutputCfg.png"));
	m_btnCfg.SetTip(_T("输出设置"));

	AddAnchor(m_stcVideo,TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(m_cbOutput,TOP_LEFT,TOP_RIGHT);

	//AddAnchor(m_rdPreview,CSize(50,0));
	//AddAnchor(m_rdLive,CSize(0,50));

	AddAnchor(m_btnOpen,TOP_RIGHT);
	AddAnchor(m_editRecPath,TOP_LEFT,TOP_RIGHT);
	AddAnchor(m_chkRecord,TOP_LEFT);
	AddAnchor(m_btnCfg,TOP_LEFT);
 
	s_curCfg.Create(CCurCfg::IDD,this);

	m_cbOutput.AddString(_T("停止输出..."));
	m_cbOutput.AddString(_T("预览输出..."));

	INT_PTR i; CString str;
	const CStringArray &devices =  CDevices::GetVideoDevices(FALSE);
	const CStringArray &names = CDevices::GetVideoDeviceNames(FALSE);
	for (i=0; i<names.GetCount(); ++i)
		m_cbOutput.AddString(names[i]);
	m_nOutputIndex = VideoOutputIndex(gcfg.GetOutputVideoOutput());
	m_cbOutput.SetCurSel(m_nOutputIndex);

	m_cardWriter.Start(gcfg.GetOutputVideoOutput(),CCurCfg::VSize(),CCurCfg::VBitrate());

	m_windowRender.Start(m_stcVideo);

	DWORD dwThreadId;
	m_hOutputThread = ::CreateThread(NULL,0,COutputDlg::OutptutWorkerThreadProc,this,0,&dwThreadId);
	return FALSE;
}


void COutputDlg::SetSourceDlg(CPreviewDlg *pPreviewDlg,CLiveSrcDlg *pLiveSrcDlg)
{
	m_pPreviewDlg = pPreviewDlg;
	m_pLiveSrcDlg = pLiveSrcDlg;

	//if (gcfg.GetOutputVideoInput()==0)
	//	m_rdPreview.SetChecked(TRUE);
	//else
	//	m_rdLive.SetChecked(TRUE);
	OnOutputSelChange();
}

void COutputDlg::OnBnClickedBtnRecord(void)
{
	if (m_mediaFileWriter.IsRunning())
	{
		if (!m_mediaFileWriter.End())
		{
			MessageBox(_T("结束录制失败"),_T("信息提示"),MB_ICONINFORMATION);
		}
		else
		{
			m_audioCapture.free();
			m_btnCfg.EnableWindow(TRUE);
			m_chkRecord.SetChecked(FALSE);
		}
	}
	else
	{
		CString strPath;
		m_editRecPath.GetWindowText(strPath);
		if (strPath.Trim().IsEmpty())
		{
			MessageBox(_T("文件路径为空，请重新输入"),_T("信息提示"),MB_ICONINFORMATION);
		}
		else
		{
			UINT i = 0;
			CString strExt = Fh::GetFileExt(strPath,TRUE);
			FindIndex(gsys.RecFormats(),strExt);

			if (FindIndex(gsys.RecFormats(),strExt) < 0)
				strPath += gsys.RecFormats()[gcfg.GetRecOutputFmt()]; 

			if (Fh::GetFolderPath(strPath).IsEmpty())
				strPath = gcfg.GetRecOutputPath() + strPath;

			m_editRecPath.SetWindowText(strPath);

			if (Fh::IsFileExist(strPath))
			{
				CString strTip;
				strTip.Format(_T("文件 %s 已经存在。确定要替换它？"),strPath);
				if (MessageBox(strTip,_T("信息提示"),MB_ICONINFORMATION|MB_YESNO) != IDYES)
					return;
			}

			BOOL bAudio = !CCurCfg::AInput().IsEmpty(); 
			if (!m_mediaFileWriter.Begin(strPath,CCurCfg::VSize(),CCurCfg::VBitrate(),CCurCfg::VFps(),
						(bAudio ? CCurCfg::ASampleRate() : 0), (bAudio ? CCurCfg::ABitrate() : 0)))
			{
				MessageBox(_T("开始录制失败"),_T("信息提示"),MB_ICONINFORMATION);
			}
			else
			{
				if ( bAudio)
				{
					int nBlockSize = m_mediaFileWriter.GetAudioFrameSize();
					m_audioCapture.init(def_aoChannels,def_aoBitPerSample,CCurCfg::ASampleRate(),nBlockSize,CCurCfg::AInput());
				}
				m_chkRecord.SetChecked(TRUE);
				m_btnCfg.EnableWindow(FALSE);
			}
		}
	}
}

LPCTSTR REC_VIDEO_FILTER = _T("MPEG文件 (*.mpg)|*.mpg;||");

void COutputDlg::OnBnClickedBtnSelRecFile(void)
{
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_ENABLESIZING,REC_VIDEO_FILTER);
	if (dlg.DoModal() == IDOK)
		m_editRecPath.SetWindowText(dlg.GetPathName());
}

void COutputDlg::OnOutputSelChange(void)
{
	ClearVideo();
	m_nOutputIndex = m_cbOutput.GetCurSel();
	if (m_nOutputIndex == OutputStop)
	{
		m_pPreviewDlg->SetOutput(NULL);
		m_pLiveSrcDlg->SetOutput(NULL);
	}
	else
	{
		if (m_rdPreview.IsChecked())
			m_pPreviewDlg->SetOutput(this);
		else
			m_pLiveSrcDlg->SetOutput(this);
	}
	m_cardWriter.SetCurrentCard(m_nOutputIndex-OutputCard);
}

void COutputDlg::ChangeSrcTo(BOOL bPreviewer)
{
	ClearVideo();

	m_pLiveSrcDlg->SetOutput(NULL);
	m_pPreviewDlg->SetOutput(NULL);

	if (m_nOutputIndex != OutputStop)
	{
		if (bPreviewer)
		{
			m_pPreviewDlg->SetOutput(this);
		}
		else
		{
			m_pLiveSrcDlg->SampleRef(TRUE);
			m_pLiveSrcDlg->SetOutput(this);
		}
	}
}

void COutputDlg::OnChangeSrc(void)
{
	ChangeSrcTo(m_rdPreview.IsChecked());
}
 

void COutputDlg::RenderVideo(LPCVOID buf,CSize size,int stride)
{
	m_windowRender.Fill(buf,size,stride);
	m_windowRender.Render();
	WriteMediaVideo(buf,size,stride);
}

 
void COutputDlg::WriteMediaVideo(LPCVOID buf,CSize size,int stride)
{
	m_pOutputBuf = buf;
	m_sizeOfOutput = size;
	m_nOutputStride = stride;
	m_eventOutput.SetEvent();
}


static BYTE ImageBuffer[1920*1080*def_vBytesPerPixel];
void COutputDlg::OutptutThreadProc(void)
{
	extern void scaleImage(int,int,int,int,const void*,int,void*);

	do 
	{
		m_eventOutput.Lock();
		if (m_pOutputBuf == NULL)
			break;

		if (!m_mediaFileWriter.IsRunning() &&  m_nOutputIndex<OutputCard)
			continue ;

		CSize sizeDst = CCurCfg::VSize();
		scaleImage(m_sizeOfOutput.cx,m_sizeOfOutput.cy,sizeDst.cx,sizeDst.cy,m_pOutputBuf,m_nOutputStride,ImageBuffer);
		if (m_mediaFileWriter.IsRunning())
			m_mediaFileWriter.WriteVideo(ImageBuffer);

		if (m_nOutputIndex >= OutputCard)
			m_cardWriter.WriteVideo(ImageBuffer);

	} while (TRUE);
}

DWORD WINAPI COutputDlg::OutptutWorkerThreadProc(LPVOID pv) throw()
{
	COutputDlg* pThis = reinterpret_cast< COutputDlg* >(pv); 
	pThis->OutptutThreadProc();
	return 0;
} 



void COutputDlg::onAudioData(LPCVOID data,int len)
{
	if (m_mediaFileWriter.IsRunning())
		m_mediaFileWriter.WriteAudio(data,len);
}

void COutputDlg::OnDestroy(void)
{
	m_windowRender.Stop();
	CResizableDialog::OnDestroy();
}

void COutputDlg::OnOutputCfg(void)
{
	if (!s_curCfg.IsWindowVisible())
	{
		CWindowRect rcRef(m_btnCfg);
		CWindowRect rc(s_curCfg);
		CSize size(rc.Size());

		rc.left = rcRef.left;
		rc.bottom = rcRef.top - 30;
		rc.right = rc.left + size.cx;
		rc.top = rc.bottom - size.cy;
		s_curCfg.MoveWindow(rc);

		s_curCfg.ShowWindow(SW_SHOW);
		s_curCfg.BringWindowToTop();
	}
}

LRESULT COutputDlg::OnOutputCfgFininshed(WPARAM wParam,LPARAM lParam)
{	
	if (wParam&CCurCfg::VSizeF || wParam|CCurCfg::VFpsF)
	{
		if (wParam & CCurCfg::VFpsF)
			m_pPreviewDlg->SetFps(CCurCfg::VFps());

		m_cardWriter.Start(m_nOutputIndex-OutputCard,CCurCfg::VSize(),CCurCfg::VFps());
	}
	return 0;
}