#pragma once
#include "Utility.h"
#include "Storage.h"
#include "CStudent.h"

// CombinedStudentDlg dialog

class CombinedStudentDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedStudentDlg)

public:
	CombinedStudentDlg(CWnd* pParent = nullptr);   // standard constructor
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
	DialogMode m_eDialogMode;
	Storage<STUDENT> studentStore;
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
};
