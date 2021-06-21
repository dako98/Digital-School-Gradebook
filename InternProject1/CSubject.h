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


    BOOL Validate() const;

    friend std::ostream& operator<<(std::ostream& out, const SUBJECT& obj);
    friend std::istream& operator>>(std::istream& in, SUBJECT& obj);

protected:
    void Read(std::istream& in);
};





class CSubject
{
public:
    CSubject(const std::string& path);
    virtual ~CSubject();

public:
    BOOL Add(SUBJECT& recStudent);
    BOOL Edit(SUBJECT& recStudent);
    BOOL Delete(const int nStudentID);
    BOOL Load(const int nStudentID, SUBJECT& recStudent);

private:
    BOOL _LoadAll(std::vector<SUBJECT>& allStudents, std::fstream& file);
    BOOL _AddBulk(const std::vector<SUBJECT>& allStudents, std::fstream& file);

private:
    const std::string path;
};
