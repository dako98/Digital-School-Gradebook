#include "pch.h"
#include "SubjectStore.h"

SubjectStore::SubjectStore()
	:lastID(0)
{
}

int SubjectStore::AddSubject(Subject subject)
{
	bool found = false;
	found = subjects[subject.GetID()] == subject;
	int ID = -1;
	if (!found)
	{
		ID = lastID++;
		subject.InitialiseID(ID);

		subjects.insert({ ID, subject });
	}
	return ID;
}

void SubjectStore::RemoveSubject(int subjectID)
{
	auto found = subjects.find(subjectID);

	if (found != subjects.end())
	{
		subjects.erase(found);
	}
}

void SubjectStore::EditSubject(int subjectID, const Subject& updatedSubject)
{
	auto found = subjects.find(subjectID);

	if (found != subjects.end())
	{
		Subject update(
			updatedSubject.GetName(),
			updatedSubject.GetTeacher(),
			updatedSubject.GetRoom());

		update.InitialiseID(found->second.GetID());

		found->second = update;
	}
}

std::vector<Subject> SubjectStore::GetAllSubjects() const
{
	std::vector<Subject> result;
	result.resize(subjects.size());

	for (const auto& subject : subjects)
	{
		result.push_back(subject.second);
	}
	return result;
}
