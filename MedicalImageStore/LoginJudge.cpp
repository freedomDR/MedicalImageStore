#include "stdafx.h"
#include "LoginJudge.h"
#include "SwiftTools.h"
#include "User.h"


LoginJudge::LoginJudge()
{
}


LoginJudge::~LoginJudge()
{
}

int LoginJudge::judge(CString user_group, CString user_name, CString pass)
{
	CInternetSession session;
	CHttpConnection* conn = session.GetHttpConnection(SwiftTools::server, (INTERNET_PORT)SwiftTools::port);
	file = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, TEXT("/auth/v1.0"), NULL, 1, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE);
	file->AddRequestHeaders(L"X-Storage-User: " + user_name + L":" + user_group);
	file->AddRequestHeaders(L"X-Storage-Pass: "+pass);
	file->SendRequest();
	DWORD status;
	LoginJudge::file->QueryInfoStatusCode(status);
	if (status == HTTP_STATUS_OK)
	{
		User::user_name = user_name;
		User::pass_word = pass;
		User::user_group = user_group;
		CString result = L"";
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
		file->Close();
		conn->Close();
		session.Close();
		delete file;
		delete conn;
		User::update();
	}
	return status;
}

CHttpFile* LoginJudge::file;
