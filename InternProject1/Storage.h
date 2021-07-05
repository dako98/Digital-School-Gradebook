#pragma once

#include "pch.h"

#include <fstream>
#include <vector>

#include "CStudent.h"
#include "CTeacher.h"
#include "CGrade.h"
#include "CSubject.h"

/**
* Requires:
* - operator<< 
* - operator>>
* - Validate()
* - default ctor
*/
template<class T>
class Storage
{
public:
    Storage(const std::string& path);
    virtual ~Storage();

public:
    BOOL Add(T& recStudent);
    BOOL Edit(T& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, T& recStudent);

	BOOL NextID(int& id) const;
	BOOL LoadAll(std::vector<T>& out);

private:
    BOOL _LoadAll(std::vector<T>& allStudents, std::fstream& file);
    BOOL _AddBulk(const std::vector<T>& allStudents, std::fstream& file);

private:
    const std::string path;
};


#include "afxdb.h"
#include "DBConnector.h"

template<>
class Storage<STUDENT>
{
public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
    {
        CDatabase db;

        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


    //FIXME: Rework for use with database.

    BOOL Add(STUDENT& recStudent)
    {
        BOOL isGood = TRUE;

        if (isGood = recStudent.Validate())
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("INSERT INTO [Students]([NumberInClass],[FirstName],[LastName],[Birthday]) VALUES (%d,'%s','%s','%d-%d-%d')"),
                recStudent.nID, 
                CString{ recStudent.szFirstName },
                CString{ recStudent.szLastName },
                recStudent.dtBirthDate.year, recStudent.dtBirthDate.month, recStudent.dtBirthDate.day);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Edit(STUDENT& recStudent)
    {
        BOOL isGood = TRUE;

        isGood = recStudent.Validate();

        if (isGood)
        {
            //FIXME: fix bad ID handling.
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("UPDATE [Students] SET [NumberInClass] = %d, [FirstName] = '%s',[LastName] = '%s',[Birthday] = '%d-%d-%d' WHERE [ID] = %d"),
                recStudent.nID,
                CString{ recStudent.szFirstName },
                CString{ recStudent.szLastName },
                recStudent.dtBirthDate.year, recStudent.dtBirthDate.month, recStudent.dtBirthDate.day, 
                recStudent.nID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Delete(const int nStudentID)
    {
        BOOL isGood = TRUE;

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("DELETE [Students] WHERE [ID] = %d"),nStudentID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }

        return isGood;
    }
    BOOL Load(const int nStudentID, STUDENT& recStudent)
    {
        BOOL isGood = TRUE;
        STUDENT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        StudentSet sSet(&db);

        StudentSetWrapper st(&sSet);

        isGood = st.Load(nStudentID, recStudent);
        return isGood;
    }

    BOOL NextID(int& id) const
    {
        BOOL isGood = TRUE;
        STUDENT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        StudentSet sSet(&db);

        StudentSetWrapper st(&sSet);

        isGood = st.NextID(id);
        return isGood;
    }
    BOOL LoadAll(std::vector<STUDENT>& out)
    {
        BOOL isOK = FALSE;

        std::fstream file;

        isOK = _LoadAll(out, file);

        return isOK;
    }

private:
    BOOL _LoadAll(std::vector<STUDENT>& allStudents, std::fstream& file)
    {
        //FIXME: Copy code here.
        BOOL isGood = TRUE;
        STUDENT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        StudentSet sSet(&db);

        StudentSetWrapper st(&sSet);

        isGood = st.LoadAll(allStudents);
        return isGood;
    }
    BOOL _AddBulk(const std::vector<STUDENT>& allStudents, std::fstream& file)
    {
        BOOL isGood = TRUE;

        for (const STUDENT& student : allStudents)
        {
            if (isGood = student.Validate())
            {

                file << student << '\n';

                isGood = file.good();
            }
        }

        return isGood;
    }

    const CString connectionString;
};


template<>
class Storage<TEACHER>
{
public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
    {
        CDatabase db;

        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


    //FIXME: Rework for use with database.

    BOOL Add(TEACHER& recStudent)
    {
        BOOL isGood = TRUE;

        if (isGood = recStudent.Validate())
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("INSERT INTO [Teachers]([FirstName],[LastName]) VALUES ('%s','%s')"),
                CString{ recStudent.szFirstName },
                CString{ recStudent.szLastName });
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Edit(TEACHER& recStudent)
    {
        BOOL isGood = TRUE;

        isGood = recStudent.Validate();

        if (isGood)
        {
            //FIXME: fix bad ID handling.
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("UPDATE [Teachers] SET [FirstName] = '%s',[LastName] = '%s' WHERE [ID] = %d"),
                CString{ recStudent.szFirstName },
                CString{ recStudent.szLastName },
                recStudent.nID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Delete(const int nStudentID)
    {
        BOOL isGood = TRUE;

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("DELETE [Teachers] WHERE [ID] = %d"), nStudentID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }

        return isGood;
    }
    BOOL Load(const int nStudentID, TEACHER& recStudent)
    {
        BOOL isGood = TRUE;
        TEACHER tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        TeacherSet sSet(&db);

        TeacherSetWrapper st(&sSet);

        isGood = st.Load(nStudentID, recStudent);
        return isGood;
    }

    BOOL NextID(int& id) const
    {
        BOOL isGood = TRUE;
        TEACHER tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        TeacherSet sSet(&db);

        TeacherSetWrapper st(&sSet);

        isGood = st.NextID(id);
        return isGood;
    }
    BOOL LoadAll(std::vector<TEACHER>& out)
    {
        BOOL isOK = FALSE;

        std::fstream file;

        isOK = _LoadAll(out, file);

        return isOK;
    }

private:
    BOOL _LoadAll(std::vector<TEACHER>& allStudents, std::fstream& file)
    {
        //FIXME: Copy code here.
        BOOL isGood = TRUE;
        TEACHER tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        TeacherSet sSet(&db);

        TeacherSetWrapper st(&sSet);

        isGood = st.LoadAll(allStudents);
        return isGood;
    }
    BOOL _AddBulk(const std::vector<TEACHER>& allStudents, std::fstream& file)
    {
        BOOL isGood = TRUE;

        for (const TEACHER& student : allStudents)
        {
            if (isGood = student.Validate())
            {

                file << student << '\n';

                isGood = file.good();
            }
        }

        return isGood;
    }

    const CString connectionString;
};


template<>
class Storage<GRADE>
{
public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
    {
        CDatabase db;

        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


    //FIXME: Rework for use with database.

    BOOL Add(GRADE& recStudent)
    {
        BOOL isGood = TRUE;

        if (isGood = recStudent.Validate())
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("INSERT INTO [Grades]([StudentID],[SubjectID], [Date],[Value] ) VALUES ('%d','%d', '%d-%d-%d %d:%d:%d',%d)"),
                recStudent.nStudentID,
                recStudent.nSubjectID,
                recStudent.dtDate.year,
                recStudent.dtDate.month,
                recStudent.dtDate.day,
                recStudent.dtDate.hour,
                recStudent.dtDate.minute,
                recStudent.dtDate.second,
                recStudent.value);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Edit(GRADE& recStudent)
    {
        BOOL isGood = TRUE;

        isGood = recStudent.Validate();

        if (isGood)
        {
            //FIXME: fix bad ID handling.
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("UPDATE [Grades] SET [StudentID] = '%d',[SubjectID] = '%d', [Date] = '%d-%d-%d %d:%d:%d', [Value] = %d WHERE [ID] = %d"),
                recStudent.nStudentID,
                recStudent.nSubjectID,
                recStudent.dtDate.year,
                recStudent.dtDate.month,
                recStudent.dtDate.day,
                recStudent.dtDate.hour,
                recStudent.dtDate.minute,
                recStudent.dtDate.second,
                recStudent.value,
                recStudent.nID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Delete(const int nStudentID)
    {
        BOOL isGood = TRUE;

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("DELETE [Grades] WHERE [ID] = %d"), nStudentID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }

        return isGood;
    }
    BOOL Load(const int nStudentID, GRADE& recStudent)
    {
        BOOL isGood = TRUE;
        GRADE tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        GradeSet sSet(&db);

        GradeSetWrapper st(&sSet);

        isGood = st.Load(nStudentID, recStudent);
        return isGood;
    }

    BOOL NextID(int& id) const
    {
        BOOL isGood = TRUE;
        GRADE tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        GradeSet sSet(&db);

        GradeSetWrapper st(&sSet);

        isGood = st.NextID(id);
        return isGood;
    }
    BOOL LoadAll(std::vector<GRADE>& out)
    {
        BOOL isOK = FALSE;

        std::fstream file;

        isOK = _LoadAll(out, file);

        return isOK;
    }

private:
    BOOL _LoadAll(std::vector<GRADE>& allStudents, std::fstream& file)
    {
        //FIXME: Copy code here.
        BOOL isGood = TRUE;
        GRADE tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        GradeSet sSet(&db);

        GradeSetWrapper st(&sSet);

        isGood = st.LoadAll(allStudents);
        return isGood;
    }
    BOOL _AddBulk(const std::vector<GRADE>& allStudents, std::fstream& file)
    {
        BOOL isGood = TRUE;

        for (const GRADE& student : allStudents)
        {
            if (isGood = student.Validate())
            {

                file << student << '\n';

                isGood = file.good();
            }
        }

        return isGood;
    }

    const CString connectionString;
};


template<>
class Storage<SUBJECT>
{
public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
    {
        CDatabase db;

        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


    //FIXME: Rework for use with database.

    BOOL Add(SUBJECT& recStudent)
    {
        BOOL isGood = TRUE;

        if (isGood = recStudent.Validate())
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("INSERT INTO [Subjects]([Name], [TeacherID], [RoomName] ) VALUES ('%s','%d', '%s')"),
                CString{ recStudent.szName },
                recStudent.nTeacherID,
                CString{ recStudent.szRoom });
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Edit(SUBJECT& recStudent)
    {
        BOOL isGood = TRUE;

        isGood = recStudent.Validate();

        if (isGood)
        {
            //FIXME: fix bad ID handling.
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("UPDATE [Subjects] SET [Name] = '%s',[TeacherID] = %d, [RoomName] = '%s' WHERE [ID] = %d"),
                CString{ recStudent.szName },
                recStudent.nTeacherID,
                CString{ recStudent.szRoom },
                recStudent.nID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Delete(const int nStudentID)
    {
        BOOL isGood = TRUE;

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;
            sSQL.Format(_T("DELETE [Subjects] WHERE [ID] = %d"), nStudentID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }

        return isGood;
    }
    BOOL Load(const int nStudentID, SUBJECT& recStudent)
    {
        BOOL isGood = TRUE;
        SUBJECT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        SubjectSet sSet(&db);

        SubjectSetWrapper st(&sSet);

        isGood = st.Load(nStudentID, recStudent);
        return isGood;
    }

    BOOL NextID(int& id) const
    {
        BOOL isGood = TRUE;
        SUBJECT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        SubjectSet sSet(&db);

        SubjectSetWrapper st(&sSet);

        isGood = st.NextID(id);
        return isGood;
    }
    BOOL LoadAll(std::vector<SUBJECT>& out)
    {
        BOOL isOK = FALSE;

        std::fstream file;

        isOK = _LoadAll(out, file);

        return isOK;
    }

private:
    BOOL _LoadAll(std::vector<SUBJECT>& allStudents, std::fstream& file)
    {
        //FIXME: Copy code here.
        BOOL isGood = TRUE;
        SUBJECT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        SubjectSet sSet(&db);

        SubjectSetWrapper st(&sSet);

        isGood = st.LoadAll(allStudents);
        return isGood;
    }
    BOOL _AddBulk(const std::vector<SUBJECT>& allStudents, std::fstream& file)
    {
        BOOL isGood = TRUE;

        for (const SUBJECT& student : allStudents)
        {
            if (isGood = student.Validate())
            {

                file << student << '\n';

                isGood = file.good();
            }
        }

        return isGood;
    }

    const CString connectionString;
};





#include "Storage.c++"