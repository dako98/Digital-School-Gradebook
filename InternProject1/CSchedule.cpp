#include "pch.h"
#include "CSchedule.h"

ScheduleDay::ScheduleDay()
{
    classes.SetSorted(true);
}

BOOL ScheduleClass::Validate() const
{
    return nSubjectID >= -1 &&
        nNumberInDay > 0;
}
