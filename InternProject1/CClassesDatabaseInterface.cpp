#include "pch.h"
#include "CClassesDatabaseInterface.h"

void ClassesDatabaseInterface::DoFieldExchange(CFieldExchange* pFX)
{    
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int     (pFX, _T("[ID]"),               m_oData.nID);

    RFX_Text    (pFX, _T("[Name]"),             m_oData.szName,     m_oData.MAX_NAME_SIZE);
    RFX_Int     (pFX, _T("[ClassTeacherID]"),   m_oData.teacherID);
}