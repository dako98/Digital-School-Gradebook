#pragma once

#include <stdexcept>

#include <string>

class Person
{
public:
	Person(const CString& name);

	CString getName() const;

private:
	CString name;
};

