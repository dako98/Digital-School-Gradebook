#include "pch.h"
#include "CSchedule.h"


ScheduleClassSet::ScheduleClassSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;

    ID                          =   -1;     __COUNTER__;
    m_rgID                      =   NULL;
    m_rgIDLengths               =   NULL;

    beginTime                   =   "";     __COUNTER__;
    m_rgBeginTime               =   NULL;
    m_rgBeginTimeLengths        =   NULL;

    duration                    =   "";     __COUNTER__;
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

    RFX_Text    (pFX, _T("[Begin]"),        beginTime);
    RFX_Text    (pFX, _T("[Duration]"),     duration);
    RFX_Int     (pFX, _T("[SubjectID]"),    subjectID);
    RFX_Int     (pFX, _T("[DayOfWeek]"),    dayOfWeek);
    RFX_Int     (pFX, _T("[ClassID]"),      classID);
}
void ScheduleClassSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),           &m_rgID, &m_rgIDLengths);

    RFX_Text_Bulk   (pFX, _T("[Begin]"),        &m_rgBeginTime, &m_rgBeginTimeLengths,50);
    RFX_Text_Bulk   (pFX, _T("[Duration]"),     &m_rgDuration, &m_rgDurationLengths,50);
    RFX_Int_Bulk    (pFX, _T("[SubjectID]"),    &m_rgSubjectID, &m_rgSubjectIDLengths);
    RFX_Int_Bulk    (pFX, _T("[DayOfWeek]"),    &m_rgDayOfWeek, &m_rgDayOfWeekLengths);
    RFX_Int_Bulk    (pFX, _T("[ClassID]"),      &m_rgClassID, &m_rgClassIDLengths);
}

ScheduleDay::ScheduleDay()
{
    classes.SetSorted(true);
}

BOOL ScheduleClass::Validate() const
{
    return nSubjectID != -1;
}
