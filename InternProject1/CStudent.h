#pragma once

#include <string>
#include <vector>

#include "CPerson.h"

struct STUDENT : public PERSON
{
    STUDENT();

    DBTIMESTAMP dtBirthDate;
    int classID;
    int numberInClass;

    virtual BOOL Validate() const override;

protected:
    void Read(std::istream& in);
};