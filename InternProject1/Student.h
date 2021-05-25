#pragma once


#include "Person.h"
class Student :
    public Person
{
public:
    Student() = default;
    Student(const std::string& name, const tm &birthdate, int numberInClass);

private:
    tm birthday;
    int number;
};

