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





template<class T>
Storage<T>::Storage(const std::string& path)
	:path(path)
{
	std::fstream file(path, std::ios::in | std::ios::out);

	if (!file.is_open())
	{
		throw std::exception{ std::string{"Can not access file: \"" + path + "\""}.c_str() };
	}

	file.close();
}

template<class T>
Storage<T>::~Storage()
{
}

template<class T>
BOOL Storage<T>::Add(T& recStudent)
{
	BOOL isGood = TRUE;

	if (isGood &= recStudent.Validate())
	{
		std::ofstream file(path, std::ofstream::app);

		file << recStudent << '\n';

		isGood &= file.good();
		file.close();
	}
	return isGood;
}

template<class T>
BOOL Storage<T>::Edit(T& recStudent)
{
	BOOL isGood = TRUE;

	std::vector<T> students;
	std::fstream file(path, std::ios::in);

	if (isGood && file.good())
	{
		if (isGood = _LoadAll(students, file))
		{
			int count = students.size();

			for (size_t i = 0; i < count; i++)
			{
				if (isGood && students[i].nID == recStudent.nID)
				{
					students[i] = recStudent;
				}
			}
			file.close();
			file.open(path, std::ios::out | std::ios::trunc);

			isGood = _AddBulk(students, file);
		}
	}
	file.close();

	return isGood;
}

template<class T>
BOOL Storage<T>::_AddBulk(const std::vector<T>& allStudents, std::fstream& file)
{
	BOOL isGood = TRUE;

	for (const T& student : allStudents)
	{
		if (isGood &= student.Validate())
		{

			file << student << '\n';

			isGood &= file.good();
		}
	}

	return isGood;
}

template<class T>
BOOL Storage<T>::Delete(const int nStudentID)
{
	BOOL isGood = TRUE;

	std::vector<T> students;
	std::fstream file(path, std::ios::in);

	if (isGood &= file.is_open())
	{
		if (isGood &= _LoadAll(students, file))
		{

			students.erase(std::remove_if(students.begin(), students.end(),
				[nStudentID](const T& s) {return s.nID == nStudentID; }),
				students.end());

			file.close();
			file.open(path, std::ios::out | std::ios::trunc);

			isGood &= _AddBulk(students, file);
		}
	}
	file.close();

	return isGood;
}

template<class T>
BOOL Storage<T>::Load(const int nStudentID, T& recStudent)
{
	BOOL isGood = TRUE;
	T tmp;

	std::ifstream file(path);

	if (file.is_open())
	{
		while (file.good() && file.peek() != EOF)
		{
			file >> tmp;

			if (file.good() && tmp.nID == nStudentID)
			{
				break;
			}
		}
	}
	else
	{
		isGood = FALSE;
	}

	isGood &= file.good();
	file.close();

	if (isGood && tmp.Validate())
	{
		recStudent = tmp;
	}

	return isGood;
}

template<class T>
inline int Storage<T>::LastID() const
{
	std::ifstream file(path);
	int lastID = 0;
	T tmp;
	while (file >> tmp)
	{
		lastID = max(lastID, tmp.nID);
	}
	file.close();

	return lastID;
}

template<class T>
inline BOOL Storage<T>::LoadAll(std::vector<T>& out)
{
	std::fstream file(path, std::ios::in);
	if (file.is_open())
	{
		_LoadAll(out, file);
	}
	file.close();
	return TRUE;
}

template<class T>
BOOL Storage<T>::_LoadAll(std::vector<T>& allStudents, std::fstream& file)
{
	BOOL isGood = TRUE;
	T tmp;

	allStudents.clear();

	if (file.good())
	{
		int count;

		while (file.good() && file.peek() != EOF)
		{
			file >> tmp;
			file.ignore(1);

			if (file.good() && tmp.Validate())
			{
				allStudents.push_back(tmp);
			}
			else
			{
				isGood = FALSE;
				break;
			}
		}
	}
	else
	{
		isGood = FALSE;
	}

	return isGood;
}