#pragma once

#include <vector>
#include <unordered_map>

#include "Grade.h"
#include "GradeStore.h"
#include "SubjectStore.h"

class GradeStore
{
public:
	static GradeStore* GetInstance();
	
	GradeStore(const GradeStore& other) = delete;
	GradeStore(GradeStore&& other) = default;
	GradeStore& operator=(const GradeStore& other) = delete;
	GradeStore& operator=(GradeStore&& other) = default;

	void AddGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade);
	void RemoveGrade(int studentNum, int subjectID, const COleDateTime& date);
	void EditGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade);
	float GetAverage(int studentNum, int subjectID) const;
	float GetAverage(int studentNum) const;
	void ClearStudent(int studentNum);
	void ClearSubject(int subjectID);

	std::vector<Grade> GetGrades(int studentNum, int subjectID) const;

	~GradeStore();
private:

	GradeStore();
	static GradeStore* instance;

	// SubjectID -> Student -> Grades
	std::unordered_map<int, std::unordered_map<int, std::vector<Grade>>> grades;
	
//	SubjectStore* subjectStore;
};

