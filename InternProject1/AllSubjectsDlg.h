#pragma once


// AllSubjectsDlg dialog

class AllSubjectsDlg : public CDialog
{
	DECLARE_DYNAMIC(AllSubjectsDlg)

public:
	AllSubjectsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AllSubjectsDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALL_SUBJECTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox subjectsList;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();
private:
	BOOL PrintAll();
};
