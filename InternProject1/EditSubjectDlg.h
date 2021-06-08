#pragma once

#include <vector>

#include "Teacher.h"
#include "Subject.h"

// EditSubjectDlg dialog

class EditSubjectDlg : public CDialog
{
	DECLARE_DYNAMIC(EditSubjectDlg)

public:
	EditSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditSubjectDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_SUBJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	
	void LoadSubjects();
	void LoadTeachers();

	std::vector<Subject> allSubjects;
	std::vector<Teacher> allTeachers;


public:
	CComboBox subjectComboBox;
	CEdit subjectNameComboBox;
	CComboBox teacherComboBox;
	CEdit roomName;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	CString subjectNameComboBoxVal;
	CString roomNameVal;
};
