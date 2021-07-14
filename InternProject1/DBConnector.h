#pragma once

#include "afxdb.h"
#include <tuple>
#include <unordered_map>

#include "CStudent.h"
#include "CTeacher.h"
#include "CGrade.h"
#include "CSubject.h"
#include "CClass.h"

class StudentSet : public CRecordset
{
public:

    int* m_rgID;
    long* m_rgIDLengths;

    int* m_rgNumber;
    long* m_rgNumberLengths;

    LPSTR m_rgFirstName;
    long* m_rgFirstNameLengths;

    LPSTR m_rgLastName;
    long* m_rgLastNameLengths;

    TIMESTAMP_STRUCT* m_rgBirthday;
    long* m_rgBirthdayLengths;

    int* m_rgClassID;
    long* m_rgClassIDLengths;


    StudentSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
class StudentSetWrapper
{
public:

    StudentSetWrapper(StudentSet *sSet);

    BOOL Add(STUDENT& recStudent);
    BOOL Edit(STUDENT& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, STUDENT& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<STUDENT>& out);

private:

    StudentSet* blk;

};

class TeacherSet : public CRecordset
{
public:

    int* m_rgID;
    long* m_rgIDLengths;

    LPSTR m_rgFirstName;
    long* m_rgFirstNameLengths;

    LPSTR m_rgLastName;
    long* m_rgLastNameLengths;

    TeacherSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
class TeacherSetWrapper
{
public:

    TeacherSetWrapper(TeacherSet* sSet);

    BOOL Add(STUDENT& recStudent);
    BOOL Edit(STUDENT& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, TEACHER& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<TEACHER>& out);

private:

    TeacherSet* blk;
};

class GradeSet : public CRecordset
{
public:


    int* m_rgID;
    long* m_rgIDLengths;

    int* m_rgStudentID;
    long* m_rgStudentIDLengths;

    int* m_rgSubjectID;
    long* m_rgSubjectIDLengths;

    int* m_rgValue;
    long* m_rgValueLengths;

    TIMESTAMP_STRUCT* m_rgDate;
    long* m_rgDateLengths;

    GradeSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
class GradeSetWrapper
{
public:

    GradeSetWrapper(GradeSet* sSet);

    BOOL Add(STUDENT& recStudent);
    BOOL Edit(STUDENT& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, GRADE& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<GRADE>& out);

private:

    GradeSet* blk;
};

class SubjectSet : public CRecordset
{
public:


    int* m_rgID;
    long* m_rgIDLengths;

    LPSTR m_rgName;
    long* m_rgNameLengths;

    int* m_rgTeacherID;
    long* m_rgTeacherIDLengths;

    LPSTR m_rgRoomName;
    long* m_rgRoomNameLengths;

    SubjectSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
class SubjectSetWrapper
{
public:

    SubjectSetWrapper(SubjectSet* sSet);

    BOOL Add(STUDENT& recStudent);
    BOOL Edit(STUDENT& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, SUBJECT& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<SUBJECT>& out);

private:

    SubjectSet* blk;
};

class ClassesSet : public CRecordset
{
public:

    int* m_rgID;
    long* m_rgIDLengths;

    LPSTR m_rgName;
    long* m_rgNameLengths;

    int* m_rgTeacherID;
    long* m_rgTeacherIDLengths;

    ClassesSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
class ClassesSetWrapper
{
public:

    ClassesSetWrapper(ClassesSet* sSet);

    BOOL Add(CClass& recStudent);
    BOOL Edit(CClass& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, CClass& recStudent);
    
    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<CClass>& out);

private:

    ClassesSet* blk;
};


class IDtoNameSet : public CRecordset
{
public:

    int* m_rgID;
    long* m_rgIDLengths;

    LPSTR m_rgName;
    long* m_rgNameLengths;

    IDtoNameSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};

BOOL IDtoNameMapper(
    const CString& connectionString,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const std::vector<int>& id,
    std::unordered_map<int, CString>& name);