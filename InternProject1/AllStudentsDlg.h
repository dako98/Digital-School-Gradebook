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
	CListBox allStudentsList;
	CString allStudentsListVal;
	CButton studentsRadioBtn;
	afx_msg void OnBnClickedRadio4();

private:
	void PrintAllStudents();
	void PrintAllTeachers();
	void PrintAll();

public:
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();
};
