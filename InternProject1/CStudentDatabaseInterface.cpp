#include "pch.h"

#include "CStudentDatabaseInterface.h"

void StudentDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),               m_oData.nID);

    RFX_Int     (pFX, _T("[NumberInClass]"),    m_oData.numberInClass);
    RFX_Text    (pFX, _T("[FirstName]"),        m_oData.szFirstName,    m_oData.MAX_NAME_SIZE);
    RFX_Text    (pFX, _T("[LastName]"),         m_oData.szLastName,     m_oData.MAX_NAME_SIZE);
    RFX_Date    (pFX, _T("[Birthday]"),         m_oData.dtBirthDate);
    RFX_Int     (pFX, _T("[ClassID]"),          m_oData.classID);
}