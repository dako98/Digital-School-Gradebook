#pragma once

#include <string>
#include <vector>

#include "CPerson.h"

struct STUDENT : public PERSON
{
    STUDENT();

    DBTIMESTAMP dtBirthDate;

    virtual BOOL Validate() const override;

    friend std::ostream& operator<<(std::ostream& out, const STUDENT& obj);
    friend std::istream& operator>>(std::istream& in, STUDENT& obj);

protected:
    void Read(std::istream& in);
};