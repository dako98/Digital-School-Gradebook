#pragma once
#include "CBaseRecordSet.h"
#include "CStudent.h"

class StudentDatabaseInterface : public CBaseRecordSet<STUDENT>
{
public:
    StudentDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Students"), pDB)
    {
        CRecordset::m_nFields = 6;
    }

    virtual ~StudentDatabaseInterface()
    {}



    virtual void DoFieldExchange(CFieldExchange* pFX) override;

};