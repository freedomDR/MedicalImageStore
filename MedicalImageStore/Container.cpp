#include "stdafx.h"
#include "Container.h"
#include "json\json.h"
#include "SwiftTools.h"
#include "User.h"

Container::Container()
{
}


Container::~Container()
{
}

void Container::getAllContainer()
{
	CInternetSession session;
	CHttpConnection * conn = session.GetHttpConnection(SwiftTools::server, (INTERNET_PORT)SwiftTools::port);
	CHttpFile* file = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, L"v1/AUTH_" + User::user_name + L"?format=json", NULL, 1, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE);
	file->AddRequestHeaders(L"X-Auth-Token: " + User::auth_token);
	file->SendRequest();
	DWORD status;
	file->QueryInfoStatusCode(status);
	if (status == HTTP_STATUS_OK)
	{
		CString result = L"";
		file->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, result);
		User::headInfo = result;
		int pos = 0;
		CString value = result.Tokenize(L"\n\r", pos);
		while (value != L"")
		{
			CString mid;
			int mid_pos = 0;
			if ((mid = value.Tokenize(L":", mid_pos)) == L"X-Account-Container-Count")
			{
				mid = value.Tokenize(L":", mid_pos);
				User::containerLength = _ttoi(mid);
			}
			value = result.Tokenize(L"\n\r", pos);
		}

		char mid[4096] = { 0 };
		int num;
		result = L"";
		while ((num = file->Read(mid, 4095)) > 0)
		{
			mid[num] = '\0';
			result += mid;
		}
		//解析json数据-----------------------------------------------------------------------   
		Json::Reader reader;
		Json::Value root;
		std::string s = (CW2A)result.GetBuffer(0);
		int len;
		if (reader.parse(s, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
		{
			len = root.size();
			for (int i = 0; i < len; i++)
			{
				User::containers[i].name = root[i]["name"].asCString();
			}
		}
	}
	file->Close();
	conn->Close();
	session.Close();
	delete file;
	delete conn;
	for (int i = 0; i < User::containerLength; i++)
	{
		//SwiftObject::getAllObject(User::containers[i].name, i);
	}
}
