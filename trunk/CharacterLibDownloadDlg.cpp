
// CharacterLibDownloadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharacterLibDownload.h"
#include "CharacterLibDownloadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BYTE_LEN 256	//字节长度


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCharacterLibDownloadDlg 对话框




CCharacterLibDownloadDlg::CCharacterLibDownloadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCharacterLibDownloadDlg::IDD, pParent)
{
	m_filename = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_font.CreatePointFont(105,_T("楷体_GB2312"));
}

void CCharacterLibDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ctlBaudrate);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctlPort);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_filename);
}

BEGIN_MESSAGE_MAP(CCharacterLibDownloadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_MESSAGE(ON_COM_RECEIVE, &CCharacterLibDownloadDlg::OnComRev)
//////////自定义消息
	ON_BN_CLICKED(IDC_SEND, &CCharacterLibDownloadDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER, &CCharacterLibDownloadDlg::OnBnClickedButtonBrowser)
	ON_MESSAGE(ON_COM_RECEIVE, &CCharacterLibDownloadDlg::OnComRev)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENCOMPORT, &CCharacterLibDownloadDlg::OnBnClickedOpencomport)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCharacterLibDownloadDlg 消息处理程序

BOOL CCharacterLibDownloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	iSecond = 0;
	((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->SetCurSel(6);

// 	HMODULE module = GetModuleHandle(0); 
	CHAR buf[MAX_PATH]; 
// 	GetModuleFileName(module, buf, sizeof(buf)); 
	GetCurrentDirectory(MAX_PATH, buf);
	CString strFilePath;
	strFilePath.Format(_T("%s\\ziku\\kt16.bin"), buf);
	m_filename = strFilePath;
	((CComboBox*)GetDlgItem(IDC_EDIT_FILENAME))->SetWindowText(strFilePath);
// 	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T(""));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCharacterLibDownloadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCharacterLibDownloadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCharacterLibDownloadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//接收串口发来的数据0xF0后将文件数据发到串口
afx_msg LRESULT CCharacterLibDownloadDlg::OnComRev(WPARAM wParam, LPARAM lParam)
{
	unsigned char buf[2] = {0};
	if (m_cncomm.Read(buf, 2))
	{
		if ((buf[0] == 0xf0) && (fileflag == 1))  
		{
			OnSenddate();
		}
	}

	return 0;
}

//发送数据到串口
void CCharacterLibDownloadDlg::OnSenddate()
{
	int iProgressPos = 0;
	CString str;
	length = fp0.Read(Buffer, BYTE_LEN);

	if (length == 0)   
	{
		return;
	}

	if (length < BYTE_LEN )
	{
		for (int i = length; i < BYTE_LEN; i++ )
		{
			Buffer[i] = 0x00;	

		}
	}
	++uiSendCnt;
	m_cncomm.Write(Buffer, BYTE_LEN);
	iProgressPos = (int)(((float)(BYTE_LEN * uiSendCnt) / (float)filelen) * 100); 
	m_progress.SetPos(iProgressPos);

	if (iProgressPos % 8)
	{
// 		str.Format("正在发送文件,已完成%d%%......", iProgressPos);
		str.Format("正在发送文件......");
	}
	else
	{
// 		str.Format("正在发送文件,已完成%d%%...", iProgressPos);
		str.Format("正在发送文件...");
	}

	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(str);
	
	if (!iProgressPos)
	{
		iSecond = 0;
	}
	if ((ULONGLONG)(BYTE_LEN * uiSendCnt) >= filelen)
	{
// 		MessageBox(_T("文件发送完成!"), _T("提示"), MB_OK | MB_ICONWARNING);
		str.Format(_T("发送完成,耗时%ds,可点击“发送”按钮继续"), iSecond);
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(str);
		m_progress.SetPos(0);
		fp0.Close();
		fileflag = FALSE;
	}
}


void CCharacterLibDownloadDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_cncomm.IsOpen())
	{
		MessageBox(_T("串口未打开，请先打开串口!"), _T("提示"), MB_OK | MB_ICONWARNING);
		return;
	}

	fp0.Close();
	if (!fp0.Open(m_filename, CFile::modeRead))
	{
// 		MessageBox(_T("打开文件出错!"), _T("错误"), MB_OK | MB_ICONWARNING);
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("打开文件出错"));
// 		fp0.Close();
		return ;
	}

	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("打开文件成功,请与设备建立连接!"));
    fileflag = TRUE;
	filelen = fp0.GetLength();
    uiSendCnt = 0;
	
	UpdateData(0);
}

void CCharacterLibDownloadDlg::OnBnClickedButtonBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog filedlg(TRUE, NULL, NULL, NULL, _T("所有文件(*.*)|*.*||"));
	int i = filedlg.DoModal();
	if (i == IDCANCEL)
	{
		return;
	}
// 	m_filename = filedlg.GetFileName();
	m_filename = filedlg.GetPathName();

	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("文件已加载！"));

	UpdateData(FALSE);

	return;
}


HBRUSH CCharacterLibDownloadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATUS:
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);//透明  
		pDC->SelectObject(&m_font);
		break;

// 	case IDC_OPENCOMPORT:
// 		pDC->SetTextColor(RGB(255, 0, 0));
// 		pDC->SetBkMode(TRANSPARENT);//透明  
// 		pDC->SelectObject(&m_font);
// 		break;

	default:
		break;
	}

	return hbr;
}


void CCharacterLibDownloadDlg::OnBnClickedOpencomport()
{
	// TODO: 在此添加控件通知处理程序代码
	CString msg;
	DWORD baudrate, port;

	UpdateData(TRUE);
	port = m_ctlPort.GetCurSel() + 1 ;
	CString buff;
	m_ctlBaudrate.GetWindowText(buff);
	baudrate = _tcstol(buff.GetBuffer(), NULL, 10);
	buff.ReleaseBuffer();

	m_cncomm.SetBufferSize(256, 256);
	m_cncomm.SetWnd(GetSafeHwnd());   //设置接收窗口句柄

	CString str, strOpenPort;

	strOpenPort.Format(_T("打开串口"));
	GetDlgItemText(IDC_OPENCOMPORT, str);

	if (str == strOpenPort)
	{
		if (!m_cncomm.Open(port, baudrate))
		{
			((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("打开串口失败！"));
			return;
		}
		msg.Format("串口COM%d已打开！", port);
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(msg);
		((CComboBox*)GetDlgItem(IDC_OPENCOMPORT))->SetWindowText(_T("关闭串口"));
	}
	else
	{
		m_cncomm.Close();
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("串口已关闭！"));
		((CComboBox*)GetDlgItem(IDC_OPENCOMPORT))->SetWindowText(_T("打开串口"));
	}
}


void CCharacterLibDownloadDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	++iSecond;//秒计数
}


int CCharacterLibDownloadDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	KillTimer(1);
	SetTimer(1, 1000, NULL);//定时1s

	return 0;
}
