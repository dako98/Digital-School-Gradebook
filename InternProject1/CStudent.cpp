#include "pch.h"
#include "CStudent.h"

#include <fstream>
#include <vector>
#include "Utility.h"


STUDENT::STUDENT()
	:PERSON()
	, dtBirthDate()
	, classID(-1)
	, numberInClass(-1)
{
	Clear(*this);
}

BOOL STUDENT::Validate() const
{
	return (PERSON::Validate() &&
		dtBirthDate.year <= COleDateTime::GetCurrentTime().GetYear()) &&
		classID >= 0 &&
		numberInClass > 0;
}