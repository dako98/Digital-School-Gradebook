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

	DialogMode m_eDialogMode;
	std::unique_ptr<ObjectInterface<STUDENT>>	studentStore;
	std::unique_ptr<ObjectInterface<CClass>>	classesStore;
	STUDENT student;

	DECLARE_MESSAGE_MAP()
public:
	CEdit studentNumber;
	CEdit studentFirstName;
	CEdit studentLastName;
	CDateTimeCtrl studentBirthDate;
	afx_msg void OnBnClickedOk();
	int studentNumberVal;
	COleDateTime studentBirthDateVal;
	CComboBox classList;
	CEdit numberInClassEditBox;
};
