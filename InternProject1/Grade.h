#pragma once

#include <stdexcept>


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

class Grade
{
public:

	Grade(int studentNum, int subjectID, const COleDateTime& date, int grade);
	
	int GetValue() const;
	int GetStudentNumber() const;
	int GetSubjectID() const;
	COleDateTime GetDate() const;

	static CString MapName(const int value);

private:

	int studentNumber;
	int subjectID;
	COleDateTime date;
	int grade;
};

