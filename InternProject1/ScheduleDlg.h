#pragma once

#include "DBConnector.h"

// ScheduleDlg dialog

class ScheduleDlg : public CDialog
{
	DECLARE_DYNAMIC(ScheduleDlg)

public:
	ScheduleDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ScheduleDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEDULE };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl					m_ScheduleListControl;
	CComboBox					m_classSelectDropList;


private:
	BOOL PrintSchedule();

	ScheduleDatabaseInterface	m_scheduleStore;
	ClassesDatabaseInterface	m_classStore;
	CSchedule					m_schedule;
public:
	afx_msg void OnCbnSelchangeClassCombo();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
