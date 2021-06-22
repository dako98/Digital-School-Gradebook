#include "pch.h"
#include "CGrade.h"

GRADE::GRADE()
	:nID(-1)
	,nStudentID(-1)
	,nSubjectID(-1)
	,dtDate()
	,value(GRADE::GRADES::INVALID)
{
}

BOOL GRADE::Validate() const
{
	DBTIMESTAMP now;
	COleDateTime::GetCurrentTime().GetAsDBTIMESTAMP(now);

	return (nID > 0 &&
		nStudentID > 0 &&
		nSubjectID > 0 &&
		value > GRADE::GRADES::INVALID && value < GRADE::GRADES::COUNT&&
		COleDateTime(dtDate) <= COleDateTime::GetCurrentTime());
/*		dtDate.year <= now.year &&
		dtDate.month <= now.month &&
		dtDate.day <= now.day &&
		dtDate.hour <= now.hour &&
		dtDate.minute <= now.minute);*/
}

void GRADE::Read(std::istream& in)
{
	in >> nID >>
		nStudentID >>
		nSubjectID >>
		value >>
		dtDate.year >>
		dtDate.month >>
		dtDate.day >>
		dtDate.hour >>
		dtDate.minute;
}

std::ostream& operator<<(std::ostream& out, const GRADE& obj)
{
	out << obj.nID << ' ' <<
		obj.nStudentID << ' ' <<
		obj.nSubjectID << ' ' <<
		obj.value << ' ' <<
		obj.dtDate.year << ' ' <<
		obj.dtDate.month << ' ' <<
		obj.dtDate.day << ' ' <<
		obj.dtDate.hour << ' ' <<
		obj.dtDate.minute;

	return out;
}

std::istream& operator>>(std::istream& in, GRADE& obj)
{
	obj.Read(in);

	return in;
}
