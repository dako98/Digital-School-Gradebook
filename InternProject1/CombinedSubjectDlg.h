#pragma once

#include "Utility.h"

#include "Storage.h"
#include "CSubject.h"
#include "DBConnector.h"

// CombinedSubjectDlg dialog

class CombinedSubjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedSubjectDlg)

public:
	CombinedSubjectDlg(DialogMode eMode, SUBJECT& data);

	BOOL OnInitDialog() override;

	virtual ~CombinedSubjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUBJECT_COMBINED };
#endif

private:
	DialogMode					m_eDialogMode;
//	Storage<SUBJECT> store;
	SubjectDatabaseInterface	m_subjectStore;
//	GradeDatabaseInterface		m_gradeStore;
	TeacherDatabaseInterface	m_teacherStore;
	SUBJECT&					m_data;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox					m_teacherDropdown;
	int							m_subjectIDVal;
	CEdit						m_subjectName;
	CEdit						m_subjectRoom;
	CEdit						m_subjectID;

	afx_msg void OnBnClickedOk();
};
