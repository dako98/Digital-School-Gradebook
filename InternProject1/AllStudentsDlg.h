#pragma once


// AllStudentsDlg dialog

class AllStudentsDlg : public CDialog
{
	DECLARE_DYNAMIC(AllStudentsDlg)

public:
	AllStudentsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AllStudentsDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALL_STUDENTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox					m_allStudentsList;
	CString						m_allStudentsListVal;
	CButton						m_rbnStudents;

	afx_msg void OnBnClickedRadio4();

private:
	// няма да са мембъри след новия дизайн.
	StudentDatabaseInterface	m_studentStore;
	TeacherDatabaseInterface	m_teacherStore;

	BOOL PrintAllStudents();
	BOOL PrintAllTeachers();
	BOOL PrintAll();

public:
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();
};
