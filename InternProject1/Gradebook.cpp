#include "pch.h"
#include "Gradebook.h"

bool Gradebook::addStudent(const std::string& name, const tm& birthday)
{
    studentStore.AddStudent(name, birthday);
    return false;
}

bool Gradebook::addSubject(const std::string& name, int teacherID, const std::string& room)
{
	subjectStore.AddSubject({ name,teacherID, room });
    return false;
}

bool Gradebook::addGrade(int studentNumber, int subjectID, const tm& date, int grade)
{
    gradeStore.AddGrade(studentNumber, subjectID, date, grade);
    return false;
}
