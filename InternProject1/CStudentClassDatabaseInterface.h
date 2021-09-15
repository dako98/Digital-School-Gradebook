#pragma once
#include "CBaseRecordSet.h"
#include "CStudentClass.h"
//#include "CStudentClass.h"

class StudentClassDatabaseInterface : public CBaseRecordSet<STUDENT_CLASS>
{
public:
    StudentClassDatabaseInterface(CDatabase* pDB)
        :CBaseRecordSet(_T("Classes"), pDB)
    {
        CRecordset::m_nFields = 3;
    }

    virtual ~StudentClassDatabaseInterface()
    {}

    virtual void DoFieldExchange(CFieldExchange* pFX) override;
};