#pragma once

#include <vector>

#include "Student.h"
#include "Subject.h"

// AddGradeDlg dialog

class AddGradeDlg : public CDialog
{
	DECLARE_DYNAMIC(AddGradeDlg)

public:
	AddGradeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddGradeDlg();

	BOOL OnInitDialog() override;

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_GRADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	void PrintStudents();
	void PrintSubjects();

	std::vector<Student> allStudents;
	std::vector<Subject> allSubjects;

	DECLARE_MESSAGE_MAP()
public:
	CComboBox studentComboBox;
	CComboBox subjectComboBox;
	CDateTimeCtrl gradeDate;
	CSliderCtrl gradeSlider;
	
	
	CString gradeText;
	int gradeSliderVal;
};
