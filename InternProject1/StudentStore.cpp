#include "pch.h"
#include "StudentStore.h"


StudentStore::StudentStore()
	:lastID(0)
{
}

void StudentStore::AddStudent(const CString& name, const tm& birthday)
{
	Student newStudent(name, birthday, students.size());
	students.insert( { lastID, newStudent } );
	lastID++;
}

void StudentStore::RemoveStudent(int number)
{
	students.erase(number);
}

void StudentStore::EditStudent(int number, const CString& name, const tm& birthday)
{
	auto found = students.find(number);

	if (found != students.end())
	{
		(*found).second = Student(name, birthday, number);
	}
	else
	{
		throw std::out_of_range("Invalid student number.");
	}
}

Student StudentStore::GetStudent(int number) const
{
	auto found = students.find(number);
	
	if (found!=students.end())
	{
		return (*found).second;
	}
	else
	{
		throw std::out_of_range("Invalid student number.");
	}
}

std::vector<Student> StudentStore::GetAllStudents() const
{
	std::vector<Student> allStudents;
	for each (auto student in students)
	{
		allStudents.push_back(student.second);
	}
	return allStudents;
}
