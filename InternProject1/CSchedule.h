#pragma once

#include <vector>
#include <set>
#include <array>

#include "sortedVector.h"
#include "Utility.h"


struct ScheduleClass
{

    ScheduleClass()
        :nID(-1)
        , nNumberInDay(0)
        , nSubjectID(-1)
        , dayOfWeek(-1)
        , classID(-1)
    {
        Clear(*this);
    }

    int nID;

    int nNumberInDay;
	int nSubjectID;
    int dayOfWeek;
    int classID;

    bool operator< (const ScheduleClass& second) const
    {
        return this->nNumberInDay < second.nNumberInDay;
    }
    BOOL Validate() const;
};

struct ScheduleDay
{
	ScheduleDay();

private:
    struct cmp {
        bool operator() (const ScheduleClass& first, const ScheduleClass& second) const
        {
            return first.nNumberInDay < second.nNumberInDay;
        }
    };
public:
    sorted_vector<ScheduleClass> classes;
};

struct CSchedule
{
    CSchedule()
        :classID(-1)
    { }
    static const int DAYS_IN_WEEK = 7;

    int classID;
	std::array<ScheduleDay, DAYS_IN_WEEK> days;
};
