#include "pch.h"
#include "CStudent.h"

#include <fstream>
#include <vector>

static const int MAX_NAME_SIZE = 50;

CStudent::CStudent(const std::string& path)
	:path(path)
{
}

CStudent::~CStudent()
{
}

BOOL CStudent::Add(STUDENT& recStudent)
{
	BOOL isGood = TRUE;

	if (recStudent.Validate())
	{
		std::ofstream file(path, std::ofstream::app);

		file << recStudent.nID << ',' <<
			strlen(recStudent.szFirstName) << " " << recStudent.szFirstName << ',' <<
			strlen(recStudent.szLastName) << " " << recStudent.szLastName << ',' <<
			recStudent.dtBirthDate.year << ' ' << recStudent.dtBirthDate.month << ' ' << recStudent.dtBirthDate.day << '\n';

		isGood &= file.good();
		file.close();
	}
	return isGood;
}

BOOL CStudent::Edit(STUDENT& recStudent)
{
	BOOL isGood = TRUE;

	std::vector<STUDENT> students;
	std::fstream file(path, std::fstream::trunc);

	if (isGood &= file.is_open())
	{
		if (isGood &= _LoadAll(students, file))
		{
			int count = students.size();

			for (size_t i = 0; i < count; i++)
			{
				if (isGood && students[i].nID == recStudent.nID)
				{
					students[i] = recStudent;
				}
			}
			isGood &= _AddBulk(students, file);
		}
	}
	file.close();

	return isGood;
}

BOOL CStudent::_AddBulk(const std::vector<STUDENT>& allStudents, std::fstream& file)
{
	BOOL isGood = TRUE;

	for (const STUDENT& student : allStudents)
	{
		if (isGood && student.Validate())
		{

			file << student.nID << ',' <<
				strlen(student.szFirstName) << " " << student.szFirstName << ',' <<
				strlen(student.szLastName) << " " << student.szLastName << ',' <<
				student.dtBirthDate.year << ' ' << student.dtBirthDate.month << ' ' << student.dtBirthDate.day << '\n';

			isGood &= file.good();
		}
	}
	file.close();

	return isGood;
}

BOOL CStudent::Delete(const int nStudentID)
{
	BOOL isGood = TRUE;

	std::vector<STUDENT> students;
	std::fstream file(path, std::fstream::trunc);

	if (isGood &= file.is_open())
	{
		if (isGood &= _LoadAll(students, file))
		{
			int count = students.size();

			for (size_t i = 0; i < count; i++)
			{
				if (isGood && students[i].nID == nStudentID)
				{
					students.erase(students.begin() + i);
				}
			}
			isGood &= _AddBulk(students, file);
		}
	}
	file.close();

	return isGood;
}

BOOL CStudent::Load(const int nStudentID, STUDENT& recStudent)
{
	BOOL isGood = TRUE;

	std::ifstream file(path, std::ifstream::app);
	//file.open(path, std::ios::in);

		STUDENT tmp;
	if (file.is_open())
	{
		int count;

		while (file.peek() != EOF)
		{
			file >> tmp.nID;

			if (file.good())
			{
				if (tmp.nID == nStudentID)
				{
					file >> count;

					// Validate name lenght
					if (file.good() && count <= MAX_NAME_SIZE)
					{
						// Get name
						file.getline(tmp.szFirstName, count);

						// Check format
						if (file.peek() == ',')
						{
							file.ignore(1);
						}
						else
						{
							isGood = FALSE;
							break;
						}
					} // !First name

					file >> count;
					// Validate name lenght
					if (file.good() && count <= MAX_NAME_SIZE)
					{
						// Get name
						file.getline(tmp.szLastName, count);

						// Check format
						if (file.peek() == ',')
						{
							file.ignore(1);
						}
						else
						{
							isGood = FALSE;
							break;
						}
					}// !Last name

					// Birth date
					file >> tmp.dtBirthDate.year >> tmp.dtBirthDate.month >> tmp.dtBirthDate.day;
					if (file.good())
					{
						file.ignore(1);
					}
					else
					{
						isGood = FALSE;
						break;
					}
				}// !Right number
				else
				{
					// Skip row
					file.ignore(LLONG_MAX, '\n');
				}
			}// !Read number
		}// !While
	}// !File is open
	isGood &= file.good();
	file.close();

	if (isGood && tmp.Validate())
	{
		recStudent = tmp;
	}

	return isGood;
}

BOOL CStudent::_LoadAll(std::vector<STUDENT>& allStudents, std::fstream& file)
{
	BOOL isGood = TRUE;

	allStudents.clear();

	STUDENT tmp;
	if (file.is_open())
	{
		int count;

		while (file.peek() != EOF)
		{
			file >> tmp.nID;

			if (file.good())
			{
				file >> count;

				// Validate name lenght
				if (file.good() && count <= MAX_NAME_SIZE)
				{
					// Get name
					file.getline(tmp.szFirstName, count);

					// Check format
					if (file.peek() == ',')
					{
						file.ignore(1);
					}
					else
					{
						isGood = FALSE;
						break;
					}
				} // !First name

				file >> count;
				// Validate name lenght
				if (file.good() && count <= MAX_NAME_SIZE)
				{
					// Get name
					file.getline(tmp.szLastName, count);

					// Check format
					if (file.peek() == ',')
					{
						file.ignore(1);
					}
					else
					{
						isGood = FALSE;
						break;
					}
				}// !Last name

				// Birth date
				file >> tmp.dtBirthDate.year >> tmp.dtBirthDate.month >> tmp.dtBirthDate.day;
				if (file.good())
				{
					file.ignore(1);
				}
				else
				{
					isGood = FALSE;
					break;
				}
			}// !Read number
			else
			{
				isGood = FALSE;
				break;
			}

			if (isGood && tmp.Validate())
			{
				allStudents.push_back(tmp);
			}

		}// !While not EOF
	}// !File is open
	else
	{
		isGood = FALSE;
	}

	isGood &= file.good();
	file.close();

	return isGood;
}

STUDENT::STUDENT()
	:PERSON()
	,dtBirthDate()
{
}

BOOL STUDENT::Validate() const
{
	return (PERSON::Validate() &&
		dtBirthDate.year < COleDateTime::GetCurrentTime().GetYear());
}

/*
std::ostream& operator<<(std::ostream& out, const STUDENT& obj)
{
	out << obj.nID << ',' <<
		strlen(obj.szFirstName) << ' ' << obj.szFirstName << ',' <<
		strlen(obj.szLastName) << ' ' << obj.szLastName << ',' <<
		obj.dtBirthDate.year << ' ' << obj.dtBirthDate.month << ' ' << obj.dtBirthDate.day << '\n';

	return out;
}
*/

std::ostream& operator<<(std::ostream& out, const STUDENT& obj)
{
	out << (PERSON)obj << ' ' <<
		obj.dtBirthDate.year << ' ' << obj.dtBirthDate.month << ' ' << obj.dtBirthDate.day;

	return out;
}

/*
std::istream& operator>>(std::istream& in, STUDENT& obj)
{
	STUDENT tmp;

	in >> tmp.nID;

	if (in.good())
	{
		int count;
		in >> count;

		// Validate name lenght
		if (in.good() && count <= MAX_NAME_SIZE)
		{
			// Get name
			in.getline(tmp.szFirstName, count);

			// Check format
			if (in.good() && in.peek() == ',')
			{
				in.ignore(1);
			}
			else
			{
				in.setstate(std::ios_base::failbit);
			}
		} // !First name
		else
		{
			in.setstate(std::ios_base::failbit);
		}

		if (in.good())
		{
			in >> count;
			// Validate name lenght
			if (in.good() && count <= MAX_NAME_SIZE)
			{
				// Get name
				in.getline(tmp.szLastName, count);

				// Check format
				if (in.good() && in.peek() == ',')
				{
					in.ignore(1);
				}
				else
				{
					in.setstate(std::ios_base::failbit);
				}
			}// !Last name
			else
			{
				in.setstate(std::ios_base::failbit);
			}
		}
		// Birth date
		in >> tmp.dtBirthDate.year >> tmp.dtBirthDate.month >> tmp.dtBirthDate.day;
		if (in.good())
		{
			in.ignore(1);
		}
		else
		{
			in.setstate(std::ios_base::failbit);
		}
	}// !Right number

	if (in.good())
	{
		obj = tmp;
	}

	return in;
}
*/

std::istream& operator>>(std::istream& in, STUDENT& obj)
{
	STUDENT tmp;

	in >> (PERSON)tmp;

	if (in.good())
	{
		// Birth date
		in >> tmp.dtBirthDate.year >> tmp.dtBirthDate.month >> tmp.dtBirthDate.day;
		//if (in.good())
		//{
		//	in.ignore(1);
		//}
		//else
		//{
		//	in.setstate(std::ios_base::failbit);
		//}
	}

	if (in.good())
	{
		obj = tmp;
	}

	return in;
}
