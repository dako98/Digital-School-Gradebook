#include "pch.h"
#include "DBConnector.h"

#include "Utility.h"

StudentSet::StudentSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;

    ID                          = -1;   __COUNTER__;
    m_rgID                      = NULL; 
    m_rgIDLengths               = NULL; 
    
    numberInClass               = -1;   __COUNTER__;
    m_rgNumberInClass           = NULL; 
    m_rgNumberInClassLengths    = NULL; 

    firstName                   = "";   __COUNTER__;
    m_rgFirstName               = NULL; 
    m_rgFirstNameLengths        = NULL; 

    lastName                    = "";   __COUNTER__;
    m_rgLastName                = NULL; 
    m_rgLastNameLengths         = NULL; 

    birthday                    = { 0, }; __COUNTER__;
    m_rgBirthday                = NULL; 
    m_rgBirthdayLengths         = NULL; 

    classID                     = -1;   __COUNTER__;
    m_rgClassID                 = NULL; 
    m_rgClassIDLengths          = NULL; 

    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields                   = count;
}

void StudentSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),               &m_rgID,                &m_rgIDLengths);
    RFX_Int_Bulk    (pFX, _T("[NumberInClass]"),    &m_rgNumberInClass,     &m_rgNumberInClassLengths);
    RFX_Text_Bulk   (pFX, _T("[FirstName]"),        &m_rgFirstName,         &m_rgFirstNameLengths,      20);
    RFX_Text_Bulk   (pFX, _T("[LastName]"),         &m_rgLastName,          &m_rgLastNameLengths,       20);
    RFX_Date_Bulk   (pFX, _T("[Birthday]"),         &m_rgBirthday,          &m_rgBirthdayLengths);
    RFX_Int_Bulk    (pFX, _T("[ClassID]"),          &m_rgClassID,           &m_rgClassIDLengths);

}
void StudentSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),               ID);
    RFX_Int     (pFX, _T("[NumberInClass]"),    numberInClass);
    RFX_Text    (pFX, _T("[FirstName]"),        firstName);
    RFX_Text    (pFX, _T("[LastName]"),         lastName);
    RFX_Date    (pFX, _T("[Birthday]"),         birthday);
    RFX_Int     (pFX, _T("[ClassID]"),          classID);

}


//FIXME: Add number field from database.
StudentSetWrapper::StudentSetWrapper(StudentSet *pDB)
    :blk(&*pDB)
{
    ASSERT(FALSE);
}
BOOL StudentSetWrapper::Load(const int nStudentID, STUDENT& recStudent)
{
    BOOL isOK = TRUE;
    STUDENT tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Students] WHERE [ID] = %d"),nStudentID);

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;
        int rowsFetched = blk->GetRowsFetched();

        tmp.nID = *(blk->m_rgID);

//        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

//        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

        tmp.dtBirthDate.year    =   (blk->m_rgBirthday)->year;
        tmp.dtBirthDate.month   =   (blk->m_rgBirthday)->month;
        tmp.dtBirthDate.day     =   (blk->m_rgBirthday)->day;
        tmp.dtBirthDate.hour    =   (blk->m_rgBirthday)->hour;
        tmp.dtBirthDate.minute  =   (blk->m_rgBirthday)->minute;
        tmp.dtBirthDate.second  =   (blk->m_rgBirthday)->second;

        tmp.classID             =   *(blk->m_rgClassID);
        tmp.numberInClass       =   *(blk->m_rgNumberInClass);

        recStudent = tmp;
    }

    blk->Close();

    return isOK;
}
BOOL StudentSetWrapper::NextID(int& id) const
{
    BOOL isOK = TRUE;
    STUDENT tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT TOP 1 * FROM [Students] ORDER BY [ID] DESC"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL /*, CRecordset::useMultiRowFetch*/);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
//        tmp.nID = *(blk->m_rgID);

//        id = tmp.nID + 1;
        id = 100;
    }

    blk->Close();

    return isOK;
}
BOOL StudentSetWrapper::LoadAll(std::vector<STUDENT>& out)
{
    out.clear();
    BOOL isOK = TRUE;
    STUDENT tmp;

    CString sSQL;
//    sSQL.Format(_T("SELECT * FROM [Students]"));
    sSQL.Format(_T("Students"));

    try
    {
//        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::none/*, CRecordset::useMultiRowFetch*/);
        blk->Open(CRecordset::dynaset, sSQL, CRecordset::none/*, CRecordset::useMultiRowFetch*/);
//        blk->Open
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {

        int rowsFetched = blk->GetRowsFetched();

        for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
        {
            //Check if value is null
/*            if (blk->m_rgFirstName[nPosInRowset] == SQL_NULL_DATA)
                continue;*/
//            blk->m_strFilter = "ID = 1";
            blk->Delete();

            // THIS WORKS!!!

            BOOL canadd = blk->CanAppend();
            
            blk->AddNew();

            blk->numberInClass = 100;

            blk->birthday.day = 1;
            blk->birthday.month = 1;
            blk->birthday.year = 2021;
            blk->birthday.hour = 0;
            blk->birthday.minute = 0;
            blk->birthday.second = 0;
            blk->birthday.fraction = 0;

            blk->classID = 1;
            blk->firstName = "ASD";
            blk->lastName = "DSA";

            blk->Update();

            tmp.nID = *(blk->m_rgID + nPosInRowset);

//            strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName + nPosInRowset * 20);

//            strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName + nPosInRowset * 20);

            tmp.dtBirthDate.year    =   (blk->m_rgBirthday + nPosInRowset)->year;
            tmp.dtBirthDate.month   =   (blk->m_rgBirthday + nPosInRowset)->month;
            tmp.dtBirthDate.day     =   (blk->m_rgBirthday + nPosInRowset)->day;
            tmp.dtBirthDate.hour    =   (blk->m_rgBirthday + nPosInRowset)->hour;
            tmp.dtBirthDate.minute  =   (blk->m_rgBirthday + nPosInRowset)->minute;
            tmp.dtBirthDate.second  =   (blk->m_rgBirthday + nPosInRowset)->second;

            tmp.classID             =   *(blk->m_rgClassID + nPosInRowset);
            tmp.numberInClass       =   *(blk->m_rgNumberInClass + nPosInRowset);

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}


TeacherSet::TeacherSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;

    ID                      = -1; __COUNTER__;
    m_rgID                  = NULL; 
    m_rgIDLengths           = NULL; 

    firstName               = ""; __COUNTER__;
    m_rgFirstName           = NULL; 
    m_rgFirstNameLengths    = NULL; 

    lastName                = ""; __COUNTER__;
    m_rgLastName            = NULL; 
    m_rgLastNameLengths     = NULL; 

    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields               = count;
}
void TeacherSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),           &m_rgID, &m_rgIDLengths);
    RFX_Text_Bulk   (pFX, _T("[FirstName]"),   &m_rgFirstName, &m_rgFirstNameLengths, 20);
    RFX_Text_Bulk   (pFX, _T("[LastName]"),    &m_rgLastName, &m_rgLastNameLengths, 20);
}

void TeacherSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           ID);
    RFX_Text    (pFX, _T("[FirstName]"),    firstName);
    RFX_Text    (pFX, _T("[LastName]"),     lastName);
}

TeacherSetWrapper::TeacherSetWrapper(TeacherSet* pDB)
    :blk(&*pDB)
{
    ASSERT(FALSE);
}
BOOL TeacherSetWrapper::Load(const int nStudentID, TEACHER& recStudent)
{
    BOOL isOK = TRUE;
    TEACHER tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Teachers] WHERE [ID] = %d"), nStudentID);

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

//        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

//        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

        recStudent = tmp;
    }

    blk->Close();

    return isOK;
}
BOOL TeacherSetWrapper::NextID(int& id) const
{
    BOOL isOK = TRUE;
    STUDENT tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT TOP 1 * FROM [Teachers] ORDER BY [ID] DESC"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

//        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

//        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

        id = tmp.nID + 1;
    }

    blk->Close();

    return isOK;
}
BOOL TeacherSetWrapper::LoadAll(std::vector<TEACHER>& out)
{
    out.clear();
    BOOL isOK = TRUE;
    TEACHER tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Teachers]"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
        blk->Open();
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {

        int rowsFetched = blk->GetRowsFetched();

        for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
        {
            //Check if value is null
            if (blk->m_rgFirstName[nPosInRowset] == SQL_NULL_DATA)
                continue;

            CString csComboString;

            tmp.nID = *(blk->m_rgID + nPosInRowset);

//            strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName + nPosInRowset * 20);

//            strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName + nPosInRowset * 20);

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}


GradeSet::GradeSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;

    ID                      = -1;   __COUNTER__;
    m_rgID                  = NULL;
    m_rgIDLengths           = NULL;

    studentID               = -1;   __COUNTER__;
    m_rgStudentID           = NULL;
    m_rgStudentIDLengths    = NULL;

    subjectID               = -1;   __COUNTER__;
    m_rgSubjectID           = NULL;
    m_rgSubjectIDLengths    = NULL;

    value                   = GRADE::INVALID; __COUNTER__;
    m_rgValue               = NULL;
    m_rgValueLengths        = NULL;

    date                    = { 0, }; __COUNTER__;
    m_rgDate                = NULL;
    m_rgDateLengths         = NULL;


    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields               = count;
}

void GradeSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk(pFX, _T("[ID]"),           &m_rgID, &m_rgIDLengths);
    RFX_Int_Bulk(pFX, _T("[StudentID]"),    &m_rgStudentID, &m_rgStudentIDLengths);
    RFX_Int_Bulk(pFX, _T("[SubjectID]"),    &m_rgSubjectID, &m_rgSubjectIDLengths);
    RFX_Date_Bulk(pFX, _T("[Date]"),        &m_rgDate, &m_rgDateLengths);
    RFX_Int_Bulk(pFX, _T("[Value]"),        &m_rgValue, &m_rgValueLengths);
}
void GradeSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           ID);
    RFX_Int     (pFX, _T("[StudentID]"),    studentID);
    RFX_Int     (pFX, _T("[SubjectID]"),    subjectID);
    RFX_Date    (pFX, _T("[Date]"),         date);
    RFX_Int     (pFX, _T("[Value]"),        value);
}

GradeSetWrapper::GradeSetWrapper(GradeSet* pDB)
    :blk(&*pDB)
{
}
BOOL GradeSetWrapper::Load(const int nStudentID, GRADE& recStudent)
{
    BOOL isOK = TRUE;
    GRADE tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Grades] WHERE [ID] = %d"), nStudentID);

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

        tmp.nID             =   *(blk->m_rgID);
        tmp.nStudentID      =   *(blk->m_rgStudentID);
        tmp.nSubjectID      =   *(blk->m_rgSubjectID);

        tmp.dtDate.year     =   (blk->m_rgDate)->year;
        tmp.dtDate.month    =   (blk->m_rgDate)->month;
        tmp.dtDate.day      =   (blk->m_rgDate)->day;
        tmp.dtDate.hour     =   (blk->m_rgDate)->hour;
        tmp.dtDate.minute   =   (blk->m_rgDate)->minute;
        tmp.dtDate.second   =   (blk->m_rgDate)->second;

        tmp.value           =   *(blk->m_rgValue);

        recStudent = tmp;
    }

    blk->Close();

    return isOK;
}
BOOL GradeSetWrapper::NextID(int& id) const
{
    BOOL isOK = TRUE;
    GRADE tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT TOP 1 * FROM [Grades] ORDER BY [ID] DESC"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

        id = tmp.nID + 1;
    }

    blk->Close();

    return isOK;
}
BOOL GradeSetWrapper::LoadAll(std::vector<GRADE>& out)
{
    out.clear();
    BOOL isOK = TRUE;
    GRADE tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Grades]"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {

        int rowsFetched = blk->GetRowsFetched();

        for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
        {

            CString csComboString;

            tmp.nID             =   *(blk->m_rgID + nPosInRowset);
            tmp.nStudentID      =   *(blk->m_rgStudentID + nPosInRowset);
            tmp.nSubjectID      =   *(blk->m_rgSubjectID + nPosInRowset);

            tmp.dtDate.year     =   (blk->m_rgDate + nPosInRowset)->year;
            tmp.dtDate.month    =   (blk->m_rgDate + nPosInRowset)->month;
            tmp.dtDate.day      =   (blk->m_rgDate + nPosInRowset)->day;
            tmp.dtDate.hour     =   (blk->m_rgDate + nPosInRowset)->hour;
            tmp.dtDate.minute   =   (blk->m_rgDate + nPosInRowset)->minute;
            tmp.dtDate.second   =   (blk->m_rgDate + nPosInRowset)->second;

            tmp.value           =   *(blk->m_rgValue + nPosInRowset);

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}


SubjectSet::SubjectSet(CDatabase* pDB)
    : CRecordset(pDB)
{

    constexpr int cntBefore = __COUNTER__;

    ID =                    -1;     __COUNTER__;
    m_rgID                  = NULL;
    m_rgIDLengths           = NULL;

    name                    = "";   __COUNTER__;
    m_rgName                = NULL;
    m_rgNameLengths         = NULL;

    teacherID               = -1;   __COUNTER__;
    m_rgTeacherID           = NULL;
    m_rgTeacherIDLengths    = NULL;

    roomName                = "";   __COUNTER__;
    m_rgRoomName            = NULL;
    m_rgRoomNameLengths     = NULL;

    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields               = count;
}
void SubjectSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),           &m_rgID, &m_rgIDLengths);
    RFX_Text_Bulk   (pFX, _T("[Name]"),         &m_rgName, &m_rgNameLengths, 20);
    RFX_Int_Bulk    (pFX, _T("[TeacherID]"),    &m_rgTeacherID, &m_rgTeacherIDLengths);
    RFX_Text_Bulk   (pFX, _T("[RoomName]"),     &m_rgRoomName, &m_rgRoomNameLengths, 20);
}
void SubjectSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           ID);
    RFX_Text    (pFX, _T("[Name]"),         name);
    RFX_Int     (pFX, _T("[TeacherID]"),    teacherID);
    RFX_Text    (pFX, _T("[RoomName]"),     roomName);
}

SubjectSetWrapper::SubjectSetWrapper(SubjectSet* pDB)
    :blk(&*pDB)
{
}
BOOL SubjectSetWrapper::Load(const int nStudentID, SUBJECT& recStudent)
{
    BOOL isOK = TRUE;
    SUBJECT tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Subjects] WHERE [ID] = %d"), nStudentID);

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

        tmp.szName = blk->name;

        tmp.nTeacherID = *(blk->m_rgTeacherID);

        tmp.szRoom = blk->roomName;

        recStudent = tmp;
    }

    blk->Close();

    return isOK;
}
BOOL SubjectSetWrapper::NextID(int& id) const
{
    BOOL isOK = TRUE;
    GRADE tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT TOP 1 * FROM [Subjects] ORDER BY [ID] DESC"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

        id = tmp.nID + 1;
    }

    blk->Close();

    return isOK;
}
BOOL SubjectSetWrapper::LoadAll(std::vector<SUBJECT>& out)
{
    out.clear();
    BOOL isOK = TRUE;
    SUBJECT tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Subjects]"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {

        int rowsFetched = blk->GetRowsFetched();

        for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
        {

            CString csComboString;


            tmp.nID = *(blk->m_rgID + nPosInRowset);

            tmp.szName = blk->m_rgName + nPosInRowset * 20;

            tmp.nTeacherID = *(blk->m_rgTeacherID + nPosInRowset);

            tmp.szRoom = blk->m_rgRoomName + nPosInRowset * 20;

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}


ClassesSet::ClassesSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;


    ID                      = -1; __COUNTER__;
    m_rgID                  = NULL; 
    m_rgIDLengths           = NULL; 

    name                    = ""; __COUNTER__;
    m_rgName                = NULL; 
    m_rgNameLengths         = NULL; 

    teacherID               = -1; __COUNTER__;
    m_rgTeacherID           = NULL; 
    m_rgTeacherIDLengths    = NULL; 

    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields               = count;
}
void ClassesSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),               &m_rgID, &m_rgIDLengths);
    RFX_Text_Bulk   (pFX, _T("[Name]"),             &m_rgName, &m_rgNameLengths, 5);
    RFX_Int_Bulk    (pFX, _T("[ClassTeacherID]"),   &m_rgTeacherID, &m_rgTeacherIDLengths);
}
void ClassesSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),               ID);
    RFX_Text    (pFX, _T("[Name]"),             name);
    RFX_Int     (pFX, _T("[ClassTeacherID]"),   teacherID);
}

ClassesSetWrapper::ClassesSetWrapper(ClassesSet* pDB)
    :blk(&*pDB)
{
}
BOOL ClassesSetWrapper::Load(const int nStudentID, CClass& recStudent)
{
    BOOL isOK = TRUE;
    CClass tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Classes] WHERE [ID] = %d"), nStudentID);

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;
        tmp.ID          =   *(blk->m_rgID);
        tmp.name        =   CString{ blk->m_rgName};
        tmp.teacherID   =   *(blk->m_rgTeacherID);

        /*
        tmp.nID = *(blk->m_rgID);

        strcpy_s(tmp.szName, tmp.MAX_NAME_SIZE, blk->m_rgName);

        tmp.nTeacherID = *(blk->m_rgTeacherID);

        strcpy_s(tmp.szRoom, tmp.MAX_NAME_SIZE, blk->m_rgRoomName);
        */
        recStudent = tmp;
    }

    blk->Close();

    return isOK;
}
BOOL ClassesSetWrapper::NextID(int& id) const
{
    BOOL isOK = TRUE;
    GRADE tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT TOP 1 * FROM [Classes] ORDER BY [ID] DESC"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        CString csComboString;

        tmp.nID = *(blk->m_rgID);

        id = tmp.nID + 1;
    }

    blk->Close();

    return isOK;
}
BOOL ClassesSetWrapper::LoadAll(std::vector<CClass>& out)
{
    out.clear();
    BOOL isOK = TRUE;
    CClass tmp;
    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Classes]"));

    try
    {
        blk->Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {

        int rowsFetched = blk->GetRowsFetched();

        for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
        {

            CString csComboString;

            tmp.ID          =   *(blk->m_rgID + nPosInRowset);
            tmp.name        =   CString{ blk->m_rgName + nPosInRowset * 5 };
            tmp.teacherID   =   *(blk->m_rgTeacherID + nPosInRowset);

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}

IDtoNameSet::IDtoNameSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;



    m_rgID                  = NULL; __COUNTER__;
    m_rgIDLengths           = NULL; __COUNTER__;

    m_rgName                = NULL; __COUNTER__;
    m_rgNameLengths         = NULL; __COUNTER__;

    constexpr int count = (__COUNTER__ - cntBefore - 1) / 2;

    m_nFields               = count;
}
void IDtoNameSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk(pFX, _T("[ID]"), &m_rgID, &m_rgIDLengths);
    RFX_Text_Bulk(pFX, _T("[Name]"), &m_rgName, &m_rgNameLengths, 256);
}


BOOL IDtoNameMapper(CDatabase* db,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const std::vector<int>& ids,
    std::unordered_map<int, CString>& map)
{
    unsigned int idsCount = ids.size();

    BOOL isOK = idsCount > 0;

        if (isOK)
        {
            CString sSQL;
            sSQL.Format(_T("SELECT [%s], [%s] FROM [%s] WHERE [%s] IN ("), idField, nameField, table, idField);
            unsigned int len = 0;
            for (int id : ids)
            {
                len += DigitsCount(id);
                len += sizeof(",") - 1;
            }
            len += 1;   // For '\0'

            sSQL.Preallocate(len);

            for (size_t i = 0; i < idsCount - 1; i++)
            {
                sSQL.AppendFormat(_T("%d,"), ids[i]);
            }
            sSQL.AppendFormat(_T("%d)"), ids[idsCount - 1]);

            // Begin reading all records
            IDtoNameSet blk(db);

            try
            {
                blk.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
            }
            catch (const std::exception&)
            {
                isOK = FALSE;
            }

            if (isOK)
            {
                int rowsFetched = blk.GetRowsFetched();
                while (!blk.IsEOF())
                {
                    for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
                    {
                        int id = *(blk.m_rgID + nPosInRowset);
                        CString name = CString{ blk.m_rgName + nPosInRowset * 256 };

                        map[id] = name;
                    }
                    blk.MoveNext();
                }
            }// !Getting fields

            blk.Close();

        }// !Creating SQL querry

    return isOK;
}

template<class T>
BOOL DatabaseInterface<T>::LastID(int& id) const
{
    BOOL isGood = TRUE;
    id = -1;

    CRecordset rs(db);
    try
    {
        rs.Open(CRecordset::forwardOnly, _T("select scope_identity() as last_id"), CRecordset::readOnly);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    CString strLastID;

    if (isGood)
    {
        rs.GetFieldValue(_T("last_id"), strLastID);
        rs.Close();
        isGood = strLastID != "";
    }

    if (isGood)
    {
        id = _wtoi(strLastID);
    }
    return isGood;
}

StudentDatabaseInterface::~StudentDatabaseInterface()
{
    if (recordSet.IsOpen())
    {
        recordSet.Close();
    }
}
StudentDatabaseInterface::StudentDatabaseInterface(const std::wstring& tableName, CDatabase* db)
    :DatabaseInterface(db)
    , recordSet(this->db)
    , table(tableName.c_str())
{ }
BOOL StudentDatabaseInterface::Add(STUDENT& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        // Check if number in class is duplicate
        recordSet.m_strFilter.Format(_T("[NumberInClass] = %d AND [ClassID] = %d"), recStudent.numberInClass, recStudent.classID);
        try
        {
            recordSet.Open(CRecordset::dynaset, table, CRecordset::none);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }
        isGood = recordSet.GetRowsFetched() == 0;

        recordSet.m_strFilter = "";

        isGood = isGood && recordSet.Requery();

        if (isGood)
        {
            isGood = recordSet.CanAppend();
        }

        if (isGood)
        {
            db->BeginTrans();

            recordSet.AddNew();

            recordSet.numberInClass     = recStudent.numberInClass;
            recordSet.firstName         = recStudent.szFirstName;
            recordSet.lastName          = recStudent.szLastName;
            recordSet.birthday.year     = recStudent.dtBirthDate.year;
            recordSet.birthday.month    = recStudent.dtBirthDate.month;
            recordSet.birthday.day      = recStudent.dtBirthDate.day;
            recordSet.classID           = recStudent.classID;

            recordSet.birthday.hour     = 0;
            recordSet.birthday.minute   = 0;
            recordSet.birthday.second   = 0;
            recordSet.birthday.fraction = 0;

            try
            {
                isGood = recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }


            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            if (isGood)
            {
                LastID(recStudent.nID);
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL StudentDatabaseInterface::Edit(const STUDENT& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        recordSet.m_strFilter.Format(_T("ID = %d"), recStudent.nID);

        try
        {
            recordSet.Open(CRecordset::dynaset, table);

            ASSERT(recordSet.GetRowsFetched() == 1);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }
        if (isGood)
        {
            isGood = recordSet.CanUpdate();
        }
        if (isGood)
        {
            db->BeginTrans();

            recordSet.Edit();

            recordSet.numberInClass     = recStudent.numberInClass;
            recordSet.firstName         = recStudent.szFirstName;
            recordSet.lastName          = recStudent.szLastName;
            recordSet.birthday.year     = recStudent.dtBirthDate.year;
            recordSet.birthday.month    = recStudent.dtBirthDate.month;
            recordSet.birthday.day      = recStudent.dtBirthDate.day;
            recordSet.classID           = recStudent.classID;

            try
            {
                recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }

            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL StudentDatabaseInterface::Delete(const int nID)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::dynaset, table);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }
    if (isGood)
    {
        isGood = recordSet.CanUpdate();
    }
    if (isGood)
    {
        db->BeginTrans();


        try
        {
            recordSet.Delete();
            recordSet.MoveNext();
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            db->CommitTrans();
        }
        else
        {
            db->Rollback();
        }

        recordSet.Close();
    }

    return isGood;
}
BOOL StudentDatabaseInterface::Load(const int nID, STUDENT& recStudent)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        recStudent.nID                  = recordSet.ID;

        recStudent.szFirstName          = recordSet.firstName;
        recStudent.szLastName           = recordSet.lastName;

        recStudent.dtBirthDate.year     = recordSet.birthday.year;
        recStudent.dtBirthDate.month    = recordSet.birthday.month;
        recStudent.dtBirthDate.day      = recordSet.birthday.day;
        recStudent.dtBirthDate.hour     = recordSet.birthday.hour;
        recStudent.dtBirthDate.minute   = recordSet.birthday.minute;
        recStudent.dtBirthDate.second   = recordSet.birthday.second;

        recStudent.classID              = recordSet.classID;
        recStudent.numberInClass        = recordSet.numberInClass;

        recordSet.Close();

        isGood = recStudent.Validate();
    }

    return isGood;
}

BOOL StudentDatabaseInterface::LoadAll(std::vector<STUDENT>& out)
{
    BOOL isGood = TRUE;
    out.clear();
    recordSet.m_strFilter = "";

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly | CRecordset::useMultiRowFetch);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        int rowsFetched = recordSet.GetRowsFetched();
        while (!recordSet.IsEOF())
        {
            for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
            {
                STUDENT tmp;

                tmp.nID                 = *(recordSet.m_rgID + nPosInRowset);


                tmp.szFirstName         = CString{ recordSet.m_rgFirstName + nPosInRowset*20 };
                tmp.szLastName          = CString{ recordSet.m_rgLastName + nPosInRowset*20 };

                tmp.dtBirthDate.year    = (recordSet.m_rgBirthday + nPosInRowset)->year;
                tmp.dtBirthDate.month   = (recordSet.m_rgBirthday + nPosInRowset)->month;
                tmp.dtBirthDate.day     = (recordSet.m_rgBirthday + nPosInRowset)->day;
                tmp.dtBirthDate.hour    = (recordSet.m_rgBirthday + nPosInRowset)->hour;
                tmp.dtBirthDate.minute  = (recordSet.m_rgBirthday + nPosInRowset)->minute;
                tmp.dtBirthDate.second  = (recordSet.m_rgBirthday + nPosInRowset)->second;

                tmp.classID             = *(recordSet.m_rgClassID + nPosInRowset);
                tmp.numberInClass       = *(recordSet.m_rgNumberInClass + nPosInRowset);

                isGood = tmp.Validate();

                if (isGood)
                {
                    out.push_back(tmp);
                }
            }
            recordSet.MoveNext();
        }
        recordSet.Close();
    }
    return isGood;
}

TeacherDatabaseInterface::TeacherDatabaseInterface(const std::wstring& tableName, CDatabase* db)
    :DatabaseInterface(db)
    , recordSet(this->db)
    , table(tableName.c_str())
{ }
BOOL TeacherDatabaseInterface::Add(TEACHER& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        try
        {
            recordSet.Open(CRecordset::dynaset, table, CRecordset::none);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            isGood = recordSet.CanAppend();
        }

        if (isGood)
        {
            db->BeginTrans();

            recordSet.AddNew();

            recordSet.firstName = CString{ recStudent.szFirstName };
            recordSet.lastName  = CString{ recStudent.szLastName };

            try
            {
                isGood = recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }


            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            if (isGood)
            {
                LastID(recStudent.nID);
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL TeacherDatabaseInterface::Edit(const TEACHER& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        recordSet.m_strFilter.Format(_T("ID = %d"), recStudent.nID);

        try
        {
            recordSet.Open(CRecordset::dynaset, table);

            ASSERT(recordSet.GetRowsFetched() == 1);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }
        if (isGood)
        {
            isGood = recordSet.CanUpdate();
        }
        if (isGood)
        {
            db->BeginTrans();

            recordSet.Edit();

            recordSet.firstName = recStudent.szFirstName;
            recordSet.lastName  = recStudent.szLastName;

            try
            {
                recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }

            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL TeacherDatabaseInterface::Delete(const int nID)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::dynaset, table);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }
    if (isGood)
    {
        isGood = recordSet.CanUpdate();
    }
    if (isGood)
    {
        db->BeginTrans();


        try
        {
            recordSet.Delete();
            recordSet.MoveNext();
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            db->CommitTrans();
        }
        else
        {
            db->Rollback();
        }

        recordSet.Close();
    }

    return isGood;
}
BOOL TeacherDatabaseInterface::Load(const int nID, TEACHER& recStudent)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        recStudent.nID = recordSet.ID;

        recStudent.szFirstName  = recordSet.firstName;
        recStudent.szLastName   = recordSet.lastName;

        recordSet.Close();

        isGood = recStudent.Validate();
    }

    return isGood;
}
BOOL TeacherDatabaseInterface::LoadAll(std::vector<TEACHER>& out)
{
    BOOL isGood = TRUE;
    out.clear();
    recordSet.m_strFilter = "";

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly | CRecordset::useMultiRowFetch);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        int rowsFetched = recordSet.GetRowsFetched();
        while (!recordSet.IsEOF())
        {
            for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
            {
                TEACHER tmp;

                tmp.nID = *(recordSet.m_rgID + nPosInRowset);

                tmp.szFirstName =  recordSet.m_rgFirstName + nPosInRowset * 20;
                tmp.szLastName  =  recordSet.m_rgLastName + nPosInRowset * 20;

                isGood = tmp.Validate();

                if (isGood)
                {
                    out.push_back(tmp);
                }
            }
            recordSet.MoveNext();
        }
        recordSet.Close();
    }
    return isGood;
}
TeacherDatabaseInterface::~TeacherDatabaseInterface()
{
    if (recordSet.IsOpen())
    {
        recordSet.Close();
    }
}

SubjectDatabaseInterface::SubjectDatabaseInterface(const std::wstring& tableName, CDatabase* db)
    :DatabaseInterface(db)
    , recordSet(this->db)
    , table(tableName.c_str())
{ }
BOOL SubjectDatabaseInterface::Add(SUBJECT& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        try
        {
            recordSet.Open(CRecordset::dynaset, table, CRecordset::none);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            isGood = recordSet.CanAppend();
        }

        if (isGood)
        {
            db->BeginTrans();

            recordSet.AddNew();

            recordSet.name          = recStudent.szName;
            recordSet.teacherID     = recStudent.nTeacherID;
            recordSet.roomName      = recStudent.szRoom;

            try
            {
                isGood = recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }


            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            if (isGood)
            {
                LastID(recStudent.nID);
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL SubjectDatabaseInterface::Edit(const SUBJECT& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        recordSet.m_strFilter.Format(_T("ID = %d"), recStudent.nID);

        try
        {
            recordSet.Open(CRecordset::dynaset, table);

            ASSERT(recordSet.GetRowsFetched() == 1);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }
        if (isGood)
        {
            isGood = recordSet.CanUpdate();
        }
        if (isGood)
        {
            db->BeginTrans();

            recordSet.Edit();

            recordSet.name          = recordSet.name;
            recordSet.teacherID     = recStudent.nTeacherID;
            recordSet.roomName      = recStudent.szRoom;

            try
            {
                recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }

            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL SubjectDatabaseInterface::Delete(const int nID)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::dynaset, table);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }
    if (isGood)
    {
        isGood = recordSet.CanUpdate();
    }
    if (isGood)
    {
        db->BeginTrans();


        try
        {
            recordSet.Delete();
            recordSet.MoveNext();
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            db->CommitTrans();
        }
        else
        {
            db->Rollback();
        }

        recordSet.Close();
    }

    return isGood;
}
BOOL SubjectDatabaseInterface::Load(const int nID, SUBJECT& recStudent)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        recStudent.nID          = recordSet.ID;

        recStudent.szName       = recordSet.name;
        recStudent.nTeacherID   = recordSet.teacherID;
        recStudent.szRoom       = recordSet.roomName;

        recordSet.Close();

        isGood = recStudent.Validate();
    }

    return isGood;
}
BOOL SubjectDatabaseInterface::LoadAll(std::vector<SUBJECT>& out)
{
    BOOL isGood = TRUE;
    out.clear();
    recordSet.m_strFilter = "";

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly | CRecordset::useMultiRowFetch);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        int rowsFetched = recordSet.GetRowsFetched();
        while (!recordSet.IsEOF())
        {
            for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
            {
                SUBJECT tmp;


                tmp.nID = *(recordSet.m_rgID + nPosInRowset);

                tmp.nTeacherID  = *(recordSet.m_rgTeacherID + nPosInRowset);
                tmp.szName      = (recordSet.m_rgName + nPosInRowset * 20);
                tmp.szRoom      = (recordSet.m_rgRoomName + nPosInRowset * 20);

                isGood = tmp.Validate();

                if (isGood)
                {
                    out.push_back(tmp);
                }
            }
            recordSet.MoveNext();
        }
        recordSet.Close();
    }
    return isGood;
}
SubjectDatabaseInterface::~SubjectDatabaseInterface()
{
    if (recordSet.IsOpen())
    {
        recordSet.Close();
    }
}

GradeDatabaseInterface::GradeDatabaseInterface(const std::wstring& tableName, CDatabase* db)
    :DatabaseInterface(db)
    , recordSet(this->db)
    , table(tableName.c_str())
{ }
BOOL GradeDatabaseInterface::Add(GRADE& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        try
        {
            recordSet.Open(CRecordset::dynaset, table, CRecordset::none);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            isGood = recordSet.CanAppend();
        }

        if (isGood)
        {
            db->BeginTrans();

            recordSet.AddNew();

            recordSet.studentID     = recStudent.nStudentID;
            recordSet.subjectID     = recStudent.nSubjectID;
            recordSet.value         = recStudent.value;
            
            recordSet.date.year     = recStudent.dtDate.year;
            recordSet.date.month    = recStudent.dtDate.month;
            recordSet.date.day      = recStudent.dtDate.day;
            recordSet.date.hour     = recStudent.dtDate.hour;
            recordSet.date.minute   = recStudent.dtDate.minute;
            recordSet.date.second   = recStudent.dtDate.second;
            recordSet.date.fraction = recStudent.dtDate.fraction;

            try
            {
                isGood = recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }


            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            if (isGood)
            {
                LastID(recStudent.nID);
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL GradeDatabaseInterface::Edit(const GRADE& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        recordSet.m_strFilter.Format(_T("ID = %d"), recStudent.nID);

        try
        {
            recordSet.Open(CRecordset::dynaset, table);

            ASSERT(recordSet.GetRowsFetched() == 1);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }
        if (isGood)
        {
            isGood = recordSet.CanUpdate();
        }
        if (isGood)
        {
            db->BeginTrans();

            recordSet.Edit();

            recordSet.studentID     = recStudent.nStudentID;
            recordSet.subjectID     = recStudent.nSubjectID;
            recordSet.value         = recStudent.value;
            
            recordSet.date.year     = recStudent.dtDate.year;
            recordSet.date.month    = recStudent.dtDate.month;
            recordSet.date.day      = recStudent.dtDate.day;
            recordSet.date.hour     = recStudent.dtDate.hour;
            recordSet.date.minute   = recStudent.dtDate.minute;
            recordSet.date.second   = recStudent.dtDate.second;
            recordSet.date.fraction = recStudent.dtDate.fraction;

            try
            {
                recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }

            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL GradeDatabaseInterface::Delete(const int nID)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::dynaset, table);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }
    if (isGood)
    {
        isGood = recordSet.CanUpdate();
    }
    if (isGood)
    {
        db->BeginTrans();


        try
        {
            recordSet.Delete();
            recordSet.MoveNext();
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            db->CommitTrans();
        }
        else
        {
            db->Rollback();
        }

        recordSet.Close();
    }

    return isGood;
}
BOOL GradeDatabaseInterface::Load(const int nID, GRADE& recStudent)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        recStudent.nID              = recordSet.ID;
        recStudent.nStudentID       = recordSet.studentID;
        recStudent.nSubjectID       = recordSet.subjectID;
        recStudent.value            = recordSet.value;
        
        recStudent.dtDate.year      = recordSet.date.year;
        recStudent.dtDate.month     = recordSet.date.month;
        recStudent.dtDate.day       = recordSet.date.day;
        recStudent.dtDate.hour      = recordSet.date.hour;
        recStudent.dtDate.minute    = recordSet.date.minute;
        recStudent.dtDate.second    = recordSet.date.second;
        recStudent.dtDate.fraction  = recordSet.date.fraction;

        recordSet.Close();

        isGood = recStudent.Validate();
    }

    return isGood;
}
BOOL GradeDatabaseInterface::LoadAll(std::vector<GRADE>& out)
{
    BOOL isGood = TRUE;
    out.clear();
    recordSet.m_strFilter = "";

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly | CRecordset::useMultiRowFetch);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        int rowsFetched = recordSet.GetRowsFetched();
        while (!recordSet.IsEOF())
        {
            for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
            {
                GRADE tmp;

                tmp.nID              = *(recordSet.m_rgID + nPosInRowset);
                tmp.nStudentID       = *(recordSet.m_rgStudentID + nPosInRowset);
                tmp.nSubjectID       = *(recordSet.m_rgSubjectID + nPosInRowset);
                tmp.value            = *(recordSet.m_rgValue + nPosInRowset);
                
                tmp.dtDate.year      = (recordSet.m_rgDate + nPosInRowset)->year;
                tmp.dtDate.month     = (recordSet.m_rgDate + nPosInRowset)->month;
                tmp.dtDate.day       = (recordSet.m_rgDate + nPosInRowset)->day;
                tmp.dtDate.hour      = (recordSet.m_rgDate + nPosInRowset)->hour;
                tmp.dtDate.minute    = (recordSet.m_rgDate + nPosInRowset)->minute;
                tmp.dtDate.second    = (recordSet.m_rgDate + nPosInRowset)->second;
                tmp.dtDate.fraction  = (recordSet.m_rgDate + nPosInRowset)->fraction;

                isGood = tmp.Validate();

                if (isGood)
                {
                    out.push_back(tmp);
                }
            }
            recordSet.MoveNext();
        }
        recordSet.Close();
    }
    return isGood;
}
GradeDatabaseInterface::~GradeDatabaseInterface()
{
    if (recordSet.IsOpen())
    {
        recordSet.Close();
    }
}

ClassesDatabaseInterface::ClassesDatabaseInterface(const std::wstring& tableName, CDatabase* db)
    :DatabaseInterface(db)
    , recordSet(this->db)
    , table(tableName.c_str())
{ }
BOOL ClassesDatabaseInterface::Add(CClass& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        try
        {
            recordSet.Open(CRecordset::dynaset, table, CRecordset::none);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            isGood = recordSet.CanAppend();
        }

        if (isGood)
        {
            db->BeginTrans();

            recordSet.AddNew();

            recordSet.name          = recStudent.name;
            recordSet.teacherID     = recStudent.teacherID;

            try
            {
                isGood = recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }


            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            if (isGood)
            {
                LastID(recStudent.ID);
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL ClassesDatabaseInterface::Edit(const CClass& recStudent)
{
    BOOL isGood = TRUE;

    if (isGood = recStudent.Validate())
    {
        recordSet.m_strFilter.Format(_T("ID = %d"), recStudent.ID);

        try
        {
            recordSet.Open(CRecordset::dynaset, table);

            ASSERT(recordSet.GetRowsFetched() == 1);
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }
        if (isGood)
        {
            isGood = recordSet.CanUpdate();
        }
        if (isGood)
        {
            db->BeginTrans();

            recordSet.Edit();

            recordSet.name          = recStudent.name;
            recordSet.teacherID     = recStudent.teacherID;

            try
            {
                recordSet.Update();
            }
            catch (const CDBException&)
            {
                isGood = FALSE;
            }

            if (isGood)
            {
                db->CommitTrans();
            }
            else
            {
                db->Rollback();
            }

            recordSet.Close();
        }
    }
    return isGood;
}
BOOL ClassesDatabaseInterface::Delete(const int nID)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::dynaset, table);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }
    if (isGood)
    {
        isGood = recordSet.CanUpdate();
    }
    if (isGood)
    {
        db->BeginTrans();


        try
        {
            recordSet.Delete();
            recordSet.MoveNext();
        }
        catch (const CDBException&)
        {
            isGood = FALSE;
        }

        if (isGood)
        {
            db->CommitTrans();
        }
        else
        {
            db->Rollback();
        }

        recordSet.Close();
    }

    return isGood;
}
BOOL ClassesDatabaseInterface::Load(const int nID, CClass& recStudent)
{
    BOOL isGood = TRUE;

    recordSet.m_strFilter.Format(_T("ID = %d"), nID);

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly);

        ASSERT(recordSet.GetRowsFetched() == 1);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        recStudent.ID           = recordSet.ID;
        recStudent.name         = recordSet.name;
        recStudent.teacherID    = recordSet.teacherID;

        recordSet.Close();

        isGood = recStudent.Validate();
    }

    return isGood;
}
BOOL ClassesDatabaseInterface::LoadAll(std::vector<CClass>& out)
{
    BOOL isGood = TRUE;
    out.clear();
    recordSet.m_strFilter = "";

    try
    {
        recordSet.Open(CRecordset::snapshot, table, CRecordset::readOnly | CRecordset::useMultiRowFetch);
    }
    catch (const CDBException&)
    {
        isGood = FALSE;
    }

    if (isGood)
    {
        int rowsFetched = recordSet.GetRowsFetched();
        while (!recordSet.IsEOF())
        {
            for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
            {
                CClass tmp;

                tmp.ID          = *(recordSet.m_rgID + nPosInRowset);
                tmp.name        = CString{ recordSet.m_rgName + nPosInRowset * 5 };
                tmp.teacherID   = *(recordSet.m_rgTeacherID + nPosInRowset);

                isGood = tmp.Validate();

                if (isGood)
                {
                    out.push_back(tmp);
                }
            }
            recordSet.MoveNext();
        }
        recordSet.Close();
    }
    return isGood;
}
ClassesDatabaseInterface::~ClassesDatabaseInterface()
{
    if (recordSet.IsOpen())
    {
        recordSet.Close();
    }
}

ScheduleDatabaseInterface::ScheduleDatabaseInterface(const std::wstring& tableName, CDatabase* db)
    :DatabaseInterface(db)
    , recordSet(this->db)
    , table(tableName.c_str())
{}
ScheduleDatabaseInterface::~ScheduleDatabaseInterface()
{
    if (recordSet.IsOpen())
    {
        recordSet.Close();
    }
}
BOOL ScheduleDatabaseInterface::Load(const int classID, CSchedule& recStudent)
{
    BOOL isGood = TRUE;
    CSchedule result;
    ScheduleClass sc;
    result.classID = classID;

    recordSet.m_strFilter.Format(_T("[ClassID] = %d"), classID);


    recordSet.Open(AFX_DB_USE_DEFAULT_TYPE, _T("Schedule"), CRecordset::readOnly | CRecordset::useMultiRowFetch);


    while (!recordSet.IsEOF())
    {
        int rowsFetched = recordSet.GetRowsFetched();

        for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
        {

            sc.nID              = *(recordSet.m_rgID + nPosInRowset);
            sc.nSubjectID       = *(recordSet.m_rgSubjectID + nPosInRowset);
            sc.begin.hour       = (recordSet.m_rgBeginTime + nPosInRowset)->hour;
            sc.begin.minute     = (recordSet.m_rgBeginTime + nPosInRowset)->minute;
            sc.begin.second     = (recordSet.m_rgBeginTime + nPosInRowset)->second;
            sc.duration.hour    = (recordSet.m_rgDuration + nPosInRowset)->hour;
            sc.duration.minute  = (recordSet.m_rgDuration + nPosInRowset)->minute;
            sc.duration.second  = (recordSet.m_rgDuration + nPosInRowset)->second;

            int dayOfWeek       = *(recordSet.m_rgDayOfWeek + nPosInRowset);

            ASSERT(dayOfWeek < 7);

            //                result.days[dayOfWeek].classes.push_back(sc);
            result.days[dayOfWeek].classes.insert(sc);
        }
        recordSet.MoveNext();
    }

    recordSet.Close();

    recordSet.m_strFilter = "";

    recStudent = result;

    return isGood;
}
BOOL ScheduleDatabaseInterface::Edit(const CSchedule& recStudent)
{
    BOOL isGood = TRUE;


    int size = recStudent.days.size();
    recordSet.Open(CRecordset::dynaset, table);

    for (int dayOfWeek = 0; dayOfWeek < size; dayOfWeek++)
    {
        for (const auto& _class : recStudent.days[dayOfWeek].classes)
        {
            recordSet.m_strFilter.Format(_T("[ID] = %d"), _class.nID);
            isGood = recordSet.Requery();

            if (isGood)
            {
                db->BeginTrans();

                recordSet.Edit();

                recordSet.beginTime.hour    = _class.begin.hour;
                recordSet.beginTime.minute  = _class.begin.minute;
                recordSet.beginTime.second  = _class.begin.second;

                recordSet.duration.hour     = _class.duration.hour;
                recordSet.duration.minute   = _class.duration.minute;
                recordSet.duration.second   = _class.duration.second;

                recordSet.subjectID         = _class.nSubjectID;
                recordSet.dayOfWeek         = dayOfWeek;

                try
                {
                    recordSet.Update();
                }
                catch (const CDBException&)
                {
                    isGood = FALSE;
                }

                if (isGood)
                {
                    db->CommitTrans();
                }
                else
                {
                    db->Rollback();
                }
            }
        }
    }

    recordSet.Close();

    return isGood;
}