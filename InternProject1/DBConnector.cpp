#include "pch.h"
#include "DBConnector.h"

#include <sstream>

CString DBTIMEToCString(const DBTIME& time)
{
    CString result;
    result.Format(_T("%02d:%02d:%02d"), time.hour, time.minute, time.second);
    return result;
}

DBTIME CStringToDBTIME(const CString& time)
{
    if (time == "")
    {
        throw std::invalid_argument("Empty string.");
    }

    DBTIME result;
    std::wstringstream ss(time.GetString());

    ss >> result.hour;
    ss.ignore();

    ss >> result.minute;
    ss.ignore();

    ss >> result.second;

    return result;
}

DBTIME CStringToDBTIME(const wchar_t* time)
{
    if (time == nullptr)
    {
        throw std::invalid_argument("Empty string.");
    }

    DBTIME result;
    std::wstringstream ss(time);

    ss >> result.hour;
    ss.ignore();

    ss >> result.minute;
    ss.ignore();

    ss >> result.second;

    return result;
}


CString DBTIMESTAMPToCString(const DBTIMESTAMP& time)
{
    CString result;
    result.Format(_T("%d-%02d-%02d %02d:%02d:%02d:%02d"), time.year, time.month, time.day, time.hour, time.minute, time.second, time.fraction);
    return result;
}


DBTIMESTAMP CStringToDBTIMESTAMP(const CString& time)
{
    if (time == "")
    {
        throw std::invalid_argument("Empty string.");
    }

    DBTIMESTAMP result;
    std::wstringstream ss(time.GetString());

    ss >> result.year;
    ss.ignore();

    ss >> result.month;
    ss.ignore();

    ss >> result.day;
    ss.ignore();

    ss >> result.hour;
    ss.ignore();

    ss >> result.minute;
    ss.ignore();

    ss >> result.second;
    ss.ignore();

    ss >> result.fraction;

    return result;
}

IDtoNameSet::IDtoNameSet(CDatabase* pDB)
    : CRecordset(pDB)
{
    constexpr int cntBefore = __COUNTER__;


    ID                      = -1; __COUNTER__;
    m_rgID                  = NULL;
    m_rgIDLengths           = NULL;

    name                    = ""; __COUNTER__;
    m_rgName                = NULL;
    m_rgNameLengths         = NULL;

    constexpr int count = (__COUNTER__ - cntBefore - 1);

    m_nFields               = count;
}
void IDtoNameSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int (pFX, _T("[ID]"),   ID);
    RFX_Text(pFX, _T("[Name]"), name);
}
void IDtoNameSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);

    RFX_Int_Bulk    (pFX, _T("[ID]"),   &m_rgID,    &m_rgIDLengths);
    RFX_Text_Bulk   (pFX, _T("[Name]"), &m_rgName,  &m_rgNameLengths, 256);
}


BOOL IDtoNameMapper(CDatabase* db,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const std::vector<int>& ids,
    std::unordered_map<int, CString>& map)
{
    unsigned int idsCount = ids.size();

    BOOL isOK = idsCount > 0;

        if (isOK)
        {
            CString sSQL;
            sSQL.Format(_T("SELECT [%s], [%s] FROM [%s] WHERE [%s] IN ("), idField, nameField, table, idField);
            unsigned int len = 0;
            for (int id : ids)
            {
                len += DigitsCount(id);
                len += sizeof(",") - 1;
            }
            len += 1;   // For '\0'

            sSQL.Preallocate(len);

            for (size_t i = 0; i < idsCount - 1; i++)
            {
                sSQL.AppendFormat(_T("%d,"), ids[i]);
            }
            sSQL.AppendFormat(_T("%d)"), ids[idsCount - 1]);

            // Begin reading all records
            IDtoNameSet blk(db);

            try
            {
                blk.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::useMultiRowFetch);
            }
            catch (const std::exception&)
            {
                isOK = FALSE;
            }

            if (isOK)
            {
                int rowsFetched = blk.GetRowsFetched();
                while (!blk.IsEOF())
                {
                    for (int nPosInRowset = 0; nPosInRowset < rowsFetched; nPosInRowset++)
                    {
                        int id = *(blk.m_rgID + nPosInRowset);
                        CString name = CString{ blk.m_rgName + nPosInRowset * 256 };

                        map[id] = name;
                    }
                    blk.MoveNext();
                }
            }// !Getting fields

            blk.Close();

        }// !Creating SQL querry

    return isOK;
}

BOOL IDtoNameMapper(CDatabase* db,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const int& id,
    CString& name)
{
    BOOL isOK = TRUE;
    
    CString sSQL;
    sSQL.Format(_T("SELECT [%s], [%s] FROM [%s] WHERE [%s] = %d"), idField, nameField, table, idField, id);

    IDtoNameSet rs(db);

    try
    {
        rs.Open(AFX_DB_USE_DEFAULT_TYPE, sSQL, CRecordset::readOnly);
    }
    catch (const std::exception&)
    {
        isOK = FALSE;
    }

    if (isOK)
    {
        ASSERT(rs.GetRowsFetched() == 1);

        name = rs.name;
        rs.Close();
    }

    return isOK;
}
