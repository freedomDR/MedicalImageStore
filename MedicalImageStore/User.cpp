#include "stdafx.h"
#include "User.h"
#include "SwiftTools.h"
#include "User.h"
#include "Container.h"
#include "json/json.h"


User::User()
{
}


User::~User()
{
}

void User::update()
{
	CInternetSession session;
	CHttpConnection * conn = session.GetHttpConnection(SwiftTools::server, (INTERNET_PORT)SwiftTools::port);
	CHttpFile* file = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, TEXT("/auth/v1.0"));
	file->AddRequestHeaders(L"X-Storage-User: " + User::user_name + L":" + User::user_group);
	file->AddRequestHeaders(L"X-Storage-Pass: " + User::pass_word);
	file->SendRequest();
	DWORD status;
	file->QueryInfoStatusCode(status);
	if (status == HTTP_STATUS_OK)
	{
		CString result=L"";
		file->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, result);
		int pos = 0;
		CString value = result.Tokenize(L"\n\r", pos);
		while (value != L"")
		{
			CString mid;
			int mid_pos = 0;
			if ((mid = value.Tokenize(L":", mid_pos)) == L"X-Auth-Token")
			{
				User::auth_token = value.Tokenize(L":", mid_pos);
			}
			if (mid == L"X-Storage-Url")
			{
				User::storage_url = value.Tokenize(L" ", mid_pos);
			}
			value = result.Tokenize(L"\n\r", pos);
		}
	}
	//file->Close();
	//conn->Close();
	//session.Close();
	
	file->Close();
	conn->Close();
	session.Close();
	Container::getAllContainer();
}




CString User::user_group;
CString User::user_name; 
CString User::pass_word;
CString User::auth_token;
CString User::storage_url;
CString User::headInfo;
CString User::selectContainerName;
int User::selectContainerId;
int User::containerLength = 0;
Container User::containers[1000];