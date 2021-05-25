#include "pch.h"
#include "SubjectStore.h"

SubjectStore::SubjectStore()
	:lastID(0)
{
}

void SubjectStore::AddSubject(const Subject& subject)
{
	throw std::exception("Not implemented.");
}

void SubjectStore::RemoveSubject(int subjectID)
{
	throw std::exception("Not implemented.");
}

void SubjectStore::EditSubject(int subjectID, const Subject& updatedSubject)
{
	throw std::exception("Not implemented.");
}

std::vector<Subject> SubjectStore::GetAllSubjects() const
{
	throw std::exception("Not implemented.");
	return std::vector<Subject>();
}
