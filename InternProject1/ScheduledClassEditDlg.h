#pragma once

#include <unordered_map>

// ScheduledClassEditDlg dialog

class ScheduledClassEditDlg : public CDialog
{
	DECLARE_DYNAMIC(ScheduledClassEditDlg)

public:
	ScheduledClassEditDlg(const CSchedule& m_schedule);   // standard constructor
	virtual ~ScheduledClassEditDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_SCHEDULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	void PrintClassesOfDay(int day);
	void MoveScheduledClass(int id, int up = 0, int tomorrow = 0);

	CSchedule							m_schedule;
	std::unordered_map<int, CString>	m_subjectNames;
	SubjectDatabaseInterface			m_subjectStore;
	ScheduledClassDatabaseInterface		m_scheduledClassStore;
	ScheduleDatabaseInterface			m_scheduleStore;
	std::vector<ScheduleClass>			m_toDelete;
	std::vector<ScheduleClass>			m_toAdd;

	DECLARE_MESSAGE_MAP()
public:
	CComboBox							m_daysOfWeekList;
	CListBox							m_classesInDayList;
	CEdit								m_currentClassEdit;
	CButton								m_buttonUp;
	CButton								m_buttonDown;

	afx_msg void OnCbnSelchangeDay();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnLbnSelchangeClass();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedOk();
};
