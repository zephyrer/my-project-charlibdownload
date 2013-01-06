
// CharacterLibDownloadDlg.h : ͷ�ļ�
//
#include "TextProgressCtrl.h"

#pragma once


// CCharacterLibDownloadDlg �Ի���
class CCharacterLibDownloadDlg : public CDialogEx
{
// ����
public:
	CCharacterLibDownloadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHARACTERLIBDOWNLOAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	char Buffer[1024];
	CFile fp0 ;
	int length;
// 	int i,j;
	int uiSendCnt;	//�ļ������ݷ��ʹ���
	ULONGLONG filelen;
	char fileflag;            //���ļ����
	cnComm m_cncomm;

// 	CProgressCtrl	m_progress;
	CTextProgressCtrl m_progress;
	CComboBox	m_ctlBaudrate;
	CComboBox	m_ctlPort;
	CString	m_filename;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnComRev(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	void OnSenddate();
public:
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedButtonBrowser();
private:
	CFont m_font;
	CBrush m_brush;
	int iSecond;
// 	afx_msg LRESULT OnComRev(WPARAM wParam, LPARAM lParam);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOpencomport();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
