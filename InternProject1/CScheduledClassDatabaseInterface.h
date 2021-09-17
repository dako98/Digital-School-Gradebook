#pragma once
#include "CBaseRecordSet.h"
#include "CSchedule.h"

class ScheduledClassDatabaseInterface : public CBaseRecordSet<ScheduleClass>
{
public:
    ScheduledClassDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Schedule"), pDB)
    {
        CRecordset::m_nFields = 5;
    }

    virtual ~ScheduledClassDatabaseInterface()
    {}


    virtual void DoFieldExchange(CFieldExchange* pFX) override;

};