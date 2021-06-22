#pragma once

#include <string>
#include <vector>
#include <fstream>


struct SUBJECT
{
    static const int MAX_NAME_SIZE = 50;

    SUBJECT();

    int nID;
    int nTeacherID;
    char szName[MAX_NAME_SIZE + 1];
    char szRoom[MAX_NAME_SIZE + 1];


    virtual BOOL Validate() const;

    friend std::ostream& operator<<(std::ostream& out, const SUBJECT& obj);
    friend std::istream& operator>>(std::istream& in, SUBJECT& obj);

protected:
    void Read(std::istream& in);
};
