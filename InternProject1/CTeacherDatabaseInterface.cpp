#include "pch.h"
#include "CTeacherDatabaseInterface.h"

void TeacherDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int(pFX, _T("[ID]"), m_oData.nID);

    RFX_Text(pFX, _T("[FirstName]"), m_oData.szFirstName, m_oData.MAX_NAME_SIZE);
    RFX_Text(pFX, _T("[LastName]"), m_oData.szLastName, m_oData.MAX_NAME_SIZE);
}
