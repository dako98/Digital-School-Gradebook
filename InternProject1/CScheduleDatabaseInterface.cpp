#include "pch.h"
#include "CScheduleDatabaseInterface.h"

BOOL ScheduleDatabaseInterface::Edit(const CSchedule& recStudent)
{
    BOOL isGood = TRUE;

    for (const auto& day : recStudent.days)
    {
        for (const auto& _class : day.classes)
        {
            if (_class.nID != -1)
            {
                isGood = isGood && sClass.Edit(_class);
            }
        }
    }

    return isGood;
}

BOOL ScheduleDatabaseInterface::Load(const int classID, CSchedule& recTeacher)
{
    CSchedule result;

    result.classID = classID;
    CString filter;
    std::vector<ScheduleClass> filteredClasses;
    filter.Format(_T("[ClassID] = %d"), classID);

    if(!sClass.LoadWhere(filter, filteredClasses))
    {
        return FALSE;
    }

    for (const auto& scheduledClass : filteredClasses)
    {
        result.days[scheduledClass.dayOfWeek].classes.push_sorted(scheduledClass);
    }
    recTeacher = result;
    return TRUE;
}
