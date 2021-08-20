#pragma once
#include "DBConnector.h"

// StudentAverageDlg dialog

class StudentAverageDlg : public CDialog
{
	DECLARE_DYNAMIC(StudentAverageDlg)

public:
	StudentAverageDlg(CWnd* pParent = nullptr);   // standard constructor

	BOOL OnInitDialog() override;

	virtual ~StudentAverageDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT_AVERAGE_GRADE };
#endif

private:
	BOOL UpdateAverage();
	BOOL PrintAllStudents();
	BOOL PrintAllSubjects();

	StudentDatabaseInterface	m_studentStore;
	GradeDatabaseInterface		m_gradeStore;
	SubjectDatabaseInterface	m_subjectStore;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox					m_studentDropList;
	CComboBox					m_subjectDropList;
	CEdit						m_studentAverage;
	CEdit						m_subjectAverage;
	float						m_studentAverageVal;
	float						m_subjectAverageVal;
	afx_msg void OnCbnSelchangeStudent();
	afx_msg void OnCbnSelchangeSubject();
};
