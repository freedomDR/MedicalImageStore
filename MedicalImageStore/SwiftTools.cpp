#include "stdafx.h"
#include "SwiftTools.h"


SwiftTools::SwiftTools()
{
}


SwiftTools::~SwiftTools()
{
}

void SwiftTools::Test()
{
	CInternetSession mySession;
	CString mid;
	mid.Format(L"%s", "www.baidu.com");

	//CHttpConnection *conn = mySession.GetHttpConnection(TEXT("192.168.108.128"),(INTERNET_PORT)8088);
	CHttpConnection *conn = mySession.GetHttpConnection(server, (INTERNET_PORT)port);
	CHttpFile *pFile = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET,TEXT("/auth/v1.0"));
	pFile->AddRequestHeaders(L"X-Storage-User: test:tester");
	pFile->AddRequestHeaders(L"X-Storage-Pass: testing");
	
	//CHttpFile *pFile = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, TEXT("/info"));
	
	BOOL flag = pFile->SendRequest();
	
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);

	if (dwRet != HTTP_STATUS_OK)
	{
		CString errText;
		errText.Format(L"POST³ö´í£¬´íÎóÂë£º%d", dwRet);
		AfxMessageBox(errText);
	}
	else
	{
		int len = pFile->GetLength();
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
		while((numread = pFile->Read(buff,4000)) > 0)
		{
			//buf[numread] = '\0';
			buff[numread] = '\0';
			strFile += buff;
			myfile.Write(buff, numread);
			//strFile += mid;
		}
		myfile.Close();
	}

	mySession.Close();
	pFile->Close();
	delete pFile;
}


CString SwiftTools::server = L"192.168.108.128";
int SwiftTools::port = 8088;