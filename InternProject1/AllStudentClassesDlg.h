#pragma once


// AllStudentClassesDlg dialog

class AllStudentClassesDlg : public CDialog
{
	DECLARE_DYNAMIC(AllStudentClassesDlg)

public:
	AllStudentClassesDlg(CWnd* pParent = nullptr);   // standard constructor
	BOOL OnInitDialog() override;
	virtual ~AllStudentClassesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALL_STUDENT_CLASSES};
#endif

private:
	BOOL PrintAllStudentClasses();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_allStudentClassesList;
	afx_msg void OnBnClickedBtnAddStudentClass();
	afx_msg void OnBnClickedBtnEditStudentClass();
	afx_msg void OnBnClickedBtnRemoveStudentClass();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
