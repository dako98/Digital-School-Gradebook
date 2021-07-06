#include "pch.h"
#include "CStudent.h"

#include <fstream>
#include <vector>


STUDENT::STUDENT()
	:PERSON()
	, dtBirthDate()
	, classID(-1)
{
}

BOOL STUDENT::Validate() const
{
	return (PERSON::Validate() &&
		dtBirthDate.year <= COleDateTime::GetCurrentTime().GetYear()) &&
		classID >= 0;
}

void STUDENT::Read(std::istream& in)
{
	PERSON::Read(in);
	
	if (in.good())
	{
		// Birth date
		in >> dtBirthDate.year >> dtBirthDate.month >> dtBirthDate.day >>
			classID;
	}

}

std::ostream& operator<<(std::ostream& out, const STUDENT& obj)
{
	out << (PERSON)obj << ' ' <<
		obj.dtBirthDate.year << ' ' << obj.dtBirthDate.month << ' ' << obj.dtBirthDate.day << ' ' <<
		obj.classID;

	return out;
}

std::istream& operator>>(std::istream& in, STUDENT& obj)
{
	obj.Read(in);

	return in;
}
