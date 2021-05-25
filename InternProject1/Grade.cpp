#include "pch.h"
#include "Grade.h"

Grade::Grade(int studentNum, int subjectID, const tm& date, int grade)
{
	if (/* validate student num*/
		/* validate subject ID*/
		   (date.tm_year >= 0 && date.tm_mon >= 0 && date.tm_mday > 0)
		&& (grade > GRADES::INVALID && grade < GRADES::COUNT))
	{
		this->studentNumber	= studentNum;
		this->subjectID		= subjectID;

		this->date.tm_mday	= date.tm_mday;
		this->date.tm_mon	= date.tm_mon;
		this->date.tm_year	= date.tm_year;

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

tm Grade::GetDate() const
{
	return date;
}