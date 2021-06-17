#pragma once

#include <stdexcept>
#include <vector>
#include <unordered_map>

#include "Student.h"
//#include "GradeStore.h"
class StudentStore
{
public:

	void Initialise(const std::string& path);

	static StudentStore *GetInstance();

	StudentStore(const StudentStore& other) = delete;
	StudentStore(StudentStore&& other) = default;
	StudentStore& operator=(const StudentStore& other) = delete;
	StudentStore& operator=(StudentStore&& other) = default;

	void		AddStudent(const CString& name, const COleDateTime& birthday);
	void		RemoveStudent(int number);
	void		EditStudent(int number, const CString& name, const COleDateTime& birthday);
	Student		GetStudent(int number);
	std::vector<Student> GetAllStudents();
	std::vector<Student> GetBirthdayers(const COleDateTime& date);

	~StudentStore();
private:

	StudentStore();
	static StudentStore* instance;

	int lastID;
	static int instances;

	std::string path;

};

