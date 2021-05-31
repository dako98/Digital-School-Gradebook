#include "pch.h"
#include "SubjectStore.h"

SubjectStore* SubjectStore::instance = nullptr;

SubjectStore::SubjectStore()
	:lastID(0)
{
}

SubjectStore* SubjectStore::GetInstance()
{
	if (!instance)
	{
		instance = new SubjectStore;
	}
	return instance;
}

void SubjectStore::AddSubject(const CString& name, int teacherID, const CString& room)
{
	Subject newSubject(name, teacherID, room, lastID);
	subjects.insert({ lastID, newSubject });
	lastID++;
}

void SubjectStore::RemoveSubject(int subjectID)
{
	auto found = subjects.find(subjectID);

	if (found != subjects.end())
	{
		subjects.erase(found);
	}
}

void SubjectStore::EditSubject(int subjectID, const CString& name, int teacherID, const CString& room)
{
	auto found = subjects.find(subjectID);

	if (found != subjects.end())
	{
		found->second = Subject{ name, teacherID, room, subjectID };
	}
	else
	{
		throw std::out_of_range("Invalid student number.");
	}
}

Subject SubjectStore::GetSubject(int subjectID) const
{
	auto found = subjects.find(subjectID);
	Subject result;

	if (found != subjects.end())
	{
		result = found->second;
	}
	else
	{
		throw std::out_of_range("Invalid student number.");
	}
	return result;
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

SubjectStore::~SubjectStore()
{
	delete instance;
}
