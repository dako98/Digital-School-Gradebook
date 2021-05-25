#pragma once

#include <vector>
#include <unordered_map>

#include "Grade.h"
#include "GradeStore.h"
#include "SubjectStore.h"

class GradeStore
{
public:
	GradeStore() = default;

	void AddGrade(int studentNum, int subjectNum, const tm& date, int grade);
	void RemoveGrade(int studentNum, int subjectID, const tm& date);
	void EditGrade(int studentNum, int subjectNum, const tm& date, int grade);
	float GetAverage(int studentNum, int subjectID) const;
	void ClearStudent(int studentNum);

	std::vector<Grade> GetGrades(int studentNum, int subjectID) const;
private:


	// SubjectID -> Student -> Grades
	std::unordered_map<int, std::unordered_map<int, std::vector<Grade>>> grades;
	
	SubjectStore* subjectStore;
	GradeStore* gradeStore;
};

