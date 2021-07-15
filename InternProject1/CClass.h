#pragma once
struct CClass
{
	CClass();

	int ID;
	CString name;
	int teacherID;

	BOOL Validate() const;
};

