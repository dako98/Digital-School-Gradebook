#include "pch.h"
#include "CSubject.h"

SUBJECT::SUBJECT()
    :nID(-1)
    , nTeacherID(-1)
    , szName()
    , szRoom()
{
}

BOOL SUBJECT::Validate() const
{
    return
        (szName != "" &&
        szRoom != "" &&
        nTeacherID > 0);
}