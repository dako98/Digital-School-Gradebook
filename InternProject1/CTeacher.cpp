#include "pch.h"
#include "CTeacher.h"


TEACHER::TEACHER()
	:PERSON()
{
	Clear(*this);
}

BOOL TEACHER::Validate() const
{
	return PERSON::Validate();
}
