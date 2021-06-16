#pragma once

#include <stdexcept>
#include <string>
#include <iostream>

class Subject
{
public:
	Subject() = default;
	Subject(const CString& name, int teacherID, const CString& room, int subjectID);

	bool operator==(const Subject& other) const;


	int GetID() const;
	int GetTeacher() const;
	CString GetName() const;
	CString GetRoom() const;

	friend std::ostream& operator<<(std::ostream& out, const Subject& obj);
	friend std::istream& operator>>(std::istream& in, Subject& obj);


private:

	int subjectID;
	int teacherID;
	CString name;
	CString room;

};

