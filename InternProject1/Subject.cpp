#include "pch.h"
#include "Subject.h"

Subject::Subject(const CString name, int teacherID, const CString& room)
{
	if (name != "" && room != "" /*TODO: verify TeacherID*/)
	{
		this->name = name;
		this->teacherID = teacherID;
		this->room = room;
	}
	else
	{
		throw std::invalid_argument("Invalid arguments.");
	}
}

int Subject::GetID() const
{
	return subjectID;
}

int Subject::GetTeacher() const
{
	return teacherID;
}

CString Subject::GetName() const
{
	return name;
}

CString Subject::GetRoom() const
{
	return room;
}
