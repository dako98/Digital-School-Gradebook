#include "pch.h"
#include "Person.h"

Person::Person(const std::string& name)
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

std::string Person::getName() const
{
	return name;
}
