#include "pch.h"
#include "StudentStore.h"

#include <fstream>

int StudentStore::instances = 0;
StudentStore* StudentStore::instance = nullptr;

StudentStore::StudentStore()
	:lastID(1)
{
	instances++;
}

void StudentStore::Initialise(const std::string& path)
{
	std::fstream file(path, std::ios::in | std::ios::out);
	if (!file)
	{
		throw std::exception{"Can't open Students file."};
	}
	this->path = path;
	GetAllStudents();

	file.close();
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
	std::fstream file(path, std::ios::out | std::ios::app);
	Student newStudent(name, birthday, lastID);

	file.seekp(0, file.end);
	file << newStudent;
	file.close();
	lastID++;
}

void StudentStore::RemoveStudent(int number)
{
	std::vector<Student> students = GetAllStudents();

	auto found = students.begin();
	bool isFound = false;

	while (found != students.end())
	{
		if (found->GetNumber() == number)
		{
			isFound = true;
			students.erase(found);
			break;
		}
		found++;
	}
	if (!isFound)
	{
		throw std::out_of_range("Invalid student number.");
	}

	std::fstream file(path, std::ios::out);

	// Write all subjects
	for (const Student& student : students)
	{
		file << student;
	}
	file.close();
}

void StudentStore::EditStudent(int number, const CString& name, const COleDateTime& birthday)
{
	std::vector<Student> students = GetAllStudents();

	auto found = students.begin();

	while (found != students.end())
	{
		if (found->GetNumber() == number)
		{
			*found = Student{ name, birthday, number};
			break;
		}
		found++;
	}
	if (found == students.end())
	{
		throw std::out_of_range("Invalid student number.");
	}

	std::fstream file(path, std::ios::out);

	// Write all subjects
	for (const Student& student : students)
	{
		file << student;
	}
	file.close();
}

Student StudentStore::GetStudent(int number)
{
	std::vector<Student> students = GetAllStudents();

	auto found = students.begin();
	Student* result = nullptr;

	while (found != students.end())
	{
		if (found->GetNumber() == number)
		{
			// TODO: Is this the right way?
			result = &*found;
			break;
		}
		found++;
	}
	if (result == nullptr)
	{
		throw std::out_of_range("Invalid student number.");
	}
	return *result;

}

std::vector<Student> StudentStore::GetAllStudents()
{
	std::vector<Student> result;

	std::fstream file(path, std::ios::in);

	file.seekp(0, file.beg);
	file.seekg(0, file.beg);
	while (file.peek() != EOF)
	{
		Student tmp{ file };
		result.push_back(tmp);
		lastID = (lastID > tmp.GetNumber()) ? lastID : tmp.GetNumber();
	}
	file.close();
	return result;
}

std::vector<Student> StudentStore::GetBirthdayers(const COleDateTime& date)
{
	std::vector<Student> birthdayers;
	std::vector<Student> students = GetAllStudents();

	for (const auto& student : students)
	{
		if (student.GetBirthday().GetDay() == date.GetDay() &&
			student.GetBirthday().GetMonth() == date.GetMonth())
		{
			birthdayers.push_back(student);
		}
	}
	return birthdayers;
}

StudentStore::~StudentStore()
{
	delete instance;
	instances--;
}
