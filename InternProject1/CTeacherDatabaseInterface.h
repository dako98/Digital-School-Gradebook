#pragma once
#include "CBaseRecordSet.h"
#include "CTeacher.h"

class TeacherDatabaseInterface : public CBaseRecordSet<TEACHER>
{
public:
    TeacherDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Teachers"), pDB)
    {
        CRecordset::m_nFields = 3;
    }

    virtual ~TeacherDatabaseInterface()
    {}



    virtual void DoFieldExchange(CFieldExchange* pFX) override;

};