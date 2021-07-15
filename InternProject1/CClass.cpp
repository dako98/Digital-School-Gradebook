#include "pch.h"
#include "CClass.h"

CClass::CClass()
    :ID(-1)
    , name()
    , teacherID(-1)
{
}

BOOL CClass::Validate() const
{
    return ID > 0 &&
        name != "" &&
        teacherID > 0;
}
