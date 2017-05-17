#pragma once
#include "SwiftObject.h"
class Container
{
public:
	Container();
	~Container();
	CString name;
	int length;
	SwiftObject* swiftObject[1000];
	static CString container_name;
	static void getAllContainer();
	CString headInfo;
};

