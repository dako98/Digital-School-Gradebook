#include "pch.h"
#include "StudentStore.h"

int StudentStore::instances = 0;
StudentStore* StudentStore::instance = nullptr;

StudentStore::StudentStore()
	:lastID(1)
{
	instances++;
}

StudentStore* StudentStore::GetInstance()
{
	if (!instance)
	{
		instance = new StudentStore;
	}
	return instance;
}

void StudentStore::AddStudent(const CString& name, const COleDateTime& birthday)
{
	Student newStudent(name, birthday, lastID);
	students.insert( { lastID, newStudent } );
	lastID++;
}

void StudentStore::RemoveStudent(int number)
{
	students.erase(number);
}

void StudentStore::EditStudent(int number, const CString& name, const COleDateTime& birthday)
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

StudentStore::~StudentStore()
{
	delete instance;
	instances--;
}
