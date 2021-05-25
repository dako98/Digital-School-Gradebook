#include "pch.h"
#include "Student.h"

Student::Student(const std::string& name, const tm& birthdate, int numberInClass)
	:Person(name)
{
	if (birthdate.tm_year < 0 || birthdate.tm_mon < 0 || birthdate.tm_mday <= 0)
	{
		throw std::invalid_argument("Invalid date.");
	}
	if (numberInClass<=0)
	{
		throw std::invalid_argument("Invalid number in class.");
	}

	this->birthday.tm_mday = birthdate.tm_mday;
	this->birthday.tm_mon = birthdate.tm_mon;
	this->birthday.tm_year = birthdate.tm_year;

	number = numberInClass;
}
