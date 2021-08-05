#include "pch.h"
#include "CTeacher.h"


TEACHER::TEACHER()
	:PERSON()
{
}

BOOL TEACHER::Validate() const
{
	return PERSON::Validate();
}
