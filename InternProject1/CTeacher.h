#pragma once

#include <fstream>

#include "CPerson.h"


struct TEACHER : public PERSON
{
	virtual BOOL Validate() const override;

	friend std::ostream& operator<<(std::ostream& out, const TEACHER& obj);
	friend std::istream& operator>>(std::istream& in, TEACHER& obj);

//	virtual std::ostream& operator<<(std::ostream& out) const override;
//	virtual std::istream& operator>>(std::istream& in) override;

};
