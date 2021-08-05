// ScheduledClassEditDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ScheduledClassEditDlg.h"
#include "afxdialogex.h"

#include "Utility.h"
#include "CombinedScheduleClassDlg.h"
#include <vector>


// ScheduledClassEditDlg dialog

IMPLEMENT_DYNAMIC(ScheduledClassEditDlg, CDialog)

ScheduledClassEditDlg::ScheduledClassEditDlg(const CSchedule& m_schedule)
	: CDialog(IDD_EDIT_SCHEDULE, nullptr)
	, m_subjectStore(_T("Subjects"), &databaseConnection)
	, m_scheduledClassStore(_T("Schedule"), &databaseConnection)
	, m_scheduleStore( _T("Schedule"), &databaseConnection)
	, m_schedule(m_schedule)
{
}

ScheduledClassEditDlg::~ScheduledClassEditDlg()
{
}

void ScheduledClassEditDlg::PrintClassesOfDay(int day)
{
	m_classesInDayList.ResetContent();
	for (const auto& scheduledClass : m_schedule.days[day].classes)
	{
		int index = m_classesInDayList.AddString(m_subjectNames[scheduledClass.nSubjectID]);
		m_classesInDayList.SetItemData(index, scheduledClass.nID);
	}
}

void ScheduledClassEditDlg::MoveScheduledClass(int id, int up, int tomorrow)
{
	unsigned int daysInWeek = m_schedule.days.size();
	unsigned int dayLength = 0;
	unsigned int day, indexInDay = 0;

	bool found = false;

	for (day = 0; day < daysInWeek; day++)
	{
		dayLength = m_schedule.days[day].classes.size();

		for (indexInDay = 0; indexInDay < dayLength; indexInDay++)
		{
			if (m_schedule.days[day].classes[indexInDay].nID == id)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	if (up > 0)
	{
		ASSERT(indexInDay > 0);

		std::swap(m_schedule.days[day].classes[indexInDay].nID, m_schedule.days[day].classes[indexInDay - 1].nID);
		std::swap(m_schedule.days[day].classes[indexInDay].nSubjectID, m_schedule.days[day].classes[indexInDay - 1].nSubjectID);
	}
	else if (up < 0)
	{
		ASSERT(indexInDay < dayLength - 1);

		std::swap(m_schedule.days[day].classes[indexInDay].nID, m_schedule.days[day].classes[indexInDay + 1].nID);
		std::swap(m_schedule.days[day].classes[indexInDay].nSubjectID, m_schedule.days[day].classes[indexInDay + 1].nSubjectID);
	}

	if (tomorrow > 0)
	{
		ASSERT(day > 0);

		std::swap(m_schedule.days[day].classes[indexInDay].nID, m_schedule.days[day - 1].classes[indexInDay].nID);
		std::swap(m_schedule.days[day].classes[indexInDay].nSubjectID, m_schedule.days[day - 1].classes[indexInDay].nSubjectID);
	}
	else if (tomorrow < 0)
	{
		ASSERT(day < daysInWeek - 1);

		std::swap(m_schedule.days[day].classes[indexInDay].nID, m_schedule.days[day + 1].classes[indexInDay].nID);
		std::swap(m_schedule.days[day].classes[indexInDay].nSubjectID, m_schedule.days[day + 1].classes[indexInDay].nSubjectID);
	}
}

BOOL ScheduledClassEditDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	CString className;
	isOK = IDtoNameMapper(&databaseConnection, CString{ "Classes" }, CString{ "ID" }, CString{ "Name" },  m_schedule.classID , className);

	m_currentClassEdit.SetWindowText(className);


	std::set<int> uniqueIDs;

	// Print days of week
	unsigned int daysInWeek = m_schedule.days.size();
	CString text;
	for (size_t i = 0; i < daysInWeek; i++)
	{
		text.Format(_T("Day %d"), i + 1);
		int index = m_daysOfWeekList.AddString(text);
		m_daysOfWeekList.SetItemData(index, i);

		for (const auto& _class : m_schedule.days[i].classes)
		{
			uniqueIDs.insert(_class.nSubjectID);
		}
	}

	// Map subject names
	std::vector<int> ids(uniqueIDs.begin(), uniqueIDs.end());
	isOK = IDtoNameMapper(&databaseConnection, CString{ "Subjects" }, CString{ "ID" }, CString{ "Name" }, ids, m_subjectNames);

	// Select first day
	m_daysOfWeekList.SetCurSel(daysInWeek > 0 ? 0 : CB_ERR);

	// Print classes for the day
	if (m_daysOfWeekList.GetCurSel() != CB_ERR)
	{
		PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
	}

	return isOK;
}

void ScheduledClassEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_daysOfWeekList);
	DDX_Control(pDX, IDC_LIST1, m_classesInDayList);
	DDX_Control(pDX, IDC_EDIT1, m_currentClassEdit);
	DDX_Control(pDX, IDC_BUTTON2, m_buttonUp);
	DDX_Control(pDX, IDC_BUTTON3, m_buttonDown);
}


BEGIN_MESSAGE_MAP(ScheduledClassEditDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ScheduledClassEditDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &ScheduledClassEditDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON3, &ScheduledClassEditDlg::OnBnClickedButtonDown)
	ON_LBN_SELCHANGE(IDC_LIST1, &ScheduledClassEditDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &ScheduledClassEditDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &ScheduledClassEditDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &ScheduledClassEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ScheduledClassEditDlg message handlers


void ScheduledClassEditDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
}


void ScheduledClassEditDlg::OnBnClickedButtonUp()
{
	// TODO: Add your control notification handler code here
	int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCurSel());
	MoveScheduledClass(id, 1, 0);
	PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
	m_classesInDayList.SetCurSel(GetIndexByData(id,m_classesInDayList));
	OnLbnSelchangeList1();
}


void ScheduledClassEditDlg::OnBnClickedButtonDown()
{
	// TODO: Add your control notification handler code here
	int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCurSel());
	MoveScheduledClass(id, -1, 0);
	PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
	m_classesInDayList.SetCurSel(GetIndexByData(id, m_classesInDayList));
	OnLbnSelchangeList1();
}


void ScheduledClassEditDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	if (m_classesInDayList.GetCurSel() <= 0)
	{
		m_buttonUp.EnableWindow(FALSE);
	}
	else
	{
		m_buttonUp.EnableWindow(TRUE);
	}

	if (m_classesInDayList.GetCurSel() >= m_classesInDayList.GetCount() - 1)
	{
		m_buttonDown.EnableWindow(FALSE);
	}
	else
	{
		m_buttonDown.EnableWindow(TRUE);
	}

}


void ScheduledClassEditDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int day = m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel());
	int classesinDayCount = m_schedule.days[day].classes.size();
	ScheduleClass tmp;
	if (classesinDayCount > 0)
	{
		tmp.duration = m_schedule.days[day].classes[classesinDayCount - 1].duration;
		tmp.begin.hour += (m_schedule.days[day].classes[classesinDayCount - 1].begin.minute + 40 + 10) / 60;
		tmp.begin.minute += (m_schedule.days[day].classes[classesinDayCount - 1].begin.minute + 40 + 10) % 60;
	}

	CombinedScheduleClassDlg subjectPicker(eDialogMode_Add, tmp);
	subjectPicker.DoModal();

	if (tmp.nSubjectID != -1)
	{
		m_schedule.days[day].classes.push_sorted(tmp);
		tmp.classID = m_schedule.classID;
		tmp.dayOfWeek = day;
		m_toAdd.push_back(tmp);
		PrintClassesOfDay(day);
	}

}


void ScheduledClassEditDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	SUBJECT subject;
	int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCurSel());
	
	unsigned int daysInWeek = m_schedule.days.size();
	unsigned int dayLength = 0;
	unsigned int day, indexInDay = 0;
	bool found = false;;

	for (day = 0; day < daysInWeek; day++)
	{
		dayLength = m_schedule.days[day].classes.size();

		for (indexInDay = 0; indexInDay < dayLength; indexInDay++)
		{
			if (m_schedule.days[day].classes[indexInDay].nID == id)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	ScheduleClass tmp;
	m_scheduledClassStore.Load(m_schedule.days[day].classes[indexInDay].nID,tmp);

	CombinedScheduleClassDlg subjectPicker(eDialogMode_Remove, tmp);
	subjectPicker.DoModal();

	if (tmp.nSubjectID != -1)
	{
		m_toDelete.push_back(m_schedule.days[day].classes[indexInDay]);

		m_schedule.days[day].classes.erase(m_schedule.days[day].classes.begin() + indexInDay);
		PrintClassesOfDay(day);
	}
}


void ScheduledClassEditDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	for (auto& scheduledClass : m_toAdd)
	{
		ASSERT(scheduledClass.nSubjectID != -1);

		m_scheduledClassStore.Add(scheduledClass);
	}
	m_scheduleStore.Edit(m_schedule);
	for (const auto& scheduledClass : m_toDelete)
	{
		if (scheduledClass.nID != -1)
		{
			m_scheduledClassStore.Delete(scheduledClass.nID);
		}
	}
	CDialog::OnOK();
}
