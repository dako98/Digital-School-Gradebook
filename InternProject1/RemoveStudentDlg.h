#pragma once

#include <vector>

#include "Student.h"

// RemoveStudentDlg dialog

class RemoveStudentDlg : public CDialog
{
	DECLARE_DYNAMIC(RemoveStudentDlg)

public:
	RemoveStudentDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RemoveStudentDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOVE_STUDENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox studentList;
	afx_msg void OnBnClickedButton1();

private:
	std::vector<Student> allStudents;
};
