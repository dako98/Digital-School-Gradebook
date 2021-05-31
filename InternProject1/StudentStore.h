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
	static StudentStore *GetInstance();

	StudentStore(const StudentStore& other) = delete;
	StudentStore(StudentStore&& other) = default;
	StudentStore& operator=(const StudentStore& other) = delete;
	StudentStore& operator=(StudentStore&& other) = default;

	void AddStudent(const CString& name, const COleDateTime& birthday);
	void RemoveStudent(int number);
	void EditStudent(int number, const CString& name, const COleDateTime& birthday);
	Student GetStudent(int number) const;
	std::vector<Student> GetAllStudents() const;

	~StudentStore();
private:

	StudentStore();
	static StudentStore* instance;

	std::unordered_map<int,Student> students;
	int lastID;
	static int instances;

};

