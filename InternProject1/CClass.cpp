#include "pch.h"
#include "CClass.h"
#include "Utility.h"


CClass::CClass()
    :nID(-1)
    , szName()
    , teacherID(-1)
{
    Clear(*this);
}

BOOL CClass::Validate() const
{
    return (lstrlenW(szName) > 0 &&
        teacherID > 0);
}
