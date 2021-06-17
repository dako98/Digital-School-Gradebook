#pragma once

#include <unordered_map>
#include <fstream>

#include "Subject.h"
class SubjectStore
{
public:

	void Initialise(const std::string& path);

	static SubjectStore* GetInstance();

	SubjectStore(const SubjectStore& other) = delete;
	SubjectStore(SubjectStore&& other) = default;
	SubjectStore& operator=(const SubjectStore& other) = delete;
	SubjectStore& operator=(SubjectStore&& other) = default;

	void		AddSubject(const CString& name, int teacherID, const CString& room);
	void		RemoveSubject(int subjectID);
	void		EditSubject(int subjectID, const CString& name, int teacherID, const CString& room);
	Subject	GetSubject(int subjectID);
	std::vector<Subject> GetAllSubjects();

	~SubjectStore();
private:
	SubjectStore();
	static SubjectStore* instance;

//	std::unordered_map<int, Subject> subjects;
	int lastID;

	std::fstream file;
	std::string path;
};

