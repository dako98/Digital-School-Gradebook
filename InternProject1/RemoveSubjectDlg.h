#pragma once

#include <vector>

#include "Subject.h"
#include "Teacher.h"
#include "Student.h"

// RemoveSubjectDlg dialog

class RemoveSubjectDlg : public CDialog
{
	DECLARE_DYNAMIC(RemoveSubjectDlg)

public:
	RemoveSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RemoveSubjectDlg();
	
	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOVE_SUBJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:

	void LoadSubjects();

	std::vector<Subject> allSubjects;
	std::vector<Teacher> allTeachers;
	std::vector<Student> allStudents;

public:
	CComboBox subjectsComboBox;
	afx_msg void OnBnClickedButton1();
};
