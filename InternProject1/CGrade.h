#pragma once

#include <fstream>



struct GRADE
{
	static enum GRADES
	{
		INVALID,

		F,
		D,
		C,
		B,
		A,

		COUNT
	};

	int nID;
	int nStudentID;
	int nSubjectID;
	DBTIMESTAMP dtDate;
	GRADES value;

	BOOL Validate() const;

	friend std::ostream& operator<<(std::ostream& out, const GRADE& obj);
	friend std::istream& operator>>(std::istream& in, GRADE& obj);
};