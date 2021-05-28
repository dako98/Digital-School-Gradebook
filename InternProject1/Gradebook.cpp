#include "pch.h"
#include "Gradebook.h"

Gradebook::Gradebook()
    :studentStore()
    ,gradeStore()
    ,subjectStore()
{
}

bool Gradebook::addStudent(const CString& name, const tm& birthday)
{
    studentStore.AddStudent(name, birthday);
    return false;
}

bool Gradebook::addSubject(const CString& name, int teacherID, const CString& room)
{
	subjectStore.AddSubject( Subject{ name,teacherID, room });
    return false;
}

bool Gradebook::addTeacher(const CString& name)
{
    // TODO
    return false;
}

bool Gradebook::addGrade(int studentNumber, int subjectID, const tm& date, int grade)
{
    gradeStore.AddGrade(studentNumber, subjectID, date, grade);
    return false;
}
