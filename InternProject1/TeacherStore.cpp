#include "pch.h"
#include "TeacherStore.h"

TeacherStore* TeacherStore::instance = nullptr;

TeacherStore::TeacherStore()
	:lastID(1)
{
}

TeacherStore* TeacherStore::GetInstance()
{
	if (!instance)
	{
		instance = new TeacherStore;
	}
	return instance;
}

void TeacherStore::AddTeacher(const CString& name)
{
	Teacher newTeacher(name, lastID);
	teachers.insert({ lastID, newTeacher });
	lastID++;
}

void TeacherStore::RemoveTeacher(int number)
{
	teachers.erase(number);
}

void TeacherStore::EditTeacher(int number, const CString& name)
{
	auto found = teachers.find(number);

	if (found != teachers.end())
	{
		found->second = Teacher(name, number);
	}
	else
	{
		throw std::out_of_range("Invalid Teacher number.");
	}
}

Teacher TeacherStore::GetTeacher(int number) const
{
	auto found = teachers.find(number);

	if (found != teachers.end())
	{
		return found->second;
	}
	else
	{
		throw std::out_of_range("Invalid Teacher number.");
	}
}

std::vector<Teacher> TeacherStore::GetAllTeachers() const
{
	std::vector<Teacher> allTeachers;
	for each (auto teacher in teachers)
	{
		allTeachers.push_back(teacher.second);
	}
	return allTeachers;
}

TeacherStore::~TeacherStore()
{
	delete instance;
}