#include "pch.h"
#include "StudentStore.h"

#include <list>

StudentStore::StudentStore()
	:lastID(0)
{
}

void StudentStore::AddStudent(const std::string& name, const tm& birthday)
{
	Student newStudent(name, birthday, students.size());
	students.insert( { lastID, newStudent } );
	lastID++;
}

void StudentStore::RemoveStudent(int number)
{
	students.erase(number);
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
