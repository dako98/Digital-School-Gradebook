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

	bool addStudent(const CString& name, const COleDateTime& birthday);
	bool addSubject(const CString& name, int teacherID, const CString& room);
	bool addTeacher(const CString& name);
	bool addGrade(int studentNumber, int subjectID, const COleDateTime& date, int grade);

private:

	// StudentNumber -> grades
	StudentStore*	studentStore;
	GradeStore		gradeStore;
	SubjectStore	subjectStore;

};

