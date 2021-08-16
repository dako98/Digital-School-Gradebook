#include "pch.h"
#include "CSubject.h"
#include "Utility.h"

SUBJECT::SUBJECT()
    :nID(-1)
    , nTeacherID(-1)
    , szName(_T(""))
    , szRoom(_T(""))
{
    Clear(*this);
}

BOOL SUBJECT::Validate() const
{
    return
        (lstrlenW(szName) > 0 &&
            lstrlenW(szRoom) > 0 &&
            nTeacherID > 0);
}