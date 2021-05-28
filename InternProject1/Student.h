#pragma once


#include "Person.h"
class Student :
    public Person
{
public:
    Student() = default;
    Student(const CString& name, const tm &birthdate, int numberInClass);

private:
    tm birthday;
    int number;
};

