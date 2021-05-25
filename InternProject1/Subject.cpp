#include "pch.h"
#include "Subject.h"

Subject::Subject(const std::string name, int teacherID, const std::string& room)
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

std::string Subject::GetName() const
{
	return name;
}

std::string Subject::GetRoom() const
{
	return room;
}
