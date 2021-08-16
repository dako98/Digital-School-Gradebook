#include "pch.h"
#include "CPerson.h"
#include "Utility.h"


PERSON::PERSON()
	:nID(-1)
	, szFirstName(_T(""))
	, szLastName(_T(""))
{
	Clear(*this);
}

BOOL PERSON::Validate() const
{
	return
		(lstrlenW(szFirstName) > 0 &&
			lstrlenW(szLastName) > 0);
}