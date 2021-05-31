#pragma once

#include <unordered_map>

#include "Subject.h"
class SubjectStore
{
public:
	static SubjectStore* GetInstance();

	SubjectStore(const SubjectStore& other) = delete;
	SubjectStore(SubjectStore&& other) = default;
	SubjectStore& operator=(const SubjectStore& other) = delete;
	SubjectStore& operator=(SubjectStore&& other) = default;

	void	AddSubject(const CString& name, int teacherID, const CString& room);
	void	RemoveSubject(int subjectID);
	void	EditSubject(int subjectID, const CString& name, int teacherID, const CString& room);
	Subject	GetSubject(int subjectID) const;
	std::vector<Subject> GetAllSubjects() const;

	~SubjectStore();
private:
	SubjectStore();
	static SubjectStore* instance;

	std::unordered_map<int, Subject> subjects;
	int lastID;

};

