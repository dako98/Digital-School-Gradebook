#pragma once

#include "DBConnector.h"
#include "Utility.h"

// CombinedScheduleClassDlg dialog

class CombinedScheduleClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedScheduleClassDlg)

public:
	CombinedScheduleClassDlg(DialogMode eMode, ScheduleClass& data);   // standard constructor

	BOOL OnInitDialog() override;

	virtual ~CombinedScheduleClassDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMBINED_SCHEDULED_CLASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	SubjectDatabaseInterface	m_scheduledClassStore;
	SubjectDatabaseInterface	m_subjectStore;
	DialogMode					m_dialogMode;
	ScheduleClass&				m_data;


	DECLARE_MESSAGE_MAP()
public:
	CComboBox subjectsList;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
