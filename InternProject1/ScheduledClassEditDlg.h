#pragma once

#include <unordered_map>

// ScheduledClassEditDlg dialog

class ScheduledClassEditDlg : public CDialog
{
	DECLARE_DYNAMIC(ScheduledClassEditDlg)

public:
	ScheduledClassEditDlg(const CSchedule& schedule);   // standard constructor
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

	CSchedule schedule;
	std::unordered_map<int, CString> subjectNames;
	std::unique_ptr<ObjectInterface<SUBJECT>> subjectStore;
	std::unique_ptr<ObjectInterface<ScheduleClass>> scheduledClassStore;
	std::unique_ptr<ObjectInterface<CSchedule>> scheduleStore;
	std::vector<ScheduleClass> toDelete;
	std::vector<ScheduleClass> toAdd;

	DECLARE_MESSAGE_MAP()
public:
	CComboBox daysOfWeekList;
	CListBox classesInDayList;
	CEdit currentClassEdit;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnLbnSelchangeList1();
	CButton buttonUp;
	CButton buttonDown;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
};
