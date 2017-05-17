#pragma once
class SwiftObject
{
public:
	SwiftObject();
	~SwiftObject();
	CString name;
	static CString user_name;
	static void getAllObject(CString container_name, int pos);
	CString headInfo;
};

