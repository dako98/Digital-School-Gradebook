#pragma once

#include "CStudentClass.h"
// CombinedStudentClassDlg dialog

class CombinedStudentClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedStudentClassDlg)

public:
	CombinedStudentClassDlg(DialogMode dialogMode, STUDENT_CLASS& studentClass);   // standard constructor
	BOOL OnInitDialog() override;
	virtual ~CombinedStudentClassDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_DIALOG1 };
	enum { IDD = IDD_COMBINED_STUDENT_CLASS};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_teachersDropdown;
	CEdit				m_className;
	afx_msg void OnBnClickedOk();

private:
	DialogMode			m_eDialogMode;
	STUDENT_CLASS&		m_data;
	STUDENT_CLASS		m_tmp;
};
