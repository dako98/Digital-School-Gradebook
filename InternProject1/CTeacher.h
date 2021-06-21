#pragma once

#include <fstream>

#include "CPerson.h"


struct TEACHER : public PERSON
{
	TEACHER();

	virtual BOOL Validate() const override;

	friend std::ostream& operator<<(std::ostream& out, const TEACHER& obj);
	friend std::istream& operator>>(std::istream& in, TEACHER& obj);

protected:
	void Read(std::istream& in);
};
