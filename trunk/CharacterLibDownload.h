
// CharacterLibDownload.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCharacterLibDownloadApp:
// �йش����ʵ�֣������ CharacterLibDownload.cpp
//

class CCharacterLibDownloadApp : public CWinApp
{
public:
	CCharacterLibDownloadApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCharacterLibDownloadApp theApp;