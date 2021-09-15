#pragma once
#include <afxdb.h>
#include <vector>

template<class T>
class CBaseRecordSet : public CRecordset
{
public:
    CBaseRecordSet(const std::wstring& lpszTableName, CDatabase* pDB)
        : CRecordset(pDB)
    {
        CRecordset::m_strTableName = lpszTableName.c_str();
    }
    virtual ~CBaseRecordSet()
    {
    }

public:
    virtual BOOL Add(T& input);

    virtual BOOL Edit(const T& input);
    virtual BOOL Delete(const int id);
    virtual BOOL Load(const int ID, T& result);

    virtual BOOL LastID(int& id);
    virtual BOOL LoadAll(std::vector<T>& out);
    virtual BOOL LoadWhere(const CString& filter, std::vector<T>& out);

    virtual void DoFieldExchange(CFieldExchange* pFX) = 0;

    T m_oData;
};


template<class T>
BOOL CBaseRecordSet<T>::Add(T& input)
{
    try
    {
        if (!CRecordset::Open(CRecordset::dynaset, CRecordset::m_strTableName, CRecordset::appendOnly))
        {
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        return FALSE;
    }

    if (!CRecordset::CanAppend())
    {
        CRecordset::Close();
        return FALSE;
    }

    CRecordset::AddNew();

    m_oData = input;

    try
    {
        if (!CRecordset::Update())
        {
            CRecordset::Close();
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        CRecordset::Close();
        return FALSE;
    }

    CRecordset::Close();

    return TRUE;
}

template<class T>
BOOL CBaseRecordSet<T>::Edit(const T& input)
{
    CRecordset::m_strFilter.Format(_T("[ID] = %d"), input.nID);

    try
    {
        if (!CRecordset::Open(CRecordset::dynaset, CRecordset::m_strTableName, CRecordset::none))
        {
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        return FALSE;
    }

    assert(CRecordset::GetRowsFetched() == 1, "Got more rows than expected");

    if (CRecordset::GetRowsFetched() > 1)
    {
        CRecordset::Close();
        throw std::length_error("ID is not unique!");
    }

    if (memcmp(&m_oData, &input, sizeof(input)) == 0)
    {
        CRecordset::Close();
        return TRUE;
    }

    CRecordset::Edit();

    m_oData = input;

    try
    {
        if (!CRecordset::Update())
        {
            CRecordset::Close();
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        CRecordset::Close();
        return FALSE;
    }

    CRecordset::Close();

    return TRUE;
}

template<class T>
BOOL CBaseRecordSet<T>::Delete(const int id)
{
    CRecordset::m_strFilter.Format(_T("[ID] = %d"), id);

    try
    {
        if (!CRecordset::Open(CRecordset::dynaset, CRecordset::m_strTableName, CRecordset::none))
        {
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        return FALSE;
    }

    assert(CRecordset::GetRowsFetched() == 1, "Got more rows than expected");

    if (CRecordset::GetRowsFetched() > 1)
    {
        CRecordset::Close();
        throw std::length_error("ID is not unique!");
    }

    try
    {
        CRecordset::Delete();
        CRecordset::MoveNext();
    }
    catch (const CDBException&)
    {
        CRecordset::Close();
        return FALSE;
    }

    CRecordset::Close();

    return TRUE;
}

template<class T>
BOOL CBaseRecordSet<T>::Load(const int ID, T& result)
{
    CString filter;
    filter.Format(_T("[ID] = %d"), ID);
    std::vector<T> response;

    if (!LoadWhere(filter, response))
    {
        return FALSE;
    }

    assert(response.size() <= 1, "ID is not unique!");

    result = ((response.size() >= 1) ? response[0] : result);

    return TRUE;
}

template<class T>
BOOL CBaseRecordSet<T>::LastID(int& id)
{
    id = -1;
    CRecordset rs{ CRecordset::m_pDatabase };
    try
    {
        if (!rs.Open(CRecordset::forwardOnly, _T("select @@IDENTITY as last_id"), CRecordset::readOnly))
        {
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        return FALSE;
    }

    assert(rs.GetRowsFetched() == 1, "Did not receive 1 row as answer.");
    CString strLastID;


    rs.GetFieldValue(_T("last_id"), strLastID);
    rs.Close();

    if (strLastID == "")
    {
        return FALSE;
    }

    id = _wtoi(strLastID);

    return TRUE;
}

template<class T>
BOOL CBaseRecordSet<T>::LoadAll(std::vector<T>& out)
{
    return LoadWhere(_T(""), out);
}

template<class T>
BOOL CBaseRecordSet<T>::LoadWhere(const CString& filter, std::vector<T>& out)
{
    out.clear();
    CRecordset::m_strFilter = filter;

    try
    {
        if (!CRecordset::Open(CRecordset::forwardOnly, CRecordset::m_strTableName, CRecordset::readOnly))
        {
            return FALSE;
        }
    }
    catch (const CDBException&)
    {
        return FALSE;
    }

    T tmp;

    while (!CRecordset::IsEOF())
    {
        tmp = m_oData;

        if (tmp.Validate())
        {
            out.push_back(tmp);
        }
        else
        {
            CRecordset::Close();
            return FALSE;
        }

        CRecordset::MoveNext();
    }
    CRecordset::Close();

    return TRUE;
}

