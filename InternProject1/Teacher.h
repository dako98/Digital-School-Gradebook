#pragma once

#include "Person.h"


class Teacher : public Person
{
public:
	Teacher(const std::string& name, int teacherID);

private:
	int teacherID;

};

