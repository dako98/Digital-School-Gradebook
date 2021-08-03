#pragma once
#include "Utility.h"
#include "Storage.h"
#include "CStudent.h"

// CombinedStudentDlg dialog

class CombinedStudentDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedStudentDlg)

public:
	CombinedStudentDlg(DialogMode eMode, const STUDENT& data);

	BOOL OnInitDialog() override;

	virtual ~CombinedStudentDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT_COMBINED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:

	BOOL LoadAllClasses();

	DialogMode					m_eDialogMode;
	StudentDatabaseInterface	m_studentStore;
	ClassesDatabaseInterface	m_classesStore;
	STUDENT						m_student;

	DECLARE_MESSAGE_MAP()
public:
	CEdit						m_studentNumber;
	CEdit						m_studentFirstName;
	CEdit						m_studentLastName;
	CDateTimeCtrl				m_studentBirthDate;
	int							m_studentNumberVal;
	COleDateTime				m_studentBirthDateVal;
	CComboBox					m_classList;
	CEdit						m_numberInClassEditBox;

	afx_msg void OnBnClickedOk();
};
