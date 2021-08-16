#pragma once

#include <string>
#include <vector>
#include <fstream>


struct SUBJECT
{
    static const int MAX_NAME_SIZE = 20;

    SUBJECT();

    int nID;
    int nTeacherID;
    wchar_t szName[MAX_NAME_SIZE + 1];
    wchar_t szRoom[MAX_NAME_SIZE + 1];

    BOOL Validate() const;

protected:
    void Read(std::istream& in);
};
