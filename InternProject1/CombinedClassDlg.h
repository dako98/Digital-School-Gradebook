#pragma once

#include "CStudentClass.h"
// CombinedClassDlg dialog

class CombinedClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedClassDlg)

public:
	CombinedClassDlg(DialogMode dialogMode, STUDENT_CLASS& studentClass);   // standard constructor
	BOOL OnInitDialog() override;
	virtual ~CombinedClassDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_DIALOG1 };
	enum { IDD = IDD_COMBINED_CLASS };
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
