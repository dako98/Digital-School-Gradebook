#include "pch.h"
#include "CClass.h"

BOOL CClass::Validate() const
{
    return ID > 0 &&
        name != "" &&
        teacherID > 0;
}
