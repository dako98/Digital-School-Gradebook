#pragma once

#include <stdexcept>

#include <string>

class Person
{
public:
	Person(const std::string& name);

	std::string getName() const;

private:
	std::string name;
};

