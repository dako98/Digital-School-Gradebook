#include "pch.h"
#include "CSubjectDatabaseInterface.h"

void SubjectDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int(pFX, _T("[ID]"), m_oData.nID);

    RFX_Text(pFX, _T("[Name]"), m_oData.szName, m_oData.MAX_NAME_SIZE);
    RFX_Int(pFX, _T("[TeacherID]"), m_oData.nTeacherID);
    RFX_Text(pFX, _T("[RoomName]"), m_oData.szRoom, m_oData.MAX_NAME_SIZE);
}
