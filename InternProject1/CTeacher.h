#pragma once

#include <fstream>

#include "CPerson.h"


struct TEACHER : public PERSON
{
	TEACHER();

	virtual BOOL Validate() const override;

protected:
	void Read(std::istream& in);
};
