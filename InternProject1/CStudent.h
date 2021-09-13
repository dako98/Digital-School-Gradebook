#pragma once

#include "CPerson.h"

struct STUDENT : public PERSON
{
    STUDENT();

    TIMESTAMP_STRUCT dtBirthDate;
    int classID;
    int numberInClass;

    BOOL Validate() const;
};