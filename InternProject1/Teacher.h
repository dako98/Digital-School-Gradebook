#pragma once

#include "Person.h"


class Teacher : public Person
{
public:
	Teacher(const CString& name, int teacherID);

private:
	int teacherID;

};

