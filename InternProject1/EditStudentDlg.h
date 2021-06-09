#pragma once

#include <vector>

#include "Student.h"
#include "Teacher.h"

// EditStudentDlg dialog

class EditStudentDlg : public CDialog
{
	DECLARE_DYNAMIC(EditStudentDlg)

public:
	EditStudentDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditStudentDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox studentsComboBox;
	CString studentNameVal;
	COleDateTime studentBirthdayVal;
	afx_msg void OnBnClickedOk();

private:
	std::vector<Student> allStudents;
	std::vector<Teacher> allTeachers;
	void PrintStudents();
	void PrintTeachers();

public:
	CEdit studentName;
	CDateTimeCtrl studentBirthday;
	CButton studentsRadioBtn;
	CButton teachersRadioBtn;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};
