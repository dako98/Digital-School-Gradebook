#pragma once


// ManageGradesDlg dialog

class ManageGradesDlg : public CDialog
{
	DECLARE_DYNAMIC(ManageGradesDlg)

public:
	ManageGradesDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ManageGradesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGE_GRADES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAllGrades();
	afx_msg void OnBnClickedButtonAddGrade();

private:
	GradeDatabaseInterface m_gradeStore;
};
