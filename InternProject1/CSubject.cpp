#include "pch.h"
#include "CSubject.h"

std::ostream& operator<<(std::ostream& out, const SUBJECT& obj)
{
    out << obj.nID << ' ' <<
        obj.nTeacherID << ' ' <<
        strlen(obj.szName) << ' ' << obj.szName << ' ' <<
        strlen(obj.szRoom) << ' ' << obj.szRoom;

    return out;
}

std::istream& operator>>(std::istream& in, SUBJECT& obj)
{
    obj.Read(in);

    return in;
}

SUBJECT::SUBJECT()
    :nID(-1)
    ,nTeacherID(-1)
{
    szName[0] = '\0';
    szRoom[0] = '\0';
}

BOOL SUBJECT::Validate() const
{
    return (strcmp(szName, "") != 0 && strlen(szName) <= MAX_NAME_SIZE &&
        nID > 0 &&
        strcmp(szRoom, "") != 0 && strlen(szRoom) <= MAX_NAME_SIZE &&
        nTeacherID > 0);
}

void SUBJECT::Read(std::istream& in)
{
    in >> nID >> nTeacherID;

    if (in.good())
    {
        int len;
        in >> len;

        if (in.good())
        {
            if (len <= SUBJECT::MAX_NAME_SIZE)
            {
                in.ignore(1);

                in.read(szName, len);
                szName[len] = '\0';
            }
            else
            {
                in.setstate(std::ios_base::failbit);
            }
        }

        in >> len;
        if (in.good())
        {
            if (len <= SUBJECT::MAX_NAME_SIZE)
            {
                in.ignore(1);

                in.read(szRoom, len);
                szRoom[len] = '\0';
            }
            else
            {
                in.setstate(std::ios_base::failbit);
            }
        }
    }
}
