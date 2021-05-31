#pragma once


// AddStudentDlg dialog

class AddStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddStudentDlg)

public:
	AddStudentDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddStudentDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDSTUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString studentNameVal;
	COleDateTime studentBirthdayVal;
};
