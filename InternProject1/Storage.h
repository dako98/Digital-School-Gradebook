#pragma once

#include "pch.h"

#include <fstream>
#include <vector>


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
#include "Storage.c++"

#include "afxdb.h"
#include "DBConnector.h"
#include "CStudent.h"
#include "CTeacher.h"
#include "CGrade.h"
#include "CSubject.h"
#include "CSchedule.h"


template<>
class Storage<STUDENT>
{
public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
//        , db(&databaseConnection)
    {
        ASSERT(FALSE);
    }

    //Storage(CDatabase& db)
    //    :db(&db)
    //{

    //}

    virtual ~Storage()
    {}


    BOOL Add(STUDENT& recStudent)
    {
        BOOL isGood = TRUE;

        if (isGood = recStudent.Validate())
        {
            StudentSet ss(db);

            ss.Open(CRecordset::dynaset, _T("Student"), CRecordset::appendOnly);

            ss.AddNew();

            ss.numberInClass    = recStudent.numberInClass;
            ss.firstName        = CString{ recStudent.szFirstName };
            ss.lastName         = CString{ recStudent.szLastName };
            ss.birthday.year    = recStudent.dtBirthDate.year;
            ss.birthday.month   = recStudent.dtBirthDate.month;
            ss.birthday.day     = recStudent.dtBirthDate.day;
            ss.classID          = recStudent.classID;

            ss.Update();
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
            sSQL.Format(_T("UPDATE [Students] SET [NumberInClass] = %d, [FirstName] = '%s',[LastName] = '%s',[Birthday] = '%d-%d-%d', [ClassID] = %d WHERE [ID] = %d"),
                recStudent.numberInClass,
                CString{ recStudent.szFirstName },
                CString{ recStudent.szLastName },
                recStudent.dtBirthDate.year, recStudent.dtBirthDate.month, recStudent.dtBirthDate.day, 
                recStudent.classID,
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
        db.Close();

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
        db.Close();

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
        BOOL isGood = TRUE;
        STUDENT tmp;

        CDatabase db;
        db.OpenEx(connectionString, /*CDatabase::openReadOnly | */CDatabase::noOdbcDialog);
        StudentSet sSet(&db);

        StudentSetWrapper st(&sSet);
        
        isGood = st.LoadAll(allStudents);

        db.Close();
        
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

    CDatabase* db;
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
        ASSERT(FALSE);

        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


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
        db.Close();

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
        db.Close();

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
        BOOL isGood = TRUE;
        TEACHER tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        TeacherSet sSet(&db);

        TeacherSetWrapper st(&sSet);

        isGood = st.LoadAll(allStudents);
        db.Close();

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
        ASSERT(FALSE);
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


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
        db.Close();

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
        db.Close();

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
        BOOL isGood = TRUE;
        GRADE tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        GradeSet sSet(&db);

        GradeSetWrapper st(&sSet);

        isGood = st.LoadAll(allStudents);
        db.Close();

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
        ASSERT(FALSE);
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}


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
        db.Close();

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
        db.Close();

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
        db.Close();

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

template<>
class Storage<CSchedule>
{
    // FIXME: This should be for each subject in the day, not for the whole week.
    // CSchedule should only be a thing at the client in order to organise the data.

public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
    {
        CDatabase db;
        ASSERT(FALSE);
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}

    BOOL Add(CSchedule& recStudent)
    {
        BOOL isGood = TRUE;
/*
        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;

            int size = recStudent.days.size();
            for (int dayOfWeek = 0; dayOfWeek < size; dayOfWeek++)
            {
                for (auto _class : recStudent.days[dayOfWeek].classes)
                {
                    sSQL.Format(_T("INSERT INTO [Schedule]([Begin],[Duration],[ClassID],[DayOfWeek]) VALUES ('%d:%d:00','%d:%d:00', %d, %d)"),
                        _class.begin.hour,
                        _class.begin.minute,
                        _class.duration.hour,
                        _class.duration.minute,
                        _class.nSubjectID,
                        dayOfWeek);
                }
            }
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
        */
        ASSERT(FALSE && "Can not create a whole schedule. You can only add scheduled classes.");
        return FALSE;
    }
    BOOL Edit(CSchedule& recStudent)
    {
        BOOL isGood = TRUE;

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;

            int size = recStudent.days.size();
            for (int dayOfWeek = 0; dayOfWeek < size; dayOfWeek++)
            {
                for (const auto& _class : recStudent.days[dayOfWeek].classes)
                {

                    sSQL.Format(_T("UPDATE [Schedule] SET [Begin] = '%d:%d:00', [Duration] = '%d:%d:00', [SubjectID] = %d, [DayOfWeek] = %d WHERE [ID] = %d"),
                        _class.begin.hour,
                        _class.begin.minute,
                        _class.duration.hour,
                        _class.duration.minute,
                        _class.nSubjectID,
                        dayOfWeek,
                        _class.nID);

                    db.ExecuteSQL(sSQL);
                    db.Close();
                }
            }
        }
        return isGood;
    }
    BOOL Delete(const int nStudentID)
    {
        BOOL isGood = TRUE;
/*
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
        */
        ASSERT(FALSE && "Can not delete a whole schedule. You can only delete scheduled classes.");
        return FALSE;
    }
    BOOL Load(const int classID, CSchedule& recStudent)
    {
        BOOL isGood = TRUE;
        CSchedule result;
        ScheduleClass sc;
        result.classID = classID;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        ScheduleClassSet sSet(&db);


        CString sSQL;
        sSQL.Format(_T("SELECT * FROM [Schedule] WHERE [ClassID] = %d"), classID);
        sSet.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);


        while (!sSet.IsEOF())
        {
            int rowsFetched = sSet.GetRowsFetched();

            for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
            {
                /*
                sc.nID              =   *(sSet.m_rgID + nPosInRowset);
                sc.nSubjectID       =   *(sSet.m_rgSubjectID + nPosInRowset);
                sc.begin.hour       =   (sSet.m_rgBeginTime + nPosInRowset)->hour;
                sc.begin.minute     =   (sSet.m_rgBeginTime + nPosInRowset)->minute;
                sc.begin.second     =   (sSet.m_rgBeginTime + nPosInRowset)->second;
                sc.duration.hour    =   (sSet.m_rgDuration + nPosInRowset)->hour;
                sc.duration.minute  =   (sSet.m_rgDuration + nPosInRowset)->minute;
                sc.duration.second  =   (sSet.m_rgDuration + nPosInRowset)->second;
                */
                ASSERT(FALSE);
                int dayOfWeek = *(sSet.m_rgDayOfWeek + nPosInRowset);

                ASSERT(dayOfWeek < 7);

//                result.days[dayOfWeek].classes.push_back(sc);
//                result.days[dayOfWeek].classes.insert(sc);
                  result.days[dayOfWeek].classes.push_sorted(sc);
            }
            sSet.MoveNext();
        }

        sSet.Close();
        db.Close();

        recStudent = result;

        return isGood;
    }
    
    BOOL NextID(int& id) const
    {
        BOOL isGood = TRUE;
/*
        SUBJECT tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        SubjectSet sSet(&db);

        SubjectSetWrapper st(&sSet);

        isGood = st.NextID(id);
        db.Close();

        return isGood;
        */
        ASSERT(FALSE && "Can not get an ID for a whole schedule. You can only get ID for scheduled classes.");
        return FALSE;
    }
    BOOL LoadAll(std::vector<CSchedule>& out)
    {
        BOOL isOK = FALSE;
        /*
        std::fstream file;

        isOK = _LoadAll(out, file);

        return isOK;
        */
        ASSERT(FALSE && "Can not load all schedule. You can only load one schedule.");
        return FALSE;
    }

private:
    const CString connectionString;
};

template<>
class Storage<CClass>
{
public:
    Storage(const std::string& path)
        :connectionString(path.c_str())
    {
        CDatabase db;
        ASSERT(FALSE);
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        db.Close();
    }
    virtual ~Storage()
    {}

    BOOL Add(CClass& recStudent)
    {
        BOOL isGood = TRUE;

        isGood = recStudent.Validate();

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;

            sSQL.Format(_T("INSERT INTO [Classes]([Name],[ClassTeacherID]) VALUES ('%s',%d)"),
                recStudent.name,
                recStudent.teacherID);

            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Edit(CClass& recStudent)
    {
        BOOL isGood = TRUE;

        isGood = recStudent.Validate();

        if (isGood)
        {
            CDatabase db;
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
            CString sSQL;

            sSQL.Format(_T("UPDATE [Classes] SET [Name] = '%s', [ClassTeacherID] = %d WHERE [ID] = %d"),
                recStudent.name,
                recStudent.teacherID,
                recStudent.ID);

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
            sSQL.Format(_T("DELETE [Classes] WHERE [ID] = %d"), nStudentID);
            db.ExecuteSQL(sSQL);
            db.Close();
        }
        return isGood;
    }
    BOOL Load(const int classID, CClass& recStudent)
    {
        BOOL isGood = TRUE;
        CClass result;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        ClassesSet cSet(&db);


        CString sSQL;
        sSQL.Format(_T("SELECT * FROM [Classes] WHERE [ID] = %d"), classID);
        cSet.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);

        ASSERT(cSet.GetRowsFetched() == 1);

        result.ID = *(cSet.m_rgID);
        result.name = *(cSet.m_rgName);
        result.teacherID = *(cSet.m_rgTeacherID);


        cSet.Close();
        db.Close();

        recStudent = result;

        return isGood;
    }


    BOOL NextID(int& id) const
    {
        BOOL isGood = TRUE;

        CClass tmp;

        CDatabase db;
        db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        ClassesSet cSet(&db);

        CString sSQL;
        sSQL.Format(_T("SELECT TOP 1 * FROM [Classes] ORDER BY [ID] DESC"));

        try
        {
            cSet.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
        }
        catch (const std::exception&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            CString csComboString;

            tmp.ID = *(cSet.m_rgID);

            id = tmp.ID + 1;
        }

        cSet.Close();


        return isGood;

    }
    BOOL LoadAll(std::vector<CClass>& out)
    {
        BOOL isOK = TRUE;

        CDatabase db;
        try
        {
            db.OpenEx(connectionString, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
        }
        catch (const std::exception&)
        {
            isOK = FALSE;
        }
        if (isOK)
        {
            ClassesSet cSet(&db);
            CClass tmp;

            CString sSQL;
            sSQL.Format(_T("SELECT * FROM [Classes]"));
            try
            {
                cSet.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
            }
            catch (const std::exception&)
            {
                isOK = FALSE;
            }

            if (isOK)
            {
                int rowsFetched = cSet.GetRowsFetched();
                while (!cSet.IsEOF())
                {
                    for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
                    {
                        tmp.ID = *(cSet.m_rgID + nPosInRowset);
                        tmp.name = CString{ cSet.m_rgName + nPosInRowset * 5 };
                        tmp.teacherID = *(cSet.m_rgTeacherID + nPosInRowset);

                        out.push_back(tmp);
                    }
                    cSet.MoveNext();
                }
            }// !Getting fields
            cSet.Close();
            db.Close();
        }
        return isOK;
    }

private:
    const CString connectionString;
};

/*

template<class T>
class TRecordSet : public CRecordset
{
public:
    TRecordSet(const std::string& tableName)
        :tableName(tableName.c_str())
    {
    }
    virtual ~Storage()
    {}


    BOOL Add(T& recStudent)
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
        db.Close();

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
        db.Close();

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


    const CString tableName;
};

*/