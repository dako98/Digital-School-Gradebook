#include "pch.h"
#include "DBConnector.h"

StudentSet::StudentSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    m_rgID                  = NULL;
    m_rgIDLengths           = NULL;

    m_rgNumber              = NULL;
    m_rgNumberLengths       = NULL;

    m_rgFirstName           = NULL;
    m_rgFirstNameLengths    = NULL;

    m_rgLastName            = NULL;
    m_rgLastNameLengths     = NULL;

    m_rgBirthday            = NULL;
    m_rgBirthdayLengths     = NULL;

    m_nFields               = 5;
}
void StudentSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),               &m_rgID,        &m_rgIDLengths);
    RFX_Int_Bulk    (pFX, _T("[NumberInClass]"),    &m_rgNumber,    &m_rgNumberLengths);
    RFX_Text_Bulk   (pFX, _T("[FirstName]"),        &m_rgFirstName, &m_rgFirstNameLengths,  20);
    RFX_Text_Bulk   (pFX, _T("[LastName]"),         &m_rgLastName,  &m_rgLastNameLengths,   20);
    RFX_Date_Bulk   (pFX, _T("[Birthday]"),         &m_rgBirthday,  &m_rgBirthdayLengths);
}

//FIXME: Add number field from database.
StudentSetWrapper::StudentSetWrapper(StudentSet *pDB)
    :blk(&*pDB)
{
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

        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

        tmp.dtBirthDate.year    =   (blk->m_rgBirthday)->year;
        tmp.dtBirthDate.month   =   (blk->m_rgBirthday)->month;
        tmp.dtBirthDate.day     =   (blk->m_rgBirthday)->day;
        tmp.dtBirthDate.hour    =   (blk->m_rgBirthday)->hour;
        tmp.dtBirthDate.minute  =   (blk->m_rgBirthday)->minute;
        tmp.dtBirthDate.second  =   (blk->m_rgBirthday)->second;

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

        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

        tmp.dtBirthDate.year    =   (blk->m_rgBirthday)->year;
        tmp.dtBirthDate.month   =   (blk->m_rgBirthday)->month;
        tmp.dtBirthDate.day     =   (blk->m_rgBirthday)->day;
        tmp.dtBirthDate.hour    =   (blk->m_rgBirthday)->hour;
        tmp.dtBirthDate.minute  =   (blk->m_rgBirthday)->minute;
        tmp.dtBirthDate.second  =   (blk->m_rgBirthday)->second;

        id = tmp.nID + 1;
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
    sSQL.Format(_T("SELECT * FROM [Students]"));

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
            //Check if value is null
            if (blk->m_rgFirstName[nPosInRowset] == SQL_NULL_DATA)
                continue;

            CString csComboString;

            tmp.nID = *(blk->m_rgID + nPosInRowset);

            strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName + nPosInRowset * 20);

            strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName + nPosInRowset * 20);

            tmp.dtBirthDate.year    =   (blk->m_rgBirthday + nPosInRowset)->year;
            tmp.dtBirthDate.month   =   (blk->m_rgBirthday + nPosInRowset)->month;
            tmp.dtBirthDate.day     =   (blk->m_rgBirthday + nPosInRowset)->day;
            tmp.dtBirthDate.hour    =   (blk->m_rgBirthday + nPosInRowset)->hour;
            tmp.dtBirthDate.minute  =   (blk->m_rgBirthday + nPosInRowset)->minute;
            tmp.dtBirthDate.second  =   (blk->m_rgBirthday + nPosInRowset)->second;

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}


TeacherSet::TeacherSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    m_rgID = NULL;
    m_rgIDLengths = NULL;

    m_rgFirstName = NULL;
    m_rgFirstNameLengths = NULL;

    m_rgLastName = NULL;
    m_rgLastNameLengths = NULL;


    m_nFields = 3;
}
void TeacherSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk(pFX, _T("[ID]"), &m_rgID, &m_rgIDLengths);
    RFX_Text_Bulk(pFX, _T("[FirstName]"), &m_rgFirstName, &m_rgFirstNameLengths, 20);
    RFX_Text_Bulk(pFX, _T("[LastName]"), &m_rgLastName, &m_rgLastNameLengths, 20);
}

TeacherSetWrapper::TeacherSetWrapper(TeacherSet* pDB)
    :blk(&*pDB)
{
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

        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

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

        strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName);

        strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName);

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

            strcpy_s(tmp.szFirstName, tmp.MAX_NAME_SIZE, blk->m_rgFirstName + nPosInRowset * 20);

            strcpy_s(tmp.szLastName, tmp.MAX_NAME_SIZE, blk->m_rgLastName + nPosInRowset * 20);

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}


GradeSet::GradeSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    m_rgID                  = NULL;
    m_rgIDLengths           = NULL;

    m_rgStudentID           = NULL;
    m_rgStudentIDLengths    = NULL;

    m_rgSubjectID           = NULL;
    m_rgSubjectIDLengths    = NULL;

    m_rgValue               = NULL;
    m_rgValueLengths        = NULL;

    m_rgDate                = NULL;
    m_rgDateLengths         = NULL;

    m_nFields = 5;
}
void GradeSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk(pFX, _T("[ID]"), &m_rgID, &m_rgIDLengths);
    RFX_Int_Bulk(pFX, _T("[StudentID]"), &m_rgStudentID, &m_rgStudentIDLengths);
    RFX_Int_Bulk(pFX, _T("[SubjectID]"), &m_rgSubjectID, &m_rgSubjectIDLengths);
    RFX_Date_Bulk(pFX, _T("[Date]"), &m_rgDate, &m_rgDateLengths);
    RFX_Int_Bulk(pFX, _T("[Value]"), &m_rgValue, &m_rgValueLengths);
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



    m_rgID                = NULL;
    m_rgIDLengths         = NULL;

    m_rgName              = NULL;
    m_rgNameLengths       = NULL;

    m_rgTeacherID         = NULL;
    m_rgTeacherIDLengths  = NULL;

    m_rgRoomName          = NULL;
    m_rgRoomNameLengths   = NULL;


    m_nFields = 4;
}
void SubjectSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk(pFX, _T("[ID]"), &m_rgID, &m_rgIDLengths);
    RFX_Text_Bulk(pFX, _T("[Name]"), &m_rgName, &m_rgNameLengths, 20);
    RFX_Int_Bulk(pFX, _T("[TeacherID]"), &m_rgTeacherID, &m_rgTeacherIDLengths);
    RFX_Text_Bulk(pFX, _T("[RoomName]"), &m_rgRoomName, &m_rgRoomNameLengths, 20);

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

        strcpy_s(tmp.szName, tmp.MAX_NAME_SIZE, blk->m_rgName);

        tmp.nTeacherID = *(blk->m_rgTeacherID);

        strcpy_s(tmp.szRoom, tmp.MAX_NAME_SIZE, blk->m_rgRoomName);

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

            strcpy_s(tmp.szName, tmp.MAX_NAME_SIZE, blk->m_rgName + nPosInRowset * 20);

            tmp.nTeacherID = *(blk->m_rgTeacherID + nPosInRowset);

            strcpy_s(tmp.szRoom, tmp.MAX_NAME_SIZE, blk->m_rgRoomName + nPosInRowset * 20);

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}
