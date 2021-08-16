#pragma once
#include "CBaseRecordSet.h"
#include "CScheduledClassDatabaseInterface.h"
#include "CSchedule.h"

class ScheduleDatabaseInterface
{
public:
    ScheduleDatabaseInterface(CDatabase* db)
        :sClass(db)
    {}
    virtual ~ScheduleDatabaseInterface()
    {}

    virtual BOOL Edit(const CSchedule& recTeacher);
    virtual BOOL Load(const int classID, CSchedule& recTeacher);

private:

    ScheduledClassDatabaseInterface sClass;
};