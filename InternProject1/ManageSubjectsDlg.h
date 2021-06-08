#pragma once


// ManageSubjectsDlg dialog

class ManageSubjectsDlg : public CDialog
{
	DECLARE_DYNAMIC(ManageSubjectsDlg)

public:
	ManageSubjectsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ManageSubjectsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
