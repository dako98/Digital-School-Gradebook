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
	CombinedSubjectDlg(DialogMode eMode, const SUBJECT& data);

	BOOL OnInitDialog() override;

	virtual ~CombinedSubjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUBJECT_COMBINED };
#endif

private:
	DialogMode m_eDialogMode;
//	Storage<SUBJECT> store;
	std::unique_ptr<ObjectInterface<SUBJECT>>	subjectStore;
	std::unique_ptr<ObjectInterface<GRADE>>		gradeStore;
	std::unique_ptr<ObjectInterface<TEACHER>>	teacherStore;
	SUBJECT tmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox teacherDropdown;
	int subjectIDVal;
	CEdit subjectName;
	CEdit subjectRoom;
	afx_msg void OnBnClickedOk();
	CEdit subjectID;
};
