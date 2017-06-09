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