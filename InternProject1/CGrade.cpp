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
		COleDateTime{ dtDate.year, dtDate.month, dtDate.day, dtDate.hour, dtDate.minute, dtDate.second, } <= COleDateTime::GetCurrentTime()
);
}