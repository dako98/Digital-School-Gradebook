#pragma once

#include "afxdb.h"
#include <unordered_map>

#include "CStudent.h"
#include "CTeacher.h"
#include "CGrade.h"
#include "CSubject.h"
#include "CClass.h"
#include "CSchedule.h"

class StudentSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;


    int numberInClass;
    int* m_rgNumberInClass;
    long* m_rgNumberInClassLengths;


    CString firstName;
    LPSTR m_rgFirstName;
    long* m_rgFirstNameLengths;


    CString lastName;
    LPSTR m_rgLastName;
    long* m_rgLastNameLengths;


    TIMESTAMP_STRUCT birthday;
    TIMESTAMP_STRUCT* m_rgBirthday;
    long* m_rgBirthdayLengths;


    int classID;
    int* m_rgClassID;
    long* m_rgClassIDLengths;


    StudentSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;

};
/*
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
*/
class TeacherSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    CString firstName;
    LPSTR m_rgFirstName;
    long* m_rgFirstNameLengths;

    CString lastName;
    LPSTR m_rgLastName;
    long* m_rgLastNameLengths;

    TeacherSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
/*
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
*/
class GradeSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    int studentID;
    int* m_rgStudentID;
    long* m_rgStudentIDLengths;

    int subjectID;
    int* m_rgSubjectID;
    long* m_rgSubjectIDLengths;

    int value;
    int* m_rgValue;
    long* m_rgValueLengths;

    TIMESTAMP_STRUCT date;
    TIMESTAMP_STRUCT* m_rgDate;
    long* m_rgDateLengths;

    GradeSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
/*class GradeSetWrapper
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
*/
class SubjectSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    CString name;
    LPSTR m_rgName;
    long* m_rgNameLengths;

    int teacherID;
    int* m_rgTeacherID;
    long* m_rgTeacherIDLengths;

    CString roomName;
    LPSTR m_rgRoomName;
    long* m_rgRoomNameLengths;

    SubjectSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
/*
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
*/
class ClassesSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    CString name;
    LPSTR m_rgName;
    long* m_rgNameLengths;

    int teacherID;
    int* m_rgTeacherID;
    long* m_rgTeacherIDLengths;

    ClassesSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
/*
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
*/

class IDtoNameSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    CString name;
    LPSTR m_rgName;
    long* m_rgNameLengths;

    IDtoNameSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};

BOOL IDtoNameMapper(
    CDatabase* database,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const std::vector<int>& id,
    std::unordered_map<int, CString>& name);

BOOL IDtoNameMapper(CDatabase* db,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const int& id,
    CString& name);

BOOL    ValidateUniqueStudentNumber(const STUDENT& recStudent, CDatabase* db);
DBTIME  CStringToDBTIME(const CString& time);
CString DBTIMEToCString(const DBTIME& time);


template<class T>
class ObjectInterface
{
public:
    virtual ~ObjectInterface() {}

public:
    virtual BOOL Add        (T& input)                  = 0;
    virtual BOOL Edit       (const T& input)            = 0;
    virtual BOOL Delete     (const int id)              = 0;
    virtual BOOL Load       (const int ID, T& result)   = 0;
     
    virtual BOOL LastID     (int& id) const             = 0;
    virtual BOOL LoadAll    (std::vector<T>& out)       = 0;
};

template<class T>
class DatabaseInterface : public ObjectInterface<T>
{
public:
    DatabaseInterface(CDatabase* db)
        :db(db) {}
    virtual ~DatabaseInterface() {}

    BOOL LastID(int& id) const override;

protected:
    CDatabase* db;
};

class StudentDatabaseInterface : public DatabaseInterface<STUDENT>
{
public:
    StudentDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~StudentDatabaseInterface();

public:
	virtual BOOL Add        (STUDENT& recStudent)                       override; 
	virtual BOOL Edit       (const STUDENT& recStudent)                 override;
	virtual BOOL Delete     (const int nID)                             override;
	virtual BOOL Load       (const int nStudentID, STUDENT& recStudent) override;

	virtual BOOL LoadAll    (std::vector<STUDENT>& out)                 override;

private:
    StudentSet recordSet;
    const CString table;
};

class TeacherDatabaseInterface : public DatabaseInterface<TEACHER>
{
public:
    TeacherDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~TeacherDatabaseInterface();

public:
    virtual BOOL Add(TEACHER& recTeacher)                               override;
    virtual BOOL Edit(const TEACHER& recTeacher)                        override;
    virtual BOOL Delete(const int nID)                                  override;
    virtual BOOL Load(const int nTeacherID, TEACHER& recTeacher)        override;

    virtual BOOL LoadAll(std::vector<TEACHER>& out)                     override;

private:
    TeacherSet recordSet;
    const CString table;
};

class SubjectDatabaseInterface : public DatabaseInterface<SUBJECT>
{
public:
    SubjectDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~SubjectDatabaseInterface();

public:
    virtual BOOL Add(SUBJECT& recTeacher)                               override;
    virtual BOOL Edit(const SUBJECT& recTeacher)                        override;
    virtual BOOL Delete(const int nID)                                  override;
    virtual BOOL Load(const int nTeacherID, SUBJECT& recTeacher)        override;

    virtual BOOL LoadAll(std::vector<SUBJECT>& out)                     override;

private:
    SubjectSet recordSet;
    const CString table;
};

class GradeDatabaseInterface : public DatabaseInterface<GRADE>
{
public:
    GradeDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~GradeDatabaseInterface();

public:
    virtual BOOL Add(GRADE& recTeacher)                                 override;
    virtual BOOL Edit(const GRADE& recTeacher)                          override;
    virtual BOOL Delete(const int nID)                                  override;
    virtual BOOL Load(const int nTeacherID, GRADE& recTeacher)          override;

    virtual BOOL LoadAll(std::vector<GRADE>& out)                       override;

private:
    GradeSet recordSet;
    const CString table;
};

class ClassesDatabaseInterface : public DatabaseInterface<CClass>
{
public:
    ClassesDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~ClassesDatabaseInterface();

public:
    virtual BOOL Add(CClass& recTeacher)                                override;
    virtual BOOL Edit(const CClass& recTeacher)                         override;
    virtual BOOL Delete(const int nID)                                  override;
    virtual BOOL Load(const int nTeacherID, CClass& recTeacher)         override;

    virtual BOOL LoadAll(std::vector<CClass>& out)                      override;

private:
    ClassesSet recordSet;
    const CString table;
};

class ScheduleDatabaseInterface : public DatabaseInterface<CSchedule>
{
public:
    ScheduleDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~ScheduleDatabaseInterface();

    virtual BOOL Edit(const CSchedule& recTeacher)                      override;
    virtual BOOL Load(const int classID, CSchedule& recTeacher)         override;

private:
    virtual BOOL Add(CSchedule& recTeacher)                             override { return FALSE; }
    virtual BOOL Delete(const int nID)                                  override { return FALSE; }
    virtual BOOL LoadAll(std::vector<CSchedule>& out)                   override { return FALSE; }

    ScheduleClassSet recordSet;
    const CString table;
};

class ScheduledClassDatabaseInterface : public DatabaseInterface<ScheduleClass>
{
public:
    ScheduledClassDatabaseInterface(const std::wstring& tableName, CDatabase* db);
    virtual ~ScheduledClassDatabaseInterface();

    virtual BOOL Edit(const ScheduleClass& recTeacher)                  override;
    virtual BOOL Load(const int nID, ScheduleClass& recTeacher)         override;
    virtual BOOL Add(ScheduleClass& recTeacher)                         override;
    virtual BOOL Delete(const int nID)                                  override;

private:
    virtual BOOL LoadAll(std::vector<ScheduleClass>& out)               override { return FALSE; }

    ScheduleClassSet recordSet;
    const CString table;
};
