#include "pch.h"
#include "CTeacher.h"



TEACHER::TEACHER()
	:PERSON()
{
}

BOOL TEACHER::Validate() const
{
	return PERSON::Validate();
}


std::ostream& operator<<(std::ostream& out, const TEACHER& obj)
{
	out << (PERSON)obj << ' ' <<
		obj.nID;

	return out;
}

std::istream& operator>>(std::istream& in, TEACHER& obj)
{
	obj.Read(in);

	return in;
}

void TEACHER::Read(std::istream& in)
{
	PERSON::Read(in);

	if (in.good())
	{
		in >> nID;
	}
}