#pragma once

#include "CGrade.h"
#include "Utility.h"
#include "Storage.h"

// CombinedGradeDlg dialog

class CombinedGradeDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedGradeDlg)

public:
	CombinedGradeDlg(DialogMode eMode, GRADE& data);

	BOOL OnInitDialog() override;

	virtual ~CombinedGradeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRADES_COMBINED };
#endif

private:
	BOOL PrintAllStudents();
	BOOL PrintAllSubjects();

	DialogMode					m_eDialogMode;
	StudentDatabaseInterface	m_studentStore;
	SubjectDatabaseInterface	m_subjectStore;
	GRADE&						m_data;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int							m_gradeIDVal;
	CComboBox					m_studentDropdown;
	CComboBox					m_subjectDropdown;
	CComboBox					m_gradeDropdown;
	CDateTimeCtrl				m_gradeDate;
	COleDateTime				m_gradeDateVal;
	afx_msg void OnBnClickedOk();
};
