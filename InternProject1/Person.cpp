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
