#include "pch.h"
#include "GradeStore.h"
#include "SubjectStore.h"
#include "StudentStore.h"

GradeStore* GradeStore::instance = nullptr;

GradeStore::GradeStore()
	:lastID(0)
{
}

int GradeStore::GetCount(int studentNum) const
{

	std::vector<Subject> subjects = SubjectStore::GetInstance()->GetAllSubjects();

	int count = 0;

	for (const Subject& subject : subjects)
	{
		count += GetCount(studentNum, subject.GetID());
	}
	return count;
}

int GradeStore::GetCount(int studentNum, int subjectID) const
{
	int count = 0;

	auto* studentsInSubject = &grades.find(subjectID)->second;
	auto studentGrades = studentsInSubject->find(studentNum);
	
	if (studentGrades != studentsInSubject->end())
	{
		count = studentGrades->second.size();
	}

	return count;
}

GradeStore* GradeStore::GetInstance()
{
	if (!instance)
	{
		instance = new GradeStore;
	}
	return instance;
}

bool GradeStore::AddGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade)
{
	bool isOK;
	if(isOK = Grade::Validate(studentNum, subjectNum, date, grade));
	{
		Grade newGrade(studentNum, subjectNum, date, grade,lastID);
		lastID++;

		grades[subjectNum][studentNum].push_back(newGrade);
	}
	return isOK;
}

void GradeStore::RemoveGrade(int studentNum, int subjectID, const COleDateTime& date)
{
	// TODO: validate studentNum and subjectID
	// TODO: Get array in a better way.
	std::vector<Grade>* studentGrades = &grades.find(subjectID)->second.find(studentNum)->second;

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

bool GradeStore::EditGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade)
{
	bool isOK;

	if (isOK = Grade::Validate(studentNum, subjectNum, date, grade))
	{
		RemoveGrade(studentNum, subjectNum, date);
		AddGrade(studentNum, subjectNum, date, grade);
	}
	return isOK;
}

float GradeStore::GetAverage(int studentNum, int subjectID) const
{
	// TODO: validate studentNum and subjectID

	float sum = 0;
	float average;
	int count = 0;

	std::vector<Grade> studentGrades = GetGrades(subjectID,studentNum);
	count = studentGrades.size();

	for (const Grade& grade : studentGrades)
	{
		sum += grade.GetValue();
	}

	if (count > 0)
	{
		average = sum / count;
	}
	else
	{
		average = 0;
	}

	return average;
}

float GradeStore::GetAverage(int studentNum) const
{
	std::vector<Subject> subjects = SubjectStore::GetInstance()->GetAllSubjects();

	float average = 0;
	float sum = 0;
	int count = 0;

	for (const auto& subject : subjects)
	{
		sum += GetAverage(subject.GetID());
	}
	count = GetCount(studentNum);

	if (count > 0)
	{
		average = (float)sum / count;
	}
	else
	{
		average = 0;
	}

	return average;
}

std::set<int> GradeStore::GetExcellent() const
{
	std::set<int> excellents;

	std::vector<Student> allStudents = StudentStore::GetInstance()->GetAllStudents();
	std::vector<Subject> allSubjects = SubjectStore::GetInstance()->GetAllSubjects();
	
	for (const Student& student : allStudents)
	{
//		auto studentGrades = GetAllGrades(student.GetNumber());
		std::vector<Grade> studentGrades;
		bool isExcellent = true;

		for (const Grade& grade : studentGrades)
		{
			if (grade.GetValue() < GRADES::A)
			{
				isExcellent = false;
				break;
			}
		}

		if (isExcellent)
		{
			excellents.insert(student.GetNumber());
		}
	}

	return excellents;
}

std::set<int> GradeStore::GetFails() const
{
	std::vector<Student> allStudents = StudentStore::GetInstance()->GetAllStudents();
	std::vector<Subject> allSubjects = SubjectStore::GetInstance()->GetAllSubjects();
	std::set<int> fails;

	for (const Subject& subject : allSubjects)
	{
		for (const Student& student : allStudents)
		{
			if (GetAverage(student.GetNumber(), subject.GetID()) < 3)
			{
				fails.insert(student.GetNumber());
			}
		}
	}

	return fails;
}

std::set<int> GradeStore::GetWithGradeStreek(GRADES grade, int count) const
{
	std::set<int> studentIDs;

	std::vector<Student> allStudents = StudentStore::GetInstance()->GetAllStudents();
	std::vector<Subject> allSubjects = SubjectStore::GetInstance()->GetAllSubjects();

	// For each student
	for (const Student& student : allStudents)
	{

		int currentCount = 0;

		// For each subject
		for (const Subject& subject : allSubjects)
		{

			std::vector<Grade> studentGrades = GetGrades(student.GetNumber(), subject.GetID());

			if (currentCount >= count)
			{
				studentIDs.insert(student.GetNumber());
				break;	// Go to next student.
			}

			for (const Grade& currentGrade : studentGrades)
			{
				if (currentGrade.GetValue() == grade)
				{
					currentCount++;
					break;	// Go to next subject.
				}
			}

		}
	}

	return studentIDs;
}

std::vector<Grade> GradeStore::GetAllGrades() const
{
	std::vector<Grade> allGrades;

	// For each subject
	for (const auto& subject : grades)
	{
		// For each student student
		for (const auto& student : subject.second)
		{
			// Insert each grade
			for (const Grade& grade : student.second)
			{
				allGrades.push_back(grade);
			}
		}
	}


	return allGrades;
}

std::vector<Grade> GradeStore::GetAllGrades(int studentNum) const
{
	std::vector<Grade> studentAllGrades;

	// For each subject
	for (const auto& subject : grades)
	{
		// Find the wanted student
		auto it = subject.second.find(studentNum);

		// If he has grades
		if (it != subject.second.end())
		{
			// Insert all his grades.
			for (const Grade& grade : it->second)
				studentAllGrades.push_back(grade);
		}
	}

	return studentAllGrades;
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
