
// CharacterLibDownloadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CharacterLibDownload.h"
#include "CharacterLibDownloadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BYTE_LEN 256	//�ֽڳ���


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCharacterLibDownloadDlg �Ի���




CCharacterLibDownloadDlg::CCharacterLibDownloadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCharacterLibDownloadDlg::IDD, pParent)
{
	m_filename = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_font.CreatePointFont(105,_T("����_GB2312"));
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
//////////�Զ�����Ϣ
	ON_BN_CLICKED(IDC_SEND, &CCharacterLibDownloadDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER, &CCharacterLibDownloadDlg::OnBnClickedButtonBrowser)
	ON_MESSAGE(ON_COM_RECEIVE, &CCharacterLibDownloadDlg::OnComRev)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENCOMPORT, &CCharacterLibDownloadDlg::OnBnClickedOpencomport)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCharacterLibDownloadDlg ��Ϣ�������

BOOL CCharacterLibDownloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCharacterLibDownloadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCharacterLibDownloadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���մ��ڷ���������0xF0���ļ����ݷ�������
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

//�������ݵ�����
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
// 		str.Format("���ڷ����ļ�,�����%d%%......", iProgressPos);
		str.Format("���ڷ����ļ�......");
	}
	else
	{
// 		str.Format("���ڷ����ļ�,�����%d%%...", iProgressPos);
		str.Format("���ڷ����ļ�...");
	}

	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(str);
	
	if (!iProgressPos)
	{
		iSecond = 0;
	}
	if ((ULONGLONG)(BYTE_LEN * uiSendCnt) >= filelen)
	{
// 		MessageBox(_T("�ļ��������!"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		str.Format(_T("�������,��ʱ%ds,�ɵ�������͡���ť����"), iSecond);
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(str);
		m_progress.SetPos(0);
		fp0.Close();
		fileflag = FALSE;
	}
}


void CCharacterLibDownloadDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_cncomm.IsOpen())
	{
		MessageBox(_T("����δ�򿪣����ȴ򿪴���!"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}

	fp0.Close();
	if (!fp0.Open(m_filename, CFile::modeRead))
	{
// 		MessageBox(_T("���ļ�����!"), _T("����"), MB_OK | MB_ICONWARNING);
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("���ļ�����"));
// 		fp0.Close();
		return ;
	}

	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("���ļ��ɹ�,�����豸��������!"));
    fileflag = TRUE;
	filelen = fp0.GetLength();
    uiSendCnt = 0;
	
	UpdateData(0);
}

void CCharacterLibDownloadDlg::OnBnClickedButtonBrowser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog filedlg(TRUE, NULL, NULL, NULL, _T("�����ļ�(*.*)|*.*||"));
	int i = filedlg.DoModal();
	if (i == IDCANCEL)
	{
		return;
	}
// 	m_filename = filedlg.GetFileName();
	m_filename = filedlg.GetPathName();

	((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("�ļ��Ѽ��أ�"));

	UpdateData(FALSE);

	return;
}


HBRUSH CCharacterLibDownloadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATUS:
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);//͸��  
		pDC->SelectObject(&m_font);
		break;

// 	case IDC_OPENCOMPORT:
// 		pDC->SetTextColor(RGB(255, 0, 0));
// 		pDC->SetBkMode(TRANSPARENT);//͸��  
// 		pDC->SelectObject(&m_font);
// 		break;

	default:
		break;
	}

	return hbr;
}


void CCharacterLibDownloadDlg::OnBnClickedOpencomport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString msg;
	DWORD baudrate, port;

	UpdateData(TRUE);
	port = m_ctlPort.GetCurSel() + 1 ;
	CString buff;
	m_ctlBaudrate.GetWindowText(buff);
	baudrate = _tcstol(buff.GetBuffer(), NULL, 10);
	buff.ReleaseBuffer();

	m_cncomm.SetBufferSize(256, 256);
	m_cncomm.SetWnd(GetSafeHwnd());   //���ý��մ��ھ��

	CString str, strOpenPort;

	strOpenPort.Format(_T("�򿪴���"));
	GetDlgItemText(IDC_OPENCOMPORT, str);

	if (str == strOpenPort)
	{
		if (!m_cncomm.Open(port, baudrate))
		{
			((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("�򿪴���ʧ�ܣ�"));
			return;
		}
		msg.Format("����COM%d�Ѵ򿪣�", port);
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(msg);
		((CComboBox*)GetDlgItem(IDC_OPENCOMPORT))->SetWindowText(_T("�رմ���"));
	}
	else
	{
		m_cncomm.Close();
		((CComboBox*)GetDlgItem(IDC_STATUS))->SetWindowText(_T("�����ѹرգ�"));
		((CComboBox*)GetDlgItem(IDC_OPENCOMPORT))->SetWindowText(_T("�򿪴���"));
	}
}


void CCharacterLibDownloadDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
	++iSecond;//�����
}


int CCharacterLibDownloadDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	KillTimer(1);
	SetTimer(1, 1000, NULL);//��ʱ1s

	return 0;
}
