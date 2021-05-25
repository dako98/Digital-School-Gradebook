#pragma once

#include <stdexcept>
#include <string>

class Subject
{
public:
	Subject() = default;
	Subject(const std::string name, int teacherID, const std::string& room);

	int GetID() const;
	int GetTeacher() const;
	std::string GetName() const;
	std::string GetRoom() const;

private:
	int subjectID;
	int teacherID;
	std::string name;
	std::string room;
};

