#include "pch.h"
#include "CSubject.h"

std::ostream& operator<<(std::ostream& out, const SUBJECT& obj)
{
    out << obj.nID << ' ' <<
        strlen(obj.szName) << ' ' << obj.szName << '\n';

    return out;
}

std::istream& operator>>(std::istream& in, SUBJECT& obj)
{
    SUBJECT tmp;

    in >> tmp.nID;

    if (in.good())
    {
        int len;
        in >> len;

        if (in.good())
        {
            if (len <= SUBJECT::MAX_NAME_SIZE)
            {
                in.ignore(1);

                in.getline(tmp.szName, len);

                if (in.good())
                {
                    obj = tmp;
                }
            }
            else
            {
                in.setstate(std::ios_base::failbit);
            }
        }
    }
	return in;
}

BOOL SUBJECT::Validate() const
{
    return (strcmp(szName, "") != 0 && strlen(szName) <= MAX_NAME_SIZE &&
        nID > 0 &&
        strcmp(szRoom, "") != 0 && strlen(szRoom) <= MAX_NAME_SIZE &&
        nTeacherID > 0);
}
