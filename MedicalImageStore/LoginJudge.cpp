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
	file = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, TEXT("/auth/v1.0"));
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
		User::update();
	}
	return status;
}

CHttpFile* LoginJudge::file;
