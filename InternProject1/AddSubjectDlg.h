#pragma once

#include <vector>

#include "Teacher.h"
// AddSubjectDlg dialog

class AddSubjectDlg : public CDialog
{
	DECLARE_DYNAMIC(AddSubjectDlg)

public:
	AddSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddSubjectDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_SUBJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox teacherList;

private:
	std::vector<Teacher> allTeachers;
public:
	CString subjectNameVal;
	CString subjectRoomVal;
	afx_msg void OnBnClickedOk();
};
