#include "pch.h"
#include "Grade.h"

Grade::Grade(int studentNum, int subjectID, const COleDateTime& date, int grade)
{
	if (/* validate student num*/
		/* validate subject ID*/
		(grade > GRADES::INVALID && grade < GRADES::COUNT))
	{
		this->studentNumber	= studentNum;
		this->subjectID		= subjectID;

		this->date = date;

		this->grade = grade;
	}
	else
	{
		throw std::invalid_argument("Invalid grade arguments.");
	}
}

int Grade::GetValue() const
{
	return grade;
}

int Grade::GetStudentNumber() const
{
	return studentNumber;
}

int Grade::GetSubjectID() const
{
	return subjectID;
}

COleDateTime Grade::GetDate() const
{
	return date;
}