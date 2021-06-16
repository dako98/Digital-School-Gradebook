#include "pch.h"
#include "SubjectStore.h"

SubjectStore* SubjectStore::instance = nullptr;

SubjectStore::SubjectStore()
	:lastID(0)
{
}

void SubjectStore::Initialise(const std::string& path)
{
	file.open(path);
	if (!file)
	{
		throw std::exception{};
	}
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
//	subjects.insert({ lastID, newSubject });
	file << newSubject;
	lastID++;
}

void SubjectStore::RemoveSubject(int subjectID)
{
	// Get all subjects
	std::vector<Subject> subjects = GetAllSubjects();

	auto found = subjects.begin();
	bool isFound = false;

	while (found != subjects.end())
	{
		if (found->GetID() == subjectID)
		{
			isFound = true;
			subjects.erase(found);
			break;
		}
		found++;
	}
	if (!isFound)
	{
		throw std::out_of_range("Invalid student number.");
	}

	// Write all subjects
	for (const Subject& subject : subjects)
	{
		file << subject;
	}
}

void SubjectStore::EditSubject(int subjectID, const CString& name, int teacherID, const CString& room)
{
	// Get all subjects 
	std::vector<Subject> subjects = GetAllSubjects();

	auto found = subjects.begin();

	while (found != subjects.end())
	{
		if (found->GetID() == subjectID)
		{
			*found = Subject{ name, teacherID, room, subjectID };
			break;
		}
		found++;
	}
	if (found == subjects.end())
	{
		throw std::out_of_range("Invalid student number.");
	}

	// Write all subjects
	for (const Subject& subject : subjects)
	{
		file << subject;
	}

}

Subject SubjectStore::GetSubject(int subjectID) 
{
	// Get all subjects
	std::vector<Subject> subjects = GetAllSubjects();

	auto found = subjects.begin();
	Subject result;

	while (found != subjects.end())
	{
		if (found->GetID() == subjectID)
		{
			result = *found;
			break;
		}
		found++;
	}
	if (found == subjects.end())
	{
		throw std::out_of_range("Invalid student number.");
	}
	return result;
}

std::vector<Subject> SubjectStore::GetAllSubjects() 
{
	std::vector<Subject> result;
	
	// FIXME: Can not read for a second time.

	Subject tmp;
	file.seekp(0);
	file.seekg(0);
	while (!file.eof())
	{
//		tmp.ReadFromFile(file);
		file >> tmp;
		result.push_back(tmp);
	}

	return result;
}

SubjectStore::~SubjectStore()
{
	delete instance;
}
