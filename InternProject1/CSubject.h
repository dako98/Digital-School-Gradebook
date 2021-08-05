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
    CString szName;
    CString szRoom;

    virtual BOOL Validate() const;

protected:
    void Read(std::istream& in);
};
