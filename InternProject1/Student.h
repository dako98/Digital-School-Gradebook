#pragma once


#include "Person.h"
class Student :
    public Person
{
public:
    Student() = default;
    Student(const CString& name, const COleDateTime&birthdate, int numberInClass);

    COleDateTime GetBirthday() const;
    int GetNumber() const;

private:
    COleDateTime birthday;
    int number;
};

