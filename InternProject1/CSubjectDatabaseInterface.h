#pragma once
#include "CBaseRecordSet.h"
#include "CSubject.h"

class SubjectDatabaseInterface : public CBaseRecordSet<SUBJECT>
{
public:
    SubjectDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Subjects"), pDB)
    {
        CRecordset::m_nFields = 4;
    }

    virtual ~SubjectDatabaseInterface()
    {}



    virtual void DoFieldExchange(CFieldExchange* pFX) override;

};