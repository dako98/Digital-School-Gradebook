#pragma once

#include <vector>

#include "Grade.h"
#include "Student.h"
#include "Subject.h"
// EditGradeDlg dialog

class EditGradeDlg : public CDialog
{
	DECLARE_DYNAMIC(EditGradeDlg)

public:
	EditGradeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditGradeDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_GRADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:

	void PrintStudents();
	void PrintSubjects();
	void PrintGrades();
	void PrintValue();

	void UpdateGradeInList();

	std::vector<Student> allStudents;
	std::vector<Subject> allSubjects;
	std::vector<Grade> studentGrades;
	int currentStudentNum;
	int currentSubjectID;
	int currentGradeIndex;

public:
	CComboBox studentsComboBox;
	CComboBox subjectsComboBox;
	CComboBox allGradesComboBox;
	CComboBox gradeValue;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton1();
};
