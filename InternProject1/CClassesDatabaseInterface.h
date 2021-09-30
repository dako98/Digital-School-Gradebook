#pragma once
#include "CBaseRecordSet.h"
#include "CStudentClass.h"

class ClassesDatabaseInterface : public CBaseRecordSet<STUDENT_CLASS>
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