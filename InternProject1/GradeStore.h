#pragma once

#include <vector>
#include <unordered_map>
#include <set>

#include "Grade.h"
#include "GradeStore.h"

class GradeStore
{
public:
	static GradeStore* GetInstance();
	
	GradeStore(const GradeStore& other) = delete;
	GradeStore(GradeStore&& other) = default;
	GradeStore& operator=(const GradeStore& other) = delete;
	GradeStore& operator=(GradeStore&& other) = default;

	bool AddGrade(int studentNum, int subjectNum, const COleDateTime& date, int grade);
	void RemoveGrade(int id);
	void RemoveGrade(int studentNum, int subjectID, const COleDateTime& date);
	bool EditGrade(int id, int studentNum, int subjectNum, const COleDateTime& date, int grade);
	float GetAverage(int studentNum, int subjectID) const;
	float GetAverage(int studentNum) const;
	std::set<int> GetExcellent() const;
	std::set<int> GetFails() const;
	std::set<int> GetWithGradeStreek(GRADES grade, int count) const;
	std::vector<Grade> GetAllGrades() const;
	std::vector<Grade> GetAllGrades(int studentNum) const;
	void ClearStudent(int studentNum);
	void ClearSubject(int subjectID);

	std::vector<Grade> GetGrades(int studentNum, int subjectID) const;

	~GradeStore();
private:

	GradeStore();
	static GradeStore* instance;

	Grade GetGrade(int id) const;
	int GetCount(int studentNum) const;
	int GetCount(int studentNum, int subjectID) const;

	// SubjectID -> Student -> Grades
	std::unordered_map<int, std::unordered_map<int, std::vector<Grade>>> grades;
	
	int lastID;
//	SubjectStore* subjectStore;
};

