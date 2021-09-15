#include "pch.h"
#include "CStudentClass.h"
#include "Utility.h"

STUDENT_CLASS::STUDENT_CLASS()
    :nID(-1)
    , szName(_T(""))
    , nTeacherNumber(-1)
{
    Clear(*this);
}

BOOL STUDENT_CLASS::Validate() const
{
    return lstrlenW(szName) > 0 &&
        nTeacherNumber > 0;
}
