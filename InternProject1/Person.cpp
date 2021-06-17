#include "pch.h"
#include "Person.h"

Person::Person(const CString& name)
{
	if (name!="")
	{
		this->name = name;
	}
	else
	{
		throw std::invalid_argument("Invalid name.");
	}
}

CString Person::getName() const
{
	return name;
}

Person::Person(std::iostream& in)
{
	this->InitialiseFromStream(in, *this);
}

std::ostream& operator<<(std::ostream& out, const Person& obj)
{
	// "<name>"
	//
	out << '\"' << CT2A(obj.name) << '\"'
		<< std::flush;
	return out;
}

std::istream& operator>>(std::istream& in, Person& obj)
{
	obj.InitialiseFromStream(in, obj);

	return in;
}

void Person::InitialiseFromStream(std::istream& in, Person& obj)
{
	std::string tmp;

	in.ignore(1);
	std::getline(in, tmp, '\"');
	obj.name = CString{ tmp.c_str() };
	in >> std::ws;
}