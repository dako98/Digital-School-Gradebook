#pragma once
struct STUDENT_CLASS
{
	static const int MAX_NAME_SIZE = 5;

	STUDENT_CLASS();

	int nID;

	wchar_t szName[MAX_NAME_SIZE + 1];
	int nTeacherNumber;

	BOOL Validate() const;
};