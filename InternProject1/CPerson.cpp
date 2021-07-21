#include "pch.h"
#include "CPerson.h"


std::ostream& operator<<(std::ostream& out, const PERSON& obj)
{
	out << obj.nID << ' ' <<
		wcslen(obj.szFirstName) << ' ' << obj.szFirstName << ' ' <<
		wcslen(obj.szLastName) << ' ' << obj.szLastName;

	return out;
}

std::istream& operator>>(std::istream& in, PERSON& obj)
{
	obj.Read(in);

	return in;
}

void PERSON::Read(std::istream& in)
{
/*
int count;

	in >> nID;

	in >> count;

	// Validate name lenght
	if (in.good() && count <= PERSON::MAX_NAME_SIZE)
	{
		// Get name
		in.ignore(1);
		in.read(szFirstName, count);
		szFirstName[count] = '\0';

	} // !First name
	else
	{
		in.setstate(std::ios_base::failbit);
	}

	if (in.good())
	{
		in >> count;
		// Validate name lenght
		if (in.good() && count <= PERSON::MAX_NAME_SIZE)
		{
			// Get name
			in.ignore(1);
			in.read(szLastName, count);
			szLastName[count] = '\0';

		}// !Last name
		else
		{
			in.setstate(std::ios_base::failbit);
		}
	}
	*/
}

PERSON::PERSON()
	:nID(-1)
	, szFirstName("")
	, szLastName("")
{
}

BOOL PERSON::Validate() const
{
	return 
		//(strcmp(szFirstName, "") != 0 && strlen(szFirstName) <= MAX_NAME_SIZE &&
		//strcmp(szLastName, "") != 0 && strlen(szLastName) <= MAX_NAME_SIZE &&
		(szFirstName != "" &&
		szLastName != "");
}