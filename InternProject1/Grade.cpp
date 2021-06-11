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

CString Grade::MapName(const int value)
{
	CString name;

	switch (value)
	{
	case GRADES::A:		name = "Excellent";
		break;
	case GRADES::B:		name = "Very good";
		break;
	case GRADES::C:		name = "Good";
		break;
	case GRADES::D:		name = "Average";
		break;
	case GRADES::F:		name = "Bad";
		break;

	default:
		name = "";
		break;
	}

	return name;
}
