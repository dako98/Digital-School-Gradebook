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

	Grade(int studentNum, int subjectID, const tm& date, int grade);
	
	int GetValue() const;
	int GetStudentNumber() const;
	int GetSubjectID() const;
	tm GetDate() const;

private:

	int studentNumber;
	int subjectID;
	tm date;
	int grade;
};

