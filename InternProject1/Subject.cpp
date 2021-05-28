#include "pch.h"
#include "Subject.h"

Subject::Subject(const CString& name, int teacherID, const CString& room)
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

bool Subject::operator==(const Subject& other) const
{
	return this->teacherID == other.teacherID
		&& this->name == other.name
		&& this->room == other.room;
}

bool Subject::InitialiseID(int ID)
{
	bool changed = false;

	if (!valid)
	{
		subjectID = ID;
		valid = true;
		changed = true;
	}
	return changed;
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
