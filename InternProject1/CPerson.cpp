#include "pch.h"
#include "CPerson.h"


std::ostream& operator<<(std::ostream& out, const PERSON& obj)
{
	out << strlen(obj.szFirstName) << ' ' << obj.szFirstName << ',' <<
		strlen(obj.szLastName) << ' ' << obj.szLastName;

	return out;
}

/*
std::ostream& PERSON::operator<<(std::ostream& out) const
{
	out << strlen(szFirstName) << ' ' << szFirstName << ',' <<
		strlen(szLastName) << ' ' << szLastName << '\n';

	return out;
}
*/

std::istream& operator>>(std::istream& in, PERSON& obj)
{
	PERSON tmp;

	int count;
	in >> count;

	// Validate name lenght
	if (in.good() && count <= PERSON::MAX_NAME_SIZE)
	{
		// Get name
		in.ignore(1);
		in.getline(tmp.szFirstName, count);

		// Check format
		/*if (in.good() && in.peek() == ',')
		{
			in.ignore(1);
		}
		else
		{
			in.setstate(std::ios_base::failbit);
		}*/
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
			in.getline(tmp.szLastName, count);

			// Check format
			//if (in.good() && in.peek() == ',')
			//{
			//	in.ignore(1);
			//}
			//else
			//{
			//	in.setstate(std::ios_base::failbit);
			//}
		}// !Last name
		else
		{
			in.setstate(std::ios_base::failbit);
		}
	}

	if (in.good())
	{
		obj = tmp;
	}

	return in;
}

/*
std::istream& PERSON::operator>>(std::istream& in)
{
	PERSON tmp;

	int count;
	in >> count;

	// Validate name lenght
	if (in.good() && count <= PERSON::MAX_NAME_SIZE)
	{
		// Get name
		in.getline(tmp.szFirstName, count);

		// Check format
		if (in.good() && in.peek() == ',')
		{
			in.ignore(1);
		}
		else
		{
			in.setstate(std::ios_base::failbit);
		}
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
			in.getline(tmp.szLastName, count);

			// Check format
			if (in.good() && in.peek() == ',')
			{
				in.ignore(1);
			}
			else
			{
				in.setstate(std::ios_base::failbit);
			}
		}// !Last name
		else
		{
			in.setstate(std::ios_base::failbit);
		}
	}

	if (in.good())
	{
		*this = tmp;
	}

	return in;
}
*/

BOOL PERSON::Validate() const
{
	return (strcmp(szFirstName, "") != 0 && strlen(szFirstName) <= MAX_NAME_SIZE &&
		strcmp(szLastName, "") != 0 && strlen(szLastName) <= MAX_NAME_SIZE);
}