#pragma once

#include "pch.h"

#include <fstream>
#include <vector>

/**
* Requires:
* - operator<< 
* - operator>>
* - Validate()
* - default ctor
*/
template<class T>
class Storage
{
public:
    Storage(const std::string& path);
    virtual ~Storage();

public:
    BOOL Add(T& recStudent);
    BOOL Edit(T& recStudent);
    BOOL Delete(const int nID);
    BOOL Load(const int nStudentID, T& recStudent);

	int LastID() const;
	BOOL LoadAll(std::vector<T>& out);

private:
    BOOL _LoadAll(std::vector<T>& allStudents, std::fstream& file);
    BOOL _AddBulk(const std::vector<T>& allStudents, std::fstream& file);

private:
    const std::string path;
};


#include "Storage.c++"