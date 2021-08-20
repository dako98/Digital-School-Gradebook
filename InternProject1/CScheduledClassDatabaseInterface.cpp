#include "pch.h"
#include "CScheduledClassDatabaseInterface.h"

void ScheduledClassDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),           m_oData.nID);

    RFX_Text    (pFX, _T("[Begin]"),        m_oData.begin,      m_oData.MAX_LEN_CHAR_TIME);
    RFX_Text    (pFX, _T("[Duration]"),     m_oData.duration,   m_oData.MAX_LEN_CHAR_TIME);
    RFX_Int     (pFX, _T("[SubjectID]"),    m_oData.nSubjectID);
    RFX_Int     (pFX, _T("[DayOfWeek]"),    m_oData.dayOfWeek);
    RFX_Int     (pFX, _T("[ClassID]"),      m_oData.classID);
}