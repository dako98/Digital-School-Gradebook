#pragma once

#include <unordered_map>

#include "CTeacher.h"
#include "CGrade.h"
#include "CSubject.h"
#include "CClass.h"
#include "CSchedule.h"



class IDtoNameSet : public CRecordset
{
public:

    int ID;
    int* m_rgID;
    long* m_rgIDLengths;

    CString name;
    LPSTR m_rgName;
    long* m_rgNameLengths;

    IDtoNameSet(CDatabase* pDB);

    void DoFieldExchange(CFieldExchange* pFX) override;
    void DoBulkFieldExchange(CFieldExchange* pFX) override;
};

BOOL IDtoNameMapper(
    CDatabase* database,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const std::vector<int>& id,
    std::unordered_map<int, CString>& name);

BOOL IDtoNameMapper(CDatabase* db,
    const CString& table,
    const CString& idField,
    const CString& nameField,
    const int& id,
    CString& name);

DBTIME  CStringToDBTIME(const CString& time);
CString DBTIMEToCString(const DBTIME& time);
CString DBTIMESTAMPToCString(const DBTIMESTAMP& time);
DBTIMESTAMP CStringToDBTIMESTAMP(const CString& time);
DBTIME CStringToDBTIME(const wchar_t* time);
