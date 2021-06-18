#include "pch.h"
#include "CTeacher.h"



BOOL TEACHER::Validate() const
{
	return (PERSON::Validate());
}


std::ostream& operator<<(std::ostream& out, const TEACHER& obj)
{
	out << (PERSON)obj << ' ' <<
		obj.nID;

	return out;
}

std::istream& operator>>(std::istream& in, TEACHER& obj)
{
	TEACHER tmp;

	in >> (PERSON)tmp;

	if (in.good())
	{
		in >> tmp.nID;

		if (in.good())
		{
			obj = tmp;
		}
	}

	return in;
}

/*
std::ostream& TEACHER::operator<<(std::ostream& out) const
{
	PERSON::operator<<(out) << nID;

	return out;
}

std::istream& TEACHER::operator>>(std::istream& in)
{
	PERSON::operator>>(in);

	if (in.good())
	{
		in >> nID;
	}

	return in;
}
*/