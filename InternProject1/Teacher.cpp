#include "pch.h"
#include "Teacher.h"

Teacher::Teacher(const CString& name, int teacherID)
	:Person(name)
	,teacherID(teacherID)
{
}

int Teacher::GetID() const
{
	return teacherID;
}
