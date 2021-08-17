#pragma once


// AllTeachersDlg dialog

class AllTeachersDlg : public CDialog
{
	DECLARE_DYNAMIC(AllTeachersDlg)

public:
	AllTeachersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AllTeachersDlg();
	
	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALL_TEACHERS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	BOOL PrintAllTeachers();

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_allTeachersList;
	CString m_allTeachersListVal;
	afx_msg void OnBnClickedBtnTeachersAdd();
	afx_msg void OnBnClickedBtnTeachersEdit();
	afx_msg void OnBnClickedBtnTeachersRemove();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
