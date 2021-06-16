#include "pch.h"
#include "Subject.h"


Subject::Subject(const CString& name, int teacherID, const CString& room, int subjectID)
{
	if (name != "" && room != "" /*TODO: verify TeacherID*/)
	{
		this->name = name;
		this->teacherID = teacherID;
		this->room = room;
		this->subjectID = subjectID;
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


std::ostream& operator<<(std::ostream& out, const Subject& obj)
{
	// <id> <teacher> "<name>" "<room>"
	//
	out << obj.subjectID << ' '
		<< obj.teacherID << ' '
		<< '\"' << CT2A(obj.name) << '\"' << ' '
		<< '\"' << CT2A(obj.room) << '\"' << '\n'
		<< std::flush;
	return out;
}

std::istream& operator>>(std::istream& in, Subject& obj)
{
	std::string tmp;

	in >> obj.subjectID;
	in.ignore(1);

	in >> obj.teacherID;
	in.ignore(2);

	std::getline(in, tmp, '\"');
	obj.name = CString{ tmp.c_str() };
	in.ignore(2);

	std::getline(in, tmp, '\"');
	obj.room = CString{ tmp.c_str() };
	in.ignore(1);
	
	return in;
}
