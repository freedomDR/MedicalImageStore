#pragma once
class User
{
public:
	User();
	~User();
	static CString user_name;
	static CString pass_word;
	static CString token;
	static void update();
	static CString auth_token;
};

