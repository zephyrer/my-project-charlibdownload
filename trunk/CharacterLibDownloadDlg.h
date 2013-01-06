
// CharacterLibDownloadDlg.h : 头文件
//
#include "TextProgressCtrl.h"

#pragma once


// CCharacterLibDownloadDlg 对话框
class CCharacterLibDownloadDlg : public CDialogEx
{
// 构造
public:
	CCharacterLibDownloadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHARACTERLIBDOWNLOAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	char Buffer[1024];
	CFile fp0 ;
	int length;
// 	int i,j;
	int uiSendCnt;	//文件的数据发送次数
	ULONGLONG filelen;
	char fileflag;            //打开文件标记
	cnComm m_cncomm;

// 	CProgressCtrl	m_progress;
	CTextProgressCtrl m_progress;
	CComboBox	m_ctlBaudrate;
	CComboBox	m_ctlPort;
	CString	m_filename;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
