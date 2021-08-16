#pragma once
#include "CBaseRecordSet.h"
#include "CClass.h"

class ClassesDatabaseInterface : public CBaseRecordSet<CClass>
{
public:
    ClassesDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Classes"), pDB)
    {
        CRecordset::m_nFields = 3;
    }

    virtual ~ClassesDatabaseInterface()
    {}



    virtual void DoFieldExchange(CFieldExchange* pFX) override;

};