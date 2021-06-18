#include "pch.h"
#include "CGrade.h"

BOOL GRADE::Validate() const
{
	DBTIMESTAMP now;
	COleDateTime::GetCurrentTime().GetAsDBTIMESTAMP(now);

	return (nID > 0 &&
		nStudentID > 0 &&
		nSubjectID > 0 &&
		value > GRADE::GRADES::INVALID && value < GRADE::GRADES::COUNT &&
		dtDate.year <= now.year &&
		dtDate.month <= now.month &&
		dtDate.day <= now.day &&
		dtDate.hour <= now.hour &&
		dtDate.minute <= now.minute);
}

std::ostream& operator<<(std::ostream& out, const GRADE& obj)
{
	out << obj.nID << ' ' <<
		obj.nStudentID << ' ' <<
		obj.nSubjectID << ' ' <<
		obj.dtDate.year << ' ' <<
		obj.dtDate.month << ' ' <<
		obj.dtDate.day << ' ' <<
		obj.dtDate.hour << ' ' <<
		obj.dtDate.minute;

	return out;
}

std::istream& operator>>(std::istream& in, GRADE& obj)
{
	in >> obj.nID >>
		obj.nStudentID >>
		obj.nSubjectID >>
		obj.dtDate.year >>
		obj.dtDate.month >>
		obj.dtDate.day >>
		obj.dtDate.hour >>
		obj.dtDate.minute;

	return in;
}
