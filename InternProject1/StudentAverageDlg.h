#pragma once


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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox studentDropList;
	CComboBox subjectDropList;
	CEdit studentAverage;
	CEdit subjectAverage;
	float studentAverageVal;
	float subjectAverageVal;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
};
