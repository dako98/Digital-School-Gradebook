#pragma once

#include <iostream>

#include "Person.h"


class Student :
    public Person
{
public:
    Student(std::iostream& in);
    Student(const CString& name, const COleDateTime&birthdate, int numberInClass);

    COleDateTime GetBirthday() const;
    int GetNumber() const;

    friend std::ostream& operator<<(std::ostream& out, const Student& obj);
    friend std::istream& operator>>(std::istream& in, Student& obj);

private:

    void InitialiseFromStream(std::istream& in, Student& obj);

    COleDateTime birthday;
    int number;
};

