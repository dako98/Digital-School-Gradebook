#pragma once

#include "Person.h"


class Teacher : public Person
{
public:
	Teacher(const CString& name, int teacherID);

	int GetID() const;

private:
	int teacherID;

};

