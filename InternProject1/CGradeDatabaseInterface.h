#pragma once
#include "CBaseRecordSet.h"
#include "CGrade.h"

class GradeDatabaseInterface : public CBaseRecordSet<GRADE>
{
public:
    GradeDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Grades"), pDB)
    {
        CRecordset::m_nFields = 5;
    }

    virtual ~GradeDatabaseInterface()
    {}



    virtual void DoFieldExchange(CFieldExchange* pFX) override;

};