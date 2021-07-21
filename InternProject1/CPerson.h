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

	friend std::ostream& operator<<(std::ostream& out, const PERSON& obj);
	friend std::istream& operator>>(std::istream& in, PERSON& obj);

protected:
	void Read(std::istream& in);
};
