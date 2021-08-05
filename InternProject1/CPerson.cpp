#include "pch.h"
#include "CPerson.h"


PERSON::PERSON()
	:nID(-1)
	, szFirstName("")
	, szLastName("")
{
}

BOOL PERSON::Validate() const
{
	return 
		(szFirstName != "" &&
		szLastName != "");
}