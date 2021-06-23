#pragma once

#include <unordered_map>

#include "Subject.h"
class SubjectStore
{
public:
	static SubjectStore* GetInstance();

	int		AddSubject(Subject subject);
	void	RemoveSubject(int subjectID);
	void	EditSubject(int subjectID, const Subject& updatedSubject);
	Subject	GetSubject(int subjectID) const;
	std::vector<Subject> GetAllSubjects() const;

	~SubjectStore();
private:
	SubjectStore();
	static SubjectStore* instance;

	std::unordered_map<int, Subject> subjects;
	int lastID;

};

