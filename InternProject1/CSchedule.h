#pragma once

#include <vector>
#include <set>
#include <array>

#include "sortedVector.h"
#include "Utility.h"


struct ScheduleClass
{
    static const int MAX_LEN_CHAR_TIME = 8 + 1; // FIXME: Why does the "+1" fix the heap corruptions
                                                // during edit?! (format: hh:mm:ss)

    ScheduleClass()
        :nID(-1)
        , begin()
        , duration()
        , nSubjectID(-1)
        , dayOfWeek(-1)
        , classID(-1)
	{
        Clear(*this);
    }

    int nID;

    wchar_t begin       [MAX_LEN_CHAR_TIME + 1];
    wchar_t duration    [MAX_LEN_CHAR_TIME + 1];
	int nSubjectID;
    int dayOfWeek;
    int classID;

    bool operator< (const ScheduleClass& second) const
    {
        return StrCmpW(this->begin, second.begin) < 0;
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
            return StrCmpW(first.begin, second.begin) < 0;
        }
    };
public:
    sorted_vector<ScheduleClass> classes;
};

struct CSchedule
{
    CSchedule()
        :classID(-1)
    {
//        Clear(*this);
    }
private:
    static const int DAYS_IN_WEEK = 7;
public:

    int classID;
	std::array<ScheduleDay, DAYS_IN_WEEK> days;
};
