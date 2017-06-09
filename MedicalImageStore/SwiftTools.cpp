#include "stdafx.h"
#include "SwiftTools.h"
#include "User.h"


SwiftTools::SwiftTools()
{
}


SwiftTools::~SwiftTools()
{
}

void SwiftTools::Test()
{
	CInternetSession session;
	CHttpConnection * conn = session.GetHttpConnection(SwiftTools::server, (INTERNET_PORT)SwiftTools::port);
	CHttpFile* file = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, TEXT("v1/AUTH_test/DR?format=json"));
	file->AddRequestHeaders(L"X-Auth-Token: " + User::auth_token);
	file->SendRequest();
	DWORD dwRet;
	file->QueryInfoStatusCode(dwRet);

	if (dwRet != HTTP_STATUS_OK)
	{
		CString errText;
		errText.Format(L"POST³ö´í£¬´íÎóÂë£º%d", dwRet);
		AfxMessageBox(errText);
	}
	else
	{
		int len = file->GetLength();
		char buf[2000];
		int numread;
		CString filepath;
		CString strFile = L"response.txt";
		filepath.Format(L".\\%s", strFile);
		CFile myfile(filepath,
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		strFile = L"";
		//CString mid;
		//while ((numread = pFile->Read(buf, sizeof(buf) - 1)) > 0)
		char buff[5000];
		while((numread = file->Read(buff,4000)) > 0)
		{
			//buf[numread] = '\0';
			buff[numread] = '\0';
			strFile += buff;
			myfile.Write(buff, numread);
			//strFile += mid;
		}
		myfile.Close();
	}

	session.Close();
	file->Close();
	delete file;
}


CString SwiftTools::server = L"192.168.108.128";
int SwiftTools::port = 8088;