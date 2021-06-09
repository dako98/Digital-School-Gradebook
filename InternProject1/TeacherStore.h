#pragma once

#include <stdexcept>
#include <vector>
#include <unordered_map>

#include "Teacher.h"

class TeacherStore
{
public:
	static TeacherStore* GetInstance();

	TeacherStore(const TeacherStore& other) = delete;
	TeacherStore(TeacherStore&& other) = default;
	TeacherStore& operator=(const TeacherStore& other) = delete;
	TeacherStore& operator=(TeacherStore&& other) = default;

	void AddTeacher(const CString & name);
	void RemoveTeacher(int number);
	void EditTeacher(int number, const CString & name);
	Teacher GetTeacher(int number) const;
	std::vector<Teacher> GetAllTeachers() const;

	~TeacherStore();
private:

	TeacherStore();
	static TeacherStore* instance;

	std::unordered_map<int, Teacher> teachers;
	int lastID;

};

