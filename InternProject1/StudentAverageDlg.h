#pragma once
#include "DBConnector.h"

// StudentAverageDlg dialog



// Class, Number, First name, Last name, Average grade
extern std::array<CString, 5> colData;

extern const float GRADE_EPS;

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
	BOOL PrintStudentsAverage();
	BOOL PrintClassesAverage();
	BOOL PrintSchoolAverage();

	StudentDatabaseInterface	m_studentStore;
	GradeDatabaseInterface		m_gradeStore;
	SubjectDatabaseInterface	m_subjectStore;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit						m_schoolAverageGrade;
	float						m_studentAverageVal;
	float						m_subjectAverageVal;
	afx_msg void OnCbnSelchangeStudent();
	afx_msg void OnCbnSelchangeSubject();
	CListCtrl m_studentsList;
	CListCtrl m_classesList;
};
