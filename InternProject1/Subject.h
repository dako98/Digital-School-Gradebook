#pragma once

#include <stdexcept>
#include <string>

class Subject
{
public:
	Subject() = default;
	Subject(const CString& name, int teacherID, const CString& room);

	bool operator==(const Subject& other) const;

	bool InitialiseID(int ID);

	int GetID() const;
	int GetTeacher() const;
	CString GetName() const;
	CString GetRoom() const;

private:
	int subjectID;
	int teacherID;
	CString name;
	CString room;

	bool valid;
};

