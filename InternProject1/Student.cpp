#include "pch.h"
#include "Student.h"

Student::Student(std::iostream& in)
	:Person(in)
{
	this->InitialiseFromStream(in, *this);
}

Student::Student(const CString& name, const COleDateTime& birthdate, int numberInClass)
	:Person(name)
{
	if (birthdate.invalid)
	{
		throw std::invalid_argument("Invalid date.");
	}
	
	if (numberInClass<=0)
	{
		throw std::invalid_argument("Invalid number in class.");
	}
	/*
	this->birthday.tm_mday = birthdate.tm_mday;
	this->birthday.tm_mon = birthdate.tm_mon;
	this->birthday.tm_year = birthdate.tm_year;
	*/
	this->number = numberInClass;
	this->birthday = birthdate;

}

COleDateTime Student::GetBirthday() const
{
	return birthday;
}

int Student::GetNumber() const
{
	return number;
}

std::ostream& operator<<(std::ostream& out, const Student& obj)
{
	// <id> <teacher> "<name>" "<room>"
	//
	out << (Person)obj << ' '
		<< obj.number << ' '
		<< '\"' << obj.birthday.GetYear() << ' ' << obj.birthday.GetMonth() << ' ' << obj.birthday.GetDay() << '\"'
		<< std::flush;
	return out;
}

std::istream& operator>>(std::istream& in, Student& obj)
{

	in >> (Person)obj;
	in >> std::ws;

	obj.InitialiseFromStream(in, obj);

	return in;
}

void Student::InitialiseFromStream(std::istream& in, Student& obj)
{
	std::string tmp;
	int year, month, day;

	in >> obj.number;
	in >> std::ws;

	in.ignore(1);
	in >> year >> month >> day;
	in.ignore(1);

	in >> std::ws;

	obj.birthday.SetDate(year, month, day);
}