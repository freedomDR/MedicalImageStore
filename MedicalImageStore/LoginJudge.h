#pragma once
class LoginJudge
{
public:
	LoginJudge();
	~LoginJudge();
	static int judge(CString user_group,CString user_name, CString pass);
	static CHttpFile* file;
};

