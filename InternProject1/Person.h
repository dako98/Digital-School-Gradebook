#pragma once

#include <stdexcept>

#include <string>
#include <iostream>

class Person
{
public:
	Person(std::iostream& in);
	Person(const CString& name);

	CString getName() const;

	friend std::ostream& operator<<(std::ostream& out, const Person& obj);
	friend std::istream& operator>>(std::istream& in, Person& obj);

private:

	void InitialiseFromStream(std::istream& in, Person& obj);

	CString name;
};

