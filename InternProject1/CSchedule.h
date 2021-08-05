#pragma once

#include <vector>
#include <set>
#include <array>

#include "sortedVector.h"


struct ScheduleClass
{
    ScheduleClass()
        :nID(-1)
        , begin()
        , duration()
        , nSubjectID(-1)
        , dayOfWeek(-1)
        , classID(-1)
	{}

    int nID;
	DBTIME begin;
	DBTIME duration;
	int nSubjectID;
    int dayOfWeek;
    int classID;

    bool operator< (const ScheduleClass& second) const
    {
        return (this->begin.hour < second.begin.hour) || this->begin.hour == second.begin.hour && this->begin.minute < second.begin.minute;
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
            return (first.begin.hour < second.begin.hour) ||
                first.begin.hour == second.begin.hour && first.begin.minute < second.begin.minute;
        }
    };
public:
    sorted_vector<ScheduleClass> classes;
};

struct CSchedule
{
    CSchedule()
        :classID(-1)
    {}
private:
    static const int DAYS_IN_WEEK = 7;
public:

    int classID;
	std::array<ScheduleDay, DAYS_IN_WEEK> days;
};


class ScheduleClassSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    CString beginTime;
    LPSTR m_rgBeginTime;
    long* m_rgBeginTimeLengths;

    CString duration;
    LPSTR m_rgDuration;
    long* m_rgDurationLengths;

    int subjectID;
    int* m_rgSubjectID;
    long* m_rgSubjectIDLengths;

    int dayOfWeek;
    int* m_rgDayOfWeek;
    long* m_rgDayOfWeekLengths;

    int classID;
    int* m_rgClassID;
    long* m_rgClassIDLengths;

    ScheduleClassSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
