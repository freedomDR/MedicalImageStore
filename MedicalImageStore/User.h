#pragma once
#include "Container.h"
class User
{
public:
	User();
	~User();
	static CString user_group;
	static CString user_name;
	static CString pass_word;
	static CString token;
	static void update();
	
	
	static CString auth_token;
	static CString storage_url;
	static Container containers[1000];
	static int containerLength;
	static CString headInfo;
	static CString selectContainerName;
	static int selectContainerId;
};

