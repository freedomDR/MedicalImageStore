
// MedicalImageStore.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMedicalImageStoreApp: 
// �йش����ʵ�֣������ MedicalImageStore.cpp
//

class CMedicalImageStoreApp : public CWinApp
{
public:
	CMedicalImageStoreApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CMedicalImageStoreApp theApp;