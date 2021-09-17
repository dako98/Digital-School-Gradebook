#pragma once

#include <unordered_map>

enum Direction
{
	Up,
	Down
};

// ScheduledClassEditDlg dialog

class ScheduledClassEditDlg : public CDialog
{
	DECLARE_DYNAMIC(ScheduledClassEditDlg)

public:
	ScheduledClassEditDlg(const int classID, const int daysInWeek);   // standard constructor
	virtual ~ScheduledClassEditDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_SCHEDULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	BOOL PrintClassesOfDay(int day);
	BOOL MoveScheduledClass(int id, Direction direction);

	const int m_classID;
	const int m_daysInWeek;

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
