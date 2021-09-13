#include "pch.h"
#include "CGrade.h"
#include "Utility.h"


GRADE::GRADE()
	:nID(-1)
	,nStudentID(-1)
	,nSubjectID(-1)
	,dtDate()
	,value(GRADE::GRADES::INVALID)
{
	Clear(*this);
}

BOOL GRADE::Validate() const
{
	return (nStudentID > 0 &&
		nSubjectID > 0 &&
		value > GRADE::GRADES::INVALID && value < GRADE::GRADES::COUNT &&
		COleDateTime{ dtDate.year, dtDate.month, dtDate.day, dtDate.hour, dtDate.minute, dtDate.second, } <= COleDateTime::GetCurrentTime());
}

CString MapGradeName(const int value) noexcept
{
	CString name;

	switch (value)
	{
	case GRADE::GRADES::A:	name = "Excellent";	break;
	case GRADE::GRADES::B:	name = "Very good";	break;
	case GRADE::GRADES::C:	name = "Good";		break;
	case GRADE::GRADES::D:	name = "Average";	break;
	case GRADE::GRADES::F:	name = "Bad";		break;

	default:
		name = "";
		ASSERT(false && "Invalid grade.");
		break;
	}

	return name;
}