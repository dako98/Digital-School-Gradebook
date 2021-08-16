#include "pch.h"
#include "CGradeDatabaseInterface.h"

void GradeDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           m_oData.nID);

    RFX_Int     (pFX, _T("[StudentID]"),    m_oData.nStudentID);
    RFX_Int     (pFX, _T("[SubjectID]"),    m_oData.nSubjectID);
    RFX_Date    (pFX, _T("[Date]"),         m_oData.dtDate);
    RFX_Int     (pFX, _T("[Value]"),        m_oData.value);
}