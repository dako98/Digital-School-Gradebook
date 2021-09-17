#include "pch.h"
#include "CScheduledClassDatabaseInterface.h"

void ScheduledClassDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           m_oData.nID);

    RFX_Int     (pFX, _T("[Number]"),       m_oData.nNumberInDay);
    RFX_Int     (pFX, _T("[SubjectID]"),    m_oData.nSubjectID);
    RFX_Int     (pFX, _T("[DayOfWeek]"),    m_oData.dayOfWeek);
    RFX_Int     (pFX, _T("[ClassID]"),      m_oData.classID);
}