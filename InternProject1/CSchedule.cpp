#include "pch.h"
#include "CSchedule.h"



ScheduleClassSetWrapper::ScheduleClassSetWrapper(ScheduleClassSet* pDB)
    :blk(&*pDB)
{
}
BOOL ScheduleClassSetWrapper::Load(const int nStudentID, std::vector<ScheduleClass>& out)
{
    BOOL isOK = TRUE;
    ScheduleClass tmp;


    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Schedule] WHERE [ClassID] = %d"), nStudentID);

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
            tmp.nID             =   *(blk->m_rgID + nPosInRowset);
            tmp.nSubjectID      =   *(blk->m_rgSubjectID + nPosInRowset);
            tmp.begin.hour      =   (blk->m_rgBeginTime + nPosInRowset)->hour;
            tmp.begin.minute    =   (blk->m_rgBeginTime + nPosInRowset)->minute;
            tmp.begin.second    =   (blk->m_rgBeginTime + nPosInRowset)->second;
            tmp.duration.hour   =   (blk->m_rgDuration + nPosInRowset)->hour;
            tmp.duration.minute =   (blk->m_rgDuration + nPosInRowset)->minute;
            tmp.duration.second =   (blk->m_rgDuration + nPosInRowset)->second;

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}
BOOL ScheduleClassSetWrapper::NextID(int& id) const
{
    BOOL isOK = TRUE;
    GRADE tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT TOP 1 * FROM [Schedule] ORDER BY [ID] DESC"));

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
BOOL ScheduleClassSetWrapper::LoadAll(std::vector<ScheduleClass>& out)
{
    out.clear();
    BOOL isOK = TRUE;
    ScheduleClass tmp;

    CString sSQL;
    sSQL.Format(_T("SELECT * FROM [Schedule]"));

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

            tmp.nID                 =   *(blk->m_rgID + nPosInRowset);
            tmp.nSubjectID          =   *(blk->m_rgSubjectID + nPosInRowset);

            tmp.begin.hour          =   (blk->m_rgBeginTime + nPosInRowset)->hour;
            tmp.begin.minute        =   (blk->m_rgBeginTime + nPosInRowset)->minute;
            tmp.begin.second        =   (blk->m_rgBeginTime + nPosInRowset)->second;

            tmp.duration.hour       =   (blk->m_rgDuration + nPosInRowset)->hour;
            tmp.duration.minute     =   (blk->m_rgDuration + nPosInRowset)->minute;
            tmp.duration.second     =   (blk->m_rgDuration + nPosInRowset)->second;

            out.push_back(tmp);
        }
    }

    blk->Close();

    return isOK;
}

ScheduleClassSet::ScheduleClassSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;

    ID                          =   -1;     __COUNTER__;
    m_rgID                      =   NULL;
    m_rgIDLengths               =   NULL;

    beginTime                   =   { 0, }; __COUNTER__;
    m_rgBeginTime               =   NULL;
    m_rgBeginTimeLengths        =   NULL;

    duration                    =   { 0, }; __COUNTER__;
    m_rgDuration                =   NULL;
    m_rgDurationLengths         =   NULL;

    subjectID                   =   -1;     __COUNTER__;
    m_rgSubjectID               =   NULL;
    m_rgSubjectIDLengths        =   NULL;

    dayOfWeek                   =   -1;     __COUNTER__;
    m_rgDayOfWeek               =   NULL;
    m_rgDayOfWeekLengths        =   NULL;

    classID                     =   -1;     __COUNTER__;
    m_rgClassID                 =   NULL;
    m_rgClassIDLengths          =   NULL;

    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields = count;
}
void ScheduleClassSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           ID);

    RFX_Date    (pFX, _T("[Begin]"),         beginTime);
    RFX_Date    (pFX, _T("[Duration]"),     duration);
    RFX_Int     (pFX, _T("[SubjectID]"),    subjectID);
    RFX_Int     (pFX, _T("[DayOfWeek]"),    dayOfWeek);
    RFX_Int     (pFX, _T("[ClassID]"),      classID);
}
void ScheduleClassSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk(pFX, _T("[ID]"),               &m_rgID, &m_rgIDLengths);

    RFX_Date_Bulk   (pFX, _T("[Begin]"),         &m_rgBeginTime, &m_rgBeginTimeLengths);
    RFX_Date_Bulk   (pFX, _T("[Duration]"),     &m_rgDuration, &m_rgDurationLengths);
    RFX_Int_Bulk    (pFX, _T("[SubjectID]"),    &m_rgSubjectID, &m_rgSubjectIDLengths);
    RFX_Int_Bulk    (pFX, _T("[DayOfWeek]"),    &m_rgDayOfWeek, &m_rgDayOfWeekLengths);
    RFX_Int_Bulk    (pFX, _T("[ClassID]"),      &m_rgClassID, &m_rgClassIDLengths);
}
