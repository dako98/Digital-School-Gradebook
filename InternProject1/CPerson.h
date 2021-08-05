#pragma once

#include <fstream>

struct PERSON
{
	static const int MAX_NAME_SIZE = 50;

	PERSON();

	int nID;
	CString szFirstName;
	CString szLastName;

	virtual BOOL Validate() const;

protected:
	void Read(std::istream& in);
};
