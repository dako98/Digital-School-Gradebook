#pragma once

#include <stdexcept>


enum GRADES
{
	INVALID = -1,

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

	Grade(int studentNum, int subjectID, const COleDateTime& date, int grade, int gradeID);
	
	int GetID() const;
	int GetValue() const;
	int GetStudentNumber() const;
	int GetSubjectID() const;
	COleDateTime GetDate() const;

	static CString MapName(const int value);
	static bool Validate(int studentNum, int subjectID, const COleDateTime& date, int grade);

private:

	int id;
	int studentNumber;
	int subjectID;
	COleDateTime date;
	int grade;
};

