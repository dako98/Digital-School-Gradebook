#pragma once

#include <vector>
#include <set>
#include <array>


struct ScheduleClass
{
	ScheduleClass()
		:nID(-1)
        , begin()
		, duration()
		, nSubjectID(-1)
	{}

    int nID;
	DBTIME begin;
	DBTIME duration;
	int nSubjectID;
};

struct ScheduleDay
{
	ScheduleDay() = default;

private:
    struct cmp {
        bool operator() (const ScheduleClass& first, const ScheduleClass& second) const
        {
            return (first.begin.hour < second.begin.hour) ||
                first.begin.hour == second.begin.hour && first.begin.minute < second.begin.minute;
        }
    };
public:

//	std::vector<ScheduleClass> classes;


//    auto cmp;
    std::set<ScheduleClass, cmp> classes;

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


    int* m_rgID;
    long* m_rgIDLengths;

    TIMESTAMP_STRUCT* m_rgBeginTime;
    long* m_rgBeginTimeLengths;

    TIMESTAMP_STRUCT* m_rgDuration;
    long* m_rgDurationLengths;

    int* m_rgSubjectID;
    long* m_rgSubjectIDLengths;

    int* m_rgDayOfWeek;
    long* m_rgDayOfWeekLengths;

    int* m_rgClassID;
    long* m_rgClassIDLengths;

    ScheduleClassSet(CDatabase* pDB);

    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};
class ScheduleClassSetWrapper
{
public:

    ScheduleClassSetWrapper(ScheduleClassSet* sSet);

    BOOL Add(ScheduleClass& recStudent);
    BOOL Edit(ScheduleClass& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, std::vector<ScheduleClass>& recStudent);
    BOOL Load(const int nStudentID, ScheduleClass& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<ScheduleClass>& out);

private:

    ScheduleClassSet* blk;
};

/*
class CScheduleSet
{
public:

    CScheduleSet(CDatabase* sSet);

    BOOL Add(ScheduleClass& recStudent);
    BOOL Edit(ScheduleClass& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, std::vector<ScheduleClass>& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<ScheduleClass>& out);

private:

    CScheduleSet* blk;
};
*/
/*
class CScheduleSetWrapper
{
public:

    CScheduleSetWrapper(CScheduleSet* sSet);

    BOOL Add(CSchedule& recStudent);
    BOOL Edit(CSchedule& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, std::vector<ScheduleClass>& recStudent);
    BOOL Load(const int nStudentID, ScheduleClass& recStudent);

    BOOL NextID(int& id) const;
    BOOL LoadAll(std::vector<ScheduleClass>& out);

private:

    CScheduleSet* blk;
};
*/
