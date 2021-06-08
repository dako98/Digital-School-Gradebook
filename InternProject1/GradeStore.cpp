#include "pch.h"
#include "GradeStore.h"

GradeStore* GradeStore::instance = nullptr;

GradeStore::GradeStore()
{
}

GradeStore* GradeStore::GetInstance()
{
	if (!instance)
	{
		instance = new GradeStore;
	}
	return instance;
}

void GradeStore::AddGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade)
{
	Grade newGrade(studentNum, subjectNum, date, grade);

	grades[subjectNum][studentNum].push_back(newGrade);
}

void GradeStore::RemoveGrade(int studentNum, int subjectID, const COleDateTime& date)
{
	// TODO: validate studentNum and subjectID
	// TODO: Get array in a better way.
	std::vector<Grade>* studentGrades = &grades.find(subjectID).operator*().second.find(studentNum).operator*().second;

	std::vector<Grade>::iterator toDelete = studentGrades->begin();
	while (toDelete != studentGrades->end())
	{
		if (toDelete->GetDate() == date)
			break;
		else
			toDelete++;
	}
	studentGrades->erase(toDelete);
}

void GradeStore::EditGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade)
{
	RemoveGrade(studentNum, subjectNum, date);
	AddGrade(studentNum, subjectNum, date, grade);
}

float GradeStore::GetAverage(int studentNum, int subjectID) const
{
	// TODO: validate studentNum and subjectID

	float sum = 0;
	float average;

	std::vector<Grade> studentGrades = GetGrades(subjectID,studentNum);

	for each (Grade grade in studentGrades)
	{
		sum += grade.GetValue();
	}
	average = sum / studentGrades.size();

	return average;
}

float GradeStore::GetAverage(int studentNum) const
{
	std::vector<Subject> subjects = SubjectStore::GetInstance()->GetAllSubjects();

	float average = 0;
	int sum = 0;
	int count = 0;
	for (const auto& subject : grades)
	{
		std::vector<Grade> studentGrades = subject.second.find(studentNum)->second;

		for (const Grade& grade : studentGrades)
		{
			sum += grade.GetValue();
		}
		count += studentGrades.size();
	}
	average = (float)sum / count;

	return average;
}

void GradeStore::ClearStudent(int studentNum)
{
	std::vector<Subject> subjects = SubjectStore::GetInstance()->GetAllSubjects();

	for (Subject& subject : subjects)
	{
		// TODO: Test if it actually works.
		grades[subject.GetID()].erase(grades[subject.GetID()].find(studentNum));
	}
}

void GradeStore::ClearSubject(int subjectID)
{
	grades.erase(subjectID);
}

std::vector<Grade> GradeStore::GetGrades(int studentNum, int subjectID) const
{
	// TODO: Think of a better way. This does not look OK.
	std::vector<Grade> result;

	auto subject = grades.find(subjectID);
	if (subject!=grades.end())
	{
		auto student = (*subject).second.find(studentNum);
		if (student!=(*subject).second.end())
		{
			result = (*student).second;
		}
		else
		{
			throw std::invalid_argument("Invalid student number.");
		}
	}
	else
	{
		throw std::invalid_argument("Invalid subject ID.");
	}

	return result;
//	return grades.find(subjectID).operator*().second.find(studentNum).operator*().second;
}

GradeStore::~GradeStore()
{
	delete instance;
}
