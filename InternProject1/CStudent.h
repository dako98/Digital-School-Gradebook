#pragma once

#include <string>
#include <vector>

const int MAX_NAME_SIZE = 50;

struct STUDENT
{
    char szFirstName[MAX_NAME_SIZE + 1];
    char szLastName[MAX_NAME_SIZE + 1];
    int nID;
    DBTIMESTAMP dtBirthDate;

    BOOL Validate() const;
};

class CStudent
{
public:
    CStudent(const std::string& path);
    virtual ~CStudent();

public:
    BOOL Add(STUDENT& recStudent);
    BOOL Edit(STUDENT& recStudent);
    BOOL Delete(const int nStudentID);
    BOOL Load(const int nStudentID, STUDENT& recStudent);

private:
    BOOL _LoadAll(std::vector<STUDENT>& allStudents, std::fstream& file);
    BOOL _AddBulk(const std::vector<STUDENT>& allStudents, std::fstream& file);

private:
    const std::string path;
};