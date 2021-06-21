#pragma once

#include <string>
#include <vector>

#include "CPerson.h"

struct STUDENT : public PERSON
{
//static const int MAX_NAME_SIZE = 50;


    STUDENT();

//    char szFirstName[MAX_NAME_SIZE + 1];
//    char szLastName[MAX_NAME_SIZE + 1];
//    int nID;
    DBTIMESTAMP dtBirthDate;

    virtual BOOL Validate() const override;

    friend std::ostream& operator<<(std::ostream& out, const STUDENT& obj);
    friend std::istream& operator>>(std::istream& in, STUDENT& obj);

protected:
    void Read(std::istream& in);
//    virtual std::ostream& operator<<(std::ostream& out) const;
//    virtual std::istream& operator>>(std::istream& in);
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