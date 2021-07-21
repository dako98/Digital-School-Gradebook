#pragma once

#include "CGrade.h"
#include "Utility.h"
#include "Storage.h"

// CombinedGradeDlg dialog

class CombinedGradeDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedGradeDlg)

public:
	CombinedGradeDlg(DialogMode eMode, const GRADE& data);

	BOOL OnInitDialog() override;

	virtual ~CombinedGradeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRADES_COMBINED };
#endif

private:
	BOOL PrintAllStudents();
	BOOL PrintAllSubjects();

	DialogMode m_eDialogMode;
//	Storage<GRADE> store;
	std::unique_ptr<ObjectInterface<GRADE>>		gradeStore;
	std::unique_ptr<ObjectInterface<STUDENT>>	studentStore;
	std::unique_ptr<ObjectInterface<SUBJECT>>	subjectStore;
	GRADE tmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int gradeIDVal;
	CComboBox studentDropdown;
	CComboBox subjectDropdown;
	CComboBox gradeDropdown;
	CDateTimeCtrl gradeDate;
	COleDateTime gradeDateVal;
	afx_msg void OnBnClickedOk();
};
