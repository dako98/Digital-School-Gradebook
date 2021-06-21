#pragma once

#include <fstream>

struct PERSON
{
	static const int MAX_NAME_SIZE = 50;

	char szFirstName[MAX_NAME_SIZE + 1];
	char szLastName[MAX_NAME_SIZE + 1];
	int nID;

	virtual BOOL Validate() const;

	friend std::ostream& operator<<(std::ostream& out, const PERSON& obj);
	friend std::istream& operator>>(std::istream& in, PERSON& obj);

protected:
	void Read(std::istream& in);
//	virtual std::ostream& operator<<(std::ostream& out) const;
//	virtual std::istream& operator>>(std::istream& in);

};
