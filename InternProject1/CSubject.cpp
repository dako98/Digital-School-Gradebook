#include "pch.h"
#include "CSubject.h"

std::ostream& operator<<(std::ostream& out, const SUBJECT& obj)
{
    out << obj.nID << ' ' <<
        obj.nTeacherID << ' ' <<
        obj.szName.GetLength() << ' ' << obj.szName << ' ' <<
        obj.szRoom.GetLength() << ' ' << obj.szRoom;

    return out;
}

std::istream& operator>>(std::istream& in, SUBJECT& obj)
{
    obj.Read(in);

    return in;
}

SUBJECT::SUBJECT()
    :nID(-1)
    , nTeacherID(-1)
    , szName()
    , szRoom()
{
}

BOOL SUBJECT::Validate() const
{
    return
        (szName != "" &&
        szRoom != "" &&
        nTeacherID > 0);
}

void SUBJECT::Read(std::istream& in)
{
    in >> nID >> nTeacherID;
    ASSERT(FALSE);
    /*
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
    */
}
