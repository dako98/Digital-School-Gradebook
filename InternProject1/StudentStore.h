#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

#include "Student.h"
#include "GradeStore.h"
class StudentStore
{
public:
	StudentStore();

	void AddStudent(const std::string& name, const tm& birthday);
	void RemoveStudent(int number);
	void EditStudent(int number, const std::string& name, const tm& birthday);
	Student GetStudent(int number) const;
	std::vector<Student> GetAllStudents() const;

private:
	std::unordered_map<int,Student> students;
	int lastID;

//	GradeStore* gradeStore;
};

