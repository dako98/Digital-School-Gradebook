#pragma once

#include <fstream>


struct GRADE
{
	enum GRADES
	{
		INVALID,

		F,
		D,
		C,
		B,
		A,

		COUNT
	};

	GRADE();

	int nID;
	int nStudentID;
	int nSubjectID;
	TIMESTAMP_STRUCT dtDate;
	int value;

	BOOL Validate() const;
};