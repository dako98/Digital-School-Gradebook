#include "pch.h"
#include "CScheduleDatabaseInterface.h"

BOOL ScheduleDatabaseInterface::Edit(const CSchedule& recStudent)
{
    BOOL isGood = TRUE;

    int size = recStudent.days.size();

    for (int dayOfWeek = 0; dayOfWeek < size; dayOfWeek++)
    {
        for (const auto& _class : recStudent.days[dayOfWeek].classes)
        {
            if (_class.nID != -1)
            {
                sClass.Edit(_class);
            }
        }
    }

    return isGood;
}

BOOL ScheduleDatabaseInterface::Load(const int classID, CSchedule& recTeacher)
{
    BOOL isGood = TRUE;
    CSchedule result;

    result.classID = classID;
    CString filter;
    std::vector<ScheduleClass> filteredClasses;
    filter.Format(_T("[ClassID] = %d"), classID);
    isGood = sClass.LoadWhere(filter, filteredClasses);

    if (!isGood)
    {
        return FALSE;
    }

    for (const auto& scheduledClass : filteredClasses)
    {
        result.days[scheduledClass.dayOfWeek].classes.push_sorted(scheduledClass);
    }
    recTeacher = result;
    return isGood;
}
