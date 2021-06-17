#include "pch.h"
#include "SubjectStore.h"

SubjectStore* SubjectStore::instance = nullptr;

SubjectStore::SubjectStore()
	:lastID(0)
{
}

void SubjectStore::Initialise(const std::string& path)
{
	file.open(path, std::ios::in | std::ios::out);
	if (!file)
	{
		throw std::exception{"Can't open Subjects file."};
	}
	this->path = path;
	GetAllSubjects();

	file.close();
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
	file.open(path, std::ios::out | std::ios::app);
	Subject newSubject(name, teacherID, room, lastID);

	file.seekp(0, file.end);
	file << newSubject;
	file.close();
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

	file.open(path, std::ios::out);

	// Write all subjects
	for (const Subject& subject : subjects)
	{
		file << subject;
	}
	file.close();
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
		throw std::out_of_range("Invalid subject number.");
	}

	file.open(path, std::ios::out);

	// Write all subjects
	for (const Subject& subject : subjects)
	{
		file << subject;
	}
	file.close();
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
	
	file.open(path, std::ios::in);

	Subject tmp;
	file.seekp(0, file.beg);
	file.seekg(0, file.beg);
	while (file.peek() != EOF)
	{
		file >> tmp;
		result.push_back(tmp);
//		lastID = std::max(lastID, tmp.GetID());
		lastID = (lastID > tmp.GetID()) ? lastID : tmp.GetID();
	}
	file.close();
	return result;
}

SubjectStore::~SubjectStore()
{
	delete instance;
}
