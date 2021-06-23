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
	DBTIMESTAMP dtDate;
	int value;

	virtual BOOL Validate() const;

	friend std::ostream& operator<<(std::ostream& out, const GRADE& obj);
	friend std::istream& operator>>(std::istream& in, GRADE& obj);

protected:
	void Read(std::istream& in);
};