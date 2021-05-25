#pragma once

#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>

#include "Student.h"
#include "StudentStore.h"
#include "Teacher.h"
#include "Subject.h"
#include "SubjectStore.h"
#include "Grade.h"
#include "GradeStore.h"

class Gradebook
{
public:

	Gradebook();

	bool addStudent(const std::string& name, const tm& birthday);
	bool addSubject(const std::string& name, int teacherID, const std::string& room);
	bool addTeacher(const std::string& name);
	bool addGrade(int studentNumber, int subjectID, const tm& date, int grade);

private:

	// StudentNumber -> grades
	StudentStore	studentStore;
	GradeStore		gradeStore;
	SubjectStore	subjectStore;

};

