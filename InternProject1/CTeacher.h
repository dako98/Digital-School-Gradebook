#pragma once

#include <fstream>

#include "CPerson.h"
#include "Utility.h"


struct TEACHER : public PERSON
{
	TEACHER();

	BOOL Validate() const;

protected:
	void Read(std::istream& in);
};
