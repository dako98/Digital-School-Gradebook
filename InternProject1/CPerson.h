#pragma once

#include <fstream>
#include "Utility.h"

struct PERSON
{
	static const int MAX_NAME_SIZE = 20;

	PERSON();

	int nID;

	wchar_t szFirstName[MAX_NAME_SIZE + 1];
	wchar_t szLastName[MAX_NAME_SIZE + 1];
	
	BOOL Validate() const;

protected:
	void Read(std::istream& in);
};
