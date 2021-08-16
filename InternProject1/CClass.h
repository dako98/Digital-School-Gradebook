#pragma once
struct CClass
{
	static const int MAX_NAME_SIZE = 5;

	CClass();

	int nID;
	wchar_t szName[MAX_NAME_SIZE + 1];
	int teacherID;

	BOOL Validate() const;
};

