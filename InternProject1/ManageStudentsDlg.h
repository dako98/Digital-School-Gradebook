#pragma once


// ManageStudentsDlg dialog

class ManageStudentsDlg : public CDialog
{
	DECLARE_DYNAMIC(ManageStudentsDlg)

public:
	ManageStudentsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ManageStudentsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGESTUDENTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedAllStudents();
};
